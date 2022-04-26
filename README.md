# STM32-MPU6050-MPU9250-I2C-SPI

Using the [Sparkfun 9250 breakout](https://www.sparkfun.com/products/retired/13762?_ga=2.119791887.628539036.1650944818-860039329.1650581197)


# Pinout
Refer to the diagrams located [here](https://os.mbed.com/platforms/ST-Nucleo-F401RE/)


# SPI
| MPU9250  	| STM32F401RE 	| Breakout board Comment       	|
|----------	|-------------	|------------------------------	|
| VDD      	| 3V3         	|                              	|
| VDDIO    	| 3V3         	| Shorted to VDD on PCB        	|
| GND      	| GND         	|                              	|
| AD0/SDO  	| PB4 (MISO)  	| Adjust default solder jumper 	|
| SDA/SDI  	| PB5 (MOSI)  	|                              	|
| SCL/SCLK 	| PB3 (SCK)   	|                              	|
| nCS      	| PB6         	| Chip select enable = Low     	|

# I2C


## To Do 
- Delete launch files?