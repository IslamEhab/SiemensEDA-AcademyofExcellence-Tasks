/********************************************************************************
 * @headerfile    I2C_Reg.h
 * @brief         Header file for I2C Registers on TM4C123GH6PM Microcontroller
 * @date          25/8/2021
 * @author        Islam Ehab Ezzat
 * @version       1.0.0
 * @note          This driver still under development, so it doesn't support:
 *                - uDMA Mode
 *                - Remaining Interrupts handling
 *******************************************************************************/


#ifndef DRIVERS_I2C_I2C_REG_H_
#define DRIVERS_I2C_I2C_REG_H_

/*******************************************************************************
 *                         I2C(s) Registers Base Address                       *
 *******************************************************************************/
#define I2C_0_BASE_ADDRESS      0x40020000  /* I2C0 Base Address */
#define I2C_1_BASE_ADDRESS      0x40021000  /* I2C1 Base Address */
#define I2C_2_BASE_ADDRESS      0x40022000  /* I2C2 Base Address */
#define I2C_3_BASE_ADDRESS      0x40023000  /* I2C3 Base Address */

/*******************************************************************************
 *                        I2C(s) Registers Offset Address                      *
 *******************************************************************************/
        /******************* I2C Master Register Offsets ********************/
#define I2C_MSA_REG_OFFSET         0x000       /* I2C Master Slave Address              */
#define I2C_MCS_REG_OFFSET         0x004       /* I2C Master Control/Status             */
#define I2C_MDR_REG_OFFSET         0x008       /* I2C Master Data                       */
#define I2C_MTPR_REG_OFFSET        0x00C       /* I2C Master Timer Period               */
#define I2C_MIMR_REG_OFFSET        0x010       /* I2C Master Interrupt Mask             */
#define I2C_MRIS_REG_OFFSET        0x014       /* I2C Master Raw Interrupt Status       */
#define I2C_MMIS_REG_OFFSET        0x018       /* I2C Master Masked Interrupt Status    */
#define I2C_MICR_REG_OFFSET        0x01C       /* I2C Master Interrupt Clear            */
#define I2C_MCR_REG_OFFSET         0x020       /* I2C Master Configuration              */
#define I2C_MCLKOCNT_REG_OFFSET    0x024       /* I2C Master Clock Low Timeout Count    */
#define I2C_MBMON_REG_OFFSET       0x02C       /* I2C Master Bus Monitor                */
#define I2C_MCR2_REG_OFFSET        0x038       /* 2C Master Configuration 2             */

        /******************* I2C Slave Register Offsets ********************/
#define I2C_SOAR_REG_OFFSET        0x800       /* I2C Slave Own Address                 */
#define I2C_SCSR_REG_OFFSET        0x804       /* I2C Slave Control/Status              */
#define I2C_SDR_REG_OFFSET         0x808       /* I2C Slave Data                        */
#define I2C_SIMR_REG_OFFSET        0x80C       /* I2C Slave Interrupt Mask              */
#define I2C_SRIS_REG_OFFSET        0x810       /* I2C Slave Raw Interrupt Status        */
#define I2C_SMIS_REG_OFFSET        0x814       /* I2C Slave Masked Interrupt Status     */
#define I2C_SICR_REG_OFFSET        0x818       /* I2C Slave Interrupt Clear             */
#define I2C_SOAR2_REG_OFFSET       0x81C       /* I2C Slave Own Address 2               */
#define I2C_SACKCTL_REG_OFFSET     0x820       /* I2C Slave ACK Control                 */

        /******************* I2C Status and Control Register Offsets ********************/
#define I2C_PP_REG_OFFSET          0xFC0       /* I2C Peripheral Properties             */
#define I2C_PC_REG_OFFSET          0xFC4       /* I2C Peripheral Configuration          */

/*******************************************************************************
 *                   System Control I2C Enable Clock Register                  *
 *******************************************************************************/
#define SYSCTL_RCGCI2C_REG  (*((volatile unsigned long*)0x400FE620))


#endif /* DRIVERS_I2C_I2C_PRIV_H_ */
