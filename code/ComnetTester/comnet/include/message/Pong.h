/**@file This file was autogenerated. All changes will be undone. */

/** Message: Pong, ID: 0002*/

#ifndef _PONG_H_
#define _PONG_H_

#include <comnet_marshal.h>
#include <comnet_message.h>

#include"random_numbers.h"
#include "aes.h"
using CryptoPP::AES;
#include "ccm.h"
using CryptoPP::CFB_Mode;
typedef struct {
   float64_t timestamp;
} pong_t;

msg_offset pack_pong(
   pong_t* pong,
   msg_offset offset);

msg_offset unpack_pong(
   msg_offset offset,
   pong_t* out_ptr);

void encode_pong(
   uint8_t src_id,
   uint8_t dest_id,
   pong_t* tx_msg,
   com_msg_t* msg,
   uint8_t keyArr[]);//key for encryption CryptoPP

#endif