/*
 * main.h
 *
 *  Created on: Aug 16, 2021
 *      Author: islam
 */

#ifndef MAIN_H_
#define MAIN_H_

/********************************************************************************
 *                                Includes Needed                               *
 *******************************************************************************/
#include "std_types.h"
#include "UART_Init.h"
#include "SSI_Init.h"


/*******************************************************************************
 *                               Registers Addresses                           *
 *******************************************************************************/

/*****************************************************************************
                               GPIO registers (PORTA)
*****************************************************************************/
#define GPIO_PORTA_DATA_REG       (*((volatile unsigned long *)0x400043FC))
#define GPIO_PORTA_DIR_REG        (*((volatile unsigned long *)0x40004400))
#define GPIO_PORTA_AFSEL_REG      (*((volatile unsigned long *)0x40004420))
#define GPIO_PORTA_PUR_REG        (*((volatile unsigned long *)0x40004510))
#define GPIO_PORTA_PDR_REG        (*((volatile unsigned long *)0x40004514))
#define GPIO_PORTA_DEN_REG        (*((volatile unsigned long *)0x4000451C))
#define GPIO_PORTA_LOCK_REG       (*((volatile unsigned long *)0x40004520))
#define GPIO_PORTA_CR_REG         (*((volatile unsigned long *)0x40004524))
#define GPIO_PORTA_AMSEL_REG      (*((volatile unsigned long *)0x40004528))
#define GPIO_PORTA_PCTL_REG       (*((volatile unsigned long *)0x4000452C))

/* PORTA External Interrupts Registers */
#define GPIO_PORTA_IS_REG         (*((volatile unsigned long *)0x40004404))
#define GPIO_PORTA_IBE_REG        (*((volatile unsigned long *)0x40004408))
#define GPIO_PORTA_IEV_REG        (*((volatile unsigned long *)0x4000440C))
#define GPIO_PORTA_IM_REG         (*((volatile unsigned long *)0x40004410))
#define GPIO_PORTA_RIS_REG        (*((volatile unsigned long *)0x40004414))
#define GPIO_PORTA_ICR_REG        (*((volatile unsigned long *)0x4000441C))

/*****************************************************************************
                            GPIO registers (PORTB)
*****************************************************************************/
#define GPIO_PORTB_DATA_REG       (*((volatile unsigned long *)0x400053FC))
#define GPIO_PORTB_DIR_REG        (*((volatile unsigned long *)0x40005400))
#define GPIO_PORTB_AFSEL_REG      (*((volatile unsigned long *)0x40005420))
#define GPIO_PORTB_ODR_REG        (*((volatile unsigned long *)0x4000550C))
#define GPIO_PORTB_PUR_REG        (*((volatile unsigned long *)0x40005510))
#define GPIO_PORTB_PDR_REG        (*((volatile unsigned long *)0x40005514))
#define GPIO_PORTB_DEN_REG        (*((volatile unsigned long *)0x4000551C))
#define GPIO_PORTB_LOCK_REG       (*((volatile unsigned long *)0x40005520))
#define GPIO_PORTB_CR_REG         (*((volatile unsigned long *)0x40005524))
#define GPIO_PORTB_AMSEL_REG      (*((volatile unsigned long *)0x40005528))
#define GPIO_PORTB_PCTL_REG       (*((volatile unsigned long *)0x4000552C))

/* PORTB External Interrupts Registers */
#define GPIO_PORTB_IS_REG         (*((volatile unsigned long *)0x40005404))
#define GPIO_PORTB_IBE_REG        (*((volatile unsigned long *)0x40005408))
#define GPIO_PORTB_IEV_REG        (*((volatile unsigned long *)0x4000540C))
#define GPIO_PORTB_IM_REG         (*((volatile unsigned long *)0x40005410))
#define GPIO_PORTB_RIS_REG        (*((volatile unsigned long *)0x40005414))
#define GPIO_PORTB_ICR_REG        (*((volatile unsigned long *)0x4000541C))


/*****************************************************************************
                            GPIO registers (PORTF)
*****************************************************************************/
#define GPIO_PORTF_DATA_REG       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_REG        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_REG      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_REG        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_PDR_REG        (*((volatile unsigned long *)0x40025514))
#define GPIO_PORTF_DEN_REG        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_REG       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_REG         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_REG      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_REG       (*((volatile unsigned long *)0x4002552C))

/* PORTF External Interrupts Registers */
#define GPIO_PORTF_IS_REG         (*((volatile unsigned long *)0x40025404))
#define GPIO_PORTF_IBE_REG        (*((volatile unsigned long *)0x40025408))
#define GPIO_PORTF_IEV_REG        (*((volatile unsigned long *)0x4002540C))
#define GPIO_PORTF_IM_REG         (*((volatile unsigned long *)0x40025410))
#define GPIO_PORTF_RIS_REG        (*((volatile unsigned long *)0x40025414))
#define GPIO_PORTF_ICR_REG        (*((volatile unsigned long *)0x4002541C))


/*****************************************************************************
                   System Control Addresses (For Enabling Clocks)
*****************************************************************************/
#define SYSCTL_REGCGC2_REG        (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_REGCGC1_REG        (*((volatile unsigned long *)0x400FE104))

/*****************************************************************************
                    NVIC Address (To Enable UART0 Interrupt)
*****************************************************************************/
#define NVIC_EN0_REG              (*((volatile unsigned long *)0xE000E100))
#define NVIC_EN1_REG              (*((volatile unsigned long *)0xE000E104))
#define NVIC_PEND0_REG            (*((volatile unsigned long *)0xE000E200))
#define NVIC_PEND1_REG            (*((volatile unsigned long *)0xE000E204))

/*****************************************************************************
                                   Function Macros
*****************************************************************************/
/* Enable IRQ Interrupts ... This Macro enables IRQ interrupts by clearing the I-bit in the PRIMASK. */
#define Enable_Interrupts()    __asm("  CPSIE I")

/* Disable IRQ Interrupts ... This Macro disables IRQ interrupts by setting the I-bit in the PRIMASK. */
#define Disable_Interrupts()   __asm("  CPSID I")

/* Go to low power mode while waiting for the next interrupt */
#define Wait_For_Interrupt()   __asm("  WFI")



#endif /* MAIN_H_ */
