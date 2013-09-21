/*
 * Bus.cpp
 *
 *  Created on: Sep 18, 2013
 *      Author: ant
 */

#include "Bus.h"

#include <node_object_wrap.h>
#include <v8.h>
#include <sys/fcntl.h>
#include "i2c-dev.h"
#include <sys/ioctl.h>

using namespace v8;

Persistent<Function> Bus::constructor;

Bus::Bus(Handle<Value> data) {
	this->addr = data->Int32Value();
	char filename[20];

	snprintf(filename, 19, "/dev/i2c-%d", this->addr);
	file = open(filename, O_RDWR);
	if (file < 0) {
		printf("Error open bus!\n ");
		/* ERROR HANDLING; you can check errno to see what went wrong */
	}

	printf("New Bus is created with addr = %d, file= %d\n", this->addr,
			this->file);
}

Bus::~Bus() {
	printf("bus is deleted with addr = %d\n", this->addr);
}

void Bus::Init() {
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("i2cbus"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->PrototypeTemplate()->Set(String::NewSymbol("readByte"),
			FunctionTemplate::New(Method<&Bus::ReadByte>)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("writeByte"),
			FunctionTemplate::New(Method<&Bus::WriteByte>)->GetFunction());
	tpl->PrototypeTemplate()->Set(String::NewSymbol("setAddress"),
			FunctionTemplate::New(Method<&Bus::SetAddress>)->GetFunction());

	constructor = Persistent<Function>::New(tpl->GetFunction());
}

Handle<Value> Bus::New(const Arguments& args) {
	HandleScope scope;

	Bus* bus = new Bus(args[0]);
	bus->Wrap(args.This());

	return args.This();
}

Handle<Value> Bus::NewInstance(const v8::Arguments& args) {
	HandleScope scope;

	const unsigned argc = 1;
	Handle<Value> argv[argc] = { args[0] };
	return scope.Close(Bus::constructor->NewInstance(argc, argv));
}

int Bus::SetI2CAddress(const int addr) {
	int result = ioctl(this->file, I2C_SLAVE_FORCE, addr);
	printf("Set address: 0x%x, result: %d\n", addr, result);
	return result;
}

Handle<Value> Bus::SetAddress(const Arguments& args) {
	int8_t addr = args[0]->Int32Value();

	int result = this->SetI2CAddress(addr);
	if (result == -1) {
		ThrowException(
				Exception::TypeError(String::New("Failed to set address")));
	}
	return Boolean::New(true);
}

v8::Handle<v8::Value> Bus::ReadByte(const v8::Arguments& args) {
	HandleScope scope;
	__u8 command = args[0]->Int32Value();

	__s32 res = i2c_smbus_read_byte_data(this->file, command);

	return scope.Close(Number::New(res));
}

v8::Handle<v8::Value> Bus::WriteByte(const v8::Arguments& args) {
	HandleScope scope;
	__u8 command = args[0]->Int32Value();
	__u8 data = args[1]->Int32Value();

	__s32 res = i2c_smbus_write_byte_data(this->file, command, data);

	return scope.Close(Number::New(res));
}
