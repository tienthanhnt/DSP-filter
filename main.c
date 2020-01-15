#include "Init.h"
#include "sysreg.h"
#include "ccblkfn.h"

// left input data from ad1836
int iChannel0LeftIn, iChannel1LeftIn;
// right input data from ad1836
int iChannel0RightIn, iChannel1RightIn;
// left ouput data for ad1836
int iChannel0LeftOut, iChannel1LeftOut;
// right ouput data for ad1836
int iChannel0RightOut, iChannel1RightOut;
// array for registers to configure the ad1836
// names are defined in "Talkthrough.h"
volatile short sCodec1836TxRegs[CODEC_1836_REGS_LENGTH] =
{
                    DAC_CONTROL_1   | 0x000,
                    DAC_CONTROL_2   | 0x000,
                    DAC_VOLUME_0    | 0x3ff,
                    DAC_VOLUME_1    | 0x3ff,
                    DAC_VOLUME_2    | 0x3ff,
                    DAC_VOLUME_3    | 0x3ff,
                    DAC_VOLUME_4    | 0x3ff,
                    DAC_VOLUME_5    | 0x3ff,
                    ADC_CONTROL_1   | 0x000,
                    ADC_CONTROL_2   | 0x180,
                    ADC_CONTROL_3   | 0x000

};
// SPORT0 DMA transmit buffer
volatile int iTxBuffer1[8];
// SPORT0 DMA receive buffer
volatile int iRxBuffer1[8];

volatile int filterIndex;

void main(void)
{
    adi_initComponents();
    sysreg_write(reg_SYSCFG, 0x32);
    Init_EBIU();
    Init_Flash();
    Init1836();
    Init_Sport0();
    Init_DMA();
    Init_Sport_Interrupts();
    Enable_DMA_Sport0();
    while(1);
}

