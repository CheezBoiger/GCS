/**@file This file was autogenerated. All changes will be undone. */

/** Message: Payload_Operating_Status, ID: 4002*/

#ifndef _PAYLOAD_OPERATING_STATUS_H_
#define _PAYLOAD_OPERATING_STATUS_H_

#include <comnet_marshal.h>
#include <comnet_message.h>

#include"random_numbers.h"
#include "aes.h"
using CryptoPP::AES;
#include "ccm.h"
using CryptoPP::CFB_Mode;
typedef struct {
   float64_t timestamp;
   uint16_t payload_ID;
   uint8_t payload_mode;
   uint8_t payload_status;
} payload_operating_status_t;

msg_offset pack_payload_operating_status(
   payload_operating_status_t* payload_operating_status,
   msg_offset offset);

msg_offset unpack_payload_operating_status(
   msg_offset offset,
   payload_operating_status_t* out_ptr);

void encode_payload_operating_status(
   uint8_t src_id,
   uint8_t dest_id,
   payload_operating_status_t* tx_msg,
   com_msg_t* msg,
   uint8_t keyArr[]);//key for encryption CryptoPP

#endif