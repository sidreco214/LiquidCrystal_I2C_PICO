if (NOT TARGET LiquidCrystal_I2C_PICO)
    add_library(LiquidCrystal_I2C_PICO INTERFACE)
    target_include_directories(LiquidCrystal_I2C_PICO INTERFACE include)
    # dependencies handled in implementation CMakeLists.txt

    target_sources(LiquidCrystal_I2C_PICO  INTERFACE 
        ${CMAKE_CURRENT_LIST_DIR}/LiquidCrystal_I2C_PICO.cpp
    )
    
    target_link_libraries(LiquidCrystal_I2C_PICO INTERFACE
        pico_stdlib
        hardware_i2c    
    )
endif()