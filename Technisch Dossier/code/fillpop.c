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