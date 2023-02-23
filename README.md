# LiquidCrystal_I2C_PICO
LiquidCrystal_I2C for Raspberry Pi Pico

I2C expender device is PCF8574 IIC I2C(ordinarily used)

## Warring
Only 2~4 rows of LCD could be compatible.
(I test only 1602, 2004, but I expect 0802, 2002, 4002, 1604 are compatible)

## How to use
To use this, you must link LiquidCrystal_I2C and add subdirectory

Download Library with git console
```console
cd $PICO_SDK_PATH/..
mkdir pico-lib
cd pico-lib
git clone https://github.com/sidreco214/LiquidCrystal_I2C_PICO.git
```

CMakeLists.txt in main
```console
set(PICO_LIB_PATH ${PICO_SDK_PATH}/../pico-lib)
add_subdirectory(${PICO_LIB_PATH}/LiquidCrystal_I2C_PICO LiquidCrystal_I2C_PICO)
```

CMakeLists.txt in source
```console
target_link_libraries((target name) LiquidCrystal_I2C_PICO)
```

Blog
https://sidreco.tistory.com/10
