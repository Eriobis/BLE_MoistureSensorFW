/**********************************************************************************************************************
 * @file    bsp.h
 * @author  Simon Benoit
 * @date    20-09-2017
 * @brief   
 *********************************************************************************************************************/

#ifndef __BSP_H__
#define __BSP_H__

/* Includes ---------------------------------------------------------------------------------------------------------*/

#include <stdint.h>
#include <stdbool.h>

/* Global Defines ---------------------------------------------------------------------------------------------------*/

#define LED1_PIN            GPIO_Pin_6
#define LED2_PIN            GPIO_Pin_8
#define SENSOR_POWER_PIN    GPIO_Pin_5
#define POWER_ON_PIN        GPIO_Pin_3
#define EXCITATION_PIN      GPIO_Pin_2
#define SENSE_HIGH_PIN      ADC2
#define SENSE_LOW_PIN       ADC1

/* Global Enum ------------------------------------------------------------------------------------------------------*/

/* Global Variables -------------------------------------------------------------------------------------------------*/

/* Global Functions Prototypes --------------------------------------------------------------------------------------*/

void BSP_Init       (void);
void BSP_HoldPowerOn(void);
void BSP_Shutdown   (void);
void BSP_ActivateSensor(void);
void BSP_DeactivateSensor(void);
void BSP_StartExcitation(void);
void BSP_StopExcitation(void);

/* ------------------------------------------------------------------------------------------------------------------*/

#endif//__BSP_H__
