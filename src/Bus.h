/*
 * Bus.h
 *
 *  Created on: Sep 18, 2013
 *      Author: ant
 */
#ifndef BUS_H_
#define BUS_H_

#include <node_object_wrap.h>
#include <node.h>

class Bus: public node::ObjectWrap {

public:
	static void Init();
	static v8::Handle<v8::Value> NewInstance(const v8::Arguments& args);

private:
	Bus(v8::Handle<v8::Value>);
	~Bus();

	int addr;
	int file;

	typedef v8::Handle<v8::Value> (Bus::*WrappedMethod)(
			const v8::Arguments& args);

	template<WrappedMethod m>
	static v8::Handle<v8::Value> Method(const v8::Arguments& args) {
		Bus* obj = ObjectWrap::Unwrap<Bus>(args.This());
		return (obj->*m)(args);
	}

	static v8::Persistent<v8::Function> constructor;
	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	int SetI2CAddress(const int);


	//JS API
	v8::Handle<v8::Value> SetAddress(const v8::Arguments& args);
	v8::Handle<v8::Value> ReadByte(const v8::Arguments& args);
	v8::Handle<v8::Value> WriteByte(const v8::Arguments& args);
};

#endif /* BUS_H_ */
