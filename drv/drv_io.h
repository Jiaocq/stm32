#ifndef _DRV_IO_H_
#define _DRV_IO_H_
 
#define LED5    (0x4UL | 0x1UL << 3)
#define LED6    (0x5UL | 0x1UL << 3)
#define LED7    (0x6UL | 0x1UL << 3)
#define LED8    (0x7UL | 0x1UL << 3)

#define LED10   (0x0UL | 0x1UL << 4)
#define LED11   (0x1UL | 0x1UL << 4)
#define LED12   (0x2UL | 0x1UL << 4)
#define LED13   (0x3UL | 0x1UL << 4)
#define LED14   (0x4UL | 0x1UL << 4)
#define LED15   (0x5UL | 0x1UL << 4)
#define LED16   (0x6UL | 0x1UL << 4)
#define LED17   (0x7UL | 0x1UL << 4)

#define LED18   (0x0UL | 0x1UL << 5)
#define LED19   (0x1UL | 0x1UL << 5)
#define LED20   (0x2UL | 0x1UL << 5)
#define LED21   (0x3UL | 0x1UL << 5)
#define LED22   (0x4UL | 0x1UL << 5)
#define LED23   (0x5UL | 0x1UL << 5)
#define LED24   (0x6UL | 0x1UL << 5)
#define LED25   (0x7UL | 0x1UL << 5)

#define LED26   (0x0UL | 0x1UL << 6)
#define LED27   (0x1UL | 0x1UL << 6)
#define LED28   (0x2UL | 0x1UL << 6)
#define LED29   (0x3UL | 0x1UL << 6)
#define LED30   (0x4UL | 0x1UL << 6)
#define LED31   (0x5UL | 0x1UL << 6)
#define LED32   (0x6UL | 0x1UL << 6)
#define LED33   (0x7UL | 0x1UL << 6)

#define LED34   (0x0UL | 0x1UL << 7)
#define LED35   (0x1UL | 0x1UL << 7)
#define LED36   (0x2UL | 0x1UL << 7)
#define LED37   (0x3UL | 0x1UL << 7)
#define LED38   (0x4UL | 0x1UL << 7)
#define LED39   (0x5UL | 0x1UL << 7)
#define LED40   (0x6UL | 0x1UL << 7)
#define LED41   (0x7UL | 0x1UL << 7)

#define LED42   (0x0UL | 0x1UL << 8)
#define LED43   (0x1UL | 0x1UL << 8)
#define LED44   (0x2UL | 0x1UL << 8)
#define LED45   (0x3UL | 0x1UL << 8)
#define LED46   (0x4UL | 0x1UL << 8)
#define LED47   (0x5UL | 0x1UL << 8)
#define LED48   (0x6UL | 0x1UL << 8)
#define LED49   (0x7UL | 0x1UL << 8)

#define LED50   (0x0UL | 0x1UL << 9)
#define LED51   (0x1UL | 0x1UL << 9)
#define LED52   (0x2UL | 0x1UL << 9)
#define LED53   (0x3UL | 0x1UL << 9)
#define LED54   (0x4UL | 0x1UL << 9)
#define LED55   (0x5UL | 0x1UL << 9)
#define LED56   (0x6UL | 0x1UL << 9)
#define LED57   (0x7UL | 0x1UL << 9)

#define LED58   (0x0UL | 0x1UL << 10)
#define LED59   (0x1UL | 0x1UL << 10)
#define LED60   (0x2UL | 0x1UL << 10)
#define LED61   (0x3UL | 0x1UL << 10)
#define LED62   (0x4UL | 0x1UL << 10)   
#define LED63   (0x5UL | 0x1UL << 10)
#define LED64   (0x6UL | 0x1UL << 10)
#define LED65   (0x7UL | 0x1UL << 10)   

#define LED66   (0x4UL | 0x1UL << 11)
#define LED67   (0x5UL | 0x1UL << 11)
#define LED68   (0x6UL | 0x1UL << 11)
#define LED69   (0x7UL | 0x1UL << 11)

/**write a led 
 * ledId : LEDXX
 * ledState : 0 1
 */
void WriteLED(uint32_t ledId, uint8_t ledState);

/** set all of leds to off  */
void LEDInit();

#endif 
