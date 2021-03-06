/* This file was autogenerated. All changes will be undone. */

/* Message: Vehicle_Telemetry_Command, ID: 1006*/

#include <comnet_marshal.h>
#include <comnet_message.h>
#include <message/VehicleTelemetryCommand.h>

msg_offset pack_vehicle_telemetry_command(
   vehicle_telemetry_command_t* vehicle_telemetry_command,
   msg_offset offset)
{
   offset = pack_uint64_t(vehicle_telemetry_command->timestamp,offset);
   offset = pack_uint16_t(vehicle_telemetry_command->vehicle_ID,offset);
   offset = pack_uint8_t(vehicle_telemetry_command->telemetry_select,offset);
   offset = pack_uint8_t(vehicle_telemetry_command->telemetry_rate,offset);
   return offset;
}

msg_offset unpack_vehicle_telemetry_command(
   msg_offset offset,
   vehicle_telemetry_command_t* out_ptr)
{
   offset = unpack_uint64_t(offset, &out_ptr->timestamp);
   offset = unpack_uint16_t(offset, &out_ptr->vehicle_ID);
   offset = unpack_uint8_t(offset, &out_ptr->telemetry_select);
   offset = unpack_uint8_t(offset, &out_ptr->telemetry_rate);
   return offset;
}

void encode_vehicle_telemetry_command(
   uint8_t src_id,
   uint8_t dest_id,
   vehicle_telemetry_command_t* tx_msg,
   com_msg_t* msg,
   uint8_t keyArr[])//key for encryption CryptoPP

{
   /** Random IV*/
   Random::RandomNumberGen randIV = Random::RandomNumberGen();
   randIV.generate_numbers<uint8_t>(msg->header.iv,0, AES::BLOCKSIZE,0,255);

   msg_offset start_offset, offset;
   msg->direction = Com_Out;
   start_offset = msg->data;
   offset = msg->data;
   msg->header.node_src_id = src_id;
   msg->header.node_dest_id = dest_id;
   msg->header.message_length = 12;
   msg->header.message_type = Com_Vehicle_Telemetry_Command;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   /** Encrypt */
   /* Managed C (CLR) will freak out if you pass SecByteBlock as an argument this is my half ass fix MW*/
   CryptoPP::SecByteBlock key(keyArr, AES::DEFAULT_KEYLENGTH);
   CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), msg->header.iv);
   cfbEncryption.ProcessData((byte*)offset, (byte*)offset, msg->header.message_length);

   offset = pack_vehicle_telemetry_command(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}