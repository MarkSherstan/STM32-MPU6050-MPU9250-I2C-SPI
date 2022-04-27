# STM32-MPU6050-MPU9250-I2C-SPI
Based on my original [library](https://github.com/MarkSherstan/MPU-6050-9250-I2C-CompFilter), the algorithms and IC communication has been ported for STM32 chips using HAL drivers. 

Example code uses the [Sparkfun 9250 breakout](https://www.sparkfun.com/products/retired/13762?_ga=2.119791887.628539036.1650944818-860039329.1650581197) and [Nucleo-F401RE dev board](https://www.st.com/en/evaluation-tools/nucleo-f401re.html).

There are four options available.
* I2C using CPP
* I2C using C
* SPI using CPP (MPU9250 only)
* SPI using C (MPU9250 only)

The four examples are fundamentally the same with minor differences such as the use of data structures, printing methods, etc...

# Pinout
Refer to the `.ioc` file and the pinout diagrams located [here](https://os.mbed.com/platforms/ST-Nucleo-F401RE/).

## SPI
| MPU9250  	| STM32F401RE 	| Breakout board comment       	|
|----------	|-------------	|------------------------------	|
| VDD      	| 3V3         	|                              	|
| VDDIO    	| 3V3         	| Shorted to VDD on PCB        	|
| GND      	| GND         	|                              	|
| AD0/SDO  	| PB4 (MISO)  	| Adjust default solder jumper 	|
| SDA/SDI  	| PB5 (MOSI)  	|                              	|
| SCL/SCLK 	| PB3 (SCK)   	|                              	|
| nCS      	| PB6         	| Chip select enable = Low     	|

## I2C
| MPU9250  	| STM32F401RE 	| Breakout board comment       	        |
|----------	|-------------	|-------------------------------------- |
| VDD      	| 3V3         	|                              	        |
| GND      	| GND         	|                              	        |
| SDA      	| PB9 (SDA)     | 10 kohm pull-up limit freq to 100 KHz |
| SCL      	| PB8 (SCL)     | 10 kohm pull-up limit freq to 100 KHz |
