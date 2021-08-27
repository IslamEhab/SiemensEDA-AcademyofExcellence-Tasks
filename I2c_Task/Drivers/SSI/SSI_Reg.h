/********************************************************************************
 * @headerfile    SSI_Reg.h
 * @brief         Header file for SSI Registers on TM4C123GH6PM Microcontroller
 * @date          23/8/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - uDMA Mode
 *                - Remaining Interrupts handling
 *                - FIFO Mode
 *******************************************************************************/

#ifndef DRIVERS_SSI_SSI_REG_H_
#define DRIVERS_SSI_SSI_REG_H_

/*******************************************************************************
 *                         SSI(s) Registers Base Address                       *
 *******************************************************************************/
#define SSI_0_BASE_ADDRESS      0x40008000  /* SSI0 Base Address */
#define SSI_1_BASE_ADDRESS      0x40009000  /* SSI1 Base Address */
#define SSI_2_BASE_ADDRESS      0x4000A000  /* SSI2 Base Address */
#define SSI_3_BASE_ADDRESS      0x4000B000  /* SSI3 Base Address */
/*******************************************************************************/

/*******************************************************************************
 *                        SSI(s) Registers Offset Address                      *
 *******************************************************************************/
#define SSI_CR0_REG_OFFSET         0x000       /* SSI Control 0                    */
#define SSI_CR1_REG_OFFSET         0x004       /* SSI Control 1                    */
#define SSI_DR_REG_OFFSET          0x008       /* SSI Data                         */
#define SSI_SR_REG_OFFSET          0x00C       /* SSI Status                       */
#define SSI_CPSR_REG_OFFSET        0x010       /* SSI Clock Prescale               */
#define SSI_IM_REG_OFFSET          0x014       /* SSI Interrupt Mask               */
#define SSI_RIS_REG_OFFSET         0x018       /* SSI Raw Interrupt Status         */
#define SSI_MIS_REG_OFFSET         0x01C       /* SSI Masked Interrupt Status      */
#define SSI_ICR_REG_OFFSET         0x020       /* SSI Interrupt Clear              */
#define SSI_DMACTL_REG_OFFSET      0x024       /* SSI DMA Control                  */
#define SSI_CC_REG_OFFSET          0xFC8       /* SSI Clock Configuration          */
#define SSI_PERIPHID4_REG_OFFSET   0xFD0       /* SSI Peripheral Identification 4  */
#define SSI_PERIPHID5_REG_OFFSET   0xFD4       /* SSI Peripheral Identification 5  */
#define SSI_PERIPHID6_REG_OFFSET   0xFD8       /* SSI Peripheral Identification 6  */
#define SSI_PERIPHID7_REG_OFFSET   0xFDC       /* SSI Peripheral Identification 7  */
#define SSI_PERIPHID0_REG_OFFSET   0xFE0       /* SSI Peripheral Identification 0  */
#define SSI_PERIPHID1_REG_OFFSET   0xFE4       /* SSI Peripheral Identification 1  */
#define SSI_PERIPHID2_REG_OFFSET   0xFE8       /* SSI Peripheral Identification 2  */
#define SSI_PERIPHID3_REG_OFFSET   0xFEC       /* SSI Peripheral Identification 3  */
#define SSI_CELLID0_REG_OFFSET     0xFF0       /* SSI PrimeCell Identification 0   */
#define SSI_CELLID1_REG_OFFSET     0xFF4       /* SSI PrimeCell Identification 1   */
#define SSI_CELLID2_REG_OFFSET     0xFF8       /* SSI PrimeCell Identification 2   */
#define SSI_CELLID3_REG_OFFSET     0xFFC       /* SSI PrimeCell Identification 3   */





/*******************************************************************************
 *                   System Control SSI Enable Clock Register                  *
 *******************************************************************************/
#define SYSCTL_RCGCSSI_REG  (*((volatile unsigned long*)0x400FE61C))

#endif /* DRIVERS_SSI_SSI_REG_H_ */
