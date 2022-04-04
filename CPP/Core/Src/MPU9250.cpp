/*
 * MPU9250.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: MarkSherstan
 */

#include "MPU9250.h"

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
    MPU9250::toggleCS();
    return 0;
}


/// @brief Toggle CS state to either start or end transmissions (default = high)
void toggleCS()
{
    HAL_GPIO_TogglePin(_pCSport, _CSpin);
}
