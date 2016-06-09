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
        DebugPrint("Data[");
        itoa(iteration, number, 10);
        DebugPrint(number);
        DebugPrint("]\t");
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
void printList(node_t *listHead) {
    char* number = NULL;
    int item, listNumber = 0;
    node_t *current = listHead;

    printHeaderList();
    while(current != NULL) {
        itoa(listNumber, number, 10);
        DebugPrint(number);
        DebugPrint("\t");
        for(item = 0; item < DATASIZE; item++){
            DebugPrint(current -> data[item]);
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
void appendList (node_t *listHead, char* data[DATASIZE]){
    node_t *current = listHead;
    while ((*current).next != NULL){
        current = (*current).next;
    }
    (*current).next = (struct node *) malloc(sizeof(node_t));
    if (new_node == NULL){
        DebugPrint("No memory");
    }
    for (int item = 0; item < DATASIZE; ++item){
        (*current).(*next).data[item] = data[item];
    }
    current -> next -> next = NULL;
}

/**
 * Inserts a data array to the beginning of the list.
 * @param  *head    List variable
 * @param  data     Data to write to memory
 * @param  *current Status pointer to the current memory location
 * @param  next    Status pointer to the next memory location
 * @param  item     Used for iteration
 */
void insertList (node_t ** listHead, char* dataInternal [DATASIZE]){
    node_t * new_node;
    new_node = (struct node *) malloc(sizeof(node_t));
    if (new_node == NULL){
        DebugPrint("No memory");
    }

    for (int item = 0; item < DATASIZE; ++item){
        (*new_node).data[item] = dataInternal[item];
    }
    (*new_node).next = *listHead;
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
char* popList (node_t ** head){
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

    return returnArray;
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
        current = (*current).next;
    }

    temp_node = (*current).next;

    for (int item = 0; item < DATASIZE; ++item){
        returnArray[item] = (*temp_node) -> data[item];
    }

    (*current).next = (*temp_node).next;
    free(temp_node);

    return returnArray;
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
    
    if ((*current).data[FIRSTDATAITEM] == value){
        return pop(head);
    }

    for (int item = 1; item < sizeOfList; ++item){
        temp_node = (*current).next;
        printf("Item %d, data [%s]\n", item, (*temp_node).data[FIRSTDATAITEM]);
        if((*temp_node).data[FIRSTDATAITEM] == value){
            for (int itemb = 0; itemb < DATASIZE; ++itemb){
                returnArray[itemb] = *(*temp_node).data[itemb];
            }
            (*current).next = (*temp_node).next;
            free(temp_node);

            return returnArray;
        }
        current = current -> next;
    }
    return 0;
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

    while ((*current).next != NULL){
        current = (*current).next;
        sizeOfList++;
    }
    return sizeOfList;
}

/*
int main(void){

    int datb[DATASIZE];
    
    system("clear");

    for (int i = 0; i < DATASIZE; ++i){
        datb[i]=i+5;
    }

    insert(&head,datb);

    for (int i = 0; i < DATASIZE; ++i){
        datb[i]=i+1;
    }

    append(head,datb);

    for (int i = 0; i < DATASIZE; ++i){
        datb[i]=i+8;
    }
    append(head,datb);

    // print_list(head);

    ##################################### 

    // printf("POP\n");
    // printf("POP't information\n");
    char value = pop(&head);
    // if (pop != NULL){
    //  for (int i = 0; i < DATASIZE; ++i){
    //      // printf("%d\t",*value);
    //      *value++;
    //  }
    // }
    // printf("\n");

    // printf("\n");
    // print_list(head);

    ##################################### 

    // for (int i = 0; i < DATASIZE; ++i){
    //  datb[i]=i+15;
    // }

    // append(head,datb);

    // for (int i = 0; i < DATASIZE; ++i){
    //  datb[i]=i+18;
    // }
    // append(head,datb);
    // printf("size of list:%d\n",sizeOfList(head));

    // print_list(head);

    // printf("POP't information\n");
    // value = popListByNumber(&head, 0);
    // if (pop != NULL){
    //  for (int i = 0; i < DATASIZE; ++i){
    //      printf("%d\t",*value);
    //      *value++;
    //  }
    // }
    // printf("\n");
    // print_list(head);

    ##################################### 

    for (int i = 0; i < DATASIZE; ++i){
        datb[i]=i+75;
    }

    append(head,datb);

    for (int i = 0; i < DATASIZE; ++i){
        datb[i]=i+98;
    }
    append(head,datb);
    // printf("size of list:%d\n",sizeOfList(head));

    print_list(head);

    printf("POP't information\n");
    value = popListByValue(&head, 8, sizeOfList(head));
    if (pop != NULL){
        for (int i = 0; i < DATASIZE; ++i){
            printf("%d\t",*value);
            *value++;
        }
    }

    print_list(head);

    return 0;
}
*/