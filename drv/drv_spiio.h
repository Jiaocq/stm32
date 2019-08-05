#ifndef _DEV_SPIIO_H_
#define _DEV_SPIIO_H_

#include "stm32f4xx_hal.h"

/** cs = MCU_SPI2_CS_DIDO_MCP23S17 */
#define FROMDO 0x0 /**u17 pins input from DO : 0xffff , pin 0-15 to DO 0-15 , DO high level to pins high level */
#define TODI 0x4   /**u18 pins out   to   DI : 0x0000 ,    pin 0-15 to DI 15-0 , PINS low level to connect two point */
#define TODO 0x2   /**u21 pins out   to   DO : 0x0000 ,   pin 0-15 to DO 0-15 ， pins low level to connect 10k24v */
#define FROMDI 0x3 /**u20 pins input from DI : 0xffff , pin 0-15 to DI 0-15 , DI high level to pins high level */

/** cs = MCU_SPI2_CS_AIHIO_MCP23S17 */
#define FROMHIO 0x0   /**u93 input from HIO : 0xffff , pin 7654 to HIO ch 4567 ,high to high */
#define TOFROMHIO 0x4 /**u94 0123 input for HIO ch 0123, 4567 output for HIO ch 0123 ,pin 8-11 output for HIO ch 4567 ,
                        pin 12-15 output for HIO AI 4422 , hogh to high : 0x000f*/
#define TOAI 0x3      /**u96 out put for AI , pins 0-7 for 4line's 0-7, pins 8-15 for 2line's 0-7 */

/**init all mcp23s17 */
int SpiioIinit();

/**write a pin
 *   FROMHIO  TOFROMHIO TOAI
 */
int WriteAIHIOPin(uint8_t devId, uint8_t pinId, uint8_t pinState);

/**write a pin
 * devId : FROMDO   TODI     TODO     FROMDI
 * pinId : 0-15
 */
int WriteDIDOPin(uint8_t devId, uint8_t pinId, uint8_t pinState);

/**read a pin
 * devId : FROMHIO  TOFROMHIO TOAI
 * pinId : 0-15
 * return -1,0 ,1 : err , 0,  1
 * */
int ReadAIHIOPin(uint8_t devId, uint8_t pinId);

/**read a pin
 * devId : FROMDO   TODI     TODO     FROMDI
 * pinId : 0-15
 * return -1,0 ,1 : err , 0,  1
 * */
int ReadDIDOPin(uint8_t devId, uint8_t pinId);

#endif
