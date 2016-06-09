void fillpopulationlist(char *message){	
	char *messagePointer;
	char srcid[12];
	char destid[12];
	int distance[6];
	uint8_t count, c;
	c = 0;
	count = 0;

	memset(srcid, EOS, strlen(srcid));	
	messagePointer = message;
	
	command(sbiv 1000);		// set broadcast interval
	//Rx1: *RRN: AA1122334455,1F3CFF322133,0,001843,04,-56
	
	while(*messagePointer != ','){
		//uart_putc(&uartC1, *messagePointer);
		switch(c)
		{
		case 0:		//first part of broadcast is source ID
			srcid[count] = *messagePointer;			
		case 1:		//second part is destination ID
			destid[count] = *messagePointer;
		case 3:		//third part is range
			distance[count] = *messagePointer;
			c = 0;
		}
		*messagePointer++;
		count++;
	}

	if(*messagePointer == ','){c++;};				
	//next part of the broadcast message
	if(Srcid =! myid){		
		Populationlist(srcid, longrange);			
	}
	else if(destid =! myid){
		Populationlist(destid, longrange);	
	}		
	//population list is filled
}