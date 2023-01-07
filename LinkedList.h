#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdbool.h>
#include "restaurant.h"
#include "ArrayList.h"

/**
 * @struct RestNode
 * Creatse a node to be used in the creation of the LinkedList
 */ 
typedef struct RestNode_struct{
    struct RestNode_struct* next;
    struct RestNode_struct* prev;
    Restaurant* r;
} RestNode; 

/**
 * @struct LinkedList
 * Creates a linkesList of pointers to Restaurants
 */ 
typedef struct LinkedList_struct{
    int size;
    RestNode* head;
    RestNode* tail;
} LinkedList; 

/**
 * Creates an empty LinkedList
 * @return pointer to LinkedLIst created 
 */ 
extern LinkedList* createLinkedList();

/**
 * Sorted insert into Linked List. Prioritizes rank, city, first category, then cost 
 * @param ll LinkedList to insert into
 * @param r restaurant to insert 
 */ 
extern void insertInLinkedList(LinkedList* ll, Restaurant* r); 

/**
 * Insert to head of linked list
 * @param ll Linked List to insert into 
 * @param cNode node to insert
 * @param curr node in ll to insert right before
 */ 
extern void insertAtHead(LinkedList*ll, RestNode* cNode, RestNode* curr);

/**
 * Insert to body of linked list
 * @param ll Linked List to insert into 
 * @param cNode node to insert
 * @param curr node in ll to insert right before
 */ 
extern void insertAtBody(LinkedList*ll, RestNode* cNode, RestNode* curr);


/**
 * Remove a single restuarnat from the LinkedList
 * @param ll linkedList to remove from 
 * @param rest restuarant to remove 
 */ 
extern bool removeRestFromLinkedList(LinkedList*ll, Restaurant* rest); 
/**
 * Removes a node from the linked list
 * Helper function to removeRestFromLinkedList
 * @param ll LinkedList to remove from 
 * @param node RestNode to remove from the LinkedList 
 */ 
extern void removeFromLinkedList(LinkedList* ll, RestNode* node); 

/**
 * Search a given linkedList for all the restuarant that match a certain city
 * @param ll to search
 * @param city to search for 
 * @return a linked list of the restaurant that match the city 
 */ 
extern LinkedList* searchLinkedListByCity(LinkedList* ll, char* city); 

/**
 * Remove all the restaurants thaat match a certain city
 * @param ll linkedlist to remove from 
 * @param city if matches, remove 
 * 
 */ 
extern void removeFromLinkedListByCity(LinkedList* ll, char* city); 


/**
 * Search a given linkedList for all the restuarant that match a certain name 
 * @param ll to search
 * @param name to search for 
 * @return a linked list of the restaurant that match the name
 */ 
extern LinkedList* searchLinkedListByName(LinkedList* ll, char* name);

/**
 * Remove all the restaurants thaat match a certain name
 * @param ll linkedlist to remove from 
 * @param name if matches, remove 
 * 
 */ 
extern void removeFromLinkedListByName(LinkedList* ll, char* name); 

/**
 * add the contents of one linked list to anohter
 * @param ll to add to 
 * @param toAppend linked list to add 
 */ 
extern LinkedList* appendToLinkedList(LinkedList* ll, LinkedList* toAppend); 


/**
 * Insert the contents of a linked list to an array list 
 * @param ll linked list 
 * @param ArrayList to add to 
 */ 
extern void appendLLtoAL(LinkedList* ll, ArrayList* al); 
/**
 * searches the linked list for a given restuarant
 * @param ll to search through 
 * @param r restaurant to search for
 * @return true if the restaurant is in the linked list, false if it is not 
 */ 
extern bool isInLinkedList(LinkedList* ll, Restaurant* r); 


/**
 * Print the contents of the LinkedList 
 * @param ll LinkedList to free
 */ 
extern void printLinkedList(LinkedList* ll); 

/**
 * Returns the number of elements in the linked list 
 * @param ll LinkedList to get size of 
 * @return number of elements in linked list 
 */ 
extern int getLinkedListSize(LinkedList* ll); 

/**
 * Free the linked list 
 * @param ll LinkedList to free
 */ 
extern void linkedListDestructor(LinkedList* ll); 

/**
 * Frees the linked list and also calls the restaurant destructor
 * for each of the restaurants in the linked list 
 */ 
extern void linkedListDeepDestructor(LinkedList* ll); 


#endif 