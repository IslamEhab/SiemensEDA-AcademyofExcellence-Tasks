/********************************************************************************
 * @file          main.c
 * @brief         Source file for the main UART Task on TM4C123GH6PM
 * @date          16/8/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This task is on of the tasks in
 *                "SiemensEDA Academy of Excellence" Program
 *                from Eng.Sarah El-Dawy
 * @note          GPIO and System Control Drivers didn't implement due to lack
 *                of time, the whole concentration was on UART driver
 *
 *******************************************************************************/
#include "main.h"

/*****************************************************************************
                                    Global Variables
*****************************************************************************/
/* Variable used to wait until clock is stable */
volatile uint32 delay;
/* Variable used to receive the UART byte on it */
volatile uint8 ByteReceievd = 0;
/* UART configuration structure */
Uart_Config Uart0Configurations;
/***************************************************************************/


int main(void)
{
    /* UART0 Pins Configurations */
    Uart_PinsConfigurations();

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

    /* Uart Initialization */
    Uart_Init(&Uart0Configurations);

    /* Set Callback Function address */
    Uart0_SetCallBack(UART_ReceiveInterrupt);

    Uart_SendString(&Uart0Configurations, "Hello, Enter Character: \n\r");
    while(1)
    {
        /* Assembly instruction Puts in low power mode
         * while waiting for the next interrupt */
        Wait_For_Interrupt();
    }
	return 0;
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
