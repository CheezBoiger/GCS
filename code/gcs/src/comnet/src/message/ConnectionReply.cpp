/* This file was autogenerated. All changes will be undone. */

/* Message: Connection_Reply, ID: 0006*/

#include <comnet_marshal.h>
#include <comnet_message.h>
#include <message/ConnectionReply.h>

msg_offset pack_connection_reply(
   connection_reply_t* connection_reply,
   msg_offset offset)
{
   offset = pack_float64_t(connection_reply->timestamp,offset);
   offset = pack_uint8_t(connection_reply->connection_ID,offset);
   offset = pack_uint8_t(connection_reply->trace_node_n,offset);
   offset = pack_uint8_t(connection_reply->trace_node_n_1,offset);
   return offset;
}

msg_offset unpack_connection_reply(
   msg_offset offset,
   connection_reply_t* out_ptr)
{
   offset = unpack_float64_t(offset, &out_ptr->timestamp);
   offset = unpack_uint8_t(offset, &out_ptr->connection_ID);
   offset = unpack_uint8_t(offset, &out_ptr->trace_node_n);
   offset = unpack_uint8_t(offset, &out_ptr->trace_node_n_1);
   return offset;
}

void encode_connection_reply(
   uint8_t src_id,
   uint8_t dest_id,
   connection_reply_t* tx_msg,
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
   msg->header.message_length = 11;
   msg->header.message_type = Com_Connection_Reply;
   offset = pack_sync(offset);
   offset = pack_header(&msg->header, offset);

   /** Encrypt */
   /* Managed C (CLR) will freak out if you pass SecByteBlock as an argument this is my half ass fix MW*/
   CryptoPP::SecByteBlock key(keyArr, AES::DEFAULT_KEYLENGTH);
   CFB_Mode<AES>::Encryption cfbEncryption(key, key.size(), msg->header.iv);
   cfbEncryption.ProcessData((byte*)offset, (byte*)offset, msg->header.message_length);

   offset = pack_connection_reply(tx_msg, offset);
   offset = pack_checksum(start_offset, offset);
   msg->tx_len = offset-start_offset;
}