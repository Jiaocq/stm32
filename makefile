# C defines
C_DEFS += -DUSE_HAL_DRIVER 
C_DEFS += -DSTM32F427xx 
C_DEFS += -DUSE_HAL_DRIVER 
C_DEFS += -DARM_MATH_CM4 
C_DEFS += -DLITTLE_ENDIAN


######################################
# building variables
######################################
# debug build?
DEBUG = 2
# optimization
OPT = -O0


#######################################
# C includes
#######################################
C_INCLUDES =  -IInc 
C_INCLUDES += -IDrivers/STM32F4xx_HAL_Driver/Inc 
C_INCLUDES += -IDrivers/STM32F4xx_HAL_Driver/Inc/Legacy 
C_INCLUDES += -IDrivers/CMSIS/Device/ST/STM32F4xx/Include 
C_INCLUDES += -IDrivers/CMSIS/Include 
C_INCLUDES += -IDrivers/CMSIS/DSP/Include
C_INCLUDES += -Iapp
C_INCLUDES += -Idrv


######################################
# source
######################################
# C_SOURCE
C_SOURCE_DIR += app/*.c
C_SOURCE_DIR += Src/*.c
C_SOURCE_DIR += Drivers/STM32F4xx_HAL_Driver/Src/*.c
C_SOURCE_DIR += drv/*.c

######################################
# ASM source
######################################
ASM_SOURCE_DIR += ./*.s


#######################################
# LDFLAGS
######################################
LDSCRIPT_DIR += ./*.ld


#######################################
# LIBS
######################################
LIBS += -larm_cortexM4lf_math
LIBDIR += -LDrivers/CMSIS/Lib/GCC


#######################################
# Build path
#######################################
BUILD_DIR = bin


######################################
# target executable.elf hex bin
######################################
TARGET = executable


# C sources
C_SOURCES += $(wildcard $(C_SOURCE_DIR)) 


# ASM sources
ASM_SOURCES += $(wildcard $(ASM_SOURCE_DIR)) 


# link script
LDSCRIPT += $(wildcard $(LDSCRIPT_DIR))


#######################################
# binaries
#######################################
PREFIX = arm-none-eabi-
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
# cpu
CPU = -mcpu=cortex-m4

# fpu
FPU = -mfpu=fpv4-sp-d16

# float-abi
FLOAT-ABI = -mfloat-abi=hard

# mcu
MCU = $(CPU) -mthumb $(FPU) $(FLOAT-ABI)

# macros for gcc
# AS defines
AS_DEFS = 


# AS includes
AS_INCLUDES = 


# compile gcc flags
ASFLAGS = $(MCU) $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

CFLAGS = $(MCU) $(C_DEFS) $(C_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections

ifeq ($(DEBUG), 0)
else 
	CFLAGS += -g$(DEBUG) -gdwarf-$(DEBUG)
endif


# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"



# libraries
LIBS += -lc 
LIBS += -lm 
LIBS += -lnosys 

LDFLAGS = $(MCU) -specs=nano.specs -T$(LDSCRIPT) $(LIBDIR) $(LIBS) -Wl,-Map=$(BUILD_DIR)/$(TARGET).map,--cref -Wl,--gc-sections

# default action: build all
all: $(BUILD_DIR)/$(TARGET).elf $(BUILD_DIR)/$(TARGET).hex $(BUILD_DIR)/$(TARGET).bin


#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))
# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(ASM_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(ASM_SOURCES)))

$(BUILD_DIR)/%.o: %.c makefile | $(BUILD_DIR) 
	$(CC) -c $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.s makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	
	
$(BUILD_DIR):
	mkdir $@		

#######################################
# clean up
#######################################
clean:
	-rm -fR $(BUILD_DIR)
  
#######################################
# dependencies
#######################################
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***
