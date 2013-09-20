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

	static v8::Persistent<v8::Function> constructor;
	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> Scan(const v8::Arguments& args);
};

#endif /* BUS_H_ */
