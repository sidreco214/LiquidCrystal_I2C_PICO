#include <string>
using std::string;
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "pico/binary_info.h"

#ifndef byte
typedef uint8_t byte;
#endif

// commands
#define LCD_CLEARDISPLAY  0x01
#define LCD_RETURNHOME  0x02
#define LCD_ENTRYMODESET  0x04
#define LCD_DISPLAYCONTROL  0x08
#define LCD_CURSORSHIFT  0x10
#define LCD_FUNCTIONSET  0x20
#define LCD_SETCGRAMADDR  0x40
#define LCD_SETDDRAMADDR  0x80

// flags for display entry mode
#define LCD_ENTRYSHIFTINCREMENT  0x01
#define LCD_ENTRYLEFT  0x02

// flags for display and cursor control
#define LCD_BLINKON  0x01
#define LCD_CURSORON  0x02
#define LCD_DISPLAYON  0x04

// flags for display and cursor shift
#define LCD_MOVERIGHT  0x04
#define LCD_DISPLAYMOVE  0x08

// flags for function set
#define LCD_5x8DOTS 0x00
#define LCD_5x10DOTS  0x04
#define LCD_2LINE  0x08
#define LCD_8BITMODE  0x10

// flag for backlight control
#define LCD_BACKLIGHT  0x08
#define LCD_NOBACKLIGHT 0x00

#define LCD_ENABLE_BIT  0x04

//Modes for send_byte
#define LCD_CHARACTER  1
#define LCD_COMMAND    0

//byte write delay(us)
#define LCD_DELAY 600

class LiquidCrystal_I2C_PICO {
    private:
    uint8_t _addr; //address of I2C
    uint _SDApin;
    uint _SCLpin;

    i2c_inst_t *_i2c;
    uint8_t _numlines;
    uint8_t _rows;
    uint8_t _cols;

    uint8_t _displaycontrol; //control display, cursor and toggle of blink on cursor
    uint8_t _backlight;

    private:
    void write_byte(uint8_t val);
    void pulse_enable(uint8_t val);
    void send_byte(uint8_t val, uint8_t mode);

    public:
    /// @brief Constructer of LiquidCrystal_I2C for Raspberry Pi Pico, I2C0 is used with default SDA and SCL pins (GP4, GP5 on a pico)
    /// @param address I2C address of LCD, expected 0x27 or 0x3F
    /// @param rows The number of rows on LCD
    /// @param columns The number of columns on LCD
    LiquidCrystal_I2C_PICO(uint8_t address, uint8_t rows, uint8_t columns);

    
    /// @brief Constructer of LiquidCrystal_I2C for Raspberry Pi Pico
    /// @param address address I2C address of LCD, expected 0x27 or 0x3F
    /// @param rows The number of rows on LCD
    /// @param columns The number of columns on LCD
    /// @param i2c Either \ref i2c0 or \ref i2c1
    /// @param SDApin i2c0 is on 0, 4, 8, 12, 16, 20, i2c1 is on 2, 6, 10, 14, 18, 26
    /// @param SCLpin i2c0 is on 1, 5, 9, 13, 17, 21, i2c1 is on 3, 7, 11, 15, 19, 27
    LiquidCrystal_I2C_PICO(uint8_t address, uint8_t rows, uint8_t columns, i2c_inst_t *i2c, uint8_t SDApin, uint8_t SCLpin);
    ~LiquidCrystal_I2C_PICO();

    void init(); //Initialize LCD, You must run it once before using this class
    void clear();
    void setCursor(uint8_t row, uint8_t col);
    inline void write(char ch);
    void print(char ch);
    void print(string str);

    void noDisplay();
    void display();
    void noCursor();
    void cursor();
    void noBlink();
    void blink();
    void noBacklight();
    void backlight();

    /// @brief Create custom char recorded in CGRAM
    /// @param location Assigned location of your char(Location range is from 0 to 7)
    /// @param charmap uint8_t array[8]
    void creatChar(uint8_t location, uint8_t charmap[]);
};

inline void LiquidCrystal_I2C_PICO::write(char ch) {
    send_byte(ch, LCD_CHARACTER);
}