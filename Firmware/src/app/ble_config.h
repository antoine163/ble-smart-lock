/***
 * The MIT License (MIT)
 *
 * Copyright (c) 2023 antoine163
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file ble_config.h
 * @author antoine163
 * @date 15.07.2023
 * @brief This file is recovered and adjusted from examples of ST.
 * It contains all the information needed to init the BlueNRG-1 stack.
 * These constants and variables are used from the BlueNRG-1 stack to reserve
 * RAM and FLASH according the application requests.
 */

#ifndef BLE_CONFIG_H
#define BLE_CONFIG_H

#include "bluenrg1_stack.h"
#include "stack_user_cfg.h"
#include "OTA_btl.h"

/* Default number of link */
#define MIN_NUM_LINK            1
/* Default number of GAP and GATT services */
#define DEFAULT_NUM_GATT_SERVICES   2
/* Default number of GAP and GATT attributes */
#define DEFAULT_NUM_GATT_ATTRIBUTES 9

/* Enable/disable Data length extension Max supported ATT_MTU size based on OTA client & server Max ATT_MTU sizes capabilities */
#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) && (OTA_EXTENDED_PACKET_LEN == 1)
    #define OTA_MAX_ATT_MTU_SIZE    (OTA_ATT_MTU_SIZE) //(220) /* OTA Client & Server supported ATT_MTU */
#else /* BlueNRG-1 device: no data length extension support */
    #define OTA_MAX_ATT_MTU_SIZE    (DEFAULT_ATT_MTU)          /* DEFAULT_ATT_MTU size = 23 bytes */
#endif

#if defined (ST_OTA_LOWER_APPLICATION) || defined (ST_OTA_HIGHER_APPLICATION)
    /* Number of services requests from the bl unlocker */
    #define NUM_APP_GATT_SERVICES (1 + 1) /* 1 bl unlocker service + 1 OTA service */
    /* Number of attributes requests from the bl unlocker */
    #define NUM_APP_GATT_ATTRIBUTES (5 + 9) /* 5 attributes x BLE bl unlocker service characteristics + 9 for OTA Service characteristics */
    /**
     * Set the number of 16-bytes units used on an OTA FW data packet for matching OTA client MAX ATT_MTU
     */
    #define OTA_16_BYTES_BLOCKS_NUMBER ((OTA_MAX_ATT_MTU_SIZE-4)/16)   /* 4 bytes for OTA sequence numbers + needs ack + checksum bytes */
    /* OTA characteristics maximum lenght */
    #define OTA_MAX_ATT_SIZE (4 + OTA_16_BYTES_BLOCKS_NUMBER * 16)
#else /* NO OTA Service is required */
    /* Number of services requests from the bl unlocker */
    #define NUM_APP_GATT_SERVICES 2  /* 1 bl unlocker service */
    /* Number of attributes requests from the bl unlocker demo */
    #define NUM_APP_GATT_ATTRIBUTES 16 /* ? attributes x BLE bl unlocker service characteristics */
    /* OTA characteristics maximum lenght */
    #define OTA_MAX_ATT_SIZE (0)
#endif

#define MAX_CHAR_LEN(a,b) ((a) > (b) )? (a) : (b)

/* Application characteristics maximum lenght */
#define _MAX_ATT_SIZE	(6)

/* Set supported max value for attribute size: it is the biggest attribute size enabled by the application. */
#define APP_MAX_ATT_SIZE	  MAX_CHAR_LEN(OTA_MAX_ATT_SIZE,  _MAX_ATT_SIZE)

/* Number of links needed for bl unlocker.
 * Only 1 the default
 */
#define NUM_LINKS               (MIN_NUM_LINK)

/* Number of GATT attributes needed for the bl unlocker. */
#define NUM_GATT_ATTRIBUTES     (DEFAULT_NUM_GATT_ATTRIBUTES + NUM_APP_GATT_ATTRIBUTES)

/* Number of GATT services needed for the bl unlocker. */
#define NUM_GATT_SERVICES       (DEFAULT_NUM_GATT_SERVICES + NUM_APP_GATT_SERVICES)

/* Array size for the attribute value for OTA service */
#if defined (ST_OTA_LOWER_APPLICATION) || defined (ST_OTA_HIGHER_APPLICATION)
/* OTA service: 4 characteristics (1 notify property): 99 bytes +
   Image Content characteristic length = 4  + (OTA_16_BYTES_BLOCKS_NUMBER * 16); 4 for sequence number, checksum and needs acks bytes */
#define OTA_ATT_VALUE_ARRAY_SIZE (99 + (4 + (OTA_16_BYTES_BLOCKS_NUMBER * 16)))
#else
#define OTA_ATT_VALUE_ARRAY_SIZE (0)       /* No OTA service is used */
#endif

/* Array size for the attribute value */
#define ATT_VALUE_ARRAY_SIZE    (44 + 120  + OTA_ATT_VALUE_ARRAY_SIZE) //(GATT + GAP) = 44 + Lock (Unlock (1+19+2=22) + Status ((1+19+2=22)) characteristics))  Services

/* Flash security database size */
#define FLASH_SEC_DB_SIZE       (0x400)

/* Flash server database size */
#define FLASH_SERVER_DB_SIZE    (0x400)

/* Set supported max value for ATT_MTU enabled by the application */
#if (CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED == 1) && (OTA_EXTENDED_PACKET_LEN == 1)
#define MAX_ATT_MTU             (OTA_MAX_ATT_MTU_SIZE)
#else
#define MAX_ATT_MTU             (DEFAULT_ATT_MTU)
#endif

/* Set supported max value for attribute size: it is the biggest attribute size enabled by the application */
#define MAX_ATT_SIZE            (APP_MAX_ATT_SIZE)

/* Set the minumum number of prepare write requests needed for a long write procedure for a characteristic with len > 20bytes:
 *
 * It returns 0 for characteristics with len <= 20bytes
 *
 * NOTE: If prepare write requests are used for a characteristic (reliable write on multiple characteristics), then
 * this value should be set to the number of prepare write needed by the application.
 *
 *  [New parameter added on BLE stack v2.x]
*/
#define PREPARE_WRITE_LIST_SIZE PREP_WRITE_X_ATT(MAX_ATT_SIZE)

/* Additional number of memory blocks  to be added to the minimum  */
#define OPT_MBLOCKS		(6) /* 6:  for reaching the max throughput: ~220kbps (same as BLE stack 1.x) */

/* Set the number of memory block for packet allocation */
#define MBLOCKS_COUNT           (MBLOCKS_CALC(PREPARE_WRITE_LIST_SIZE, MAX_ATT_MTU, NUM_LINKS) + OPT_MBLOCKS)

/* RAM reserved to manage all the data stack according the number of links,
 * number of services, number of attributes and attribute value length
 */
NO_INIT(uint32_t dyn_alloc_a[TOTAL_BUFFER_SIZE(NUM_LINKS,NUM_GATT_ATTRIBUTES,NUM_GATT_SERVICES,ATT_VALUE_ARRAY_SIZE,MBLOCKS_COUNT,CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED)>>2]);


/* FLASH reserved to store all the security database information and
 * and the server database information
 */
NO_INIT_SECTION(uint32_t stacklib_flash_data[TOTAL_FLASH_BUFFER_SIZE(FLASH_SEC_DB_SIZE, FLASH_SERVER_DB_SIZE)>>2], ".noinit.stacklib_flash_data");

/* FLASH reserved to store: security root keys, static random address, public address */
NO_INIT_SECTION(uint8_t stacklib_stored_device_id_data[56], ".noinit.stacklib_stored_device_id_data");

/* Maximum duration of the connection event */
#define MAX_CONN_EVENT_LENGTH 0xFFFFFFFF

/* Sleep clock accuracy */
#if (LS_SOURCE == LS_SOURCE_INTERNAL_RO)
    /* Sleep clock accuracy in Slave mode */
    #define SLAVE_SLEEP_CLOCK_ACCURACY 500
    /* Sleep clock accuracy in Master mode */
    #define MASTER_SLEEP_CLOCK_ACCURACY MASTER_SCA_500ppm
#else
    /* Sleep clock accuracy in Slave mode */
    #define SLAVE_SLEEP_CLOCK_ACCURACY 100

    /* Sleep clock accuracy in Master mode */
    #define MASTER_SLEEP_CLOCK_ACCURACY MASTER_SCA_100ppm
#endif

/* Low Speed Oscillator source */
#if (LS_SOURCE == LS_SOURCE_INTERNAL_RO)
    #define LOW_SPEED_SOURCE  1 // Internal RO
#else
    #define LOW_SPEED_SOURCE  0 // External 32 KHz
#endif

/* High Speed start up time */
#define HS_STARTUP_TIME 328 // 800 us

/* Radio Config Hot Table */
extern uint8_t hot_table_radio_config[];

/* Low level hardware configuration data for the device */
#define CONFIG_TABLE            \
{                               \
        (uint32_t*)hot_table_radio_config,          \
        MAX_CONN_EVENT_LENGTH,        \
        SLAVE_SLEEP_CLOCK_ACCURACY,   \
        MASTER_SLEEP_CLOCK_ACCURACY,  \
        LOW_SPEED_SOURCE,             \
        HS_STARTUP_TIME               \
}

/* This structure contains memory and low level hardware configuration data for the device */
const BlueNRG_Stack_Initialization_t BlueNRG_Stack_Init_params = {
    (uint8_t*)stacklib_flash_data,
    FLASH_SEC_DB_SIZE,
    FLASH_SERVER_DB_SIZE,
    (uint8_t*)stacklib_stored_device_id_data,
    (uint8_t*)dyn_alloc_a,
    TOTAL_BUFFER_SIZE(NUM_LINKS,NUM_GATT_ATTRIBUTES,NUM_GATT_SERVICES,ATT_VALUE_ARRAY_SIZE,MBLOCKS_COUNT,CONTROLLER_DATA_LENGTH_EXTENSION_ENABLED),
    NUM_GATT_ATTRIBUTES,
    NUM_GATT_SERVICES,
    ATT_VALUE_ARRAY_SIZE,
    NUM_LINKS,
    0, /* reserved for future use */
    PREPARE_WRITE_LIST_SIZE,
    MBLOCKS_COUNT,
    MAX_ATT_MTU,
    CONFIG_TABLE,
};

#endif // BLE_CONFIG_H
