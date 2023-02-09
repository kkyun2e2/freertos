/*
 * uart.c
 *
 *  Created on: Feb 3, 2023
 *      Author: NPEDU001
 */

#include "uart.h"
#include <stdio.h>;

extern UART_HandleTypeDef huart1;

#define rxBufferMax 255 // 8비트 최대 데이터
int rxBufferGp;  // 링버퍼 쓰기 변수 <- 읽어오는 값
int rxBufferPp;  // 링버퍼 읽기 변수 <- 읽어오는 값
uint8_t rxBuffer[rxBufferMax]; //링 버퍼 배열
uint8_t rxChar; // 읽어오는 값

void initUart() // uart 초기 리셋 함수
{
	HAL_UART_Receive_IT(&huart1, &rxChar, 1); // uart 읽어오는거 on/off
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) // uart 인터럽트 후 읽기
{
	rxBuffer[rxBufferPp++]=rxChar; // 읽기 변수에 읽어오는 값 저장
	rxBufferPp %= rxBufferMax; // 최대 255
	HAL_UART_Receive_IT(&huart1, &rxChar, 1); // 인터럽트하면 다시 리시브로 활성화 시켜야함
}

uint8_t getChar() //scanf 역할 함수
{
	uint8_t result; // 반환 값
	if(rxBufferGp==rxBufferPp) return 0; // 만약 쓰기전에 읽을때 0 반환
	result = rxBuffer[rxBufferGp++]; // 쓰기변수에 읽어온 값 저장
	rxBufferGp %= 255; // 최대값 255
	return result; // 쓰기 변수속 값 반환
}

int _write(int file,char *p, int len)
{
	HAL_UART_Transmit(&huart1, p, len, 1);
	return len;
}
