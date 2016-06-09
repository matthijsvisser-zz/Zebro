void sender(){
	char[12] recid;
	char[RDATLEN] rrangedata;	
	
	PORTA.DIRSET = PIN0_bm;
	//signal other microcontroller to send acoustic signal
	Tx1: ("bdat 0 BDATLEN %c\r\n",myid);						
	PORTA.DIRCLR = PIN0_bm;
	//broadcast start of acoustic sending
	
	//Rx2: sends signal when sendingprocess is finished
	if (Rx2 == "finished"){
		command(gdat);			//read out transmitted data
		//Rx1: "=RDATLEN,recid,rrangedata"			
		if(RDATLEN =! 0){
			populationlist(recid,0,x,y);
			//fills populationlist frame
		}
		else{
			//Populationlist: mark myid as done sending
			command("bdat 0 BDATLEN %c\r\n",mark);
			//done sending mark
			order();
		}
	}	
}