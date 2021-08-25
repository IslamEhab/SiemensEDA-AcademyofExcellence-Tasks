/********************************************************************************
 * @headerfile    SSI_Init.h
 * @brief         Header file for SSI module on TM4C123GH6PM Microcontroller
 * @date          23/8/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - uDMA Mode
 *                - Remaining Interrupts handling
 *                - FIFO Mode
 *******************************************************************************/

#ifndef DRIVERS_SSI_SSI_INIT_H_
#define DRIVERS_SSI_SSI_INIT_H_

#include "std_types.h"
#include "common_macros.h"


/*******************************************************************************
 *                     Defines used in Ssi_Config Variables                   *
 *******************************************************************************/
/* Define used to choose which mode is the SPI is operating with */
#define SSI_MODE_MASTER                 0x00
#define SSI_MODE_LOOPBACK               0x01    /* Output of the transmit serial shift register is connected internally to the input of the receive serial shift register */
#define SSI_MODE_SLAVE_OUTPUT_ENABLED   0x04
#define SSI_MODE_SLAVE_OUTPUT_DISABLED  0x0C

/* Define used to choose SSI Clock source                       */
#define SSI_CLOCK_SRC_SYSTEM            0x00
#define SSI_CLOCK_SRC_PIOSC             0X05

/* Define used to choose SSI Clock Polarity                     */
#define SSI_CLOCK_POLARITY_LOW          0x00    /* Clock Value during idle state is LOW     */
#define SSI_CLOCK_POLARITY_HIGH         0x01    /* Clock Value during idle state is HIGH    */

/* Define used to choose SSI Clock Phase                        */
#define SSI_CLOCK_PHASE_RISING          0x00    /* Data is captured on the RISING  edges of clock and propagated on the FALLING edges */
#define SSI_CLOCK_PHASE_FALLING         0x01    /* Data is captured on the FALLING edges of clock and propagated on the RISING edges  */

/* Define used to choose SSI Frame Format                       */
#define SSI_FRAME_FORMAT_FREESCALE_SSI  0x00
#define SSI_FRAME_FORMAT_TI_SSI         0x01
#define SSI_FRAME_FORMAT_MICROWIRE      0x02




/*******************************************************************************
 *                              User Defined Data Types                        *
 *******************************************************************************/
/*******************************************************************************
 * @enum    Ssi_Instance
 * @brief   Enum Holds SSI Instances in TM4C123GH6PM
 *******************************************************************************/
typedef enum{
    Ssi0,//!< Ssi0
    Ssi1,//!< Ssi1
    Ssi2,//!< Ssi2
    Ssi3 //!< Ssi3
}Ssi_Instance;

/*******************************************************************************
 * @enum    Ssi_WordLength
 * @brief   Enum holds Word length for SSI Tx/Rx
 ******************************************************************************/

typedef enum{
    SsiFourBits    = 0x3,//!< FourBits
    SsiFiveBits    = 0x4,//!< FiveBits
    SsiSixBits     = 0x5,//!< SixBits
    SsiSevenBits   = 0x6,//!< SevenBits
    SsiEightBits   = 0x7,//!< EightBits
    SsiNineBits    = 0x8,//!< NineBits
    SsiTenBits     = 0x9,//!< TenBits
    SsiElevenBits  = 0xA,//!< ElevenBits
    SsiTwelveBits  = 0xB,//!< TwelveBits
    SsiThirteenBits= 0xC,//!< ThirteenBits
    SsiFourteenBits= 0xD,//!< FourteenBits
    SsiFifteenBits = 0xE,//!< FifteenBits
    SsiSixteenBits = 0xF,//!< SixteenBits
}Ssi_WordLength;

/*******************************************************************************
 * @enum    Ssi_Interrupts
 * @brief   Enum Holds interrupt bits location in the register
 *******************************************************************************/

typedef enum{

    SsiInterruptsDisabled,                      //!< SsiInterruptsDisabled
    SsiInterruptMaskReceiveOverRun      = (1<<0),//!< SsiInterruptMaskReceiveOverRun
    SsiInterruptMaskReceiveTimeOut      = (1<<1),//!< SsiInterruptMaskReceiveTimeOut
    SsiInterruptMaskReceiveFIFO         = (1<<2),//!< SsiInterruptMaskReceiveFIFO
    SsiInterruptMaskTransmitFIFO        = (1<<3),//!< SsiInterruptMaskTransmitFIFO
    SsiInterruptMaskEndofTransmission   = (1<<4)//!< SsiInterruptMaskEndofTransmission
}Ssi_Interrupts;

/*******************************************************************************
 * @struct  Ssi_Config
 *
 * @brief   Structure Holds SSI Configuration Parameters
 *
 * @var     Ssi_Config::SsiNum
 *          Member 'SsiNum' used to indicate which SSI needs to be configured
 *          You can find its value @ref Ssi_Instance
 *
 * @var     Ssi_Config::WordLength
 *          Member 'WordLength' used to decide how many bits needed for SSI Tx/Rx
 *          You can find this value @ref Ssi_WordLength
 *
 * @var     Ssi_Config::SsiInterrupts
 *          Member 'UartInterrupts' used to choose Interrupts enabled from SSI
 *          module or disable all interrupts
 *          You can find this value @ref Ssi_Interrupts
 *
 * @var     Ssi_Config::SsiFreq
 *          Member 'SsiFreq' used to indicate the Required frequency needed
 *          for SSI to operate with
 *
 * @var     Ssi_Config::SsiFreq
 *          Member 'ClkValue' used to calculate the required Frequency for SSI
 *          @note This value should given by a API used to
 *          get system clk (Future work)
 *
 * @var     Ssi_Config::SsiMode
 *          Member 'SsiMode' used to choose which mode is the SPI is operating
 *          with (Master, Slave)
 *          You can find this value @ref SSI_MODE
 *
 * @var     Ssi_Config::ClkSrc
 *          Member 'ClkSrc' used to decide what is SSI clock source (system clk or PIOSC)
 *          You can find this value @ref SSI_CLOCK_SRC
 *
 * @var     Ssi_Config::SsiClkPolarity
 *          Member 'SsiClkPolarity' used to choose SSI Clock Polarity
 *          (Clock value during idle state)
 *          You can find this value @ref SSI_CLOCK_POLARITY
 *
 * @var     Ssi_Config::SsiClkPhase
 *          Member 'SsiClkPhase' used to choose SSI Clock Phase
 *          (Data is captured at which edge)
 *          You can find this value @ref SSI_CLOCK_PHASE
 *
 * @var     Ssi_Config::SsiFrameFormat
 *          Member 'SsiFrameFormat' used to choose SSI Frame Format
 *          You can find this value @ref SSI_FRAME_FORMAT
 *******************************************************************************/
typedef struct{

    Ssi_Instance    SsiNum;             /** Member 'SsiNum' used to indicate which SSI
                                            needs to be configured
                                            You can find its value @ref Ssi_Instance            */

    Ssi_WordLength  WordLength;         /** Member 'WordLength' used to decide how many
                                            bits needed for SSI Tx/Rx
                                            You can find this value @ref Ssi_WordLength         */

    Ssi_Interrupts  SsiInterrupts;      /** Member 'UartInterrupts' used to choose
                                            Interrupts enabled from SSI module or disable
                                            all interrupts
                                            You can find this value @ref Ssi_Interrupts  */

    uint32          SsiFreq;            /** Member 'SsiFreq' used to indicate the
                                            Required frequency needed for SSI to operate with   */

    uint32          ClkValue;           /** Member 'ClkValue' used to calculate the
                                            required Frequency for SSI
                                            @note This value should given by a API used to
                                            get system clk (Future work)                  */


    uint8           SsiMode;            /** Member 'SsiMode' used to choose which mode
                                            is the SPI is operating with (Master, Slave)
                                            You can find this value @ref SSI_MODE               */

    uint8           ClkSrc;             /** Member 'ClkSrc' used to decide what is SSI
                                            clock source (system clk or PIOSC)
                                            You can find this value @ref SSI_CLOCK_SRC          */

    uint8           SsiClkPolarity;     /** Member 'SsiClkPolarity' used to choose SSI
                                            Clock Polarity (Clock value during idle state)
                                            You can find this value @ref SSI_CLOCK_POLARITY     */

    uint8           SsiClkPhase;        /** Member 'SsiClkPhase' used to choose SSI
                                            Clock Phase (Data is captured at which edge)
                                            You can find this value @ref SSI_CLOCK_PHASE        */

    uint8           SsiFrameFormat;     /** Member 'SsiFrameFormat' used to choose
                                            SSI Frame Format
                                            You can find this value @ref SSI_FRAME_FORMAT       */

}Ssi_Config;

/*******************************************************************************
 *                              Functions Prototypes                          *
 *******************************************************************************/
void   Ssi0_SetCallBack(void (*f_ptr)(void));
void   Ssi1_SetCallBack(void (*f_ptr)(void));
void   Ssi2_SetCallBack(void (*f_ptr)(void));
void   Ssi3_SetCallBack(void (*f_ptr)(void));
uint8  Ssi_Init        (const Ssi_Config* ConfigPtr);
uint8  Ssi_Transmit    (const Ssi_Config* ConfigPtr, const uint16 Data);
void   Ssi_SendString  (const Ssi_Config* ConfigPtr, const uint8* String);
uint16 Ssi_Receive     (const Ssi_Config* ConfigPtr);
uint16 Ssi_ReceiveIT   (const Ssi_Config* ConfigPtr);





#endif /* DRIVERS_SSI_SSI_INIT_H_ */
