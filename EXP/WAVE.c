#include <lpc214x.h>
#include <stdio.h>
//TEJAS GANGARDE B-78
//22AETN1101026
void delay(int count) {
    int i;
    for (i = 0; i < count; i++);
}

void GPIO_Init() {
    // Configure P0.25 as GPIO
    PINSEL1 &= ~(3 << 18); // Clear bits 18 and 19 to select GPIO function for P0.25
    IO0DIR |= (1 << 25);   // Set P0.25 as output
}

void generateSquareWave() {
    while (1) {
        IO0SET = (1 << 25); // Set P0.25 high
        delay(1000);       // Adjust delay to control frequency of the waveform

        IO0CLR = (1 << 25); // Set P0.25 low
        delay(1000);       // Adjust delay to control frequency of the waveform
    }
}

int main() {
    GPIO_Init();
    generateSquareWave();
    while (1);
}
