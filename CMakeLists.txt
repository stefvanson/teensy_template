CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

# Environment-specific
SET(TEENSYPATH /home/stef/teensy)
SET(ARDUINOPATH ${TEENSYPATH}/tools/teensyduino/arduino-1.8.13)
SET(GTEST_ROOT /usr/local/lib64/)            # This is where libgtest.a is
SET(GTEST_INCLUDE_DIRS2 /usr/local/include)  # This is where gtest/gtest.h is

# Project-specific
SET(PROJECT_NAME myproject)

#************************************************************************
# Project configuration
#************************************************************************
PROJECT(${PROJECT_NAME})

# Setup the paths
SET(TOOLSPATH ${ARDUINOPATH}/hardware/tools/)  # location for Teensy Loader, teensy_post_compile and teensy_reboot
SET(COMPILERPATH ${TOOLSPATH}/arm/bin)
SET(COREPATH ${CMAKE_SOURCE_DIR}/lib/teensy/teensy4/)

# Flags for compiling C and C++-code
SET(CPUOPTIONS "-mcpu=cortex-m7 -mfloat-abi=hard -mfpu=fpv5-d16 -mthumb")
SET(CPPFLAGS "-Wall -O2 -ffunction-sections -fdata-sections")
SET(CPPFLAGS "${CPPFLAGS} ${CPUOPTIONS}")
SET(CPPFLAGS "${CPPFLAGS} -I${COREPATH} -Ilib")
SET(CPPFLAGS "${CPPFLAGS} -DF_CPU=600000000 -DUSB_SERIAL -DLAYOUT_US_ENGLISH -DUSING_MAKEFILE -DCUSTOM_TEENSY_MAIN_CPP")
SET(CPPFLAGS "${CPPFLAGS} -D__IMXRT1062__ -DARDUINO=10810 -DTEENSYDUINO=149 -DARDUINO_TEENSY40")

# Flags for compiling C-code
SET(CFLAGS)
SET(CMAKE_C_FLAGS  "${CMAKE_CXX_FLAGS} ${CFLAGS} ${CPPFLAGS}")

# Flags for compiling C++-code
SET(CXXFLAGS "-std=gnu++14 -felide-constructors -fno-exceptions")
SET(CXXFLAGS "${CXXFLAGS} -fpermissive -fno-rtti -Wno-error=narrowing")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${CXXFLAGS} ${CPPFLAGS}")

# Linker flags
SET(MCU_LD ${COREPATH}/imxrt1062.ld)
SET(LDFLAGS "-Os -Wl,--gc-sections,--relax,--print-memory-usage ${CPUOPTIONS} -T${MCU_LD}")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS}")

# Included libraries to link against
SET(LIBFLAGS "-lm -lstdc++ -larm_cortexM7lfsp_math")

# Setup the compilers and paths for other tools used for compiling
SET(CMAKE_C_COMPILER ${COMPILERPATH}/arm-none-eabi-gcc)
SET(CMAKE_CXX_COMPILER ${COMPILERPATH}/arm-none-eabi-g++)
SET(OBJCOPY ${COMPILERPATH}/arm-none-eabi-objcopy)
SET(SIZE ${COMPILERPATH}/arm-none-eabi-size)

# Add all the source files from src
FILE(GLOB_RECURSE SOURCE_CFILES "${CMAKE_SOURCE_DIR}/src/*.c")
FILE(GLOB_RECURSE SOURCE_CPPFILES "${CMAKE_SOURCE_DIR}/src/*.cpp")
SET(${PROJECT_NAME}_SOURCES ${SOURCE_CFILES} ${SOURCE_CPPFILES})
INCLUDE_DIRECTORIES(src)

# Add teensy library files
FILE(GLOB_RECURSE TEENSY_CFILES "${COREPATH}/*.c")
FILE(GLOB_RECURSE TEENSY_CPPFILES "${COREPATH}/*.cpp")
LIST(REMOVE_ITEM TEENSY_CPPFILES "${COREPATH}/main.cpp")
SET(TEENSYLIB_FILES ${TEENSY_CFILES} ${TEENSY_CPPFILES})
LIST(APPEND ${PROJECT_NAME}_SOURCES ${TEENSYLIB_FILES})
INCLUDE_DIRECTORIES(${COREPATH})

#************************************************************************
# Targets
#************************************************************************
# build the .elf file
ADD_EXECUTABLE(${PROJECT_NAME}.elf ${${PROJECT_NAME}_SOURCES})
TARGET_LINK_LIBRARIES(${PROJECT_NAME}.elf ${LIBFLAGS})

# build the .hex file from the .elf file (default target)
ADD_CUSTOM_TARGET(${PROJECT_NAME}.hex ALL)
ADD_CUSTOM_COMMAND(
  TARGET   ${PROJECT_NAME}.hex
  COMMAND  ${SIZE} ${PROJECT_NAME}.elf
  COMMAND  ${OBJCOPY} -O ihex -R .eeprom ${PROJECT_NAME}.elf ${PROJECT_NAME}.hex
)
ADD_DEPENDENCIES(${PROJECT_NAME}.hex ${PROJECT_NAME}.elf)

# 'make upload' starts the teensy flasher tool
ADD_CUSTOM_TARGET(upload)
ADD_CUSTOM_COMMAND(
  TARGET   upload
  COMMAND  ${TOOLSPATH}/teensy_post_compile -file="${CMAKE_BINARY_DIR}/${PROJECT_NAME}" -path=${CURDIR} -tools="${TOOLSPATH}"
  COMMAND  -${TOOLSPATH}/teensy_reboot
)
ADD_DEPENDENCIES(upload ${PROJECT_NAME}.hex)

ADD_SUBDIRECTORY(test)
ADD_SUBDIRECTORY(doc)
