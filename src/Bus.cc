/*
 * Bus.cpp
 *
 *  Created on: Sep 18, 2013
 *      Author: ant
 */

#include "Bus.h"

#include <node_object_wrap.h>
#include <v8.h>

using namespace v8;

Persistent<Function> Bus::constructor;

Bus::Bus(Handle<Value> data) {
	this->addr = data->Int32Value();
}

Bus::~Bus() {

}

void Bus::Init() {
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("i2cbus"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);
	tpl->PrototypeTemplate()->Set(String::NewSymbol("scan"),
			FunctionTemplate::New(Scan)->GetFunction());

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

Handle<Value> Bus::Scan(const v8::Arguments& args) {

	Bus* obj = ObjectWrap::Unwrap<Bus>(args.This());

	return Number::New(obj->addr);
}
