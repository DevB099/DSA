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
    // Set P0.25 as output for buzzer
    IO0DIR |= (1 << 25);

    while(1)
    {
        // Turn on the buzzer
        IO0SET = (1 << 25);
        delay_ms(1000);  // Delay to keep the buzzer on for 10 seconds

        // Turn off the buzzer
        IO0CLR = (1 << 25);
        delay_ms(1000);  // Delay to keep the buzzer off for 10 seconds
    }
}
