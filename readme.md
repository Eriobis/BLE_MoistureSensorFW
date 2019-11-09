# BLE Moisture Sensor FW

## Description

This repo contains the code for my BLE moisture sensor, based on the SPBTLE-1S device.

- [Link to the HW repo](https://github.com/Eriobis/i2c-moisture-sensor/tree/spbtle)

It's basicaly a BLE emitting beacon containing the raw value of a capacitive sensor

## Build

### IDE

- The project is build in Keil V5 ( License is free for Cortex-M0 devices )
- The software pack used is : Keil.STBlueNRG-1_DFP.1.2.0

## Feature

- [x] Pushbutton to power on the device with self maintained circuit
- [ ] Shutdown pin from the MCU to turn off the device
- [ ] Button input to to actions
  - Keep the device from sleeping
  - Actions TBD
- [x] Device is always sleeping and should wakeup when timer elapsed
- [x] Will burst advertising beacon when awake ( 100ms )

### Advertising packet

- 0x02
  - Instruction is 2 bytes
  - 0x01 
    - AD_TYPE_FLAGS,  // Next byte will contain flags
  - 0x06
    - FLAG_BIT_LE_GENERAL_DISCOVERABLE_MODE | FLAG_BIT_BR_EDR_NOT_SUPPORTED, 
- 0x07
  -  Next instruction is 7 bytes
    - 0x08
      - AD_TYPE_SHORTENED_LOCAL_NAME, // Local name
    - [ 6 Bytes for the name]
      - Exemple : 'S', 'B', 'M', 'S', '0', '0',
- 0x12,
  - manufacturer specific data will contain  18 bytes
    - 0xFF
      - AD_TYPE_MANUFACTURER_SPECIFIC_DATA
    
    - 0xFFFF
      - Company identifier code (
        - Default is 0x0030 for STMicroelectronics
        - FFFF = No identifier
    - [ 4 bytes ]
      - Sys voltage ( mV )
    - [ 4 bytes ]
      - Sensor Value
    - [ 4 bytes ]
      - SPARE
    - [ 3 bytes ]
      - Flags ( todo )

The advertising packet should look like : 
`02 01 06 07 08 xx xx xx xx xx xx 12 FF FF FF xx xx xx xx xx xx xx xx xx xx xx xx xx xx xx `

### MAC Address
```c
uint8_t address[6] = { 0x00,0x00,0x00,0xE1,0x80,0x02 };
                         ^^------This is the sensor number
```