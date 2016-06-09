/**
 *	File	transceive.c
 *	Created 17-05-2016
 *	Author	Matthijs Visser
 *			Amsterdam University of applied sciences
 *	contact Matthijs.Visser@hva.nl
**/

//#include "main.h"
#include "uart.h"
#include "transceive.h"
#include "list.h"

extern USART_data_t uartC0;
extern USART_data_t uartC1;
extern node_t *listHead;

/**
 * Validates the integrity of the received message
 * @param   *message   Received message
 * @param   command    Type of command
 * @return  true/false 
 */
uint8_t ValidateMessage (char *message, uint8_t command){
    uint8_t messageLength;
    messageLength = strlen(message) - 2;

    switch (command) {
        case 1: // command RRN
            if (messageLength == RRN_LENGTH){
                return true;
            }
        case 2: // command XX
            if (messageLength == RRN_LENGTH){
                return false;
            }
        case 3: // command XX
            if (messageLength == RRN_LENGTH){
                return false;
            }
        default:
            return false;
    }
}

void fillpopulationlist(char *message){				//*RRN bericht
	char *messagePointer;
	char srcid[12], destid[12];
	int distance[6];
	uint8_t count, c;
	c = 0;
	count = 0;

	memset(srcid, EOS, strlen(srcid));	
	messagePointer = message;
	
	//command(sbiv 1000);						// set broadcast interval
	//Rx1: *RRN: AA1122334455,1F3CFF322133,0,001843,04,-56
	
	*messagePointer++;
	
	while(*messagePointer != ','){
		srcid[count] = *messagePointer;
		*messagePointer++;
		count++;
	}
	
	srcid[count] = EOS;

	char* database [8];
	char* datafield = srcid;
	
	database[0] = datafield;
	
	for (int i = 1; i < 8; ++i){
		//*database[i]= *empty;
		database[i] = "test";
	}
	
	//insert(&listHead,*database);
	append(listHead,database);
	
	print_list(listHead);
	
/*	
	char* database [8];
	char* empty = "empty";
	
	for (int i = 0; i < 8; ++i){
		database[i]= empty;
	}
	
	insert(&listHead,database);
*/
	
	
	//DebugPrint("\r\n");
	//DebugPrint(srcid);
	//DebugPrint("\r\n");
	
	
	
	
	
	
	
	
	
	
	//DebugPrint("destid\r\n");
	//DebugPrint("distance\r\n");
	
	//if(Srcid =! myid){
		//Populationlist: nodeid = srcid 
		//Populationlist: longrange = distance
	//}

	//if(destid =! myid){
		//Populationlist: nodeid = destid 
		//Populationlist: longrange = distance	
	//}		
}


/**
 * Ranging result notification flag
 * @param  	
 * @param	
 */
void RRN_function (char *message){
	uart_puts(&uartC1, "\r\nfunctie\r\n");
	DebugPrint(message);
}


/**
 * Determines the meaning of the message
 * @param  	value	received value
 * @param	DetermineCommandtype
 */
void DetermineCommandtype (char *message){
	char *messagePointer;
	char command[4];
	uint8_t count = 0;
	
	memset(command, EOS, strlen(command));	
	messagePointer = message;
	
	DebugPrint(message);

	*messagePointer++;
	
	while(*messagePointer != COMMAND_END){
		*messagePointer++;
		if(*messagePointer == ( COMMAND_END)){ break;}		
		command[count] = *messagePointer;		
		count++;
	}
	command[count] = EOS;
	
	*messagePointer++;

	if		(strcmp(command, "*RRN") == 0){	// Data Notification Message
		//RRN_function(messagePointer);
		fillpopulationlist(messagePointer);
	}else if(strcmp(command, "DNO")  == 0){	// Node ID Notification Message
		
	}else if(strcmp(command, "NIN")  == 0){	// Ranging Result Notification Message
		//printf("NIN\n");
	}else if(strcmp(command, "SDAT") == 0){	// SDAT Notification Messages
		//printf("SDAT\n");
	}else if(strcmp(command, "AIR")  == 0){	// AIR Notification Message
		//printf("AIR\n");
	}else{
		DebugPrint("No command\r\n");
	}
}

char globalMessage[128];

/**
 * Translates the received message converts characters
 * to a single string
 * @param  	value	received value
 * @return	message pointer to the translated message
 */
char * TranslateMessage (void){
	char value[128];

	memset(globalMessage, EOS, strlen(globalMessage));
	memset(value, EOS, strlen(value));

	value[0] = uart_getc(&uartC0);
	strcpy(globalMessage, value);
	while (value[0] != CR){
		if (value[0] != CR){	
			
			strcat(globalMessage, value);	
		}
		value[0] = uart_getc(&uartC0);
	}
	return globalMessage;
}