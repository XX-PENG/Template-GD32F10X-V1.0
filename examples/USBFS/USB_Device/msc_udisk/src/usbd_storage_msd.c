/*!
    \file    usbd_storage_msd.c
    \brief   this file provides the disk operations functions

    \version 2026-02-12, V2.7.0, firmware for GD32F10x
*/

/*
    Copyright (c) 2026, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this 
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice, 
       this list of conditions and the following disclaimer in the documentation 
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors 
       may be used to endorse or promote products derived from this software without 
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
OF SUCH DAMAGE.
*/

#include "usb_conf.h"
#include "flash_msd.h"
#include "usbd_msc_mem.h"

/* USB mass storage standard inquiry data */
const int8_t storage_inquiry_data[] = 
{
    /* LUN 0 */
    0x00,
    0x80,
    0x00,
    0x01,
    (USBD_STD_INQUIRY_LENGTH - 5U),
    0x00,
    0x00,
    0x00,
    'G', 'D', '3', '2', ' ', ' ', ' ', ' ', /* manufacturer : 8 bytes */
    'I', 'n', 't', 'e', 'r', 'n', 'a', 'l', /* product      : 16 Bytes */
    ' ', 'f', 'l', 'a', 's', 'h', ' ', ' ',
    '1', '.', '0' ,'0',                     /* version      : 4 Bytes */
};

/* local function prototypes ('static') */
static int8_t storage_init (uint8_t Lun);
static int8_t storage_ready (uint8_t Lun);
static int8_t storage_write_protected (uint8_t Lun);
static int8_t storage_max_lun_get (void);
static int8_t storage_read (uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);
static int8_t storage_write (uint8_t lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len);

usbd_mem_cb USBD_Internal_Storage_fops =
{
    .mem_init      = storage_init,
    .mem_ready     = storage_ready,
    .mem_protected = storage_write_protected,
    .mem_read      = storage_read,
    .mem_write     = storage_write,
    .mem_maxlun    = storage_max_lun_get,

    .mem_inquiry_data = {(uint8_t *)storage_inquiry_data},

    .mem_block_size   = {ISFLASH_BLOCK_SIZE},
    .mem_block_len    = {ISFLASH_BLOCK_NUM}
};

usbd_mem_cb *usbd_mem_fops = &USBD_Internal_Storage_fops;

/*!
    \brief      initialize the storage medium
    \param[in]  Lun: logical unit number
    \param[out] none
    \retval     status
*/
static int8_t storage_init (uint8_t Lun)
{
    return 0;
}

/*!
    \brief      check whether the medium is ready
    \param[in]  Lun: logical unit number
    \param[out] none
    \retval     status
*/
static int8_t storage_ready (uint8_t Lun)
{
    flash_init();

    return 0;
}

/*!
    \brief      check whether the medium is write-protected
    \param[in]  Lun: logical unit number
    \param[out] none
    \retval     status
*/
static int8_t storage_write_protected (uint8_t Lun)
{
    return 0;
}

/*!
    \brief      read data from the medium
    \param[in]  Lun: logical unit number
    \param[in]  buf: pointer to the buffer to save data
    \param[in]  BlkAddr: address of 1st block to be read
    \param[in]  BlkLen: number of blocks to be read
    \param[out] none
    \retval     status
*/
static int8_t storage_read(uint8_t Lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
    if (0U != flash_multi_blocks_read(buf, blk_addr, ISFLASH_BLOCK_SIZE, blk_len)) {
        return 1;
    }

    return 0;
}

/*!
    \brief      write data to the medium
    \param[in]  Lun: logical unit number
    \param[in]  buf: pointer to the buffer to write
    \param[in]  BlkAddr: address of 1st block to be written
    \param[in]  BlkLen: number of blocks to be write
    \param[out] none
    \retval     status
*/
static int8_t storage_write (uint8_t Lun, uint8_t *buf, uint32_t blk_addr, uint16_t blk_len)
{
    if(0U != flash_multi_blocks_write(buf, blk_addr, ISFLASH_BLOCK_SIZE, blk_len)) {
        return 1;
    }

    return 0;
}

/*!
    \brief      get number of supported logical unit
    \param[in]  none
    \param[out] none
    \retval     number of logical unit
*/
static int8_t storage_max_lun_get (void)
{
    return (MEM_LUN_NUM - 1);
}
