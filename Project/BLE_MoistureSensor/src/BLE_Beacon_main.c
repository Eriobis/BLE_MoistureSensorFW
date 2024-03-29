
/******************** (C) COPYRIGHT 2018 STMicroelectronics ********************
* File Name          : BLE_Beacon_main.c
* Author             : RF Application Team
* Version            : 1.1.0
* Date               : 15-January-2016
* Description        : Code demostrating the BLE Beacon application
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/

/**
 * @file BLE_Beacon_main.c
 * @brief This is a BLE beacon demo that shows how to configure a BlueNRG-1,2 device 
 * in order to advertise specific manufacturing data and allow another BLE device to
 * know if it is in the range of the BlueNRG-1 beacon device. 
 * It also provides a reference example about how using the 
 * BLE Over-The-Air (OTA) Service Manager firmware upgrade capability.
 * 

* \section ATOLLIC_project ATOLLIC project
  To use the project with ATOLLIC TrueSTUDIO for ARM, please follow the instructions below:
  -# Open the ATOLLIC TrueSTUDIO for ARM and select File->Import... Project menu. 
  -# Select Existing Projects into Workspace. 
  -# Select the ATOLLIC project
  -# Select desired configuration to build from Project->Manage Configurations
  -# Select Project->Rebuild Project. This will recompile and link the entire application
  -# To download the binary image, please connect STLink to JTAG connector in your board (if available).
  -# Select Project->Download to download the related binary image.
  -# Alternatively, open the BlueNRG1 Flasher utility and download the built binary image.

* \section KEIL_project KEIL project
  To use the project with KEIL uVision 5 for ARM, please follow the instructions below:
  -# Open the KEIL uVision 5 for ARM and select Project->Open Project menu. 
  -# Open the KEIL project
     <tt> ...\\Project\\BLE_Examples\\BLE_Beacon\\MDK-ARM\\BlueNRG-1\\BLE_Beacon.uvprojx </tt> or
     <tt> ...\\Project\\BLE_Examples\\BLE_Beacon\\MDK-ARM\\BlueNRG-2\\BLE_Beacon.uvprojx </tt>
  -# Select desired configuration to build
  -# Select Project->Rebuild all target files. This will recompile and link the entire application
  -# To download the binary image, please connect STLink to JTAG connector in your board (if available).
  -# Select Project->Download to download the related binary image.
  -# Alternatively, open the BlueNRG1 Flasher utility and download the built binary image.

* \section IAR_project IAR project
  To use the project with IAR Embedded Workbench for ARM, please follow the instructions below:
  -# Open the Embedded Workbench for ARM and select File->Open->Workspace menu. 
  -# Open the IAR project
     <tt> ...\\Project\\BLE_Examples\\BLE_Beacon\\EWARM\\BlueNRG-1\\BLE_Beacon.eww </tt> or
     <tt> ...\\Project\\BLE_Examples\\BLE_Beacon\\EWARM\\BlueNRG-2\\BLE_Beacon.eww </tt>
  -# Select desired configuration to build
  -# Select Project->Rebuild All. This will recompile and link the entire application
  -# To download the binary image, please connect STLink to JTAG connector in your board (if available).
  -# Select Project->Download and Debug to download the related binary image.
  -# Alternatively, open the BlueNRG1 Flasher utility and download the built binary image.

* \subsection Project_configurations Project configurations
- \c Release - Release configuration
- \c Use_OTA_ServiceManager - Configuration for Application using OTA Service Manager

     
* \section Board_supported Boards supported
- \c STEVAL-IDB007V1
- \c STEVAL-IDB007V2
- \c STEVAL-IDB008V1
- \c STEVAL-IDB008V2
- \c STEVAL-IDB009V1


 * \section Power_settings Power configuration settings
@table

==========================================================================================================
|                                         STEVAL-IDB00XV1                                                |
----------------------------------------------------------------------------------------------------------
| Jumper name |            |  Description                                                                |
| JP1         |   JP2      |                                                                             |
----------------------------------------------------------------------------------------------------------
| ON 1-2      | ON 2-3     | USB supply power                                                            |
| ON 2-3      | ON 1-2     | The supply voltage must be provided through battery pins.                   |
| ON 1-2      |            | USB supply power to STM32L1, JP2 pin 2 external power to BlueNRG1           |


@endtable 

* \section Jumper_settings Jumper settings
@table

========================================================================================================================================================================================
|                                                                             STEVAL-IDB00XV1                                                                                          |
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
| Jumper name |                                                                Description                                                                                             |
----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------          
| JP1         | 1-2: to provide power from USB (JP2:2-3). 2-3: to provide power from battery holder (JP2:1-2)                                                                          |          
| JP2         | 1-2: to provide power from battery holder (JP1:2-3). 2-3: to provide power from USB (JP1:1-2). Pin2 to VDD  to provide external power supply to BlueNRG-1 (JP1: 1-2)   |
| JP3         | pin 1 and 2 UART RX and TX of MCU. pin 3 GND.                                                                                                                          |          
| JP4         | Fitted: to provide VBLUE to BlueNRG1. It can be used also for current measurement.                                                                                     |
| JP5         | Fitted : TEST pin to VBLUE. Not fitted:  TEST pin to GND                                                                                                               |


@endtable 

* \section Pin_settings Pin settings
@table
|            |                                                 Release                                                 |||||                                                        Use_OTA_ServiceManager                                                         |||||
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|  PIN name  |   STEVAL-IDB007V1  |   STEVAL-IDB007V2  |   STEVAL-IDB008V1  |   STEVAL-IDB008V2  |   STEVAL-IDB009V1  |      STEVAL-IDB007V1     |      STEVAL-IDB007V2     |      STEVAL-IDB008V1     |      STEVAL-IDB008V2     |      STEVAL-IDB009V1     |
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|    ADC1    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|    ADC2    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|     IO0    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|     IO1    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|    IO11    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|    IO12    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|    IO13    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|    IO14    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|    IO15    |        N.A.        |        N.A.        |        N.A.        |        N.A.        |      Not Used      |           N.A.           |           N.A.           |           N.A.           |           N.A.           |         Not Used         |
|    IO16    |        N.A.        |        N.A.        |        N.A.        |        N.A.        |      Not Used      |           N.A.           |           N.A.           |           N.A.           |           N.A.           |         Not Used         |
|    IO17    |        N.A.        |        N.A.        |        N.A.        |        N.A.        |      Not Used      |           N.A.           |           N.A.           |           N.A.           |           N.A.           |         Not Used         |
|    IO18    |        N.A.        |        N.A.        |        N.A.        |        N.A.        |      Not Used      |           N.A.           |           N.A.           |           N.A.           |           N.A.           |         Not Used         |
|    IO19    |        N.A.        |        N.A.        |        N.A.        |        N.A.        |      Not Used      |           N.A.           |           N.A.           |           N.A.           |           N.A.           |         Not Used         |
|     IO2    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|    IO20    |        N.A.        |        N.A.        |        N.A.        |        N.A.        |      Not Used      |           N.A.           |           N.A.           |           N.A.           |           N.A.           |         Not Used         |
|    IO21    |        N.A.        |        N.A.        |        N.A.        |        N.A.        |      Not Used      |           N.A.           |           N.A.           |           N.A.           |           N.A.           |         Not Used         |
|    IO22    |        N.A.        |        N.A.        |        N.A.        |        N.A.        |      Not Used      |           N.A.           |           N.A.           |           N.A.           |           N.A.           |         Not Used         |
|    IO23    |        N.A.        |        N.A.        |        N.A.        |        N.A.        |      Not Used      |           N.A.           |           N.A.           |           N.A.           |           N.A.           |         Not Used         |
|    IO24    |        N.A.        |        N.A.        |        N.A.        |        N.A.        |      Not Used      |           N.A.           |           N.A.           |           N.A.           |           N.A.           |         Not Used         |
|    IO25    |        N.A.        |        N.A.        |        N.A.        |        N.A.        |      Not Used      |           N.A.           |           N.A.           |           N.A.           |           N.A.           |         Not Used         |
|     IO3    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|     IO4    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|     IO5    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|     IO6    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|     IO7    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|     IO8    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |
|    TEST1   |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |         Not Used         |         Not Used         |         Not Used         |         Not Used         |         Not Used         |

@endtable 

* \section Serial_IO Serial I/O
@table
| Parameter name  | Value            | Unit      |
----------------------------------------------------
| Baudrate        | 115200 [default] | bit/sec   |
| Data bits       | 8                | bit       |
| Parity          | None             | bit       |
| Stop bits       | 1                | bit       |
@endtable

* \section LEDs_description LEDs description
@table
|            |                                                 Release                                                 |||||                                                                                                     Use_OTA_ServiceManager                                                                                                      |||||
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|  LED name  |   STEVAL-IDB007V1  |   STEVAL-IDB007V2  |   STEVAL-IDB008V1  |   STEVAL-IDB008V2  |   STEVAL-IDB009V1  |               STEVAL-IDB007V1              |               STEVAL-IDB007V2              |               STEVAL-IDB008V1              |               STEVAL-IDB008V2              |               STEVAL-IDB009V1              |
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|     DL1    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |                  Not Used                  |                  Not Used                  |                  Not Used                  |                  Not Used                  |                  Not Used                  |
|     DL2    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |                  Not Used                  |                  Not Used                  |                  Not Used                  |                  Not Used                  |                  Not Used                  |
|     DL3    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |   ON when OTA firmware upgrade is ongoing  |   ON when OTA firmware upgrade is ongoing  |   ON when OTA firmware upgrade is ongoing  |   ON when OTA firmware upgrade is ongoing  |   ON when OTA firmware upgrade is ongoing  |
|     DL4    |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |                  Not Used                  |                  Not Used                  |                  Not Used                  |                  Not Used                  |                  Not Used                  |

@endtable


* \section Buttons_description Buttons description
@table
|                |                                                 Release                                                 |||||                                                                                                                                                                           Use_OTA_ServiceManager                                                                                                                                                                            |||||
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|   BUTTON name  |   STEVAL-IDB007V1  |   STEVAL-IDB007V2  |   STEVAL-IDB008V1  |   STEVAL-IDB008V2  |   STEVAL-IDB009V1  |                             STEVAL-IDB007V1                            |                             STEVAL-IDB007V2                            |                             STEVAL-IDB008V1                            |                             STEVAL-IDB008V2                            |                             STEVAL-IDB009V1                            |
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
|      PUSH1     |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |  It allows BLE Beacon application to activate the OTA Service Manager  |  It allows BLE Beacon application to activate the OTA Service Manager  |  It allows BLE Beacon application to activate the OTA Service Manager  |  It allows BLE Beacon application to activate the OTA Service Manager  |  It allows BLE Beacon application to activate the OTA Service Manager  |
|      PUSH2     |      Not Used      |      Not Used      |      Not Used      |      Not Used      |      Not Used      |                                Not Used                                |                                Not Used                                |                                Not Used                                |                                Not Used                                |                                Not Used                                |
|      RESET     |   Reset BlueNRG1   |   Reset BlueNRG1   |   Reset BlueNRG2   |   Reset BlueNRG2   |   Reset BlueNRG2   |                             Reset BlueNRG1                             |                             Reset BlueNRG1                             |                             Reset BlueNRG2                             |                             Reset BlueNRG2                             |                             Reset BlueNRG2                             |

@endtable

* \section Usage Usage

The Beacon demo configures a BlueNRG-1,2 device in advertising mode (non-connectable mode) with specific manufacturing data.
It transmits advertisement packets at regular intervals which contain the following manufacturing data:
@table   
------------------------------------------------------------------------------------------------------------------------
| Data field              | Description                       | Notes                                                  |
------------------------------------------------------------------------------------------------------------------------
| Company identifier code | SIG company identifier (1)        | Default is 0x0030 (STMicroelectronics)                 |
| ID                      | Beacon ID                         | Fixed value                                            |
| Length                  | Length of the remaining payload   | NA                                                     |
| Location UUID           | Beacons UUID                      | It is used to distinguish specific beacons from others |
| Major number            | Identifier for a group of beacons | It is used to group a related set of beacons           |                                              
| Minor number            | Identifier for a single beacon    | It is used to identify a single beacon                 |                                       
| Tx Power                | 2's complement of the Tx power    | It is used to establish how far you are from device    |                                       
@endtable

 - (1): SIG company identifiers are available on https://www.bluetooth.org/en-us/specification/assigned-numbers/company-identifiers
 - NA : Not Applicable;
NOTEs:
     - OTA Service Manager support requires to build application by enabling only ST_USE_OTA_SERVICE_MANAGER_APPLICATION=1 (preprocessor, linker) options and through files: OTA_btl.[ch] (refer to Release_with_OTA_ServiceManager IAR workspace).
     - OTA FW upgrade feature is supported only on BlueNRG-2, BLE stack v2.x.

**/
   
/** @addtogroup BlueNRG1_demonstrations_applications
 *  BlueNRG-1 Beacon demo \see BLE_Beacon_main.c for documentation.
 *
 *@{
 */

/** @} */
/** \cond DOXYGEN_SHOULD_SKIP_THIS
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "BlueNRG1_it.h"
#include "BlueNRG1_conf.h"
#include "ble_const.h"
#include "bluenrg1_stack.h"
#include "sleep.h"
#include "Beacon_config.h"
#include "OTA_btl.h"
#include "clock.h"
#include "bsp.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BLE_BEACON_VERSION_STRING "1.1.0"

#define PRINTF(...)
/* Set to 1 for enabling Flags AD Type position at the beginning 
   of the advertising packet */
#define ENABLE_FLAGS_AD_TYPE_AT_BEGINNING 1

#define ADV_DATA_PAYLOAD_OFFSET (sizeof(adv_data) - 16)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint8_t adv_data[] = {
    /* Advertising data: Flags AD Type */
    0x02, 
    AD_TYPE_FLAGS,
    FLAG_BIT_LE_GENERAL_DISCOVERABLE_MODE | FLAG_BIT_BR_EDR_NOT_SUPPORTED, 
    0x07, //Len
    AD_TYPE_SHORTENED_LOCAL_NAME, // Local name
    'S', 'B', 'M', 'S', '0', '0',
    /* Advertising data: manufacturer specific data */
    0x12,                                  // len ( 18 )
    AD_TYPE_MANUFACTURER_SPECIFIC_DATA, // manufacturer type
    0xFF, 0xFF, // Company identifier code (Default is 0x0030 -
                // STMicroelectronics: To be customized for specific identifier)
                // FFFF = No identifier
    'D', 'A', 'T', 'A', // Vcc in float
    'D', 'A', 'T', 'A',
    'D', 'A', 'T', 'A',
    '\0', '\0', '\0'
    };

uint8_t address[6] = { 0x00,0x00,0x00,0xE1,0x80,0x02 };

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Device_Init(void)
{
    uint8_t ret;
    uint16_t service_handle;
    uint16_t dev_name_char_handle;
    uint16_t appearance_char_handle;
    
    /* Set the TX Power to -2 dBm */
    ret = aci_hal_set_tx_power_level(1,7);
    if(ret != 0) {
        PRINTF ("Error in aci_hal_set_tx_power_level() 0x%04xr\n", ret);
        while(1);
    }

    /* Init the GATT */
    ret = aci_gatt_init();
    if (ret != 0) 
        PRINTF ("Error in aci_gatt_init() 0x%04xr\n", ret);
    else
        PRINTF ("aci_gatt_init() --> SUCCESS\r\n");
    
    /* Init the GAP */
    ret = aci_gap_init(0x01, 0x00, 0x08, &service_handle, 
                        &dev_name_char_handle, &appearance_char_handle);
    if (ret != 0)
        PRINTF ("Error in aci_gap_init() 0x%04x\r\n", ret);
    else
        PRINTF ("aci_gap_init() --> SUCCESS\r\n");
}


/**
* @brief  Start beaconing
* @param  None 
* @retval None
*/

static void Start_Beaconing(void) {
  uint8_t ret = BLE_STATUS_SUCCESS;

  /* disable scan response */
  ret = hci_le_set_scan_response_data(0, NULL);
  if (ret != BLE_STATUS_SUCCESS) {
    PRINTF("Error in hci_le_set_scan_resp_data() 0x%04x\r\n", ret);
    return;
  } else
    PRINTF("hci_le_set_scan_resp_data() --> SUCCESS\r\n");

  /* put device in non connectable mode */
  ret = aci_hal_write_config_data(CONFIG_DATA_PUBADDR_OFFSET, 6, address);
  ret = aci_gap_set_discoverable(ADV_NONCONN_IND, 62, 150, PUBLIC_ADDR,
                                 NO_WHITE_LIST_USE, 0, NULL, 0, NULL, 0, 0);
  if (ret != BLE_STATUS_SUCCESS) {
    PRINTF("Error in aci_gap_set_discoverable() 0x%04x\r\n", ret);
    return;
  } else
    PRINTF("aci_gap_set_discoverable() --> SUCCESS\r\n");
  
  aci_gap_delete_ad_type(AD_TYPE_TX_POWER_LEVEL);
  aci_gap_delete_ad_type(0x50);
}

void update_adv_value(float volt, uint32_t data) {
    int ret;

    memcpy(&adv_data[ADV_DATA_PAYLOAD_OFFSET], &volt, 4);
    memcpy(&adv_data[ADV_DATA_PAYLOAD_OFFSET+4], &data, 4);
    ret = aci_gap_update_adv_data(sizeof(adv_data), adv_data);
}


float volt;
float senseHigh;
float senseLow ;
float delta;
bool senseDone = false;
uint32_t lastLoopTime = 0;
uint32_t lastSenseTime = 0;
int main(void) 
{
    uint8_t ret;
    
    tClockTime tickTimer;
    uint32_t capacitance;
    /* System Init */
    SystemInit();
   
        // Init the tick timer
    Clock_Init();
    tickTimer = Clock_Time();
         
    // Give a chance to the debugger to connect if sleep is enabled
    while(Clock_Time()  < 5000);
    
    /* BlueNRG-1 stack init */
    ret = BlueNRG_Stack_Initialization(&BlueNRG_Stack_Init_params);
    if (ret != BLE_STATUS_SUCCESS) {
        PRINTF("Error in BlueNRG_Stack_Initialization() 0x%02x\r\n", ret);
        while(1);
    }
    
    /* Init the BlueNRG-1 device */
    Device_Init();
   

    BSP_Init();
    BSP_HoldPowerOn();
    BSP_StartExcitation();
    BSP_ActivateSensor();

    /* Start Beacon Non Connectable Mode*/
    Start_Beaconing();
    

    while (1) {
        /* BlueNRG-1 stack tick */
        BTLE_StackTick();
        
        if (HAL_VTimerDiff_ms_sysT32(HAL_VTimerGetCurrentTime_sysT32(), lastSenseTime) > 5000)
        {
            SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO, ENABLE);
            SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_MTFX1, ENABLE);
            SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_ADC, ENABLE);
            BSP_StartExcitation();
            BSP_ActivateSensor();
            tickTimer = Clock_Time();
         
            // Give a chance to the debugger to connect if sleep is enabled
            while(Clock_Time() - tickTimer  < 10);
            
            
            ADC_SelectInput(ADC_Input_BattSensor);
            ADC_Cmd(ENABLE);
            while(!(ADC->SR_REG & ADC_FLAG_EOC));
            ADC->SR_REG &= ~ADC_FLAG_BUSY;
            volt = ADC_GetConvertedData(ADC_Input_BattSensor, ADC_ReferenceVoltage_0V6);
            while((ADC->SR_REG & ADC_FLAG_BUSY));
            
            ADC_SelectInput(ADC_Input_AdcPin1);
            ADC_Cmd(ENABLE);
            while(!(ADC->SR_REG & ADC_FLAG_EOC));
            ADC->SR_REG &= ~ADC_FLAG_BUSY;
            senseHigh = ADC_GetConvertedData(ADC_Input_AdcPin1, ADC_ReferenceVoltage_0V6);
            
            ADC_SelectInput(ADC_Input_AdcPin2);
            ADC_Cmd(ENABLE);
            while(!(ADC->SR_REG & ADC_FLAG_EOC));
            ADC->SR_REG &= ~ADC_FLAG_BUSY;
            senseLow = ADC_GetConvertedData(ADC_Input_AdcPin2, ADC_ReferenceVoltage_0V6);

            BSP_StopExcitation();
            BSP_DeactivateSensor();
            SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_GPIO, DISABLE);
            SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_MTFX1, DISABLE);
            SysCtrl_PeripheralClockCmd(CLOCK_PERIPH_ADC, DISABLE);
            
            delta = (volt - (senseHigh - senseLow))*1000;
            capacitance = (uint32_t)delta;
            
            Start_Beaconing();
            update_adv_value(volt, capacitance);
            tickTimer = Clock_Time();
            GPIO_SetBits(LED1_PIN);
            senseDone = true;
            lastSenseTime = HAL_VTimerGetCurrentTime_sysT32();
        }
        
        
        /* Enable Power Save according the Advertising Interval */
        
        BlueNRG_Sleep(SLEEPMODE_WAKETIMER, 0, 0);
        
    }
}

/****************** BlueNRG-1 Sleep Management Callback ********************************/

SleepModes App_SleepMode_Check(SleepModes sleepMode)
{
    uint32_t ret;
    //return SLEEPMODE_RUNNING;
    if (HAL_VTimerDiff_ms_sysT32(HAL_VTimerGetCurrentTime_sysT32(), lastSenseTime) > 200)
    {
        GPIO_ResetBits(LED1_PIN);
        lastLoopTime = HAL_VTimerGetCurrentTime_sysT32();
        ret = aci_gap_set_non_discoverable();
        HAL_VTimerStart_ms(1, 5000);
        //return SLEEPMODE_WAKETIMER;
        return SLEEPMODE_RUNNING;
    }
    return SLEEPMODE_RUNNING;
}

/***************************************************************************************/

#ifdef  USE_FULL_ASSERT

/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
*/
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
  ex: PRINTF("Wrong parameters value: file %s on line %d\r\n", file, line) */
  
  /* Infinite loop */
  while (1)
  {
  }
}

#endif

/******************* (C) COPYRIGHT 2015 STMicroelectronics *****END OF FILE****/
/** \endcond
 */
