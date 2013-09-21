var __MODE1              = 0x00,
__SUBADR1            = 0x02,
__SUBADR2            = 0x03,
__SUBADR3            = 0x04,
__MODE1              = 0x00,
__PRESCALE           = 0xFE,
__LED0_ON_L          = 0x06,
__LED0_ON_H          = 0x07,
__LED0_OFF_L         = 0x08,
__LED0_OFF_H         = 0x09,
__ALLLED_ON_L        = 0xFA,
__ALLLED_ON_H        = 0xFB,
__ALLLED_OFF_L       = 0xFC,
__ALLLED_OFF_H       = 0xFD;

var addon = require('../build/Release/i2cbridge');
var sleep = require('sleep').sleep;


var bus = addon.open(1);

bus.writeByte(__MODE1, 0x00)


bus.setAddress(0x40);

setPWMFreq(60);
var i=0;

while(i++<3) {
	setPWM(0,0,150);
	sleep(1);
	setPWM(0,0,600);
	sleep(1);
}

setPWM(0,0,0);

/*
 * def setPWMFreq(self, freq): "Sets the PWM frequency" prescaleval = 25000000.0 #
 * 25MHz prescaleval /= 4096.0 # 12-bit prescaleval /= float(freq) prescaleval -=
 * 1.0 if (self.debug): print "Setting PWM frequency to %d Hz" % freq print
 * "Estimated pre-scale: %d" % prescaleval prescale = math.floor(prescaleval +
 * 0.5) if (self.debug): print "Final pre-scale: %d" % prescale
 * 
 * oldmode = self.i2c.readU8(self.__MODE1); newmode = (oldmode & 0x7F) | 0x10 #
 * sleep self.i2c.write8(self.__MODE1, newmode) # go to sleep
 * self.i2c.write8(self.__PRESCALE, int(math.floor(prescale)))
 * self.i2c.write8(self.__MODE1, oldmode) time.sleep(0.005)
 * self.i2c.write8(self.__MODE1, oldmode | 0x80)
 */



function setPWMFreq(freq) {
	console.log("Setting PWM frequency to "+ freq +" Hz");
	
	var prescaleval = 25000000.0;    // 25MHz
    prescaleval /= 4096.0;       // 12-bit
    prescaleval /= freq;
    prescaleval -= 1.0;
	
    var prescale = Math.floor(prescaleval + 0.5);
    var oldmode = bus.readByte(__MODE1);
    console.log('mode read:', oldmode);

    var newmode = (oldmode & 0x7F) | 0x10             // sleep
    console.log(bus.writeByte(__MODE1, newmode))        // go to sleep
    console.log(bus.writeByte(__PRESCALE, Math.floor(prescale)))
    console.log(bus.writeByte(__MODE1, oldmode))
    sleep(0.005)
    console.log(bus.writeByte(__MODE1, oldmode | 0x80))    
}

/*
 * def setPWM(self, channel, on, off): "Sets a single PWM channel"
 * self.i2c.write8(self.__LED0_ON_L+4*channel, on & 0xFF)
 * self.i2c.write8(self.__LED0_ON_H+4*channel, on >> 8)
 * self.i2c.write8(self.__LED0_OFF_L+4*channel, off & 0xFF)
 * self.i2c.write8(self.__LED0_OFF_H+4*channel, off >> 8)
 */

function setPWM(channel, on, off) {
	console.log('Setting pwm for channel '+channel+' on:'+on+' off:'+off);
	console.log( on & 0xFF,  on >>8,  off & 0xFF, off>>8);
    console.log(bus.writeByte(__LED0_ON_L+4*channel, on & 0xFF))
    console.log(bus.writeByte(__LED0_ON_H+4*channel, on >> 8))
    console.log(bus.writeByte(__LED0_OFF_L+4*channel, off & 0xFF))
    console.log(bus.writeByte(__LED0_OFF_H+4*channel, off >> 8))
}