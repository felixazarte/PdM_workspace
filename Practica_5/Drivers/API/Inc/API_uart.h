/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __API_UART_H
#define __API_UART_H

#include "stdbool.h"                     /* <- Standar bool library*/
#include "stdint.h"                      /* <- Standard integer library */
#include "stm32f4xx_hal.h"               /* <- HAL include */
#include "stm32f4xx_nucleo_144.h"

/* User can use this section to tailor USARTx/UARTx instance used and associated
   resources */
/* Definition for USARTx clock resources */
#define USARTx                           USART3
#define USARTx_CLK_ENABLE()              __HAL_RCC_USART3_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE()      __HAL_RCC_GPIOD_CLK_ENABLE()

#define USARTx_FORCE_RESET()             __HAL_RCC_USART3_FORCE_RESET()
#define USARTx_RELEASE_RESET()           __HAL_RCC_USART3_RELEASE_RESET()

/* Definition for USARTx Pins */
#define USARTx_TX_PIN                    GPIO_PIN_8
#define USARTx_TX_GPIO_PORT              GPIOD
#define USARTx_TX_AF                     GPIO_AF7_USART3
#define USARTx_RX_PIN                    GPIO_PIN_9
#define USARTx_RX_GPIO_PORT              GPIOD
#define USARTx_RX_AF                     GPIO_AF7_USART3

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

typedef bool bool_t;

/* ################ My function definitions ################ */
/* Inicializa la uart, devuelve un true si fue exitoso o un false si hubo un error */
bool_t uartInit();
/* Envia un string o cadena de caracteres por la uart, hasta encontrar \0 */
void uartSendString(uint8_t *pstring);
/* Envia un string o cadena de caracteres por la uart, de longitud size = tamaño del array */
void uartSendStringSize(uint8_t *pstring, uint16_t size);
/* Recibe un string o cadena de caracteres por la uart, de longitud size = tamaño del array */
void uartReceiveStringSize(uint8_t * pstring, uint16_t size); //recibe una cadena de longitud size y lo guarda en pstring

#endif /* __API_UART_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
