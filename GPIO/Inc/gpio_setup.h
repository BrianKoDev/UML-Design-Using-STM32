/**
 ******************************************************************************
 * File Name          : gpio_setup.h
 * Description        : Main program body
 ******************************************************************************
 *
 * COPYRIGHT(c) 2016 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "stm32f3xx_it.h"

// define the pins to which the LEDs are attached on Port E - with USB ports at bottom
#define LED8  GPIO_PIN_14 // (top right - Orange)
#define LED6  GPIO_PIN_15 // (right - Green)
#define LED4  GPIO_PIN_8  // (bottom right - Blue)
#define LED3  GPIO_PIN_9  // (bottom - Red)
#define LED5  GPIO_PIN_10 // (bottom left  - Orange)
#define LED7  GPIO_PIN_11 // (left - Green)
#define LED9  GPIO_PIN_12 // (top left - Blue)
#define LED10 GPIO_PIN_13 // (top - Red)

// all LEDS that are going to used
#define ALL_PINS LED4 | LED3 | LED5 | LED7 | LED9 | LED10 | LED8 | LED6

// define the pin to which the USER button is attached on Port A
#define USER GPIO_PIN_0 

/*
 * Perform the configuration of the STM32 Discovery board
 * to allow input from the user button and output to LEDs
 */
void board_setup(void);


/** System Clock Configuration
 */
void SystemClock_Config(void);


/**
 * Set up GPIO ports to blink LEDs and read USER button
 */
void gpio_setup(void);

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
