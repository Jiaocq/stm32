#ifndef _DEV_SPIIO_H_
#define _DEV_SPIIO_H_

/** cs = MCU_SPI2_CS_DIDO_MCP23S17 */
#define FROMDO 0x0 /**u17 */
#define TODI 0x4   /**u18 */
#define TODO 0x5   /**u21 */
#define FROMDI 0x3 /**u20 */

/** cs = MCU_SPI2_CS_AIHIO_MCP23S17 */
#define FROMHIO 0x0   /**u93 */
#define TOFROMHIO 0x4 /**u94 */
#define TOAI 0x3      /**u96 */

/**write a pin
 *   FROMHIO  TOFROMHIO TOAI     
 */
int WriteAIHIOPin(uint8_t devId, uint8_t pinId, uint8_t pinState);

/**write a pin
 * devId : FROMDO   TODI     TODO     FROMDI      
 * pinId : 0-15
 */
int WriteDIDOPin(uint8_t devId, uint8_t pinId, uint8_t pinState);

/**init all mcp23s17 */
int SpiioIinit();

/**reaet all mcp23s17 */
int SpiioDeinit(); 

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
