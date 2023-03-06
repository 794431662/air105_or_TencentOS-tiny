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

#include "max7219.h"


void MAX7219_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	SYSCTRL_APBPeriphClockCmd(SYSCTRL_APBPeriph_GPIO, ENABLE);

	GPIO_InitStruct.GPIO_Pin = MAX7219_CS_PIN;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Remap = GPIO_Remap_1;
	GPIO_Init(MAX7219_CS_PORT, &GPIO_InitStruct);
}

void MAX7219_SPI_Init(void)
{
	SPI_InitTypeDef SPI_InitStructure;

	SYSCTRL_APBPeriphClockCmd(SYSCTRL_APBPeriph_GPIO | SYSCTRL_APBPeriph_SPI0, ENABLE);
	SYSCTRL_APBPeriphResetCmd(SYSCTRL_APBPeriph_SPI0, ENABLE);

	//SPI0
	GPIO_PinRemapConfig(MAX7219_SPIx_PORT, MAX7219_SPIx_PINS, MAX7219_SPIx_REMAP);

	SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_NSS = SPI_NSS_0;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    SPI_InitStructure.SPI_RXFIFOFullThreshold = SPI_RXFIFOFullThreshold_1;
	SPI_InitStructure.SPI_TXFIFOEmptyThreshold = SPI_TXFIFOEmptyThreshold_10;

	SPI_Init(MAX7219_SPIx, &SPI_InitStructure);
	SPI_Cmd(MAX7219_SPIx, ENABLE);
}

void MAX7219_Init(void)
{
    MAX7219_Write(SHUT_DOWN,    0x01);      // 0x00:shutdown, 0x01:normal
    MAX7219_Write(DECODE_MODE,  0x00);      // Bypass code B decoder, no-decode operation
    MAX7219_Write(SCAN_LIMIT,   0x07);      // Scan-limit, 0:1-digit, 1:2-digits, ... 7:8-digits
    MAX7219_Write(INTENSITY,    0x01);      // 0x00:min, 0xFF:max
    MAX7219_Write(DISPLAY_TEST, 0x00);      // 0x00:normal, 0x01:test mode
}

void MAX7219_ChipSelect(int state)
{
	if (state)
	{
		GPIO_SetBits(MAX7219_CS_PORT, MAX7219_CS_PIN);
	}
	else
	{
		GPIO_ResetBits(MAX7219_CS_PORT, MAX7219_CS_PIN);
	}
}

uint8_t MAX7219_SendByte(uint8_t byte)
{
	uint8_t data;
	SPI_SendData(MAX7219_SPIx, byte);
	while (RESET == SPI_GetFlagStatus(MAX7219_SPIx, SPI_FLAG_RXNE));
	data = SPI_ReceiveData(MAX7219_SPIx);
	return data;
}

void MAX7219_Write(uint8_t addr, uint8_t dat)
{
    MAX7219_ChipSelect(0);
    MAX7219_SendByte(addr);
    MAX7219_SendByte(dat);
    MAX7219_ChipSelect(1);
}
