Práctica 1

Objetivo:
Familiarizarse con el entorno de trabajo STM32CubeIDE + NUCLE-F429ZI + firmware. 

Punto 1
Implementar un programa que genere una secuencia periódica con los leds de la placa NUCLEO-F429ZI.

La secuencia debe seguir el orden: LED1, LED2, LED3, LED1,... etc.
Cada led debe permanecer encendido 200 ms. y 200 ms apagado.  No debe encenderse más de un led simultáneamente.

Punto 2
Utilizar el pulsador azul (USER_BUTTON) para controlar cómo se recorre la secuencia de leds.  Cada vez que se presiona el pulsador se debe alternar el orden de la secuencia entre:
    1. LED1, LED2, LED3, LED1,... etc.
    2. LED1, LED3, LED2, LED1,... etc.

