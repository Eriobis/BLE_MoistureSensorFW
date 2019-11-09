/**********************************************************************************************************************
 * @file    bsp.c
 * @author  Simon Benoit
 * @date    20-09-2017
 * @brief   
 *********************************************************************************************************************/

/* Includes ---------------------------------------------------------------------------------------------------------*/

#include "bsp.h"
#include "BlueNRG1_conf.h"

/* Local Defines ----------------------------------------------------------------------------------------------------*/

/* Local Typedefs ---------------------------------------------------------------------------------------------------*/

/* Forward Declarations ---------------------------------------------------------------------------------------------*/

/* Local Constants --------------------------------------------------------------------------------------------------*/

/* Local Variables --------------------------------------------------------------------------------------------------*/

/* Local Functions --------------------------------------------------------------------------------------------------*/

static void BSP_GPIO_Init()
{
    GPIO_InitType initStruct;

    // Enable GPIO periph
    SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO, ENABLE);

    initStruct.GPIO_Pin = LED1_PIN | LED2_PIN;
    initStruct.GPIO_Mode = GPIO_Output;
    initStruct.GPIO_Pull = ENABLE;
    initStruct.GPIO_HighPwr = DISABLE;
    GPIO_Init(&initStruct);

    initStruct.GPIO_Pin = POWER_ON_PIN;
    initStruct.GPIO_Mode = GPIO_Output;
    initStruct.GPIO_Pull = ENABLE;
    initStruct.GPIO_HighPwr = DISABLE;
    GPIO_Init(&initStruct);

    initStruct.GPIO_Pin = SENSOR_POWER_PIN;
    initStruct.GPIO_Mode = GPIO_Output;
    initStruct.GPIO_Pull = ENABLE;
    initStruct.GPIO_HighPwr = DISABLE;
    GPIO_Init(&initStruct);

    initStruct.GPIO_Pin = EXCITATION_PIN;
    initStruct.GPIO_Mode = Serial1_Mode; // PWM0 mode
    initStruct.GPIO_Pull = ENABLE;
    initStruct.GPIO_HighPwr = DISABLE;
    GPIO_Init(&initStruct);
}

static void BSP_ADC_Init()
{
    // Enable ADC periph
    SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_ADC, ENABLE);
    
    ADC_InitType initStruct;

    initStruct.ADC_Input = ADC_Input_BattSensor;
    initStruct.ADC_OSR = ADC_OSR_200;
    initStruct.ADC_ConversionMode = ADC_ConversionMode_Single;
    initStruct.ADC_Attenuation = ADC_Attenuation_9dB54;
    initStruct.ADC_ReferenceVoltage = ADC_ReferenceVoltage_0V6;
    ADC_Init(&initStruct);
    
    /* Enable auto offset correction */
    ADC_AutoOffsetUpdate(ENABLE);
    ADC_Calibration(ENABLE);
}

static void BSP_MFT_Init()
{
    MFT_InitType initStruct;

    // Enable ADC periph
    SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_MTFX1, ENABLE);
    
    initStruct.MFT_Mode = MFT_MODE_3; // 2 timer independant ( 50% duty cycle forced )
    initStruct.MFT_Clock1 = MFT_PRESCALED_CLK;
    initStruct.MFT_Clock2 = MFT_PRESCALED_CLK;
    initStruct.MFT_Prescaler = 0;
    initStruct.MFT_CRA = 1;
    initStruct.MFT_CRB = 0;
    MFT_Init(MFT1, &initStruct);

    MFT_TnXEN(MFT1, MFT_TnA, ENABLE); // Enable output on PWM0
}

/* Global Functions -------------------------------------------------------------------------------------------------*/

void BSP_Init()
{

    BSP_GPIO_Init();
    BSP_ADC_Init();
    BSP_MFT_Init();
}

void BSP_HoldPowerOn()
{
    GPIO_SetBits(POWER_ON_PIN);
}

void BSP_ActivateSensor()
{
    GPIO_SetBits(SENSOR_POWER_PIN);
}

void BSP_DeactivateSensor()
{
    GPIO_ResetBits(SENSOR_POWER_PIN);
}

void BSP_Shutdown()
{
    GPIO_ResetBits(POWER_ON_PIN);
}

void BSP_StartExcitation()
{
    MFT_Cmd(MFT1, ENABLE);
}

void BSP_StopExcitation()
{
    MFT_Cmd(MFT1, DISABLE);
}