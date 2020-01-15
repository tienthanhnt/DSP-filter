#include "Init.h"

/*  This function initializes and enables asynchronous memory   
    banks in External Bus Interface Unit so that Flash A can be accessed. */

void Init_EBIU(void)
{
    *pEBIU_AMBCTL0  = 0x7bb07bb0;
    *pEBIU_AMBCTL1  = 0x7bb07bb0;
    *pEBIU_AMGCTL   = 0x000f;
}

/* This function initializes pin direction of Port A in Flash A
   to output.  The AD1836_RESET on the ADSP-BF533 EZ-KIT board is connected to Port A. */

void Init_Flash(void)
{
    *pFlashA_PortA_Dir = 0x1;
}


/* This function sets up the SPI port to configure the AD1836. 
   The content of the array sCodec1836TxRegs is sent to the    */

void Init1836(void)
{
    int i;
    int j;
    static unsigned char ucActive_LED = 0x01;
    
    *pFlashA_PortA_Data = 0x00;
    *pFlashA_PortA_Data = ucActive_LED;
    
    for (i=0; i<0xf000; i++) asm("nop;");

    *pSPI_FLG = FLS4;
    *pSPI_BAUD = 16;
    *pSPI_CTL = TIMOD_DMA_TX | SIZE | MSTR;
    *pDMA5_PERIPHERAL_MAP   = 0x5000;
    *pDMA5_CONFIG = WDSIZE_16;
    *pDMA5_START_ADDR = (void *)sCodec1836TxRegs;
    *pDMA5_X_COUNT = CODEC_1836_REGS_LENGTH;
    *pDMA5_X_MODIFY = 2;
    *pDMA5_CONFIG = (*pDMA5_CONFIG | DMAEN);
    *pSPI_CTL = (*pSPI_CTL | SPE);

    // wait until dma transfers for spi are finished 
    for (j=0; j<0xaff0; j++) asm("nop;");
    *pSPI_CTL = 0x0000;
}


/* Configure Sport0 for TDM mode, to transmit/receive data  
   to/from the AD1836. Configure Sport for external clocks and frame syncs */
void Init_Sport0(void)
{
    *pSPORT0_RCR1 = RFSR;
    *pSPORT0_RCR2 = SLEN_32;
    *pSPORT0_TCR1 = TFSR;
    *pSPORT0_TCR2 = SLEN_32;
    *pSPORT0_MTCS0 = 0x000000FF;
    *pSPORT0_MRCS0 = 0x000000FF;
    *pSPORT0_MCMC1 = 0x0000;
    *pSPORT0_MCMC2 = 0x101c;
}


// Initialize DMA1 in autobuffer mode to receive and DMA2 in autobuffer mode to transmit 
void Init_DMA(void)
{
    *pDMA1_PERIPHERAL_MAP = 0x1000;
    *pDMA1_CONFIG = WNR | WDSIZE_32 | DI_EN | FLOW_1;
    *pDMA1_START_ADDR = (void *)iRxBuffer1;
    *pDMA1_X_COUNT = 8;
    *pDMA1_X_MODIFY = 4; 
    *pDMA2_PERIPHERAL_MAP = 0x2000;
    *pDMA2_CONFIG = WDSIZE_32 | FLOW_1;
    *pDMA2_START_ADDR = (void *)iTxBuffer1;
    *pDMA2_X_COUNT = 8;
    *pDMA2_X_MODIFY = 4;
}


// Initialize Interrupt for Sport0 RX      
void Init_Sport_Interrupts(void)
{
    *pSIC_IAR0 = 0xffffffff;
    *pSIC_IAR1 = 0xffffff2f;
    *pSIC_IAR2 = 0xffffffff;
    register_handler(ik_ivg9, Sport0_RX_ISR);       
    *pSIC_IMASK = 0x00000200;
    ssync();
}

// Description: Enable DMA1, DMA2, Sport0 TX and Sport0 RX
void Enable_DMA_Sport0(void)
{
    *pDMA2_CONFIG   = (*pDMA2_CONFIG | DMAEN);
    *pDMA1_CONFIG   = (*pDMA1_CONFIG | DMAEN);
    *pSPORT0_TCR1   = (*pSPORT0_TCR1 | TSPEN);
    *pSPORT0_RCR1   = (*pSPORT0_RCR1 | RSPEN);
}


