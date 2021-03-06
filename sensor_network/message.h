/*
 * This header file represents messages and their operations
 * Authors: 
 * BOSCH Sami 		- 26821500
 * SIMON Benjamin 	- 37151500
 * SLUYTERS Arthur	- 13151500
 */

#include "contiki.h"
#include "contiki-lib.h"
#include "contiki-net.h"

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

//#define DEBUG DEBUG_PRINT

#include "net/rime.h"	

/*-----------------------------------------------------------------------------*/
/* Structure of the messages */
enum {
	DESTINATION_ADVERTISEMENT, 
	TREE_ADVERTISEMENT, 
	TREE_INFORMATION_REQUEST,
	SENSOR_DATA,
	SENSOR_CONTROL
};

// I think there is a better way to do this
struct msg_header {
	uint8_t version;	// Version of the protocol (less bits ?)
	uint8_t msg_type;	// Type of the message
	uint16_t length;	// Length of the payload
};

struct msg_dest_ad_payload {
	uint8_t tree_version;
	uint8_t source_id;
	uint8_t subject_id;
};

struct msg_tree_ad_payload {
	uint8_t tree_version;
	uint8_t source_id;
	uint8_t n_hops;
};

struct msg_tree_request_payload {
	uint8_t tree_version;
	uint8_t request_attributes;		// if request_attributes & 0x1 == 1 => tree_broken
};

struct msg_data_payload_h {
	uint8_t source_id;
	uint8_t subject_id;
	uint8_t length;
};

struct msg_data_payload {
	struct msg_data_payload_h *data_header;
	void *data;
	struct msg_data_payload *next;
};

struct msg_control_payload {
	uint8_t destination_id;
	uint8_t command;
};

struct message {
	struct msg_header *header;
	void *payload;
};

/*-----------------------------------------------------------------------------*/
/* Functions */

uint32_t encode_message(struct message *decoded_msg, char **encoded_msg);

void decode_message(struct message **decoded_msg, char *encoded_msg, uint16_t msg_len); 

struct message *copy_message(struct message *msg);

void free_message(struct message *msg);
