#include <lpc214x.h>
#include <stdio.h>
//TEJAS GANGARDE B-78
//22AETN1101026
#define LCD_RS 13
#define LCD_EN 16
#define LCD_D4 17
#define LCD_D5 18
#define LCD_D6 19
#define LCD_D7 20

// Function declarations
void lcd_init(void);
void lcd_send_command(unsigned char command);
void lcd_send_data(unsigned char data);
void lcd_print_string(char *str);
void lcd_scroll_left(void);
void _delay_ms(unsigned int ms);
void _delay_us(unsigned int us);

void lcd_init(void) {
    // Initialize LCD pins as output
    IO0DIR |= (1 << LCD_RS) | (1 << LCD_EN) | (1 << LCD_D4) | (1 << LCD_D5) | (1 << LCD_D6) | (1 << LCD_D7);
    
    // Initialize LCD in 4-bit mode
    _delay_ms(20); // Wait for LCD to power up
    lcd_send_command(0x02); // Initialize in 4-bit mode
    lcd_send_command(0x28); // 4-bit mode, 2 lines, 5x7 dots
    lcd_send_command(0x0C); // Display on, cursor off
    lcd_send_command(0x06); // Increment cursor, no shift
    lcd_send_command(0x01); // Clear display
    _delay_ms(2); // Wait for the clear display command to complete
}

void lcd_send_command(unsigned char command) {
    // Send high nibble
    IO0CLR = (1 << LCD_RS); // RS = 0 for command
    IO0CLR = (0x0F << LCD_D4); // Clear data pins
    IO0SET = ((command >> 4) & 0x0F) << LCD_D4; // Send high nibble
    IO0SET = (1 << LCD_EN); // Enable pulse
    _delay_us(1);
    IO0CLR = (1 << LCD_EN); // Disable pulse

    // Send low nibble
    IO0CLR = (0x0F << LCD_D4); // Clear data pins
    IO0SET = (command & 0x0F) << LCD_D4; // Send low nibble
    IO0SET = (1 << LCD_EN); // Enable pulse
    _delay_us(1);
    IO0CLR = (1 << LCD_EN); // Disable pulse

    _delay_ms(2); // Wait for the command to complete
}

void lcd_send_data(unsigned char data) {
    // Send high nibble
    IO0SET = (1 << LCD_RS); // RS = 1 for data
    IO0CLR = (0x0F << LCD_D4); // Clear data pins
    IO0SET = ((data >> 4) & 0x0F) << LCD_D4; // Send high nibble
    IO0SET = (1 << LCD_EN); // Enable pulse
    _delay_us(1);
    IO0CLR = (1 << LCD_EN); // Disable pulse

    // Send low nibble
    IO0CLR = (0x0F << LCD_D4); // Clear data pins
    IO0SET = (data & 0x0F) << LCD_D4; // Send low nibble
    IO0SET = (1 << LCD_EN); // Enable pulse
    _delay_us(1);
    IO0CLR = (1 << LCD_EN); // Disable pulse

    _delay_ms(2); // Wait for the data to be processed
}

void lcd_print_string(char *str) {
    while (*str != '\0') {
        lcd_send_data(*str);
        str++;
    }
}

void lcd_scroll_left(void) {
    // Scroll the display to the left
    lcd_send_command(0x18); // Command for scrolling display left
    _delay_ms(100); // Delay to make the scrolling visible
}

void _delay_ms(unsigned int ms) {
    unsigned int i;
    for (i = 0; i < ms; i++) {
        _delay_us(500);
    }
}

void _delay_us(unsigned int us) {
    unsigned int i, j;
    for (i = 0; i < us; i++) {
        // Adjust this count for your specific clock frequency
        for (j = 0; j < 60; j++) {
            __asm volatile ("nop");
        }
    }
}

int main(void) {
    lcd_init();
    lcd_print_string("NAME-TEJAS GANGARDE REG NO-22AETN1101026"); // Print initial string

    while (1) {
        lcd_scroll_left(); // Scroll the display left
    }
}
