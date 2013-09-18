var addon = require('../build/Release/i2cbridge');

console.log(addon);
console.log(addon.open);
console.log(addon.open(0));

/*
var bus = addon.open(1);

var list = bus.scan();
bus.setAddr(list[0]);
var byte = bus.read();
bus.write(??);

*/