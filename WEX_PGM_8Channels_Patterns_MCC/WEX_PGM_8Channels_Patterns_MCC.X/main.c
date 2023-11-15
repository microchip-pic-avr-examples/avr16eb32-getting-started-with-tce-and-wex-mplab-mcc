/* Patterns that are written in the PGMOUT register */
#define COMPLEMENTARY_PATTERN           (WEX_PGMOUT6_bm | WEX_PGMOUT4_bm | WEX_PGMOUT2_bm | WEX_PGMOUT0_bm)
#define STAIRCASE0_PATTERN              (WEX_PGMOUT0_bm)
#define STAIRCASE1_PATTERN              (WEX_PGMOUT1_bm)
#define STAIRCASE2_PATTERN              (WEX_PGMOUT2_bm)
#define STAIRCASE3_PATTERN              (WEX_PGMOUT3_bm)
#define STAIRCASE4_PATTERN              (WEX_PGMOUT4_bm)
#define STAIRCASE5_PATTERN              (WEX_PGMOUT5_bm)
#define STAIRCASE6_PATTERN              (WEX_PGMOUT6_bm)
#define STAIRCASE7_PATTERN              (WEX_PGMOUT7_bm)
#define PATTERN_RESET                   (0x00)

#include "mcc_generated_files/system/system.h"
#include <util/delay.h>

void Complementary_Pattern_Set(void)
{
    WEX0_PatternGenerationOutputSet(COMPLEMENTARY_PATTERN);
    uint8_t complementary_pattern = COMPLEMENTARY_PATTERN;
    _delay_us(25);

    /* Complementary signals pattern */
    for(uint8_t i = 0; i < 9; i++)
    {
        /* Complementary_pattern variable changes at every step */
        complementary_pattern = ~complementary_pattern;

        /* Toggle the pattern for each of the WEX's output */
        WEX0_PatternGenerationOutputSet(complementary_pattern);

        /* Software delay added in order for the toggle to be visible */
        _delay_us(25);
    }
    
    /* Put all signals in low '0' logic and wait 250us to see the transition from one of the
     * complementary patterns to the stairs pattern*/
    WEX0_PatternGenerationOutputSet(PATTERN_RESET);
}

void Stairs_Pattern_Set(void)
{
    /* Each of the signals switch from low to high one at a time in increasing order
     * generate a stairs increment pattern*/
    WEX0_PatternGenerationOutputSet(STAIRCASE7_PATTERN);

    /* Software delay added in order for the increment to be visible */
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE6_PATTERN);
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE5_PATTERN);
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE4_PATTERN);
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE3_PATTERN);
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE2_PATTERN);
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE1_PATTERN);
    _delay_us(5);
    
    /* Each of the signals switch from low to high one at a time in decreasing order
     * generate a stairs decrement pattern*/
    WEX0_PatternGenerationOutputSet(STAIRCASE0_PATTERN);

    /* Software delay added in order for the decrement to be visible */
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE1_PATTERN);
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE2_PATTERN);
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE3_PATTERN);
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE4_PATTERN);
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE5_PATTERN);
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE6_PATTERN);
    _delay_us(5);
    WEX0_PatternGenerationOutputSet(STAIRCASE7_PATTERN);
    _delay_us(5);
    
    /* Put all signals in low '0' logic and wait 250us to see the transition from the
     * stairs pattern to one of the complementary patterns */
    WEX0_PatternGenerationOutputSet(PATTERN_RESET);
}

int main(void)
{
    SYSTEM_Initialize();


    while(1)
    {
        Complementary_Pattern_Set();
        _delay_us(250);
        Stairs_Pattern_Set();
        _delay_us(250);
    }    
}