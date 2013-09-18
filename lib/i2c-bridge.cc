/*
 * i2c-bridge.cc
 *
 *  Created on: Sep 18, 2013
 *      Author: ant
 */


#include <node.h>
#include <v8.h>
#include <linux/i2c-dev.h>
#include <unistd.h>


using namespace v8;

Handle<Value> scan(const Arguments& args) {
  HandleScope scope;

  Local<Function> cb = Local<Function>::Cast(args[0]);
  sleep(3);
  const unsigned argc =1;
  Local<Value> argv[argc] = {Local<Value>::New(String::New("scan result"))};
  cb->Call(Context::GetCurrent()->Global(), argc, argv);

  return scope.Close(String::New("world"));
}

void init(Handle<Object> exports) {
  exports->Set(String::NewSymbol("scan"),
      FunctionTemplate::New(scan)->GetFunction());
}

NODE_MODULE(i2cbridge, init)



