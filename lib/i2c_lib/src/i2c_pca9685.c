#include <i2c_dev/i2c_pca9685.h>
int PCA9685_init(int id){
	int i2c_dev = i2c_init(id);
	PCA9685_setAllPwm(i2c_dev,0,0);
	write8(i2c_dev,PCA9685_MODE2,PCA9685_OUTDRV);
	write8(i2c_dev,PCA9685_MODE1,PCA9685_ALLCALL);
	return i2c_dev;
}
void PCA9685_start(int i2c_dev){
	uint8_t m = read8(i2c_dev,PCA9685_MODE1);
	m = m & ~PCA9685_SLEEP;
	write8(i2c_dev,PCA9685_MODE1,m);
}
void PCA9685_setPwmFreq(int i2c_dev, float freq){
	uint8_t oldmode = read8(i2c_dev,PCA9685_MODE1);
	freq = floor((((25000000.0/4096.0)/freq)-1)+0.5);
	write8(i2c_dev,PCA9685_MODE1,(oldmode & 0x7F) | 0x10);
	write8(i2c_dev,PCA9685_PRESCALE,floor(freq));
	write8(i2c_dev,PCA9685_MODE1,oldmode);
	int i;
	for(i=0;i<1000;i++){}
	write8(i2c_dev,PCA9685_MODE1,(oldmode|0x80));
	
}
void PCA9685_setPwm(int i2c_dev, int chan, int on, int off){
	write8(i2c_dev,PCA9685_LED0_ON_L+4*chan, (on & 0xFF));
	write8(i2c_dev,PCA9685_LED0_ON_H+4*chan, (on >> 8));
	write8(i2c_dev,PCA9685_LED0_OFF_L+4*chan, (off & 0xFF));
	write8(i2c_dev,PCA9685_LED0_OFF_H+4*chan, (off >> 8));
}
void PCA9685_setAllPwm(int i2c_dev, int on, int off){
	write8(i2c_dev,PCA9685_ALL_LED_ON_L, (on & 0xFF));
	write8(i2c_dev,PCA9685_ALL_LED_ON_H, (on >> 8));
	write8(i2c_dev,PCA9685_ALL_LED_OFF_L, (off & 0xFF));
	write8(i2c_dev,PCA9685_ALL_LED_OFF_H, (off >> 8));
	
}
