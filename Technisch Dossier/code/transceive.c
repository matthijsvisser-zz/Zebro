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

char nodeID[16];

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

	
//command(sbiv 1000);						// set broadcast interval
//Rx1: *RRN: AA1122334455,1F3CFF322133,0,001843,04,-56

void fillpopulationlist(char *message){
	char* myNodeId = "343556767898";
	char* messagePointer;
	char* databaseRow [DATASIZE];
	uint8_t count = 0;
	row_t* rowx;
	char* NodeID;

	rowx = (struct row *) malloc(sizeof(row_t));
	messagePointer = message;
	
	while(*messagePointer != ','){
		rowx -> id[count] = *messagePointer;
		*messagePointer++;
		count++;
	}
	*messagePointer++;
	rowx -> id[count] = EOS;
	count = 0;
	
	while(*messagePointer != ','){
		rowx -> targetID[count] = *messagePointer;
		*messagePointer++;
		count++;
	}
	*messagePointer++;
	rowx -> targetID[count] = EOS;
	count = 0;

	while(*messagePointer != ','){ //skip "0,"
		*messagePointer++;
	}
	*messagePointer++;
		
	while(*messagePointer != EOS ){
		rowx -> longRange[count] = *messagePointer;
		*messagePointer++;
		count++;
	}
	rowx -> longRange[count] = EOS;
	
	DebugPrint(rowx -> longRange);

	strcpy(rowx -> shortX, "n/a");
	strcpy(rowx -> shortY, "n/a");
	strcpy(rowx -> status, "0");
	
	databaseRow[0] = rowx -> id;
	databaseRow[1] = rowx -> longRange;
	databaseRow[2] = rowx -> shortX;
	databaseRow[3] = rowx -> shortY;
	databaseRow[4] = rowx -> status;
	
	if(strcmp(myNodeId, rowx -> id)!=0){ // if ID is not my ID
		databaseRow[0] = rowx -> id;
		
		if(viewListByValue(&listHead, rowx -> id, sizeOfList(listHead))==NULL){
			insert(&listHead,databaseRow);
		}else{
			popListByValue(&listHead, rowx ->id, sizeOfList(listHead));
			insert(&listHead,databaseRow);
		}	
	}else{ // if ID is my ID
		databaseRow[0] = rowx -> targetID;
		
		if(viewListByValue(&listHead, rowx -> targetID, sizeOfList(listHead))==NULL){
			// if not in list
			insert(&listHead,databaseRow);
			}else{
			// if already in list
			popListByValue(&listHead, rowx -> targetID, sizeOfList(listHead));
			insert(&listHead,databaseRow);
		}
	}

	DebugPrint(CLEARTERM);
	print_list(listHead);
}

char* getMyNodeID (){
	Command(GNID);
	strcpy(nodeID,TranslateMessage());
	return nodeID;
}

/**
 * Ranging result notification flag
 * @param  	
 * @param	
 */
void RRN_function (char *message){
	char* messagePointer;
	
	messagePointer = message;
	
	fillpopulationlist(message);
	
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
	
	//DebugPrint(message);

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