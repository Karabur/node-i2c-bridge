var addon = require('../build/Release/i2cbridge');

function callback(params) {
	console.log('callback', params)
}


console.log(addon);
console.log(addon.scan);
console.log(addon.scan(callback));

/*
var bus = addon.open(1);

var list = bus.scan();
bus.setAddr(list[0]);
var byte = bus.read();
bus.write(??);

*/