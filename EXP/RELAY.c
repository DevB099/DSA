#include <lpc214x.h>
#include <stdio.h>
/*
TEJAS GANGARDE
22AETN1101026
*/

void delay() {
    int i, j;
    for (i = 0; i < 1000; i++)
        for (j = 0; j < 2000; j++);
}

int main() {
    // Configure P1.25 as a GPIO pin
    PINSEL1 &= ~(3 << 18); // Clear the bits corresponding to P1.25

    // Set P1.25 as output
    IODIR1 |= (1 << 25);

    while (1) {
        // Set P1.25 (turn on the pin)
        IOSET1 = (1 << 25);
        delay();
        
        // Clear P1.25 (turn off the pin)
        IOCLR1 = (1 << 25);
        delay();
    }
}
