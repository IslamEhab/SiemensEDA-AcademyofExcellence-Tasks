/********************************************************************************
 * @headerfile    I2C_Priv.h
 * @brief         Header file for I2C Defines on TM4C123GH6PM Microcontroller
 * @date          25/8/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - Remaining Interrupts handling
 *******************************************************************************/

#ifndef DRIVERS_I2C_I2C_PRIV_H_
#define DRIVERS_I2C_I2C_PRIV_H_

/********************************************************************************
 *                                  Bits Defines                                *
 *******************************************************************************/

/************************** I2C_MCR Register defines *****************************/
#define MCR_REG_LPBK_POS           ((uint8)0x0)    /* I2C LoopBack Bit Position                 */
#define MCR_REG_MFE_POS            ((uint8)0x4)    /* I2C Master Function Enable Bit Position   */
#define MCR_REG_SFE_POS            ((uint8)0x5)    /* I2C Slave Function Bit Position           */
#define MCR_REG_GEF_POS            ((uint8)0x6)    /* I2C Glitch Filter Enable Bit Position     */

#define MCR_REG_LBPK_ENABLE        ((uint8)0x1)    /* LoopBack mode Enable Value                */
#define MCR_REG_MFE_ENABLE         ((uint8)0x1)    /* I2C Master Function Enable Enable Value   */
#define MCR_REG_SFE_ENABLE         ((uint8)0x1)    /* I2C Master Function Enable value          */
#define MCR_REG_GEF_ENABLE         ((uint8)0x1)    /* I2C Glitch Filter Enable Enable Value     */

/************************** I2C_MTPR Register defines *****************************/
#define MTPR_REG_HS_POS            ((uint8)0x7)    /* High Speed Enable Bit Position */

#define MTPR_REG_HS_ENABLE         ((uint8)0x1)    /* High Speed Enable Value*/

/********************* I2C_MCS Register defines (ReadOnly) ************************/
#define MCR_REG_BUSY_POS           ((uint8)0x0)    /* I2C Busy Bit Position                     */
#define MCR_REG_ERROR_POS          ((uint8)0x1)    /* Error Bit Position                        */
#define MCR_REG_ADRACK_POS         ((uint8)0x2)    /* Acknowledge Address Bit Position          */
#define MCR_REG_DATACK_POS         ((uint8)0x3)    /* Acknowledge Data Bit Position             */
#define MCR_REG_ARBLST_POS         ((uint8)0x4)    /* Arbitration Lost Bit Position             */
#define MCR_REG_IDLE_POS           ((uint8)0x5)    /* I2C Idle Bit Position                     */
#define MCR_REG_BUSBSY_POS         ((uint8)0x6)    /* Bus Busy Bit Position                     */
#define MCR_REG_CLKTO_POS          ((uint8)0x7)    /* Clock Timeout Error Bit Position          */

#define MCR_REG_BUSY_ENABLE        ((uint8)0x1)    /* The controller is busy                    */
#define MCR_REG_ERROR_ENABLE       ((uint8)0x1)    /* An error occurred on the last operation   */
#define MCR_REG_ADRACK_ENABLE      ((uint8)0x1)    /* Transmitted address was not acknowledged  */
#define MCR_REG_DATACK_ENABLE      ((uint8)0x1)    /* The transmitted data was not acknowledged.*/
#define MCR_REG_ARBLST_ENABLE      ((uint8)0x1)    /* The I2C controller lost arbitration       */
#define MCR_REG_IDLE_ENABLE        ((uint8)0x1)    /* The I2C controller is idle.               */
#define MCR_REG_BUSBSY_ENABLE      (uint8)0x1)     /* The I2C bus is busy.                      */
#define MCR_REG_CLKTO_ENABLE       ((uint8)0x1)    /* The clock timeout error has occurred      */

/********************* I2C_MCS Register defines (WriteOnly) ************************/
#define MCR_REG_RUN_POS            ((uint8)0x0)    /* I2C Master Enable Bit Position            */
#define MCR_REG_START_POS          ((uint8)0x1)    /* Generate START Bit Position               */
#define MCR_REG_STOP_POS           ((uint8)0x2)    /* Generate STOP Bit Position                */
#define MCR_REG_ACK_POS            ((uint8)0x3)    /* Data Acknowledge Enable Bit Position      */
#define MCR_REG_HS_POS             ((uint8)0x4)    /* High-Speed Enable Bit Position            */

#define MCR_REG_RUN_ENABLE         ((uint8)0x1)    /* Master is able to transmit|receive data   */
#define MCR_REG_START_ENABLE       ((uint8)0x1)    /* Controller generates START/repeated START */
#define MCR_REG_STOP_ENABLE        ((uint8)0x1)    /* Controller generates the STOP Condition   */
#define MCR_REG_ACK_ENABLE         ((uint8)0x1)    /* Received data byte is ACK auto by Master  */
#define MCR_REG_HS_ENABLE          ((uint8)0x1)    /* The master operates in High-Speed mode    */

/************************** I2C_MMIS Register defines *****************************/
#define MMIS_REG_MIS_POS           ((uint8)0x0)    /* Masked Interrupt Status Bit Position       */
#define MMIS_REG_CLKMIS_POS        ((uint8)0x1)    /* Clock Timeout Interrupt Status Bit Position*/

#define MMIS_REG_MIS_ENABLE        ((uint8)0x1)    /* An unmasked master interrupt was signaled and is pending        */
#define MMIS_REG_CLKMIS_ENABLE     ((uint8)0x1)    /* An unmasked clock timeout interrupt was signaled and is pending */



/********************* I2C_SCSR Register defines (ReadOnly) ************************/
#define SCSR_REG_RREQ_POS          ((uint8)0x0)     /* Receive Request Bit Position             */
#define SCSR_REG_TREQ_POS          ((uint8)0x1)     /* Transmit Request Bit Position            */
#define SCSR_REG_FBR_POS           ((uint8)0x2)     /* First Byte Received Bit Position         */
#define SCSR_REG_QAR2SEL_POS       ((uint8)0x3)     /* OAR2 Address Matched Bit Position        */

#define SCSR_REG_RREQ_ENABLE       ((uint8)0x1)     /* Outstanding Transmit Request as slave    */
#define SCSR_REG_TREQ_ENABLE       ((uint8)0x1)     /* Outstanding Transmit Request as slave    */
#define SCSR_REG_FBR_ENABLE        ((uint8)0x1)     /* First byte after slave' address received */
#define SCSR_REG_QAR2SEL_ENABLE    ((uint8)0x1)     /* OAR2 address matched & ACKed by slave    */


/********************* I2C_SCSR Register defines (WriteOnly) ************************/
#define SCSR_REG_DA_POS              ((uint8)0x0)     /* Device Active Bit Position             */

#define SCSR_REG_DA_ENABLE           ((uint8)0x1)     /* Enables the I2C slave operation.       */


/************************** I2C_SIMR Register defines *****************************/
#define SIMR_REG_DATAMIS_POS         ((uint8)0x0)     /* Data Interrupt Mask Bit Position */
#define SIMR_REG_STARTMIS_POS        ((uint8)0x1)     /* Start Condition Interrupt Mask Bit Position */
#define SIMR_REG_STOPMIS_POS         ((uint8)0x2)     /* Stop Condition Interrupt Mask Bit Position */

#define SIMR_REG_DATAMIS_ENABLE      ((uint8)0x1)     /* The data received or requested interrupt is sent to the interrupt controller */
#define SIMR_REG_STARTMIS_ENABLE     ((uint8)0x1)     /* The START condition interrupt is sent to the interrupt controller */
#define SIMR_REG_STOPMIS_ENABLE      ((uint8)0x1)     /* The STOP condition interrupt is sent to the interrupt controller */

/********************************************************************************
 *                           Preprocessor Macros                                *
 *******************************************************************************/
#define SCL_LP_NORMAL               ((uint8)0x6)     /* SCL_LP Value in Standard, Fast and FastPlus Modes */
#define SCL_LP_HIGH_SPEED           ((uint8)0x2)     /* SCL_LP Value in High Speed Mode */
#define SCL_HP_NORMAL               ((uint8)0x4)     /* SCL_HP Value in Standard, Fast and FastPlus Modes */
#define SCL_HP_HIGH_SPEED           ((uint8)0x1)     /* SCL_HP Value in High Speed Mode */
#define ONE_MEGA_HERTZ_CLK_VALUE    ((uint32)1000000)/* 1 MHz Clock Value  */



#endif /* DRIVERS_I2C_I2C_PRIV_H_ */
