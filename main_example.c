
#include <stdio.h>
#include <fbm340_a14n.h>

/* Private variable */
int32_t real_p, real_t, altitude, water_depth;
//float real_p, real_t;
volatile uint32_t TMR0_Ticks = 0; //one tick per millisecond(ms)
volatile uint32_t fbm340_update_rdy = 0;

/**
 * @brief      A timer generate an interrupt every millisecond
 */
void TMR0_IRQHandler(void)
{
	if (TIMER_GetIntFlag(TIMER0) == 1)
	{
		/* Clear Timer0 time-out interrupt flag */
		TIMER_ClearIntFlag(TIMER0);

		TMR0_Ticks++;
	}
}

/*---------------------------------------------------------------------------------------------------------*/
/*  Main Function                                                                                          */
/*---------------------------------------------------------------------------------------------------------*/
int32_t main(void)
{
	/* fbm340 initiation */
	fbm340_init();

	while (1)
	{
		/* Updating fbm340 data */
		fbm340_update_data();
		if (fbm340_update_rdy) {
			/* If you need the pressure value read is in uint of Pa, use this function. */
			// real_p = fbm340_read_pressure();
			/* If you need the temperature value read is in unit of degree Celsius, use this function. */
			// real_t = fbm340_read_temperature();

			/* This function read pressure and temperature values. Pressure uint:Pa, Temperature unit:0.01 degree Celsius */
			fbm340_read_data(&real_p, &real_t);
			/* This function converts pressure value to altitude in unit of millimeter(mm). */
			altitude = fbm340_get_altitude(real_p);
			/* This function converts pressure value to water depth in unit of millimeter(mm). */
			water_depth = fbm340_get_water_depth(real_p);
			fbm340_update_rdy = 0;
		}
	}
}
