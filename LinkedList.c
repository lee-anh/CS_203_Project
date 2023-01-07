#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "LinkedList.h"

/**
 * Creates an Empty LinkedList
 * Object is malloc'd here
 * Sets the size to 0 and the head and tail to NULL
 *
 * @return pointer to LinkedList created
 */
LinkedList *createLinkedList()
{
    LinkedList *ll = malloc(sizeof(LinkedList));
    ll->size = 0;
    ll->head = NULL;
    ll->tail = NULL;
    return ll;
}

/**
 * Sorted insert into LinkedList. First prioritizes rank (high->low) then if rank matches, cost (low->high)
 * @param ll LinkedList to insert into
 * @param r restaurant to insert 
 */
void insertInLinkedList(LinkedList *ll, Restaurant *r)
{
    // first by rank (high->low) and then by cost(low->high)
    RestNode *cNode = malloc(sizeof(RestNode));
    cNode->r = r;
    cNode->next = NULL;
    cNode->prev = NULL;

    // empty insertion
    if (ll->size == 0)
    {
        ll->head = cNode;
        ll->tail = cNode;
        ll->size += 1;
        return;
    }

    RestNode *curr = ll->head;
    int cCount = ll->size;
    for (int i = 0; i < cCount; i++)
    {
        // rank
        // city
        // category (first?)
        // cost

        if (r->rank > curr->r->rank){
            if (i == 0){
                insertAtHead(ll, cNode, curr);
            }
            else{
                insertAtBody(ll, cNode, curr);
            }
            return;
        } else if (r->rank == curr->r->rank){
            // if cost is less than or equal to , then insert 
            if(r->cost <= curr->r->cost){
                if(i == 0){
                    insertAtHead(ll, cNode, curr);
                } else {
                    insertAtBody(ll, cNode, curr); 
                }
                return; 
            } 

           
            // if cost is greater than then continue traversing 

        }
        
        // continue traversing 
        if (i != ll->size - 1){
            curr = curr->next;
        } else {
            // last element, insert at end
            cNode->prev = curr;
            curr->next = cNode;
            ll->tail = cNode;
            ll->size += 1;
        }
    }
}

/**
 * Insert to head of linked list, reassigns the relavent next/prevs
 * Increments ll->size, sets new head of ll 
 * @param ll Linked List to insert into 
 * @param cNode node to insert
 * @param curr node in ll to insert right before
 */ 
void insertAtHead(LinkedList *ll, RestNode *cNode, RestNode *curr)
{
    // insert at head
    cNode->next = curr;
    curr->prev = cNode;
    ll->head = cNode;

    ll->size += 1;
}

/**
 * Insert to body of linked list, reassigns the relevant next/prevs
 * Increments ll->size
 * @param ll Linked List to insert into 
 * @param cNode node to insert
 * @param curr node in ll to insert right before
 */ 
void insertAtBody(LinkedList *ll, RestNode *cNode, RestNode *curr)
{
    // insert in body of linked list
    cNode->prev = curr->prev;
    cNode->next = curr;

    if (curr->prev != NULL)
    {
        curr->prev->next = cNode;
    }

    curr->prev = cNode;

    ll->size += 1;
}


/**
 * Remove a single restuarnat from the LinkedList
 * Calls removeFromLinkedList helper function for actual removal 
 * @param ll linkedList to remove from 
 * @param rest restuarant to remove 
 */ 
bool removeRestFromLinkedList(LinkedList* ll, Restaurant* rest){
    if(ll->size == 0){
        return false; 
    }
    RestNode* curr = ll->head; 
    while(true){
        //printf("rem rest f ll outside \n");
        if(curr->r == rest){
          //  printf("rem rest f ll \n"); 
            removeFromLinkedList(ll, curr); 
            //printf("rem rest f ll 2\n"); 
            return true; 
            break; 
        }

        if(curr->next != NULL){
            curr= curr->next; 
        } else {
            break; 
        }
    }
    return false; 
}

/**
 * Removes a node from the linked list
 * Helper function to removeRestFromLinkedList
 * Takes care of removal of head, tail and from body 
 * @param ll LinkedList to remove from 
 * @param node RestNode to remove from the LinkedList 
 */ 
void removeFromLinkedList(LinkedList* ll, RestNode* node){
    if(ll->size - 1 == 0){
        free(node); 
        ll->head = NULL;
        ll->tail = NULL; 
        ll->size = 0; 
        return; 
    }  

    if(ll->head == node){
       // printf("Case head\n"); 
        // head node 
        RestNode* newHead = node->next; 
        newHead->prev = NULL; 
        ll->head = newHead; 
        

    } else if (ll->tail == node){
       // printf("Case tail\n"); 
        // tail node 
        RestNode* newTail = node->prev;
        newTail->next = NULL; 
        ll->tail = newTail; 

    } else {
       // printf("Case body\n"); 
        // body node 
        RestNode* prev = node->prev; 
        RestNode* next = node->next; 

        prev->next = next; 
        next->prev = prev; 

    }

    ll->size -= 1; 


    free(node); 
}

/**
 * Search a given linkedList for all the restuarant that match a certain city
 * Accomplishes this by making a new linkes list of matches 
 * @param ll to search
 * @param city to search for 
 * @return a linked list of the restaurant that match the city 
 */ 
LinkedList* searchLinkedListByCity(LinkedList* ll, char* city){
    LinkedList* toReturn = createLinkedList();
    RestNode *curr = ll->head;
    for(int i = 0; i < ll->size; i++){
        if(strcmp(curr->r->city, city) == 0){
            insertInLinkedList(toReturn, curr->r); 
        }
        if(i != ll->size-1){
            curr = curr->next; 
        }
    }

    return toReturn; 
}

/**
 * Remove all the restaurants thaat match a certain city
 * Calls helper function removeFromLinkedLIst for actual removal 
 * @param ll linkedlist to remove from 
 * @param city if matches, remove 
 * 
 */ 
void removeFromLinkedListByCity(LinkedList* ll, char* city){
    //printLinkedList(ll); 
    RestNode *curr = ll->head;

    while(true){
        RestNode* temp = NULL; 
        if(curr->next != NULL){
            temp = curr->next; 
        } 

        if(strcmp(curr->r->city, city) == 0){
            removeFromLinkedList(ll, curr); 
        }

        if(temp != NULL){
            curr = temp; 
        } else {
            break; 
        }
        
    
    }
}



/**
 * Search a given linkedList for all the restuarant that match a certain name 
 * Accomplishes this by making a new linkes list of matches 
 * @param ll to search
 * @param name to search for 
 * @return a linked list of the restaurant that match the name
 */ 
LinkedList* searchLinkedListByName(LinkedList* ll, char* name){
    LinkedList* toReturn = createLinkedList();
    RestNode *curr = ll->head;
    for(int i = 0; i < ll->size; i++){
        if(strcmp(curr->r->name, name) == 0){
            insertInLinkedList(toReturn, curr->r); 
        }
        if(i != ll->size-1){
            curr = curr->next; 
        }
    }

    return toReturn; 
}


/**
 * Remove all the restaurants thaat match a certain name
 * Calls helper function removeFromLinkedLIst for actual removal 
 * @param ll linkedlist to remove from 
 * @param name if matches, remove 
 * 
 */ 
void removeFromLinkedListByName(LinkedList* ll, char* name){
    //printLinkedList(ll); 
    RestNode *curr = ll->head;

    while(true){
        RestNode* temp = NULL; 
        if(curr->next != NULL){
            temp = curr->next; 
        } 

        if(strcmp(curr->r->name, name) == 0){
            removeFromLinkedList(ll, curr); 
        }

        if(temp != NULL){
            curr = temp; 
        } else {
            break; 
        }
        
    
    }
 
}


/**
 * add the contents of one linked list to another 
 * calls the insertInLinkedList function for every element in the to append LL
 * @param ll to add to 
 * @param toAppend linked list to add 
 */ 
LinkedList* appendToLinkedList(LinkedList* ll, LinkedList* toAppend){

    // but I still want to retain the original toAppend LinkedList
    /*
    ll->size = ll->size + toAppend->size;
    ll->tail->next = toAppend->head;
    toAppend->head->prev = ll->tail; 
    ll->tail = toAppend->tail; 
    */
    
    RestNode* curr = toAppend->head; 
    while(true){
        insertInLinkedList(ll, curr->r); 
        if(curr->next != NULL){
            curr = curr->next; 
        } else {
            break; 
        }
    }
    
    return ll; 

    // TODO: any freeing? 
}

/**
 * Insert the contents of a linked list to an array list 
 * Traverses and calls insert from ArrayList.c 
 * @param ll linked list 
 * @param ArrayList to add to 
 */ 
void appendLLtoAL(LinkedList* ll, ArrayList* al){
    RestNode* curr = ll->head; 
    while(true){
        insert(al, curr->r); 
        if(curr->next != NULL){
            curr = curr->next; 
        } else {
            break; 
        }
    }
}


/**
 * searches the linked list for a given restuarant
 * @param ll to search through 
 * @param r restaurant to search for
 * @return true if the restaurant is in the linked list, false if it is not 
 */ 
bool isInLinkedList(LinkedList* ll, Restaurant* r){
    if(ll->size == 0){
        return false;
    }
    RestNode* curr = ll->head;
    while(true){
        if(curr->r == r){
            return true; 
        }
        
        if(curr->next != NULL){
            curr = curr->next; 
        } else {
            break; 
        }
    }
}
/**
 * Prints of the contents of the Linked List by traversing through
 * and calling printRestaurant (see restaurant.c)
 */
void printLinkedList(LinkedList *ll)
{
    //printf("__________________________________________________\n\n");
   //printf("ll-size%d", ll->size); 
    if(ll->head == NULL || ll->size == 0){
       // printf("Empty linkedlist\n");
        return; 
    }
    
    RestNode *curr = ll->head;
    for (int i = 0; i < ll->size; i++)
    {
        printRestaurant(curr->r);
        if (i != ll->size - 1)
        {
            curr = curr->next;
        }
        printf("__________________________________________________\n\n");
    }
    
}

/**
 * Returns the size of the linked list, which reprents the number of elements 
 */ 
int getLinkedListSize(LinkedList* ll){
    return ll->size; 
}

/**
 * Traverses the linked list and frees each node
 * Frees the linked list itself
 * @param ll linked list to free
 */
void linkedListDestructor(LinkedList *ll)
{
    RestNode *curr = ll->head;
    int llSize = ll->size;

    /*
    if(ll->size = 0){
        free(ll); 
        return; 
    }
    
    while(true){
        
        RestNode* temp = NULL; 
        if(curr->next != NULL){
            temp = curr->next; 
        }

        free(curr); 

        if(temp != NULL) {
            curr = temp; 
        } else {
            break; 
        }
    }
    */
    
    for (int i = 0; i < llSize; i++)
    {
        RestNode *temp = NULL;
        if (i != llSize - 1)
        {
            temp = curr->next;
        }
        free(curr);
        curr = temp;
    }
    
    free(ll);
}


/**
 * Frees the linked list and also calls the restaurant destructor
 * for each of the restaurants in the linked list 
 */ 
void linkedListDeepDestructor(LinkedList *ll)
{
    RestNode *curr = ll->head;
    int llSize = ll->size;
    for (int i = 0; i < llSize; i++)
    {
        RestNode *temp = NULL;
        if (i != llSize - 1)
        {
            temp = curr->next;
        }
        restaurantDestructor(curr->r); 
        free(curr);
        curr = temp;
    }
    free(ll);
}
