/********************************************************************************
 * @file          main.c
 *
 * @brief         Source file for the main SSI Task on TM4C123GH6PM
 *
 * @date          16/8/2021
 *
 * @author        Islam Ehab Ezzat
 *
 * @version       1.0.0
 *
 * @note          This task is on of the tasks in
 *                "SiemensEDA Academy of Excellence" Program
 *                from Eng.Sarah El-Dawy
 *
 * @note          GPIO and System Control Drivers didn't implement due to lack
 *                of time, the whole concentration was on UART & SSI drivers
 *
 * @note          To test SSI Driver, it operates in "LoopBack" mode,
 *                Which connects the Transmit buffer (internally) to the receive
 *                buffer
 *                For some reasons in this mode "LoobBack" the interrupt receive
 *                didn't operate maybe because the receive buffer in LoopBack mode
 *                isn't connected to Interrupt controller of SSI module.
 *
 * @note          Tested using Polling Mode for receiving because interrupt receiving
 *                didn't operate.
 *******************************************************************************/
#include "main.h"


/*****************************************************************************
                                    Global Variables
*****************************************************************************/
/* Variable used to wait until clock is stable */
volatile uint32 delay;
/* Variable used to receive the UART byte on it */
volatile uint8 ByteReceievd = 0;
/* Variable used to receive the SSI byte on it */
volatile uint8 SsiByteReceived = 0;
/* UART configuration structure */
Uart_Config Uart0Configurations;
/* SSI configuration structure */
Ssi_Config SsiConfigurations;
/***************************************************************************/



int main(void)
{
    /* Variable used to increment and send to SSI */
    uint8 Var = 'A';

    /* UART0 Pins Configurations */
    Uart_PinsConfigurations();

    /* SSI0 Pins Configurations */
    Ssi_PinsConfigurations();

    /* Enable Global Interrupt */
    Enable_Interrupts();

    /********************** UART0 Configurations **********************/
    /**             Clock    = System Clock Default 16MHz             *
     *                  BaudRate = 9600 Symbol/sec                    *
     *                          1 Stop bit                            *
     *                           No Parity                            *
     *                   Receive Interrupt Enable                     *
     *                       FIFO Mode Disabled                       *
     ******************************************************************/
    Uart0Configurations.UartNum         = Uart0;
    Uart0Configurations.WordLength      = EightBits;
    Uart0Configurations.UartInterrupts  = InterruptMaskReceive;
    Uart0Configurations.ClkValue        = 16000000;
    Uart0Configurations.BaudRate        = 9600;
    Uart0Configurations.StopBits        = STOP_BITS_1_BIT;
    Uart0Configurations.ParityMode      = PARITY_MODE_DISABLE;
    Uart0Configurations.FifoMode        = FIFO_MODE_DISABLE;
    Uart0Configurations.ClkSrc          = CLOCK_SRC_SYSTEM;


    /********************** Ssi0 Configurations **********************/
    /** Clock            : System Clock Default 16MHz                 *
     *  SSI0 Freq        : 1.6 MHz                                    *
     *  SSI0 Frame Format: FreeScale SPI                              *
     *  Clock Phase      : Rising Edge Capturing Data                 *
     *  Clock Polarity   : Low in idle state                          *
     *  Interrupt Mode   : No Interrupts                              *
     *  SSI Mode         : Master in LoopBack mode (For Testing)      *
     *  SSI WordLength   : 8 bits                                     *
     ******************************************************************/

    SsiConfigurations.SsiNum           = Ssi0;
    SsiConfigurations.WordLength       = SsiEightBits;
    SsiConfigurations.SsiInterrupts    = SsiInterruptsDisabled;
    SsiConfigurations.ClkValue         = 16000000;
    SsiConfigurations.SsiFreq          = 1600000;
    SsiConfigurations.ClkSrc           = SSI_CLOCK_SRC_SYSTEM;
    SsiConfigurations.SsiClkPhase      = SSI_CLOCK_PHASE_RISING;
    SsiConfigurations.SsiClkPolarity   = SSI_CLOCK_POLARITY_LOW;
    SsiConfigurations.SsiFrameFormat   = SSI_FRAME_FORMAT_FREESCALE_SSI;
    SsiConfigurations.SsiMode          = (SSI_MODE_LOOPBACK|SSI_MODE_MASTER);

    /* Uart Initialization */
    Uart_Init(&Uart0Configurations);

    /* Set Callback Function address */
    Uart0_SetCallBack(UART_ReceiveInterrupt);

    /* SSI Initialization */
    Ssi_Init(&SsiConfigurations);

    while(1)
    {
        Ssi_Transmit(&SsiConfigurations, (Var));
        Var +=1;
        SsiByteReceived = Ssi_Receive(&SsiConfigurations);
        Uart_SendString(&Uart0Configurations, "\n Byte Received from SSI is: ");
        Uart_Transmit(&Uart0Configurations, (SsiByteReceived));
        Uart_SendString(&Uart0Configurations, "\r\n ");
        Delay_MS(500);


    }
}


/*******************************************************************************
 * @fn              static void Uart_PinsConfigurations(void)
 * @brief           Function to initialize UART0:
 *                  - Initialize Pins Alternative functions (PA0->Rx, PA1 -> Tx)
 *                  - Enable Clock For GPIOA and UART0
 *                  - Enable Interrupt for UART0 from NVIC EN0 Register
 *                    because UART will work with receive interrupt
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
static void Uart_PinsConfigurations(void)
{
    /* Enable UART0 Clock (First Bit in Register)*/
    SYSCTL_REGCGC1_REG |= (1 << 0);
    /* Dummy operation to give clock time to start */
    delay = SYSCTL_REGCGC1_REG;

    /* Enable GPIOA Clock (First Bit in Register)*/
    SYSCTL_REGCGC2_REG |= (1 << 0);
    /* Dummy operation to give clock time to start */
    delay = SYSCTL_REGCGC2_REG;

    /* Set GPIO AFSEL Bits for Pins 0 and 1 */
    GPIO_PORTA_AFSEL_REG = ( (1<<1) | (1<<0) );

    /* Configure GPIO PCTL bits to select Pin 0 and 1 as UART */
    GPIO_PORTA_PCTL_REG = ( (1<<0) | (1<<4) );

    /* Enable Corresponding bits in Digital Enable Register */
    GPIO_PORTA_DEN_REG = ( (1<<0) | (1<<1) );

    /* Enable UART Interrupt from NVIC EN0 */
    NVIC_EN0_REG |= (1<<5);
}

/*******************************************************************************
 * @fn              static void Ssi_PinsConfigurations(void)
 * @brief           Function to initialize SSI0:
 *                  - Initialize Pins Alternative functions
 *                  (PA2->Clk, PA3 -> Fss(Chip Select),
 *                   PA4 -> Rx(MISO), PA3 ->Tx(MOSI)
 *                  - Enable Clock For GPIOA
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
static void Ssi_PinsConfigurations(void)
{
    /* Enable GPIOA Clock (First Bit in Register)*/
    SYSCTL_REGCGC2_REG |= ( (1 << 0) );

    /* Dummy operation to give clock time to start */
    delay = SYSCTL_REGCGC2_REG;

    /*************** SSI0 Pins Assignment *************/
    /* Set GPIO AFSEL Bits for Pins 2,3,4 and 5 */
    GPIO_PORTA_AFSEL_REG |= ( (1<<2) | (1<<3) | (1<<4) | (1<<5) );

    /* Configure GPIO PCTL bits to select Pin 2,3,4 and 5 as SSI (Alternative Function 2)*/
    GPIO_PORTA_PCTL_REG  |= ( (2<<8) | (2<<12)  | (2<<16) | (2<<20));

    /* Enable Corresponding bits in Digital Enable Register */
    GPIO_PORTA_DEN_REG   |= ( (1<<2) | (1<<3) | (1<<4) | (1<<5) );
}

/*******************************************************************************
 * @fn              void UART_ReceiveInterrupt(void)
 * @brief           Function to interact with UART Interrupt (Function that
 *                  called by the call back technique)
 * @param (in):     None
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void UART_ReceiveInterrupt(void)
{
    /* Receive the byte */
    ByteReceievd = Uart_ReceiveIT(&Uart0Configurations);

    /* Print New Line */
    Uart_SendString(&Uart0Configurations, "\r\n");
    /* CHeck if the received byte is a character that can be displayed */
    if( (ByteReceievd>= '!') && (ByteReceievd<= '~') )
    {
        /* Check if the received char is an small alphabetical char */
        if( (ByteReceievd>= 'a') && (ByteReceievd<= 'z') )
        {
            /* Subtract 32 (ASCII of 0) to Display the capital letter */
            ByteReceievd-=32;

            /* Send back the Capital Letter */
            Uart_Transmit(&Uart0Configurations, ByteReceievd);
        }
        /* The received char is '~', if we add 1 to it
         * the ASCII will be DEL which cannot be displayed on terminal
         * so if '~' is sent, Display a error msg */
        else if(ByteReceievd == '~')
        {
            Uart_SendString(&Uart0Configurations, "~ Doesn't have a successive letter");
        }
        /* The received char isn't a small alphabetical letter.
         * Display the successive letter of the sent one*/
        else{
            ByteReceievd+=1;
            /* Send back the Successive Letter */
            Uart_Transmit(&Uart0Configurations, ByteReceievd);
        }
    }
    /* Print New Line */
    Uart_SendString(&Uart0Configurations, "\r\n");

}

/*******************************************************************************
 * @fn              void Delay_MS(unsigned long n)
 * @brief           Function used to delay the processor (Not efficient way)
 * @param (in):     n : Number of milliseconds that the processor will wait
 * @param (out):    None
 * @param (inout):  None
 * @return          None
 *******************************************************************************/
void Delay_MS(unsigned long n)
{
    volatile unsigned long count = 0;
    while(count++ < (NUMBER_OF_ITERATIONS_PER_ONE_MILI_SECOND * n) );
}
