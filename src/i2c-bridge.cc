#include <v8.h>
#include <node.h>
#include "Bus.h"
#include <linux/i2c-dev.h>

using namespace v8;

Handle<Value> open(const Arguments& args) {
	HandleScope scope;

//	Handle<Object> bus = ;

	return scope.Close(Bus::NewInstance(args));
}

void init(Handle<Object> exports) {
	Bus::Init();
	exports->Set(String::NewSymbol("open"), FunctionTemplate::New(open)->GetFunction());
}

NODE_MODULE(i2cbridge, init)

