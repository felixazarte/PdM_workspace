
/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "API_uart.h"

/* UART handler declaration */
//Se le coloca static para encapsulamiento
static UART_HandleTypeDef UartHandle;


/* Inicializa la uart, devuelve un true si fue exitoso o un false si hubo un error */
bool_t uartInit()
{
	/*##-1- Configure the UART peripheral ######################################*/
	/* Put the USART peripheral in the Asynchronous mode (UART Mode) */
	/* UART configured as follows:
	 - Word Length = 8 Bits (7 data bit + 1 parity bit) :
	 BE CAREFUL : Program 7 data bits + 1 parity bit in PC HyperTerminal
	 - Stop Bit    = One Stop bit
	 - Parity      = ODD parity
	 - BaudRate    = 9600 baud
	 - Hardware flow control disabled (RTS and CTS signals) */
	UartHandle.Instance          = USARTx;

	UartHandle.Init.BaudRate     = 9600;
	UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
	UartHandle.Init.StopBits     = UART_STOPBITS_1;
	UartHandle.Init.Parity       = UART_PARITY_NONE;
	UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
	UartHandle.Init.Mode         = UART_MODE_TX_RX;
	UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;

	if (HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		/* Initialization Error */
		return false;
	}
	printf(	"\n\r UART configuracion:"
			"\n\r Baud Rate     = 9600 baud"
			"\n\r Word Length   = 8 Bits (7 data bit + 1 parity bit)"
			"\n\r Stop Bit      = one Stop bit"
			"\n\r Parity        = no parity"
			"\n\r HwFlowCtl     = none"
			"\n\r Modo          = tx / rx"
			"\n\r Over Sampling = oversampling 16 \n\r");

	return true;
}

/* Envia un string o cadena de caracteres por la uart, hasta encontrar \0 */
void uartSendString(uint8_t *pstring)
{
	do {
		HAL_UART_Transmit(&UartHandle, pstring, 1, 0xFFFF);
		pstring++;
	} while (*pstring != '\0');
}
/* Envia un string o cadena de caracteres por la uart, de longitud size = tamaño del array */
void uartSendStringSize(uint8_t *pstring, uint16_t size)
{
	HAL_UART_Transmit(&UartHandle, pstring, size, 0xFFFF);
}
/* Recibe un string o cadena de caracteres por la uart, de longitud size = tamaño del array */
void uartReceiveStringSize(uint8_t *pstring, uint16_t size)
{
	HAL_UART_Receive(&UartHandle, pstring, size, 0xFFFF);
}

PUTCHAR_PROTOTYPE
{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART3 and Loop until the end of transmission */
	HAL_UART_Transmit(&UartHandle, (uint8_t*) &ch, 1, 0xFFFF);

	return ch;
}
