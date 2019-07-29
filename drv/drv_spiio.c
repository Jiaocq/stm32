/**for mcp23s17 */
#include "spi.h"
#include "drv_time.h"
#include "drv_uart.h"

#define IOSPIBUS hspi2
#define TIMEOUT 1000 /*ms */
#define FrameLength 3

#define ReadReg(devId,regId)        (0x4UL << 28 | devId << 25 | 0x01UL << 24 | regId << 16)
#define WriteReg(devId,regId,data)  (0x4UL << 28 | devId << 25 | 0x00UL << 24 | regId << 16 | data << 8)
/* register address*/
#define IODIRA      0x00U    /* I/O DIRECTION REGISTER: 1-input, 0-output*/
#define IODIRB      0x01U
#define IPOLA       0x02U    /*INPUT POLARITY PORT REGISTER: 1-opposite logic, 0-same logic*/                                      */
#define IPOLB       0x03U
#define GPINTENA    0x04U    /*INTERRUPT-ON-CHANGE PINS*/
#define GPINTENB    0x05U
#define DEFVALA     0x06U    /*DEFAULT VALUE REGISTER*/
#define DEFVALB     0x07U
#define INTCONA     0x08U    /*INTERRUPT-ON-CHANGE CONTROL REGISTER*/
#define INTCONB     0x09U
#define IOCONA      0x0AU    /*I/O EXPANDER CONFIGURATION REGISTER*/
#define IOCONB      0x0BU
#define GPPUA       0x0CU    /*GPIO PULL-UP RESISTOR REGISTER*/
#define GPPUB       0x0DU
#define INTFA       0x0EU    /*INTERRUPT FLAG REGISTER*/
#define INTFB       0x0FU
#define INTCAPA     0x10U   /*INTERRUPT CAPTURED VALUE FOR PORT REGISTER*/
#define INTCAPB     0x11U
#define IOA         0x12U   /*GENERAL PURPOSE I/O PORT REGISTER:1-high, 0-low*/
#define IOB         0x13U
#define OLATA       0x14U   /*OUTPUT LATCH REGISTER: 1-high, 0-low*/
#define OLATB       0x15U

/** cs = MCU_SPI2_CS_DIDO_MCP23S17 */
#define FROMDO      0x0/**u17 */
#define TODI        0x4/**u18 */
#define TODO        0x5/**u21 */
#define FROMDI      0x3/**u20 */

/** cs = MCU_SPI2_CS_AIHIO_MCP23S17 */
#define FROMHIO     0x0 /**u93 */
#define TOFROMHIO   0x4/**u94 */
#define TOAI        0x3 /**u96 */

/**init status */
static int initStatus = 0;


static uint8_t ReadDIDO(uint32_t sendData)
{
    uint32_t readData = 0;
    HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, 0);
    HAL_SPI_TransmitReceive(&IOSPIBUS, (uint8_t*)&readData,(uint8_t *)&sendData, FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, 1);
    DelayUs(5);
    return (uint8_t)((0xffUL)&(readData >> 8));
}

static uint8_t ReadAIHIO(uint32_t sendData)
{
    uint32_t readData = 0;
    HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, 0);
    HAL_SPI_TransmitReceive(&IOSPIBUS, (uint8_t*)&readData,(uint8_t *)&sendData, FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, 1);
    DelayUs(5);
    return (uint8_t)((0xffUL)&(readData >> 8));
}

static int32_t WriteDIDO(uint32_t sendData)
{
    HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, 0);
    HAL_SPI_Transmit(&IOSPIBUS, (uint8_t *)&sendData, FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_SPI2_CS_DIDO_MCP23S17_GPIO_Port, MCU_SPI2_CS_DIDO_MCP23S17_Pin, 1);
    DelayUs(5);
    return 0;
}

static uint32_t WriteAIHIO(uint32_t sendData)
{
    HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, 0);
    HAL_SPI_Transmit(&IOSPIBUS, (uint8_t *)&sendData, FrameLength, TIMEOUT);
    HAL_GPIO_WritePin(MCU_SPI2_CS_AIHIO_MCP23S17_GPIO_Port, MCU_SPI2_CS_AIHIO_MCP23S17_Pin, 1);
    DelayUs(5);
    return 0;
}
/**init spi io */
static void MCP23S17DIDOInit(uint8_t devAddr)
{
/** set FROMDO's IOCON , input mode */
WriteDIDO(WriteReg(devAddr,IOCONA,0x38));
WriteDIDO(WriteReg(devAddr,IOCONB,0x38));
WriteDIDO(WriteReg(devAddr,IODIRA,0xff));
WriteDIDO(WriteReg(devAddr,IODIRB,0xff));
}

static void MCP23S17AIHIOInit(uint8_t devAddr)
{
/** set FROMDO's IOCON , input mode */
WriteAIHIO(WriteReg(devAddr,IOCONA,0x38));
WriteAIHIO(WriteReg(devAddr,IOCONB,0x38));
WriteAIHIO(WriteReg(devAddr,IODIRA,0xff));
WriteAIHIO(WriteReg(devAddr,IODIRB,0xff));
}
/**deinit spi io */
static void MCP23S17DIDODeinit(uint8_t devAddr)
{
/** set FROMDO's IOCON , input mode */
WriteDIDO(WriteReg(devAddr,IOCONA,0x38));
WriteDIDO(WriteReg(devAddr,IOCONB,0x38));
WriteDIDO(WriteReg(devAddr,IODIRA,0xff));
WriteDIDO(WriteReg(devAddr,IODIRB,0xff));
}

static void MCP23S17AIHIODeinit(uint8_t devAddr)
{
/** set FROMDO's IOCON , input mode */
WriteAIHIO(WriteReg(devAddr,IOCONA,0x38));
WriteAIHIO(WriteReg(devAddr,IOCONB,0x38));
WriteAIHIO(WriteReg(devAddr,IODIRA,0xff));
WriteAIHIO(WriteReg(devAddr,IODIRB,0xff));
}

int SpiioIinit()
{
/** configure  */
/**reset all gpio */
HAL_GPIO_WritePin(MCU_SPI2_RESET_MCP23S17_GPIO_Port,MCU_SPI2_RESET_MCP23S17_Pin,0);
DelayUs(5);
HAL_GPIO_WritePin(MCU_SPI2_RESET_MCP23S17_GPIO_Port,MCU_SPI2_RESET_MCP23S17_Pin,1);
/** set DIDO , input mode */
MCP23S17DIDOInit(FROMDO);
MCP23S17DIDOInit(TODI);
MCP23S17DIDOInit(TODO);
MCP23S17DIDOInit(FROMDI);
/** set AIHIO , input mode */
MCP23S17AIHIOInit(FROMHIO);
MCP23S17AIHIOInit(TOFROMHIO);
MCP23S17AIHIOInit(TOAI);
initStatus = 1;      
return 0;
}

int SpiioDeinit()
{
/** configure  */
/**reset all gpio */
HAL_GPIO_WritePin(MCU_SPI2_RESET_MCP23S17_GPIO_Port,MCU_SPI2_RESET_MCP23S17_Pin,0);
DelayUs(5);
HAL_GPIO_WritePin(MCU_SPI2_RESET_MCP23S17_GPIO_Port,MCU_SPI2_RESET_MCP23S17_Pin,1);
/** set DIDO , input mode */
MCP23S17DIDODeinit(FROMDO);
MCP23S17DIDODeinit(TODI);
MCP23S17DIDODeinit(TODO);
MCP23S17DIDODeinit(FROMDI);
/** set AIHIO , input mode */
MCP23S17AIHIODeinit(FROMHIO);
MCP23S17AIHIODeinit(TOFROMHIO);
MCP23S17AIHIODeinit(TOAI);
initStatus = 0;      
return 0;
}
/**write a pin
 * FROMDO   TODI     TODO     FROMDI   FROMHIO  TOFROMHIO TOAI     
 */
int WriteDIDOPin(uint8_t devId, uint8_t pinId, uint8_t pinState)
{
    switch (devId)
    {
    case FROMDO:
        break;
    case TODI:
        break;
    case TODO:
        break;
    case FROMDI : 
        break;
    default:
        break;
    }
    return 0;   
}           

/**write a pin
 *   FROMHIO  TOFROMHIO TOAI     
 */
int WriteAIHIOPin(uint8_t devId, uint8_t pinId, uint8_t pinState)
{
    switch (devId)
    {
    case FROMHIO : 
        break;
    case TOFROMHIO : 
        break;
    case TOAI : 
        break;
    default:
        break;
    }   
    return 0;
}
