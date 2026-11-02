cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_COMPILER "avr-gcc")
set(CMAKE_ASM_COMPILER "avr-gcc")

project(avr_os C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(lib)

add_compile_definitions(
    F_CPU=16000000L
    DEBUG=1
    BAUD=115200
)

file(GLOB_RECURSE SOURCES 
    "src/main.c"
    "lib/*.c"
    "lib/*.S"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_options(${PROJECT_NAME} PRIVATE 
    -Os
    -Wall    
    -mmcu=atmega328p
    -ffunction-sections
    -fdata-sections
    -flto
)

target_link_options(${PROJECT_NAME} PRIVATE
    -mmcu=atmega328p
    -flto
    -Wl,--gc-sections
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND avr-objcopy -O ihex -R .eeprom ${PROJECT_NAME} ${PROJECT_NAME}.hex
)

if(WIN32)
    execute_process(
        COMMAND powershell -Command "[System.IO.Ports.SerialPort]::GetPortNames() | Select-Object -First 1"
        OUTPUT_VARIABLE AUTO_COM_PORT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    
    if(NOT AUTO_COM_PORT)
        set(AUTO_COM_PORT "COM3") 
    endif()
endif()

if(UNIX AND NOT APPLE)
    execute_process(
        COMMAND sh -c "ls /dev/ttyACM* /dev/ttyUSB* 2>/dev/null | head -n 1"
        OUTPUT_VARIABLE AUTO_COM_PORT
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    
    if(NOT AUTO_COM_PORT)
        set(AUTO_COM_PORT "/dev/ttyUSB0")
    endif()
endif()

add_custom_target(flash
    COMMAND avrdude -F -V -c arduino -p m328p -P ${AUTO_COM_PORT} -b 115200 -U flash:w:${PROJECT_NAME}.hex:i
    DEPENDS ${PROJECT_NAME}
)