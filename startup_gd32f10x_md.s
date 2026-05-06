.section .text.startup_header,"a",%progbits
/*
 * GNU startup for GD32F10x medium-density devices.
 *
 * This file is adapted for arm-none-eabi/GCC from the official GigaDevice
 * startup file:
 *   Drivers/CMSIS/GD/GD32F10x/Source/ARM/startup_gd32f10x_md.s
 * in GD32F10x Firmware Library V2.7.0.
 */

.syntax unified
.cpu cortex-m3
.thumb

.global __Vectors
.global __Vectors_End
.global __Vectors_Size
.global g_pfnVectors
.global Default_Handler

.section .text.Reset_Handler
.weak Reset_Handler
.type Reset_Handler, %function
Reset_Handler:
    ldr r0, =_sidata
    ldr r1, =_sdata
    ldr r2, =_edata
1:
    cmp r1, r2
    bcc 2f
    b 3f
2:
    ldr r3, [r0], #4
    str r3, [r1], #4
    b 1b
3:
    ldr r0, =_sbss
    ldr r1, =_ebss
    movs r2, #0
4:
    cmp r0, r1
    bcc 5f
    b 6f
5:
    str r2, [r0], #4
    b 4b
6:
    bl SystemInit
    bl __libc_init_array
    bl main
7:
    b 7b
.size Reset_Handler, .-Reset_Handler

.section .text.Default_Handler,"ax",%progbits
Default_Handler:
Infinite_Loop:
    b Infinite_Loop
.size Default_Handler, .-Default_Handler

.macro def_irq handler
    .weak \handler
    .thumb_set \handler, Default_Handler
.endm

def_irq NMI_Handler
def_irq HardFault_Handler
def_irq MemManage_Handler
def_irq BusFault_Handler
def_irq UsageFault_Handler
def_irq SVC_Handler
def_irq DebugMon_Handler
def_irq PendSV_Handler
def_irq SysTick_Handler

def_irq WWDGT_IRQHandler
def_irq LVD_IRQHandler
def_irq TAMPER_IRQHandler
def_irq RTC_IRQHandler
def_irq FMC_IRQHandler
def_irq RCU_IRQHandler
def_irq EXTI0_IRQHandler
def_irq EXTI1_IRQHandler
def_irq EXTI2_IRQHandler
def_irq EXTI3_IRQHandler
def_irq EXTI4_IRQHandler
def_irq DMA0_Channel0_IRQHandler
def_irq DMA0_Channel1_IRQHandler
def_irq DMA0_Channel2_IRQHandler
def_irq DMA0_Channel3_IRQHandler
def_irq DMA0_Channel4_IRQHandler
def_irq DMA0_Channel5_IRQHandler
def_irq DMA0_Channel6_IRQHandler
def_irq ADC0_1_IRQHandler
def_irq USBD_HP_CAN0_TX_IRQHandler
def_irq USBD_LP_CAN0_RX0_IRQHandler
def_irq CAN0_RX1_IRQHandler
def_irq CAN0_EWMC_IRQHandler
def_irq EXTI5_9_IRQHandler
def_irq TIMER0_BRK_IRQHandler
def_irq TIMER0_UP_IRQHandler
def_irq TIMER0_TRG_CMT_IRQHandler
def_irq TIMER0_Channel_IRQHandler
def_irq TIMER1_IRQHandler
def_irq TIMER2_IRQHandler
def_irq TIMER3_IRQHandler
def_irq I2C0_EV_IRQHandler
def_irq I2C0_ER_IRQHandler
def_irq I2C1_EV_IRQHandler
def_irq I2C1_ER_IRQHandler
def_irq SPI0_IRQHandler
def_irq SPI1_IRQHandler
def_irq USART0_IRQHandler
def_irq USART1_IRQHandler
def_irq USART2_IRQHandler
def_irq EXTI10_15_IRQHandler
def_irq RTC_Alarm_IRQHandler
def_irq USBD_WKUP_IRQHandler
def_irq EXMC_IRQHandler

.section .isr_vector,"a",%progbits
.type __Vectors, %object
__Vectors:
    .word _estack
    .word Reset_Handler
    .word NMI_Handler
    .word HardFault_Handler
    .word MemManage_Handler
    .word BusFault_Handler
    .word UsageFault_Handler
    .word 0
    .word 0
    .word 0
    .word 0
    .word SVC_Handler
    .word DebugMon_Handler
    .word 0
    .word PendSV_Handler
    .word SysTick_Handler

    .word WWDGT_IRQHandler
    .word LVD_IRQHandler
    .word TAMPER_IRQHandler
    .word RTC_IRQHandler
    .word FMC_IRQHandler
    .word RCU_IRQHandler
    .word EXTI0_IRQHandler
    .word EXTI1_IRQHandler
    .word EXTI2_IRQHandler
    .word EXTI3_IRQHandler
    .word EXTI4_IRQHandler
    .word DMA0_Channel0_IRQHandler
    .word DMA0_Channel1_IRQHandler
    .word DMA0_Channel2_IRQHandler
    .word DMA0_Channel3_IRQHandler
    .word DMA0_Channel4_IRQHandler
    .word DMA0_Channel5_IRQHandler
    .word DMA0_Channel6_IRQHandler
    .word ADC0_1_IRQHandler
    .word USBD_HP_CAN0_TX_IRQHandler
    .word USBD_LP_CAN0_RX0_IRQHandler
    .word CAN0_RX1_IRQHandler
    .word CAN0_EWMC_IRQHandler
    .word EXTI5_9_IRQHandler
    .word TIMER0_BRK_IRQHandler
    .word TIMER0_UP_IRQHandler
    .word TIMER0_TRG_CMT_IRQHandler
    .word TIMER0_Channel_IRQHandler
    .word TIMER1_IRQHandler
    .word TIMER2_IRQHandler
    .word TIMER3_IRQHandler
    .word I2C0_EV_IRQHandler
    .word I2C0_ER_IRQHandler
    .word I2C1_EV_IRQHandler
    .word I2C1_ER_IRQHandler
    .word SPI0_IRQHandler
    .word SPI1_IRQHandler
    .word USART0_IRQHandler
    .word USART1_IRQHandler
    .word USART2_IRQHandler
    .word EXTI10_15_IRQHandler
    .word RTC_Alarm_IRQHandler
    .word USBD_WKUP_IRQHandler
    .word 0
    .word 0
    .word 0
    .word 0
    .word 0
    .word EXMC_IRQHandler
__Vectors_End:
.equ __Vectors_Size, __Vectors_End - __Vectors
.set g_pfnVectors, __Vectors
.size __Vectors, .-__Vectors

.section .text.__libc_init_array_dummy,"ax",%progbits
.weak __libc_init_array
__libc_init_array:
    bx lr
