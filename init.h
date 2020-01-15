#ifndef  __Init_DEFINNED
    #define __Init_DEFINED

#include <sys\exception.h>
#include <cdefBF533.h>
#include <ccblkfn.h>
#include <sysreg.h>

// Macro addresses for Port B in Flash A
#define pFlashA_PortA_Dir   (volatile unsigned char *)0x20270006
#define pFlashA_PortA_Data  (volatile unsigned char *)0x20270004

// Names for ad1836 audio codec registers on Kit
#define DAC_CONTROL_1       0x0000
#define DAC_CONTROL_2       0x1000
#define DAC_VOLUME_0        0x2000
#define DAC_VOLUME_1        0x3000
#define DAC_VOLUME_2        0x4000
#define DAC_VOLUME_3        0x5000
#define DAC_VOLUME_4        0x6000
#define DAC_VOLUME_5        0x7000
#define ADC_0_PEAK_LEVEL    0x8000
#define ADC_1_PEAK_LEVEL    0x9000
#define ADC_2_PEAK_LEVEL    0xA000
#define ADC_3_PEAK_LEVEL    0xB000
#define ADC_CONTROL_1       0xC000
#define ADC_CONTROL_2       0xD000
#define ADC_CONTROL_3       0xE000

// names for slots in ad1836 audio frame
#define INTERNAL_ADC_L0         0
#define INTERNAL_ADC_L1         1
#define INTERNAL_ADC_R0         4
#define INTERNAL_ADC_R1         5
#define INTERNAL_DAC_L0         0
#define INTERNAL_DAC_L1         1
#define INTERNAL_DAC_L2         2
#define INTERNAL_DAC_R0         4
#define INTERNAL_DAC_R1         5
#define INTERNAL_DAC_R2         6

// size of array codec register
#define CODEC_1836_REGS_LENGTH  11

// SPI transfer mode on BF533 chip
#define TIMOD_DMA_TX 0x0003

// SPORT0 word length
#define SLEN_32 0x001f

// DMA flow mode
#define FLOW_1  0x1000

/****** Global variables ******/                                                        

extern int iChannel0LeftIn;
extern int iChannel0RightIn;
extern int iChannel0LeftOut;
extern int iChannel0RightOut;
extern int iChannel1LeftIn;
extern int iChannel1RightIn;
extern int iChannel1LeftOut;
extern int iChannel1RightOut;
extern volatile short sCodec1836TxRegs[];
extern volatile int iRxBuffer1[];
extern volatile int iTxBuffer1[];

/***** Peripheral Handle function ******/                                                               

void Init_EBIU(void);
void Init_Flash(void);
void Init1836(void);
void Init_Sport0(void);
void Init_DMA(void);
void Init_Sport_Interrupts(void);
void Enable_DMA_Sport(void);
void Enable_DMA_Sport0(void);

// Process data function
void Process_Data(void);

// Interrupt handle function
EX_INTERRUPT_HANDLER(Sport0_RX_ISR);

#endif

