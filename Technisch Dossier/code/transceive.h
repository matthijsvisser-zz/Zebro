/**
 *	File	transceive.h
 *	Created 19-05-2016
 *	Author	Matthijs Visser
 *			Amsterdam University of applied sciences
 *	contact Matthijs.Visser@hva.nl
**/
#ifndef TRANSCEIVE_H_
#define TRANSCEIVE_H_

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>

#include "uart.h"
#include "uart_m.h"


#define NL			'\n'				// New line
#define CR			'\r'				// Carriage return
#define EOS			'\0'				// End of string

/* Command lengths */
#define RRN_LENGTH	39
#define ID_LENGTH	13
#define TYPE_RRN	1

#define COMMAND_END		':'
#define COMMAND_BEGIN	'*'

/* Begin of Swarm Bee API command list*/
// Setup commands
#define SNID		"snid\r\n"			// Sets the Node ID of swarm node
#define GNID		"gnid\r\n"			// Get Node ID of the node connected to host
#define SSET		"sset\r\n"			// Save SETtings; saves all settings including Node ID permanently to EEPROM
#define GSET		"gset\r\n"			// Get current SETtings (node configuration)

#define GFWV		"gfwv\r\n"			// Get the FirmWare Version of the swarm Node

// Ranging commands
#define RATO		"rato\r\n"			// RAnge TO; initiates an elementary ranging cycle to another swarm node
#define BRAR		"brar\r\n"			// Broadcast RAnging Results; enabled (or disabled) the broadcasting of 
										// ranging results after each successful ranging operation.
#define SROB		"srob\r\n"			// Selects Ranging Operation Blinks; sets which classes of devices the node will initiate a
										// ranging operation with upon reception of a node blink ID packet.
#define ERRN		"errn\r\n"			// Enables (or disables) Ranging Result Notification
#define GRWL		"grwl\r\n"			// Get Ranging White List.

// Data communication commands
#define EDAN		"edan\r\n"			// Enables and disables DAta Notification
#define SDAT		"sdat\r\n"			// Sends DATa to node ID
#define GDAT		"gdat\r\n"			// Gets received DATa
#define BDAT		"bdat\r\n"			// Broadcasts DATa

#define SBIV1000	"SBIV 1000\r\n"
#define SBIV500		"SBIV 500\r\n"
#define SBIV100		"SBIV 100\r\n"

#define EBID		"ebid\r\n"			// Enable Broadcast ID. Enables and disables broadcast of Node ID blink packets
#define EIDN		"eidn\r\n"			// Enables and disables Node ID Broadcast Notification

// Swarm radio node identification
#define NCFG0		"NCFG 0\r\n"		// Disable all RRN device parameter messages

/* End of Swarm Bee API command list*/

#define RRN			"*RRN"				// Ranging result notification

void DetermineCommandtype ();
char * TranslateMessage (void);
uint8_t ValidateMessage (char *message, uint8_t command);
uint16_t uart_getc(USART_data_t *uart);



#endif /* MAIN_H_ */
/**
 * Determines the meaning of the message
 * @param  	value	received value
 * @param	DetermineCommandtype
 */