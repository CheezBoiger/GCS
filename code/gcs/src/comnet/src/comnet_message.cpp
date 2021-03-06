/* This file was autogenerated. All changes will be undone. */

#include <string.h>
#include <stdio.h>
#include <comnet_marshal.h>
#include <comnet_message.h>

#include <standard_logic.h>
msg_offset pack_sync(msg_offset offset)
{
   *offset = 'C';
   *(offset+1) = 'P';
   *(offset+2) = 'P';
   *(offset+3) = 0;
   return offset+4;
}

checksum_t fletcher16(msg_offset start, msg_offset end)
    {
        uint8_t count = end - start;
        uint16_t sum1 = 0;
        uint16_t sum2 = 0;
        int index;

        for (index = 0; index < count; ++index)
        {
            sum1 = (sum1 + start[index]) % 255;
            sum2 = (sum2 + sum1) % 255;
        }

        return (sum2 << 8) | sum1;
    }

msg_offset pack_checksum(
   const msg_offset start,
   const msg_offset end)
{
checksum_t sum = fletcher16(start, end);
return pack_uint16_t(sum, end);

}

msg_offset unpack_checksum(
   msg_offset offset,
   checksum_t* out_ptr)
{
   return unpack_uint16_t(offset, (uint16_t*)out_ptr);
}

msg_offset pack_header(
   com_header_t* header,
   msg_offset offset)
{
    /** Shift the message length one bit to the left and merge it with the is_emergency! */
    /** ex.
		message length (15 bit)   is_emergency (1 bit)
		100000000000010           1

		shift left -->   1           000000000000100      
						discarded!
						
						MERGE

						0000000000001001 <-- OUTPUT
    */

   uint16_t merged_data = LSHIFT_BIT_1(header->message_length) | header->is_emergency;

   offset = pack_uint8_t(header->node_src_id, offset);
   offset = pack_uint8_t(header->node_dest_id, offset);
   offset = pack_uint8_t_ptr(header->iv, offset,16 );
   offset = pack_uint16_t(header->message_type, offset);
   offset = pack_uint16_t(merged_data, offset);
   return offset;
}

   /**Grabs the mergd bit pattern and obtains the least significant bit for the emergency 
    comcol, and obtains the last 15 bits for the message length.    
    shift the bit value right 0 times, meaning do nothing, then AND it by value 1 to obtain
    least sig bit that determines if the header contains an emergency (1) or not (0).                 
    OBTAIN FOR MESSAGE LENGTH-> 000000000000100 | 1 <- OBTAIN LAST ONE FOR EMERGENCY!*/
    inline void unpack_merged_variable(com_header_t* out_ptr, uint16_t* merged_message)
    {
        out_ptr->is_emergency = RSHIFT_BIT_0(*merged_message) & LEAST_SIG_BIT;

        // Shift to the right one bit and AND it by the max value obtainable with 16 bits.
        out_ptr->message_length = RSHIFT_BIT_1(*merged_message) & UBIT16_MAX;
    }

msg_offset unpack_header(
   msg_offset offset,
   com_header_t* out_ptr)
{
   uint16_t merged_message;
   offset = unpack_uint8_t(offset, &out_ptr->node_src_id);
   offset = unpack_uint8_t(offset, &out_ptr->node_dest_id);
   offset = unpack_uint8_t_ptr(offset, out_ptr->iv,16);
   offset = unpack_uint16_t(offset, &out_ptr->message_type);
   offset = unpack_uint16_t(offset, &merged_message);
   unpack_merged_variable(out_ptr, &merged_message);
   return offset;
}
