void receiver(){
	char[12] sendid;
	char[TDATLEN] trangedata;
	
	if(Rx1 == done sending mark){
		//Populationlist: mark sendid as done
		order();
	}
	
	//Rx1: = "AA1122334455"
	sendid = Rx1;
	if(Rx == AA1122334455 ){	//when broadcast message has been received
		PORTA.DIRSET = PIN1_bm; 
		//signal other microcontroller sending has started
		PORTA.DIRCLR = PIN1_bm;
	//Rx2: acoustic ranging results
	rangedata = Rx2;
	//TDATLEN = bytes data
	Tx1: ("sdat 1 %c TDATLEN %c\r\n",sendid, trangedata);		//send ranging information to sender
	}
}