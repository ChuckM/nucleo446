/*
 * Clock functions
 *
 * Copyright (C) 2018, Charles McManis
 * Contributed to the Public Domain, July 2018
 */

#pragma once

/* Set up the PLL clock to run at 168 Mhz */
void clock_setup(void);

/* Wait for 'ms' milleseconds to be counted by systick */
void msleep(uint32_t ms);
