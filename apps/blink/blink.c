/*
 * Simple blink program for the Nucleo F446 board.
 * 
 * User LED is on GPIO port A, pin 5.
 *
 * Copyright (C) 2018 Charles McManis
 * Contributed to the public domain July 2018.
 *
 */
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

int
main(void)
{
	/* enable GPIOA clock */
	rcc_periph_clock_enable(RCC_GPIOA);
	/* Setup the LED pin as an output pin */
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
	/* turn it on */
	gpio_set(GPIOA, GPIO5);
	while (1) {
		/* toggle the LED */
		gpio_toggle(GPIOA, GPIO5);
		/* delay by doing nothing for a while */
		for (int i = 0; i < 500000; i++) {
			/* don't let the compiler optimize this out */
			__asm__("nop");
		}
	}
}
