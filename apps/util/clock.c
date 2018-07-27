/*
 * clock.c 
 *
 * Bare minimum clock functions for the board.
 *
 * Copyright (C) 2018, Charles McManis
 * Contributed to the public domain, July 2018
 */

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/flash.h>
#include <libopencm3/cm3/nvic.h>
#include <libopencm3/cm3/systick.h>
#include "../util/clock.h"

static const struct rcc_clock_scale cs = {
	.pllr = 2,
	.pllm = 4,
	.plln = 180,
	.pllp = 2,
	.power_save = 1,
	.flash_config = FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_LATENCY_5WS,
	.hpre = RCC_CFGR_HPRE_DIV_NONE,
	.ppre1 = RCC_CFGR_PPRE_DIV_4,
	.ppre2 = RCC_CFGR_PPRE_DIV_2,
	.ahb_frequency = 180000000,
	.apb1_frequency = 45000000,
	.apb2_frequency = 90000000
};

static volatile uint32_t __systick_millis;
static volatile uint32_t __systick_delay;
void
sys_tick_handler(void)
{
	++__systick_millis;
	if (__systick_delay > 0) {
		--__systick_delay;
	}
}

/*
 * Set up the clock for 168Mhz and enable
 * the SysTick handler to run every millisecond.
 */
void
clock_setup(void)
{
	rcc_clock_setup_hse_3v3(&cs);

	/* set up the SysTick subsystem */
	systick_set_reload(168000);
	systick_set_clocksource(STK_CSR_CLKSOURCE_AHB);
	systick_counter_enable();
	systick_interrupt_enable();

}

void
msleep(uint32_t ms)
{
	__systick_delay = ms;
	while (__systick_delay > 0) { __asm__("nop"); }
}
