/**
 *  File    list.c
 *  Created 03-05-2016
 *  Author  Matthijs Visser
 *          Amsterdam University of applied sciences
 *  contact Matthijs.Visser@hva.nl
**/

#include "list.h"
#include "uart_m.h"

node_t *listHead = NULL; // head

int sizeOfList(node_t *listHead);

void printHeaderList (void){
    char* number = NULL;
    DebugPrint("\r\nPopulationlist\r\n");
    DebugPrint("Nr.\t");
    for (int iteration = 0; iteration < DATASIZE; ++iteration){
        /*
        DebugPrint("Data[");
        itoa(iteration, number, 10);
        DebugPrint(number);
        DebugPrint("]\t\t");
        */
        switch(iteration){
            case 0: 
                DebugPrint("ID\t\t");
                break;
            case 1: 
                DebugPrint("Longrange\t");
                break;
            case 2: 
                DebugPrint("X\t\t");
                break;
            case 3: 
                DebugPrint("Y\t\t");
                break;
            case 4: 
                DebugPrint("status");
                break;
        }
    }
    DebugPrint("\r\n");
}

/**
 * Print data from list
 * @param  *head    List variable
 * @param  item     Used for iteration
 * @param  *current Status pointer to the current memory location
 * @param  data     Data from memory
 * @param  next    Status pointer to the next memory location
 */
void print_list(node_t *listHead) {
    char* number = NULL;
    int item, listNumber = 0;
    node_t *current = listHead;

    printHeaderList();
    while(current != NULL) {
        itoa(listNumber, number, 10);
        DebugPrint(number);
        DebugPrint("\t");
        for(item = 0; item < DATASIZE; item++){
            _delay_ms(1);
            DebugPrint(current -> data[item]);
                
            if ((item == 1) || (item == 2) || (item == 3)){
                DebugPrint("\t");
            }
            DebugPrint("\t");
        }  
        DebugPrint("\r\n");
        
        current = current -> next;
        ++listNumber;
    }
}

/**
 * Appends a data array to the end of the list.
 * @param  *head    List variable
 * @param  data     Data to write to memory
 * @param  *current Status pointer to the current memory location
 * @param  next    Status pointer to the next memory location
 */
void append (node_t *listHead, char* data[DATASIZE]){
    node_t *current = listHead;
    while (current -> next != NULL){
        current = current -> next;
    }
    current -> next = (struct node *) malloc(sizeof(node_t));
    for (int item = 0; item < DATASIZE; ++item){
        current -> next -> data[item] = data[item];
    }
    current -> next -> next = NULL;
}

/*
void insert (node_t ** head, char* dataInternal[DATASIZE]){
    node_t * new_node;
    new_node = (struct node *) malloc(sizeof(node_t));

    for (int item = 0; item < DATASIZE; ++item){

        //(*new_node).data[item] = data[item]
        new_node -> data[item] = dataInternal[item];
    }
    new_node -> next = *head;
    *head = new_node;
}*/



/**
 * Inserts a data array to the beginning of the list.
 * @param  *head    List variable
 * @param  data     Data to write to memory
 * @param  *current Status pointer to the current memory location
 * @param  next    Status pointer to the next memory location
 * @param  item     Used for iteration
 */
void insert (node_t ** listHead, char* dataInternal [DATASIZE]){
    node_t * new_node;
    size_t size = sizeof(node_t);
    
    new_node = (struct node *) malloc(sizeof(node_t));
    if (new_node == NULL){
        DebugPrint("No memory");
    }

    memset(new_node, 0, sizeof(node_t));
    
    for (int item = 0; item < DATASIZE; ++item){
        new_node -> data[item] = dataInternal[item];
    }
    
    new_node -> next = *listHead;
    *listHead = new_node;
}

char returnArray[DATASIZE];


/**
 * Reads the first data array from the list and removes it afterwards.
 * @param  *head    List variable
 * @param  data     Data to write to memory
 * @param  *current Status pointer to the current memory location
 * @param  next     Status pointer to the next memory location
 * @param  item     Used for iteration
 * @return returnArray Returns a pointer to the array where the data is stored. 
 */
char* pop (node_t ** head){
    node_t * next_node = NULL;

    if (*head == NULL) {
        return NULL;
    }
    next_node = (*head)->next;
    for (int item = 0; item < DATASIZE; ++item){
        returnArray[item] = (*head) -> data[item];
    }

    free(*head);
    *head = next_node;

    return *returnArray;
}

/**
 * Reads the first data array from the list.
 * @param  *head    List variable
 * @param  data     Data to write to memory
 * @param  *current Status pointer to the current memory location
 * @param  next     Status pointer to the next memory location
 * @param  item     Used for iteration
 * @return returnArray Returns a pointer to the array where the data is stored. 
 */
char* view (node_t ** head){
    node_t * next_node = NULL;

    if (*head == NULL) {
        return NULL;
    }
    next_node = (*head)->next;
    for (int item = 0; item < DATASIZE; ++item){
        returnArray[item] = (*head) -> data[item];
    }

    *head = next_node;

    return *returnArray;
}

/**
 * Pops the data array with the given index number from the list and 
 * removes it afterwards.
 * @param  *head    List variable
 * @param  indexNumber Index number of the wanted data array
 * @param  data     Data to write to memory
 * @param  *current Status pointer to the current memory location
 * @param  next     Status pointer to the next memory location
 * @param  item     Used for iteration
 * @return returnArray Returns a pointer to the array where the data is stored. 
 */
char* popListByNumber(node_t ** head, int indexNumber){
    node_t *current = *head, *temp_node = NULL;

    if (indexNumber == 0){
        return pop(head);
    }

    for (int item = 0; item < indexNumber-1; ++item){
        if (current -> next == NULL){
            return NULL;
        }
        current = current -> next;
    }

    temp_node = current -> next;

    for (int item = 0; item < DATASIZE; ++item){
        returnArray[item] = temp_node -> data[item];
    }

    current -> next = temp_node -> next;
    free(temp_node);

    return *returnArray;
}

/**
 * Pops the data array with the given value at the first data array
 * from the list andremoves it afterwards.
 * @param  *head    List variable
 * @param  indexNumber Index number of the wanted data array
 * @param  data     Data to write to memory
 * @param  *current Status pointer to the current memory location
 * @param  next     Status pointer to the next memory location
 * @param  item     Used for iteration
 * @return returnArray Returns a pointer to the array where the data is stored. 
 */
char* popListByValue(node_t ** head, char* value, int sizeOfList){
    node_t *current = *head,*temp_node = NULL;
    
    if (strcmp(current -> data[FIRSTDATAITEM], value)==0){
        return pop(head);
    }

    for (int item = 1; item < sizeOfList; ++item){
        temp_node = current -> next;
        if(strcmp(temp_node -> data[FIRSTDATAITEM], value)==0){
            for (int itemb = 0; itemb < DATASIZE; ++itemb){
                returnArray[itemb] = *temp_node -> data[itemb];
            }
            current -> next = temp_node -> next;
            free(temp_node);

            return *returnArray;
        }
        current = current -> next;
    }
    return NULL;
}

/**
 * Views the data array with the given value.
 * @param  *head    List variable
 * @param  indexNumber Index number of the wanted data array
 * @param  data     Data to write to memory
 * @param  *current Status pointer to the current memory location
 * @param  next     Status pointer to the next memory location
 * @param  item     Used for iteration
 * @return returnArray Returns a pointer to the array where the data is stored. 
 */
char* viewListByValue(node_t ** head, char* value, int sizeOfList){
    node_t *current = *head,*temp_node = NULL;
    
    if (strcmp(current -> data[FIRSTDATAITEM], value)==0){
        return pop(head);
    }

    for (int item = 1; item < sizeOfList; ++item){
        temp_node = current -> next;
        if(strcmp(temp_node -> data[FIRSTDATAITEM], value)==0){
            for (int itemb = 0; itemb < DATASIZE; ++itemb){
                returnArray[itemb] = *temp_node -> data[itemb];
            }
            current -> next = temp_node -> next;

            return *returnArray;
        }
        current = current -> next;
    }
    return NULL;
}

/**
 * Retrieves the amount of data arrays in the list.
 * @param  *head    List variable
 * @param  *current Status pointer to the current memory location
 * @param  next    Status pointer to the next memory location
 * @param  sizeOfList Amount of data arrays in the list.
 */
int sizeOfList(node_t *listHead){
    int sizeOfList = 1;
    node_t * current = listHead;

    while (current -> next != NULL){
        current = current -> next;
        sizeOfList++;
    }
    return sizeOfList;
}
