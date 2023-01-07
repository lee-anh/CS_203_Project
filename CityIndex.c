#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CityIndex.h"
 
/**
 * Creates a CityIndex
 * Mallocs space, sets size to 0 and head/tail to NULL
 * @return pointer to CityIndex created 
 */ 
CityIndex* createCityIndex(){
    CityIndex *c = malloc(sizeof(CityIndex));
    c->size = 0; 
    c->head = NULL;
    c->tail = NULL;
    return c; 
}

/**
 * Inserts into the CityIndex linkedlist in lexiographic sorted order 
 * Mallocs a new node and inializes it 
 * Handles insertion to empty linked list, head/middle/tail of linked list 
 * @param c CityIndex to insert into
 * @param city to insert
 * @param restIndex to insert 
 */ 
void insertInCityIndex(CityIndex* c, char* city, Restaurant* restIndex){

    CityNode* cNode = malloc(sizeof(CityNode)); 
    cNode->data = city;
    cNode->restIndex = restIndex; 
    cNode->next = NULL;
    cNode->prev = NULL;

    // empty insertion 
    if(c->size == 0){
        c->head = cNode;
        c->tail = cNode;
        c->size += 1;
        //printf("Inserted when empty\n");
        return;
    }

    CityNode* curr = c->head;

    int cCount = c->size;

    for(int i = 0; i < cCount; i++){

        int res = strcmp(curr->data, cNode->data);

        // if cNode data is greater than equal to zero, insert right before 
        if(res >= 0){
            if(i == 0){
                // insert at head 
                cNode->next = curr;
                curr->prev = cNode;
                c->head = cNode;
                //printf("Inserted at head\n");
            } else {
                // insert in body of linked list
                cNode->prev = curr->prev;
                cNode->next = curr;
                
                if(curr->prev != NULL){
                    curr->prev->next = cNode;
                }
                
                curr->prev = cNode; 
               // printf("Inserted at body\n");
            }
            c->size += 1;
            return; 
        }
        
        
        if(i != c->size - 1){
            // continue traversing 
            curr = curr->next;

        } else {
            // last element, insert at end 
            cNode->prev = curr;
            curr->next = cNode;
            c->tail = cNode;
            c->size += 1; 
           //printf("Inserted at end\n");
        }
    }
    
}

/**
 * Remove a list of restaurants from the linked list 
 * Traverses the linked list 
 * @param toDelete LinkedList of Restaurants to delte 
 * @param c CityIndex to delete from 
 */ 
void deleteFromCityIndex(LinkedList* toDelete, CityIndex* c){
    RestNode* curr = toDelete->head; 
    while(true){
        deleteRestFromCityIndex(curr->r, c); 
        if(curr->next != NULL){
            curr = curr->next; 
        } else {
            break; 
        }
    }
} 

/**
 * Delete an individual restuarant from the CityIndex 
 * Helper frunction to deleteFromCityIndex
 * Takes care of removal from empty list and 3 cases:
 * removal of head, removal of tail, removal from body  
 * @param toDelete Restaurant to delete 
 * @param c CityIndex to delete from 
 */
void deleteRestFromCityIndex(Restaurant* toDelete, CityIndex* c){
    CityNode* curr = c->head; 
    while(true){
        if(curr->restIndex == toDelete){
            // delete using the correct case 
            CityNode* temp = curr; 
            if(curr == c->head){
                // head node 
                CityNode* newHead = curr->next;
                newHead->prev = NULL;
                c->head = newHead; 
                
                // increment to the next one here 
                curr = newHead; 
            } else if (curr == c->tail){
                // tail node 
                CityNode* newTail = curr->prev; 
                newTail->next = NULL;
                c->tail = newTail; 
                c->size -= 1; 
                free(temp); 

                // no need to increment. We are at the end 
                break; 
            } else {
                // body node 
                CityNode* prev = curr->prev;
                CityNode* next = curr->next;

                prev->next = next;
                next->prev = prev;
                // increment to the next one here 
                curr = next; 
                

            }
            // decrement the size 
            c->size -= 1;
            free(temp); 


        } else {
            if(curr->next != NULL){
                curr = curr->next; 
            } else {
                break; 
            }

        }
        
    }
}



/**
 * Prints out the contents of the CityIndex by iterating through the linked list
 * @param c CityIndex to print 
 */ 
void printCityIndex(CityIndex* c){
    CityNode* curr = c->head; 
    for(int i = 0; i < (int) c->size; i++){
        printf("%s\n", curr->data);
        if(i != c->size - 1){
            curr = curr->next; 
        }
    }
    printf("\n"); 
}

/**
 * Frees the underlying linkedlist, the CityNodes that make up the linked lists, 
 * and the object itself 
 * @param c CityIndex to free 
 */ 
void cityIndexDestructor(CityIndex *c){
    CityNode* curr = c->head;
    int cSize = c->size;
    for(int i = 0; i < cSize; i++){
        CityNode* temp = NULL;
        if(i != cSize -1){
            temp = curr->next;
        }
        free(curr);
        curr = temp;
    }
    free(c); 

}
