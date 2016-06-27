GNID

=001122334455

*RRN :1 F3123123133 ,1 F3CFF322133 ,0 ,001843

Command(NCFG0);
Command(SBIV500);

if (ValidateMessage(message,TYPE_RRN) == true){
	DetermineCommandtype(message);

if		(strcmp(command, "*RRN") == 0){	
	fillpopulationlist(messagePointer);
	
