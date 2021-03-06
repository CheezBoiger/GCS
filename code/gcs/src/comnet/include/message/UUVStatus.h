/**@file This file was autogenerated. All changes will be undone. */

/** Message: UUV_Status, ID: 8000*/

#ifndef _UUV_STATUS_H_
#define _UUV_STATUS_H_

#include <comnet_marshal.h>
#include <comnet_message.h>

#include"random_numbers.h"
#include "aes.h"
using CryptoPP::AES;
#include "ccm.h"
using CryptoPP::CFB_Mode;
typedef struct {
   uint8_t status;
} UUV_status_t;

msg_offset pack_UUV_status(
   UUV_status_t* UUV_status,
   msg_offset offset);

msg_offset unpack_UUV_status(
   msg_offset offset,
   UUV_status_t* out_ptr);

void encode_UUV_status(
   uint8_t src_id,
   uint8_t dest_id,
   UUV_status_t* tx_msg,
   com_msg_t* msg,
   uint8_t keyArr[]);//key for encryption CryptoPP

#endif