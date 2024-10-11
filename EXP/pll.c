#include <LPC214x.h>
//TEJAS GANGARDE B-78
//22AETN1101026
// Define the pin positions for RS and EN
#define RS (1 << 13)  // P0.13
#define EN (1 << 16)  // P0.16

// Define the data line positions
#define D4 (1 << 17)  // P0.17
#define D5 (1 << 18)  // P0.18
#define D6 (1 << 19)  // P0.19
#define D7 (1 << 20)  // P0.20

void delay_ms(unsigned int time) {
    unsigned int i, j;
    for(i = 0; i < time; i++)
        for(j = 0; j < 5000; j++);  // Increased delay
}

void LCD_Command(unsigned char cmd) {
    IOCLR0 = RS; // RS = 0 for command
    IOCLR0 = EN; // EN = 0 initially

    // Send higher nibble
    IOCLR0 = (D4 | D5 | D6 | D7); // Clear D4-D7
    IOSET0 = ((cmd >> 4) & 0x0F) << 17; // Send higher nibble to D4-D7
    IOSET0 = EN; // EN = 1
    delay_ms(2);  // Increased delay
    IOCLR0 = EN; // EN = 0

    // Send lower nibble
    IOCLR0 = (D4 | D5 | D6 | D7); // Clear D4-D7
    IOSET0 = (cmd & 0x0F) << 17; // Send lower nibble to D4-D7
    IOSET0 = EN; // EN = 1
    delay_ms(2);  // Increased delay
    IOCLR0 = EN; // EN = 0
}

void LCD_Init(void) {
    // Set RS, EN, D4-D7 as output
    IODIR0 |= (RS | EN | D4 | D5 | D6 | D7);
    delay_ms(20);

    LCD_Command(0x02); // Initialize LCD in 4-bit mode
    LCD_Command(0x28); // 2 lines, 5x7 matrix
    LCD_Command(0x0C); // Display on, cursor off
    LCD_Command(0x06); // Increment cursor
    LCD_Command(0x01); // Clear display
    delay_ms(2);
}

void LCD_Char(unsigned char data) {
    IOSET0 = RS; // RS = 1 for data
    IOCLR0 = EN; // EN = 0 initially

    // Send higher nibble
    IOCLR0 = (D4 | D5 | D6 | D7); // Clear D4-D7
    IOSET0 = ((data >> 4) & 0x0F) << 17; // Send higher nibble to D4-D7
    IOSET0 = EN; // EN = 1
    delay_ms(2);  // Increased delay
    IOCLR0 = EN; // EN = 0

    // Send lower nibble
    IOCLR0 = (D4 | D5 | D6 | D7); // Clear D4-D7
    IOSET0 = (data & 0x0F) << 17; // Send lower nibble to D4-D7
    IOSET0 = EN; // EN = 1
    delay_ms(2);  // Increased delay
    IOCLR0 = EN; // EN = 0
}

void LCD_String(const char *str) {
    while(*str) {
        LCD_Char(*str++);
    }
}

void LCD_SetCursor(unsigned char row, unsigned char col) {
    unsigned char pos;
    if(row == 1)
        pos = 0x80 + col; // 0x80 is the command to set the cursor to the beginning of the first line
    else if(row == 2)
        pos = 0xC0 + col; // 0xC0 is the command to set the cursor to the beginning of the second line
    
    LCD_Command(pos);
}

int main() {
    LCD_Init(); // Initialize LCD
    LCD_SetCursor(1, 0); // Set cursor to the first line, first position
    LCD_String("TEJAS GANGARDE"); // Display "TEJAS GANGARDE" on the first line
    LCD_SetCursor(2, 0); // Set cursor to the second line, first position
    LCD_String("22AETN1101026"); // Display "22AETN1101026" on the second line

    while(1);
}
