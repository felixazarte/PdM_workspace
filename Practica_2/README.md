Práctica 2

Objetivo:
Implementar un módulo de software para trabajar con retardos no bloqueantes. 

Punto 1
Implementar las funciones auxiliares necesarias para usar retardos no bloqueantes en un archivo fuente main.c con su correspondiente archivo de cabecera main.h.
En main.h se deben ubicar los prototipos de las siguientes funciones y las declaraciones
typedef uint32_t tick_t; // Qué biblioteca se debe incluir para que esto compile?
typedef bool bool_t;   // Qué biblioteca se debe incluir para que esto compile?
typedef struct{
   tick_t startTime;
   tick_t duration;
   bool_t running;
} delay_t;
void delayInit( delay_t * delay, tick_t duration );
bool_t delayRead( delay_t * delay );
void delayWrite( delay_t * delay, tick_t duration );

En main.c se deben ubicar la implementación de todas las funciones:
Consideraciones para la implementación:
    1. delayInit debe cargar el valor de duración del retardo en la estructura, en el campo correspondiente. No debe iniciar el conteo del retardo. Debe inicializar el flag running en `false´.
    2. delayRead debe verificar el estado del flag running.
        ◦ false, tomar marca de tiempo y cambiar running a ‘true’ 
        ◦ true, hacer la cuenta para saber si el tiempo del retardo se cumplió o no:

‘marca de tiempo actual - marca de tiempo inicial es mayor o igual a duración del retardo’?

y devolver un valor booleano que indique si el tiempo se cumplió o no.
        ◦ Cuando el tiempo se cumple se debe cambiar el flag running a false.
    3. delayWrite debe permitir cambiar el tiempo de duración de un delay existente

NOTA: para obtener una marca de tiempo se puede usar la función HAL_GetTick() que devuelve un valor que se incrementa cada 1 ms y que se puede usar como base de tiempo.

Punto 2
Implementar un programa que utilice retardos no bloqueantes y  haga titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F429ZI de la siguiente manera:
    • LED1: 100 ms. 
    • LED2: 500 ms.
    • LED3: 1000 ms.

