cmake_minimum_required(VERSION 3.22)

# --------------------------------------------
# Project configuration
# --------------------------------------------
set(CMAKE_PROJECT_NAME Test_VSCODE_2)
project(${CMAKE_PROJECT_NAME} C ASM)

# C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Default build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message("Build type: ${CMAKE_BUILD_TYPE}")

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# --------------------------------------------
# Toolchain (ARM GCC)
# --------------------------------------------
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_ASM_COMPILER arm-none-eabi-gcc)

# MCU & FPU settings (Cortex-M4 + FPU)
set(MCU_FLAGS "-mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard")

# Compiler flags
set(CMAKE_C_FLAGS "${MCU_FLAGS} -O0 -g3 -Wall -ffunction-sections -fdata-sections")
set(CMAKE_ASM_FLAGS "${MCU_FLAGS} -g3")

# ⚠️ IMPORTANT : Adapter le linker script pour STM32G474
set(LINKER_SCRIPT "${CMAKE_SOURCE_DIR}/STM32G474RETX_FLASH.ld")

set(CMAKE_EXE_LINKER_FLAGS
    "${MCU_FLAGS} -T${LINKER_SCRIPT} -Wl,-Map=${CMAKE_PROJECT_NAME}.map -Wl,--gc-sections"
)

# --------------------------------------------
# Source files
# --------------------------------------------
file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/Core/Src/*.c"
    "${CMAKE_SOURCE_DIR}/Core/Startup/*.s"
    "${CMAKE_SOURCE_DIR}/Drivers/STM32G4xx_HAL_Driver/Src/*.c"
    "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/RTOS2/Template/*.c"
    "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/RTOS2/Source/*.c"
)

# --------------------------------------------
# Executable
# --------------------------------------------
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})

# --------------------------------------------
# Include directories
# --------------------------------------------
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    "${CMAKE_SOURCE_DIR}/Core/Inc"
    "${CMAKE_SOURCE_DIR}/Core/Inc/user_interface"
    "${CMAKE_SOURCE_DIR}/Core/Inc/acquisition"
    "${CMAKE_SOURCE_DIR}/Core/Inc/motor_control"
    "${CMAKE_SOURCE_DIR}/Drivers/STM32g4xx_HAL_Driver/Inc"
    "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Include"
    "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/Device/ST/STM32G4xx/Include"
    "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/RTOS2/Template"
    "${CMAKE_SOURCE_DIR}/Drivers/CMSIS/RTOS2/Source"
)

# --------------------------------------------
# Preprocessor definitions
# --------------------------------------------
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    USE_HAL_DRIVER
    STM32G474xx
)

# --------------------------------------------
# Optional libs
# --------------------------------------------
# target_link_libraries(${CMAKE_PROJECT_NAME}
#     m
# )

# Remove incorrect libob.a dependency
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# --------------------------------------------
# End of file
# --------------------------------------------
