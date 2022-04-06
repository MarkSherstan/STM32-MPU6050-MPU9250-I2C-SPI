/*
 * MPU9250.h
 *
 *  Created on: Apr 2, 2022
 *      Author: MarkSherstan
 */

#ifndef SRC_MPU9250_H_
#define SRC_MPU9250_H_

// Libraries
#include <stdint.h>
#include <math.h>
#include "SPI.h"

// Constants
#define RAD2DEG 57.2957795131

// Defines
#define USER_CTRL 0x6A
#define PWR_MGMT_1 0x6B
#define GYRO_CONFIG 0x1B
#define ACCEL_CONFIG 0x1C
#define ACCEL_XOUT_H 0x3B
#define WHO_AM_I 0x75
#define WHO_AM_I_9250_ANS 0x71

#define READWRITE 0x80
#define CS_SELECT 0
#define CS_DESELECT 1
#define SPI_TIMOUT_MS 1000

// Structs
struct RawData
{
    int16_t ax, ay, az, gx, gy, gz;
};

struct ProcessedData
{
    float ax, ay, az, gx, gy, gz;
};

struct GyroCal
{
    float x, y, z;
};

struct Attitude
{
    float r, p, y;
};

// Full scale ranges
enum gyroscopeFullScaleRange
{
    GFSR_250DPS,
    GFSR_500DPS,
    GFSR_1000DPS,
    GFSR_2000DPS
};

enum accelerometerFullScaleRange
{
    AFSR_2G,
    AFSR_4G,
    AFSR_8G,
    AFSR_16G
};

class MPU9250
{
private:
    // Functions
    void REG_READ(uint8_t addr, uint8_t *pRxData, uint16_t RxSize);
    void REG_WRITE(uint8_t *pAddr, uint8_t *pVal);
    void setGyroFullScaleRange(uint8_t gFSR);
    void setAccFullScaleRange(uint8_t aFSR);
    void toggleCS();

    // Variables
    float aScaleFactor, gScaleFactor;
    SPI_HandleTypeDef* _pSPI;
    GPIO_TypeDef* _pCSport;
    uint8_t _aFSR, _gFSR;
    uint16_t _CSpin;
    float _tau, _dt;
    
    // Structs
    GyroCal gyroCal;

public:
    // Init
    MPU9250(SPI_HandleTypeDef* pSPI, GPIO_TypeDef* pCSport, uint16_t CSpin, uint8_t aFSR, uint8_t gFSR, float tau, float dt);

    // Functions
    void calibrateGyro(uint16_t numCalPoints);
    ProcessedData processData();
    Attitude calcAttitude();
    RawData readRawData();
    uint8_t begin();

    // Structs
    Attitude attitude;
};

#endif /* SRC_MPU9250_H_ */
