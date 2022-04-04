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