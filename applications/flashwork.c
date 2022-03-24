/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-13     Rick       the first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include <spi_flash.h>
#include <drv_spi.h>
#include <string.h>
#include <stdlib.h>
#include "pin_config.h"
#include "flashwork.h"
#include "fal.h"

#define DBG_TAG "FLASH"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

rt_spi_flash_device_t fm25q16;
char read_value_temp[32]={0};
Device_Info Global_Device={0};

int flash_Init(void)
{
    rt_err_t status;
    extern rt_spi_flash_device_t rt_sfud_flash_probe(const char *spi_flash_dev_name, const char *spi_dev_name);
    rt_hw_spi_device_attach("spi1", "spi10", GPIOA, GPIO_PIN_4);
    fm25q16 = rt_sfud_flash_probe("norflash0", "spi10");
    if (RT_NULL == fm25q16)
    {
        LOG_E("sfud fail\r\n");
        return RT_ERROR;
    };
    status = fal_init();
    if (status == 0)
    {
        LOG_E("fal_init fail\r\n");
        return RT_ERROR;
    };
    LOG_I("Storage Init Success\r\n");
    return RT_EOK;
}
