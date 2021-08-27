/********************************************************************************
 * @headerfile    SSI_Priv.h
 * @brief         Header file for SSI Defines on TM4C123GH6PM Microcontroller
 * @date          23/8/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - uDMA Mode
 *                - Remaining Interrupts handling
 *                - FIFO Mode
 *******************************************************************************/


#ifndef DRIVERS_SSI_SSI_PRIV_H_
#define DRIVERS_SSI_SSI_PRIV_H_




/********************************************************************************
 *                                  Bits Defines                                *
 *******************************************************************************/

/************************** SSI_CR0 Register defines *****************************/
#define CR0_REG_DSS_POS            ((uint8)0x0)    /* SSI Data Size Select Bits Position            */
#define CR0_REG_FRF_POS            ((uint8)0x4)    /* SSI Frame Format Select Bits Position         */
#define CR0_REG_SPO_POS            ((uint8)0x6)    /* SSI Serial Clock Polarity Bit Position        */
#define CR0_REG_SPH_POS            ((uint8)0x7)    /* SSI Serial Clock Phase Bit Position           */
#define CR0_REG_SCR_POS            ((uint8)0x8)    /* SSI Serial Clock Rate Bits Position           */

#define CR0_REG_FRF_MASK           ((uint8)0x3)    /* SSI Frame Format Select Mask Value            */
#define CR0_REG_SPO_MASK           ((uint8)0x1)    /* SSI Serial Clock Polarity Mask Value          */
#define CR0_REG_SPH_MASK           ((uint8)0x1)    /* SSI Serial Clock Phase Mask Value             */
#define CR0_REG_SCR_MASK           ((uint8)0xFF)   /* SSI Serial Clock Rate Mask Value              */
#define CR0_REG_MASK               (uint16)0xFFFF  /* CR0 Register Mask Value                       */


/************************** SSI_CR1 Register defines *****************************/
#define CR1_REG_LBM_POS         ((uint8)0x0)    /* SSI Loopback Mode bit position                   */
#define CR1_REG_SSE_POS         ((uint8)0x1)    /* SSI Synchronous Serial Port Enable bit position  */
#define CR1_REG_MS_POS          ((uint8)0x2)    /* SSI Master/Slave Select bit position             */
#define CR1_REG_EOT_POS         ((uint8)0x4)    /* SSI End of Transmission bit position             */

#define CR1_REG_LBM_ENABLE      ((uint8)0x1)    /* SSI Loopback Mode Enable Value                   */
#define CR1_REG_SSE_ENABLE      ((uint8)0x1)    /* SSI Synchronous Serial Port Enable Value         */
#define CR1_REG_MS_ENABLE       ((uint8)0x1)    /* SSI Slave Enable Value (Master value = 0)        */
#define CR1_REG_EOT_ENABLE      ((uint8)0x1)    /* SSI End of Transmission Interrupt Enable Value   */


/************************** SSI_SR Register defines *****************************/
#define SR_REG_TFE_POS             ((uint8)0x0)     /* SSI Transmit FIFO Empty Bit position         */
#define SR_REG_TNF_POS             ((uint8)0x1)     /* SSI Transmit FIFO Not Full Bit position      */
#define SR_REG_RNE_POS             ((uint8)0x2)     /* SSI Receive FIFO Not Empty Bit position      */
#define SR_REG_RFF_POS             ((uint8)0x3)     /* SSI Receive FIFO Full Bit position           */
#define SR_REG_BSY_POS             ((uint8)0x4)     /* SSI Busy Bit position                        */

#define SR_REG_TFE_ENABLE          ((uint8)0x1)     /* The transmit FIFO is empty Value             */
#define SR_REG_TNF_ENABLE          ((uint8)0x1)     /* The transmit FIFO is not full  Value         */
#define SR_REG_RNE_ENABLE          ((uint8)0x1)     /* The receive FIFO is not empty Value          */
#define SR_REG_RFF_ENABLE          ((uint8)0x1)     /* The receive FIFO is full Value               */
#define SR_REG_BSY_ENABLE          ((uint8)0x1)     /* SSI is currently Transmitting or receiving   */

/************************** SSI_MIS Register defines *****************************/
#define MIS_REG_RORMIS_POS         ((uint8)0x0)    /* SSI Receive Overrun Masked Interrupt Status Bit Position */
#define MIS_REG_RTMIS_POS          ((uint8)0x1)    /* SSI Receive Overrun Masked Interrupt Status Bit Position */
#define MIS_REG_RXMIS_POS          ((uint8)0x2)    /* SSI Receive FIFO Masked Interrupt Status Bit Position */
#define MIS_REG_TXMIS_POS          ((uint8)0x3)    /* SSI Transmit FIFO Masked Interrupt Status Bit Position */

#define MIS_REG_RORMIS_ENABLE      ((uint8)0x1)    /* An unmasked interrupt was signaled due to receive FIFO overflowing Value */
#define MIS_REG_RTMIS_ENABLE       ((uint8)0x1)    /* An unmasked interrupt was signaled due to the receive time out Value */
#define MIS_REG_RXMIS_ENABLE       ((uint8)0x1)    /* An unmasked interrupt was signaled due to the receive FIFO being half full or more Value */
#define MIS_REG_TXMIS_ENABLE       ((uint8)0x1)    /* An unmasked interrupt was signaled due to the transmit FIFO being half empty or less
                                                      (if the EOT bit is clear) or due to the transmission of the last data bit (if the EOT bit is set).Value */

/************************** SSI_IM Register defines *****************************/
#define IM_REG_RORIM_POS           ((uint8)0x0)   /* SSI Receive Overrun Interrupt Mask Bit Position    */
#define IM_REG_RTIM_POS            ((uint8)0x1)   /* SSI Receive Time-Out Interrupt Mask Bit Position   */
#define IM_REG_RXIM_POS            ((uint8)0x2)   /* SSI Receive FIFO Interrupt Mask Bit Position       */
#define IM_REG_TXIM_POS            ((uint8)0x3)   /* SSI Transmit FIFO Interrupt Mask Bit Position      */

#define IM_REG_RORIM_ENABLE        ((uint8)0x1)   /* SSI Receive Overrun Interrupt Mask Enable Value    */
#define IM_REG_RTIM_ENABLE         ((uint8)0x1)   /* SSI Receive Time-Out Interrupt Mask Enable Value   */
#define IM_REG_RXIM_ENABLE         ((uint8)0x1)   /* SSI Receive FIFO Interrupt Mask Enable Value       */
#define IM_REG_TXIM_ENABLE         ((uint8)0x1)   /* SSI Transmit FIFO Interrupt Mask Enable Value      */



#endif /* DRIVERS_SSI_SSI_PRIV_H_ */
