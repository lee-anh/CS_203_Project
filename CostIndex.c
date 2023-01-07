#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "CostIndex.h"

/**
 * Creates an CostIndex which consists of 3 CostLinkedlists
 * low = all $ restaruants
 * med = all $$ restaurants 
 * high = all $$$ restaurants
 * (kind of like a hashmap that has a high collison rate)
 * handles mem alloc and initalizing fields to basic values 
 * @return CostIndex 
 */ 
CostIndex* createCostIndex(){
    CostIndex* c = malloc(sizeof(CostIndex)); 

    CostLinkedList* low = malloc(sizeof(CostLinkedList));
    CostLinkedList* med = malloc(sizeof(CostLinkedList));
    CostLinkedList* high = malloc(sizeof(CostLinkedList));

    low->size = 0; 
    low->head = NULL; 
    low->tail = NULL; 

    med->size = 0; 
    med->head = NULL; 
    med->tail = NULL; 

    high->size = 0; 
    high->head = NULL; 
    high->tail = NULL; 

    c->low = low;
    c->med = med; 
    c->high = high;
    return c; 

}

/**
 * Inserts the restIndex into the right CostLinkedList
 * 
 */ 
void insertInCostIndex(CostIndex *ci, int cVal, Restaurant* restIndex){
    if(cVal == 1){
        insertInCostLinkedList(ci->low, restIndex); 
    } else if (cVal == 2){
        insertInCostLinkedList(ci->med, restIndex); 
    } else if (cVal == 3){
        insertInCostLinkedList(ci->high, restIndex); 
    }
    return; 
}

/**
 * Inserts restIndex into the back of the linked list 
 * @param cll CostLinkedList to insert into
 * @param restIndex restaurant index which will become the Node data 
 */ 
void insertInCostLinkedList(CostLinkedList *cll, Restaurant* restIndex){
    // create nodes and stuff 
    Node* curr = malloc(sizeof(Node));
    curr->next = NULL; 
    curr->prev = NULL; 
    curr->data = restIndex; 

    if(cll->size == 0){
        cll->head = curr; 
        cll->tail = curr; 
    } else {
        // insert at back 
        curr->prev = cll->tail; 
        cll->tail->next = curr; 
        cll->tail = curr; 
    }
    cll->size += 1; 
    return; 
}

/**
 * search the CostIndex for all restaurants in the given linked list that match in cost
 * or are lower in cost 
 * $$$ is considered a wild card 
 * @param ll linkedList of Restaurants to check 
 * @param c costIndex of knowledge base 
 * @param cost cost to search for 
 */ 

LinkedList* searchCostIndex(LinkedList*ll, CostIndex* c, int cost){
    LinkedList* toReturn = createLinkedList(); 
    if(cost == 2){
        // check the mediums and the lows 
        Node* curr = c->med->head; 
        while(true){
            if(isInLinkedList(ll, curr->data) == true){
                insertInLinkedList(toReturn, curr->data); 
            }
            if(curr->next != NULL){
                curr = curr->next;
            } else {
                break; 
            }

        }

    }
    // check the lows 
    // check the mediums and the lows 
        Node* curr = c->low->head; 
        while(true){
            if(isInLinkedList(ll, curr->data) == true){
                insertInLinkedList(toReturn, curr->data); 
            }
            if(curr->next != NULL){
                curr = curr->next;
            } else {
                break; 
            }

        }
    linkedListDestructor(ll); 
    return toReturn; 
}


/**
 * Delete a list of restaurants from the CostIndex
 * Calls the helper function deleteFromCostLinkedList 3 times for the lows, mediums, and highs 
 * @param toDelete LinkedList of restaurants to delete from
 * @param c CostIndex to remove from 
 */ 
void deleteFromCostIndex(LinkedList* toDelete, CostIndex* c){
    deleteFromCostLinkedList(toDelete, c->low);
    deleteFromCostLinkedList(toDelete, c->med);
    deleteFromCostLinkedList(toDelete, c->high);

}

/**
 * Helper to deleteFromCostIndex 
 * Traverses through the LinkedList 
 * @param toDelete LinkedList of restaurants to delete
 * @param cll cost linked list to delete from 
 */ 
void deleteFromCostLinkedList(LinkedList* toDelete, CostLinkedList* cll){
    RestNode* curr = toDelete->head; 
    while(true){
        deleteRestFromCostLinkedList(curr->r, cll); 
        if(curr->next != NULL){
            curr = curr->next; 
        } else {
            break; 
        }
    }
}

/**
 * Helper to deleteFromCostLinkedList
 * Takes care of removal from an empty list 
 * And 3 edge cases:
 * Removal of head 
 * Removal of tail 
 * Removal from body 
 * @param toDelte an individual restuarant to delte
 * @param cll costLinkedList to delete from 
 */ 
void deleteRestFromCostLinkedList(Restaurant* toDelete, CostLinkedList* cll){
    Node* curr = cll->head; 
    while(true){

        if(curr->data == toDelete){
            Node* temp = curr; 
            if(curr == cll->head){
                // head node 
                Node* newHead = curr->next;
                newHead->prev = NULL;
                cll->head = newHead; 
                
                curr = newHead; // increment 
            } else if (curr == cll->tail){
                // tail node 
                Node* newTail = curr->prev; 
                newTail->next = NULL;
                cll->tail = newTail; 

                cll->size -= 1;
                free(temp); 

                break; // no need to increment... we've reached the end
            } else {
                // body node 
                Node* prev = curr->prev;
                Node* next = curr->next;

                prev->next = next;
                next->prev = prev;
                
                curr = next; 

            }
            // decrement the size 
            cll->size -= 1;
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
 * Prints low/med/high linked lists 
 */ 
void printCostIndex(CostIndex* ci){
    printf("Indices of $ Restaurants: \n");
    printCostLinkedList(ci->low); 
    printf("\nIndices of $$ Restaurants: \n");
    printCostLinkedList(ci->med);
    printf("\nIndices of $$$ Restaurants: \n");
    printCostLinkedList(ci->high);
    printf("\n"); 

}

/**
 * Prints contents of the CostLinkedList by 
 * traversing through the LinkedList 
 */ 
void printCostLinkedList(CostLinkedList* cll){
    Node* curr = cll->head; 

    while(true){
        printf("%s \n", curr->data->name);
        if(curr->next != NULL){
            curr = curr->next; 
        } else {
            break; 
        }
    }
    /*
    for(int i = 0; i < cll->size; i++){
        printf("%s \n", curr->data->name); 
        if(i != cll->size-1){
            curr = curr->next; 
        }
    }
    */
}


/**
 * Frees each linked list in the CostIndex and the CostIndex itself 
 * 
 * @param ci CostIndex to free
 */ 
void costIndexDestructor(CostIndex* ci){
    costLinkedListDestructor(ci->low); 
    costLinkedListDestructor(ci->med); 
    costLinkedListDestructor(ci->high); 
    free(ci); 
}

/**
 * Frees all the nodes in the linked list and the linked list itself
 * @param cll linkedlist to free
 */ 
void costLinkedListDestructor(CostLinkedList* cll){
    Node* curr = cll->head; 
    int cllSize = cll->size; 
    for(int i = 0; i < cllSize; i++){
        Node* temp = NULL;
        if(i != cllSize-1){
            temp = curr->next; 
        } 
        free(curr); 
        curr = temp;
    }
    free(cll); 
}
