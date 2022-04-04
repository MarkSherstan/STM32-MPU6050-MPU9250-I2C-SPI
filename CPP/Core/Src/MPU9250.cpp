/*
 * MPU9250.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: MarkSherstan
 */

#include "MPU9250.h"

/// @brief MPU9250 SPI constructor
/// @param pSPI Pointer to SPI structure config
/// @param pCSport Pointer to GPIO CS port
/// @param CSpin GPIO pin number of CS pin
/// @param aFSR Accelerometer full scale range 
/// @param gFSR Gyroscope full scale range
MPU9250::MPU9250(SPI_HandleTypeDef* pSPI, GPIO_TypeDef* pCSport, uint16_t CSpin, uint8_t aFSR, uint8_t gFSR)
{
    _pSPI = pSPI;
    _aFSR = aFSR;
    _gFSR = gFSR;
    _pCSport = pCSport;
    _CSpin = CSpin;
}

uint8_t MPU9250::begin()
{
    setGyroFullScaleRange(_gFSR);
    setAccFullScaleRange(_aFSR);
    return 0;
}

/// @brief Toggle CS state to either start or end transmissions (default = high)
void MPU9250::toggleCS()
{
    HAL_GPIO_TogglePin(_pCSport, _CSpin);
}

/// @brief Read a specific registry address
/// @param pAddr Pointer to address to be written to
/// @param pVal Pointer of value to write at given address
void MPU9250::REG_WRITE(uint8_t *pAddr, uint8_t *pVal)
{
    toggleCS();
    HAL_SPI_Transmit(_pSPI, pAddr, 1, SPI_TIMOUT_MS);
    HAL_SPI_Transmit(_pSPI, pVal, 1, SPI_TIMOUT_MS);
    toggleCS();
}

/// @brief Read a specific registry address
/// @param addr Address to start reading at
/// @param pRxData Pointer to data buffer
/// @param RxSize Size of data buffer
void MPU9250::REG_READ(uint8_t addr, uint8_t *pRxData, uint16_t RxSize)
{
    toggleCS();
    uint8_t writeAddr = addr | READWRITE;
    HAL_SPI_Transmit(_pSPI, &writeAddr, 1, SPI_TIMOUT_MS);
    HAL_SPI_Receive(_pSPI, pRxData, RxSize, SPI_TIMOUT_MS);
    toggleCS();
}

/// @brief Set the gyroscope full scale range
/// @param gFSR Set 0 for ±250°/s, 1 for ±500°/s, 2 for ±1000°/s, and 3 for ±2000°/s
void MPU9250::setGyroFullScaleRange(uint8_t gScale)
{
    // Variable init
    uint8_t addr = GYRO_CONFIG;
    uint8_t val;

    // Set the value
    switch (gScale)
    {
    case GFSR_250DPS:
        gScaleFactor = 131.0;
        val = 0x00;
        REG_WRITE(&addr, &val);
        break;
    case GFSR_500DPS:
        gScaleFactor = 65.5;
        val = 0x08;
        REG_WRITE(&addr, &val);
        break;
    case GFSR_1000DPS:
        gScaleFactor = 32.8;
        val = 0x10;
        REG_WRITE(&addr, &val);
        break;
    case GFSR_2000DPS:
        gScaleFactor = 16.4;
        val = 0x18;
        REG_WRITE(&addr, &val);
        break;
    default:
        gScaleFactor = 65.5;
        val = 0x08;
        REG_WRITE(&addr, &val);
        break;
    }
}

/// @brief Set the accelerometer full scale range
/// @param aFSR Set 0 for ±2g, 1 for ±4g, 2 for ±8g, and 3 for ±16g
void MPU9250::setAccFullScaleRange(uint8_t aScale)
{
    // Variable init
    uint8_t addr = ACCEL_CONFIG;
    uint8_t val;

    // Set the value
    switch (aScale)
    {
    case AFSR_2G:
        aScaleFactor = 16384.0;
        val = 0x00;
        REG_WRITE(&addr, &val);
        break;
    case AFSR_4G:
        aScaleFactor = 8192.0;
        val = 0x08;
        REG_WRITE(&addr, &val);
        break;
    case AFSR_8G:
        aScaleFactor = 4096.0;
        val = 0x10;
        REG_WRITE(&addr, &val);
        break;
    case AFSR_16G:
        aScaleFactor = 2048.0;
        val = 0x18;
        REG_WRITE(&addr, &val);
        break;
    default:
        aScaleFactor = 8192.0;
        val = 0x08;
        REG_WRITE(&addr, &val);
        break;
    }
}