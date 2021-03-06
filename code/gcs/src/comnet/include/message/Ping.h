/**@file This file was autogenerated. All changes will be undone. */

/** Message: Ping, ID: 0001*/

#ifndef _PING_H_
#define _PING_H_

#include <comnet_marshal.h>
#include <comnet_message.h>

#include"random_numbers.h"
#include "aes.h"
using CryptoPP::AES;
#include "ccm.h"
using CryptoPP::CFB_Mode;
typedef struct {
   float64_t timestamp;
} ping_t;

msg_offset pack_ping(
   ping_t* ping,
   msg_offset offset);

msg_offset unpack_ping(
   msg_offset offset,
   ping_t* out_ptr);

void encode_ping(
   uint8_t src_id,
   uint8_t dest_id,
   ping_t* tx_msg,
   com_msg_t* msg,
   uint8_t keyArr[]);//key for encryption CryptoPP

#endif