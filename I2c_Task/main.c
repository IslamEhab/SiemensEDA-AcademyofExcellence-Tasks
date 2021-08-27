
/********************************************************************************
 * @file          main.c
 *
 * @brief         Source file for the main I2C Task on TM4C123GH6PM
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
 * @note          To test I2C Driver, it operates in "LoopBack" mode,
 *                the SDA and SCL signals from the master and are tied to the
 *                SDA and SCL signals of the slave module
 *
 * @note          This driver still under testing
 *******************************************************************************/

#include "I2C_Init.h"
#include "main.h"

int main(void)
{
    /* Variable used to wait until clock is stable */
    volatile uint32 delay;
    volatile uint8 ByteReceievd = 0;
    uint8 Var = 'A';
    I2c_Config  I2cConfigurations;

    /* Enable GPIOA & GPIOB Clock (First Bit in Register)*/
    SYSCTL_REGCGC2_REG |= ( (1 << 0) | (1<<1));
    /* Dummy operation to give clock time to start */
    delay = SYSCTL_REGCGC2_REG;

    /*************** I2C0 Pins Assignment *************/
    /* Set GPIO AFSEL Bits for Pins 2 and 3*/
    GPIO_PORTB_AFSEL_REG |= ( (1<<2) | (1<<3) );

    /* Enable SDA Pin (PB3) as Open Drain */
    GPIO_PORTB_ODR_REG |= (1<<3);

    /* Configure GPIO PCTL bits to select Pin 2,3 as I2C (Alternative Function 3)*/
    GPIO_PORTB_PCTL_REG  |= ( (3<<8) | (3<<12) );

    /********************** I2C Configurations **********************/
    I2cConfigurations.I2cNum           = I2c0;
    I2cConfigurations.I2cInterrupts    = I2cInterruptsDisabled;
    I2cConfigurations.ClkValue         = 16000000;
    I2cConfigurations.I2cFreq          = 100000;    /* 100 Kbps */
    I2cConfigurations.I2cMode          = (I2C_MODE_MASTER | I2C_MODE_SLAVE |I2C_MODE_LOOPBACK); /* Slave Mode enabled for LoopBack Debugging */
    I2cConfigurations.I2cTransmitMode  = I2C_TRANSMIT_MODE_SINGLE;
    I2cConfigurations.I2cSlaveAddress  = 0x1;

    /* I2C Initialization */
    I2c_Init(&I2cConfigurations);


    while(1)
    {
        I2c_Transmit(&I2cConfigurations, &Var, 1);
        Var+=1;
        I2cConfigurations.I2cMode = 0;
        I2cConfigurations.I2cMode = I2C_MODE_SLAVE;
        I2c_Receive(&I2cConfigurations, (uint8*)&ByteReceievd, 1);
    }
    return 0;
}
