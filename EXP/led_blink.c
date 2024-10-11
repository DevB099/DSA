#include <lpc214x.h>
#include <stdint.h>
//TEJAS GANGARDE B-78
//22AETN1101026
void delay_ms(uint16_t j) /* Function for delay in milliseconds */
{
    uint16_t x, i;
    for (i = 0; i < j; i++)
    {
        for (x = 0; x < 6000; x++); /* loop to generate 1 millisecond delay with 12MHz Fosc. */
    }
}

int main(void)
{
    // Set P0.4, P0.5, P0.6, P0.7, P0.22, P0.28, P0.30, and P1.16 as output bits
    IO0DIR |= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7) | (1 << 22) | (1 << 28) | (1 << 30);
    IO1DIR |= (1 << 16);

    // Ensure P0.30 and P0.28 are set to GPIO mode
    PINSEL1 &= ~(3 << 28); // Set P0.30 to GPIO mode (clear bits 28-29 in PINSEL1)
    PINSEL1 &= ~(3 << 24); // Set P0.28 to GPIO mode (clear bits 24-25 in PINSEL1)

    while(1)
    {
        // Turn on the first group of LEDs
        IO0SET = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
        delay_ms(1000); // Delay of 10000ms
        // Turn off the first group of LEDs
        IO0CLR = (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
        // Turn on the second group of LEDs
        IO0SET = (1 << 22) | (1 << 28) | (1 << 30);
        IO1SET = (1 << 16);
        delay_ms(1000); // Delay of 10000ms

        // Turn off the second group of LEDs
        IO0CLR = (1 << 22) | (1 << 28) | (1 << 30);
        IO1CLR = (1 << 16);
    }
}