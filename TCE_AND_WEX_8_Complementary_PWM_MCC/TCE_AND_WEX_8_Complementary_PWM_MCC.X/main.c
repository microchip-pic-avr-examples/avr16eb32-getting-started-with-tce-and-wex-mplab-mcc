/* Calculated values for TCE's period and the maximum duty cycle */
#define TCE_PERIOD            (0x3E8)
#define MAX_DUTY_CYCLE        (0x3DE)

#include "mcc_generated_files/system/system.h"
#include <util/delay.h>

/* Callback function that is called in the ISR routine */
void UserCallback_CMP0(void)
{
    static uint16_t duty_cycle = 0;

    /* Duty cycle update in interrupt */
    duty_cycle += 5;
    if(duty_cycle >= MAX_DUTY_CYCLE)
      duty_cycle = 0;
    TCE0_PWM_BufferedDutyCycle0Set(duty_cycle);
}

/* Callback function that is called in the ISR routine */
void UserCallback_CMP1(void)
{
    static uint16_t duty_cycle = 0;

    /* Duty cycle update in interrupt */
    duty_cycle += 15;
    if(duty_cycle >= MAX_DUTY_CYCLE)
      duty_cycle = 0;
    TCE0_PWM_BufferedDutyCycle1Set(duty_cycle);
}

/* Callback function that is called in the ISR routine */
void UserCallback_CMP2(void)
{
    static uint16_t duty_cycle = 0;

    /* Duty cycle update in interrupt */
    duty_cycle += 25;
    if(duty_cycle >= MAX_DUTY_CYCLE)
      duty_cycle = 0;
    TCE0_PWM_BufferedDutyCycle2Set(duty_cycle);
}

/* Callback function that is called in the ISR routine */
void UserCallback_CMP3(void)
{
    static uint16_t duty_cycle = 0;

    /* Duty cycle update in interrupt */
    duty_cycle += 35;
    if(duty_cycle >= MAX_DUTY_CYCLE)
      duty_cycle = 0;
    TCE0_PWM_BufferedDutyCycle3Set(duty_cycle);
}

void Create_Fault(void)
{
    /* Fault creation, repeat in main loop to see it on Logic Analyzer. This is an event generated using a software command */
    EVSYS_SoftwareEventASet(EVSYS_SWEVENTA_CH0_gc);
}

void Clear_Fault(void)
{
    /* Clear fault condition using a software command */
    WEX0_SoftwareCommand(WEX_CMD_FAULTCLR_gc);
}

int main(void)
{
    SYSTEM_Initialize();

    TCE0_Compare0CallbackRegister(UserCallback_CMP0);
    TCE0_Compare1CallbackRegister(UserCallback_CMP1);
    TCE0_Compare2CallbackRegister(UserCallback_CMP2);
    TCE0_Compare3CallbackRegister(UserCallback_CMP3);

    while(1)
    {
      Create_Fault();
      _delay_us(250);
      Clear_Fault();
      _delay_us(250);
    }    
}