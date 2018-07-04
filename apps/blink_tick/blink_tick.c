/*
 * A blinker that uses the systick interrupt
 * to be a bit more accurate.
 *
 * Copyright (C) 2018, Charles McManis
 * Contributed to the Public Domain, July 2018 by Charles McManis
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "../util/clock.h"

int
main(void)
{
	/* Call clock setup from the clock code */
	clock_setup();
	/* enable GPIOA clock */
	rcc_periph_clock_enable(RCC_GPIOA);
	/* set up pin 5 of GPIO A as an output */
	gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO5);
	/* Set the logic state to 'high' for GPIO5 */
	gpio_set(GPIOA, GPIO5);
	while (1) {
		/* toggle the state of GPIO5 */
		gpio_toggle(GPIOA, GPIO5);
		/* sleep for 500 milleseconds */
		msleep(500);
	}
}
