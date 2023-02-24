#include "LiquidCrystal_I2C_PICO.h"

void LiquidCrystal_I2C_PICO::write_byte(uint8_t val) {
    i2c_write_blocking(_i2c, _addr, &val, 1, false);
}

void LiquidCrystal_I2C_PICO::pulse_enable(uint8_t val) {
    sleep_us(LCD_DELAY);
    write_byte(val | LCD_ENABLE_BIT);
    sleep_us(LCD_DELAY);
    write_byte(val & ~LCD_ENABLE_BIT);
    sleep_us(LCD_DELAY);
}

void LiquidCrystal_I2C_PICO::send_byte(uint8_t val, uint8_t mode) {
    uint8_t highNible = mode | (val & 0xf0) | _backlight;
    uint8_t lowNible = mode | ((val << 4) & 0xf0) | _backlight;

    write_byte(highNible);
    pulse_enable(highNible);
    write_byte(lowNible);
    pulse_enable(lowNible);
}

LiquidCrystal_I2C_PICO::LiquidCrystal_I2C_PICO(uint8_t address, uint8_t rows, uint8_t columns)
: _addr(address), _rows(rows), _cols(columns), _i2c(i2c0), _SDApin(4), _SCLpin(5) {
    _displaycontrol = LCD_DISPLAYCONTROL;
    _backlight = LCD_BACKLIGHT;

    i2c_init(_i2c, 100 * 1000);

    //gpio setting
    gpio_set_function(_SDApin, GPIO_FUNC_I2C);
    gpio_set_function(_SCLpin, GPIO_FUNC_I2C);
    gpio_pull_up(_SDApin);
    gpio_pull_up(_SCLpin);

    //Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(_SDApin, _SCLpin, GPIO_FUNC_I2C));
}

LiquidCrystal_I2C_PICO::LiquidCrystal_I2C_PICO(uint8_t address, uint8_t rows, uint8_t columns, i2c_inst_t *i2c, uint8_t SDApin, uint8_t SCLpin)
: _addr(address), _rows(rows), _cols(columns), _i2c(i2c), _SDApin(SDApin), _SCLpin(SCLpin) {
    _displaycontrol = LCD_DISPLAYCONTROL;
    _backlight = LCD_BACKLIGHT;

    i2c_init(_i2c, 100 * 1000);

    //gpio setting
    gpio_set_function(_SDApin, GPIO_FUNC_I2C);
    gpio_set_function(_SCLpin, GPIO_FUNC_I2C);
    gpio_pull_up(_SDApin);
    gpio_pull_up(_SCLpin);

    //Make the I2C pins available to picotool
    bi_decl(bi_2pins_with_func(_SDApin, _SCLpin, GPIO_FUNC_I2C));
}



void LiquidCrystal_I2C_PICO::init() {
    //the chip begins in 8bit Mode, try to set 4bit mode
    send_byte(0x03, LCD_COMMAND);
    send_byte(0x03, LCD_COMMAND);
    send_byte(0x03, LCD_COMMAND);
    send_byte(0x02, LCD_COMMAND);

    send_byte(LCD_ENTRYMODESET | LCD_ENTRYLEFT, LCD_COMMAND);
    _displaycontrol |= LCD_DISPLAYON; 
    send_byte(_displaycontrol, LCD_COMMAND);
    send_byte(LCD_FUNCTIONSET | LCD_2LINE | LCD_5x8DOTS, LCD_COMMAND);
    clear();
}

void LiquidCrystal_I2C_PICO::clear() {
    send_byte(LCD_CLEARDISPLAY, LCD_COMMAND);
}

void LiquidCrystal_I2C_PICO::setCursor(uint8_t row, uint8_t col) {
    if(row > _rows) row = _rows-1;
    if(col > _cols) col = _cols-1;
    uint8_t row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };
    send_byte(0x80 | (col + row_offsets[row]), LCD_COMMAND);
}

void LiquidCrystal_I2C_PICO::print(char ch) {
    write(ch);
}

void LiquidCrystal_I2C_PICO::print(string str) {
    for(int i=0; i<str.length(); i++) send_byte(str[i], LCD_CHARACTER);
}



void LiquidCrystal_I2C_PICO::noDisplay() {
    _displaycontrol &= ~LCD_DISPLAYON;
    send_byte(_displaycontrol, LCD_COMMAND);
}

void LiquidCrystal_I2C_PICO::display() {
    _displaycontrol |= LCD_DISPLAYON;
    send_byte(_displaycontrol, LCD_COMMAND);
}


void LiquidCrystal_I2C_PICO::noCursor() {
    _displaycontrol &= ~LCD_CURSORON;
    send_byte(_displaycontrol, LCD_COMMAND);
}

void LiquidCrystal_I2C_PICO::cursor() {
    _displaycontrol |= LCD_CURSORON;
    send_byte(_displaycontrol, LCD_COMMAND);
}


void LiquidCrystal_I2C_PICO::noBlink() {
    _displaycontrol &= ~LCD_BLINKON;
    send_byte(_displaycontrol, LCD_COMMAND);
}

void LiquidCrystal_I2C_PICO::blink() {
    _displaycontrol |= LCD_BLINKON;
    send_byte(_displaycontrol, LCD_COMMAND);
}

void LiquidCrystal_I2C_PICO::noBacklight() {
    _backlight = LCD_NOBACKLIGHT;
    write_byte(0);
}

void LiquidCrystal_I2C_PICO::backlight() {
    _backlight = LCD_BACKLIGHT;
    write_byte(0);
}

void LiquidCrystal_I2C_PICO::creatChar(uint8_t location, uint8_t charmap[]) {
    location &= 0x7;
    send_byte(LCD_SETCGRAMADDR | (location << 3), LCD_COMMAND);
    for(int i=0; i<8; i++) send_byte(charmap[i], LCD_CHARACTER);
}