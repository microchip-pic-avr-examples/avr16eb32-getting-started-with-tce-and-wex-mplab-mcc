/* Calculated values for Period, CMP, Amplitude and OFFSET registers */
#define TCE_PERIOD                      (0xFA0)
#define DUTY_CYCLE_20_PERCENT           (0x1999)
#define DUTY_CYCLE_40_PERCENT           (0x3333)
#define DUTY_CYCLE_60_PERCENT           (0x4CCC)
#define DUTY_CYCLE_80_PERCENT           (0x660C)
#define AMPLITUDE_MAX_DCY_50_PERCENT    (0x4000)
#define AMPLITUDE_MAX_DCY_75_PERCENT    (0x6000)
#define AMPLITUDE_MAX_DCY_100_PERCENT   (0x8000)
#define AMPLITUDE_MAX_DCY_150_PERCENT   (0xC000)
#define TCE_OFFSET                      (0x00)

#include "mcc_generated_files/system/system.h"
#include <util/delay.h>


void Amplitude_Value_Set(uint16_t value)
{
    /* Set the value of amplitude */
    TCE0_AmplitudeSet(value);
    
    /* Rewrite the values in CMPBUF registers so that the duty cycle get scaled according to the new value of amplitude */
    TCE0_CompareAllChannelsBufferedSet(DUTY_CYCLE_20_PERCENT, DUTY_CYCLE_40_PERCENT, DUTY_CYCLE_60_PERCENT, DUTY_CYCLE_80_PERCENT);
    
    /* Toggle PD5 pin to know when the value of amplitude has changed */
    IO_PD5_Toggle();
}

int main(void)
{
    SYSTEM_Initialize();


    while(1)
    {
        Amplitude_Value_Set(AMPLITUDE_MAX_DCY_50_PERCENT);
        _delay_ms(10);
        Amplitude_Value_Set(AMPLITUDE_MAX_DCY_75_PERCENT);
        _delay_ms(10);
        Amplitude_Value_Set(AMPLITUDE_MAX_DCY_100_PERCENT);
        _delay_ms(10);
        Amplitude_Value_Set(AMPLITUDE_MAX_DCY_150_PERCENT);
        _delay_ms(10);
    }    
}