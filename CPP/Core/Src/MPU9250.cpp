/*
 * MPU9250.cpp
 *
 *  Created on: Apr 2, 2022
 *      Author: MarkSherstan
 */

#include "MPU9250.h"

MPU9250::MPU9250(SPI_HandleTypeDef *pSPI, uint8_t aFSR, uint8_t gFSR)
{
    _pSPI = pSPI;
    _aFSR = aFSR;
    _gFSR = gFSR;
}


uint8_t MPU9250::begin()
{
    return 0;
}