[![MCHP](../images/microchip.png)](https://www.microchip.com)

## Generate PWM Signals Using TCE

Below is an example of how to set a Timer/Counter Type E (TCE) instance to generate four Pulse-Width Modulation (PWM) signals at 10 kHz with duty cycles of 20%, 40%, 60%, and 80%. In this example the scaling feature of the values set in compare registers is highlighted, as well as the high resolution feature. The user can increase the PWM signal resolution up to three bits.

## Related Documentation

More details and code examples on the AVR16EB32 can be found at the following links:

- [AVR<sup>®</sup> EB Product Page](https://www.microchip.com/en-us/product/AVR16EB32)
- [AVR<sup>®</sup> EB Code Examples on GitHub](https://github.com/microchip-pic-avr-examples?q=AVR16EB32)

## Software Used

- [MPLAB® X IDE v6.15 or newer](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)
- [AVR-Ex DFP-2.8.189 or newer Device Pack](https://packs.download.microchip.com/)
- [MPLAB® XC8 compiler v2.45](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers/downloads-documentation#XC8)
- [MPLAB® Code Configurator (MCC) v5.3.7](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator)
- [MPLAB® Code Configurator (MCC) Melody Core v2.6.2 or newer](https://www.microchip.com/en-us/tools-resources/configure/mplab-code-configurator)

## Hardware Used

- [AVR<sup>®</sup> EB Curiosity Nano](https://www.microchip.com/en-us/product/AVR16EB32)

## Setup

The AVR16EB32 Curiosity Nano Development board is used as a test platform.

<br><img src="../images/AVR16EB32_Cnano_Board.png">

## Functionality

<br>After the peripheral clock, the output port pins and TCE are initialized, the  ```Amplitude_Value_Set``` function is called in an infinite loop. This function changes the value written in the AMP register. Based on this value, the values initially written in the CMPBUF registers of TCE are scaled in hardware. TCE has a scaling hardware accelerator that modifies the values from CMPBUF registers based on the scale mode and the values from AMP and OFFSET registers. In this application, the amplitude changes, establishing the maximum possible values for duty cycles of 50%, 75%, 100% and 150%.

<br>For example, when the amplitude is set so that the maximum duty cycle is 50%, the initial value from CMP0BUF of 20% duty cycle gets scaled to 10%, the initial value from CMP1BUF of 40% duty cycle gets scaled to 20%, the initial value from CMP2BUF of 60% duty cycle gets scaled to 30%, and the initial value from CMP3BUF of 80% duty cycle gets scaled to 40%. Notice that if the scaled duty cycle is higher than 100%, it will be saturated at 100%, meaning that the TCE's output pin will stay in logic `1` high.

<br>The values in CMPBUF registers must be rewritten for the amplitude change to take place. To see the changes on a logic analyzer, a pin toggle is used at the end of the function. High resolution is also enabled and set to 4X, which means that one peripheral clock cycle duration get shortened four times. For example, a 20 MHz clock speed has a clock cycle duration of 50 ns. With the high resolution enabled one clock cycle duration will be approximate 12.5 ns.

## Function Called in an Infinite Loop

```c
void Amplitude_Value_Set(uint16_t value)
{
    /* Set the value of amplitude */
    TCE0_AmplitudeSet(value);
    
    /* Rewrite the values in CMPBUF registers so that the duty cycle get scaled according to the new value of amplitude */
    TCE0_CompareAllChannelsBufferedSet(DUTY_CYCLE_20_PERCENT, DUTY_CYCLE_40_PERCENT, DUTY_CYCLE_60_PERCENT, DUTY_CYCLE_80_PERCENT);
    
    /* Toggle PD5 pin to know when the value of amplitude has changed */
    IO_PD5_Toggle();
}
```

<br><img src="../images/tce_scale_flowchart.png">

<br>To generate this project using MPLAB X IDE and the MPLAB X Code Configurator (MCC Melody, MCC Clasic is not supported on this device), follow the next steps:

<br>1. Open MPLAB X IDE and create a new project for the AVR16EB32 device.

<br>2. Open MCC from the toolbar (more information on how to install the MCC plug-in can be found [here](https://onlinedocs.microchip.com/pr/GUID-1F7007B8-9A46-4D03-AEED-650357BA760D-en-US-6/index.html?GUID-D98198EA-93B9-45D2-9D96-C97DBCA55267)).

<br>3. In **MCC Content Manager** tab click the **Select MCC Melody** button and then click **Finish**.<br><img src="../images/addMCC.png">
<br><img src="../images/selectMCCMelody.png">
<br><img src="../images/mccFinish.png">

<br>4. Click on Project _Resources>System>CLKCTRL_, then do the following configuration:
<br><img src="../images/Select_CLKCTRL.png">
    <br> - Disable the Prescaler enable button
    <br> - Clock Select: PLL Oscillator
    <br> - PLL Multiplication Factor: Multiply by 16
    <br> - PLL Source Division: DIV4 
    <br> - Prescaler B division PDIVB: DIV4
<br><img src="../images/CLKCTRL_usecase1.png">

<br>5. To add the TCE module, go to _Device Resources>Drivers>Timer>TCE0_, then do the following configuration:
<br><img src="../images/Add_TCE.png">
    <br>  - Module Enable: Must be enabled by default, if not just toggle the button (it turns blue if enabled)
    <br>  - Clock Selection: System clock (by default the divider must be 1 - System clock)
    <br>  - Waveform Generation Mode: Dual-Slope PWM mode with overflow on TOP and BOTTOM (DSBOTH)
    <br>  - Requested Period[s]: 0.0001
    <br>  - Duty Cycle 0 [%] : 20
    <br>  - Duty Cycle 1 [%] : 40
    <br>  - Duty Cycle 2 [%] : 60
    <br>  - Duty Cycle 3 [%] : 80
    <br>  - Waveform Output n : Check the boxes from the Enable column for Waveform Output 0, 1, 2, 3
    <br>  - Duty Cycle High Resolution: Resolution increased by 4
    <br>  - Scale mode: CMP values are scaled from Bottom, 0% DC (duty cycle)
    <br>  - Scaled Writing to registers: Fractional
    <br>  - Amplitude Control Enable: Toggle the button (it turns blue if enabled)
    <br>  - Amplitude Value: 1
<br><img src="../images/TCE_UI1.png">
<br><img src="../images/TCE_UI2.png">

<br>6. In the **Pin Grid View** tab check if the TCE WO [0-3] pins are locked as outputs on PORTA. When the boxes from Enable column from Waveform Output n are checked, the pins are also locked. To change the PORT simply click a pin from another PORT in **Pin Grid View**. Select PIN5 of PORTD as an output for toggle to see the amplitude and compare values changes.

 |Pin                       | Configuration       |
 | :---------------------:  | :----------------:  |
 |            PA0           |   TCE WO0           |
 |            PA1           |   TCE WO1           |
 |            PA2           |   TCE WO2           |
 |            PA3           |   TCE WO3           |
 |            PD5           |   digital output    |

<br><img src="../images/Pin_Grid_View_UseCase1.png">

<br>7. In the **Project Resources** tab, click the **Generate** button so that MCC will generate all the specified drivers and configurations.
<br>
<br>
<br><img src="../images/Generate_Code.png">
<br>

<br>8. After MCC Melody generates the project files with the configuration explained above, overwrite the content from the ```main.c``` file with this:

```c
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
```

<br>9. Now the project can be built and run from MPLAB X IDE. At run time, the scaling value for the compare registers modifies every 10 ms and the range of the duty cycles modifies accordingly.

 ## Operation
 
 1. Connect the board to the PC.

 2. Open the ```TCE_DS_4PWM_Signals_MCC.X``` solution in MPLAB X IDE.

 3. Right click the project and select Set as main project.

<br><img src="../images/Set_as_main_project.png">

 4.  Build the ```TCE_DS_4PWM_Signals_MCC.X``` project by clicking **Clean and Build Project**.

<br><img src="../images/Clean_and_build.png">

 5. Click **Make and Program Device** to program the project to the board.

<br><img src="../images/Program_board.png">

## Results

The logic analyzer captures below show how the 4 PWM signals look and how and how the scaling of the duty cycles are made using the amplitude and offset:

<br>The range of the duty cycles is 0-50% of the PERIOD 
<br><img src="../images/usecase1_0_50.png">

<br>The range of the duty cycles is scaled to 0-75% of the PERIOD
<br><img src="../images/usecase1_0_75.png">

<br>The range of the duty cycles is scaled to 0-100% of the PERIOD
<br><img src="../images/usecase1_0_100.png">

<br>The range of the duty cycles is scaled to 0-150% of the PERIOD
<br><img src="../images/usecase1_0_150.png">

## Summary

This project shows how to use the TCE to generate PWM signals in Dual Ramp mode and how to use the high resolution and scaling mode of PWM duty cycle, depending on the set amplitude and offset.