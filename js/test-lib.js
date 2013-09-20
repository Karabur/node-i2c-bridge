var addon = require('../build/Release/i2cbridge');

console.log(addon);
var bus = addon.open(1);
console.log(bus);
console.log(bus.scan());

/*
var bus = addon.open(1);

var list = bus.scan();
bus.setAddr(list[0]);
var byte = bus.read();
bus.write(??);

*/