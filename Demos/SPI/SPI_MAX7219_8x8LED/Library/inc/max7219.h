// Copyright 2022 IOsetting <iosetting(at)outlook.com>
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef __MAX7219_H
#define	__MAX7219_H

#ifdef __cplusplus
extern "C"
{
#endif 

#include "air105.h"
#include "stdint.h"

#define MAX7219_SPIx        SPIM0
#define MAX7219_CS_PORT     GPIOC
#define MAX7219_CS_PIN      GPIO_Pin_13

#define MAX7219_SPIx_PORT   GPIOC
#define MAX7219_SPIx_PINS   GPIO_Pin_12|GPIO_Pin_14|GPIO_Pin_15
#define MAX7219_SPIx_REMAP  GPIO_Remap_2


#define DECODE_MODE  0x09
#define INTENSITY    0x0A
#define SCAN_LIMIT   0x0B
#define SHUT_DOWN    0x0C
#define DISPLAY_TEST 0x0F

void MAX7219_GPIO_Init(void);
void MAX7219_SPI_Init(void);
void MAX7219_Init(void);
void MAX7219_Write(uint8_t addr, uint8_t dat);

#ifdef __cplusplus
}
#endif

#endif   ///< __MAX7219_H
