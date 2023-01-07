#ifndef COSTINDEX_H
#define COSTINDEX_H 

#include <stdbool.h>
#include "LinkedList.h"
#include "restaurant.h"


/**
 * @struct Node
 * Creates a node to be used in the creation of CostLinkedLists
 * Contins the restuarant index 
 */ 
typedef struct Node_struct{
    struct Node_struct* next; 
    struct Node_struct* prev;
    Restaurant* data; // data is going to be the restIndex; 

} Node; 

/**
 * @struct CostLinkedList
 * Creates a doubly linked list of Nodes 
 */ 
typedef struct CostLinkedList_struct{
    int size; 
    Node* head; 
    Node* tail; 

} CostLinkedList; 

/**
 * @struct CostIndex
 * Contains a linked list for each of the price brakets 
 */ 
typedef struct CostIndex_struct{
    CostLinkedList* low;
    CostLinkedList* med;
    CostLinkedList* high; 
} CostIndex;

extern CostIndex* createCostIndex(); 


/**
 * Inserts a cost and restuarant pair into the index 
 * @param ci CostIndex pointer 
 * @param cVal cost value
 * @param restIndex restaurant index 
 */ 
extern void insertInCostIndex(CostIndex *ci, int cVal, Restaurant* restIndex); 

/**
 * Inserts a restuarant into the specified CostLinkedList
 * Helper to insertInCostIndex 
 * @param cll CostLinkedList pointer
 */ 
extern void insertInCostLinkedList(CostLinkedList *cll, Restaurant* restIndex); 

/**
 * search the CostIndex for all restaurants in the given linked list that match in cost
 * or are lower in cost 
 * @param ll linkedList of Restaurants to check 
 * @param c costIndex of knowledge base 
 * @param cost cost to search for 
 */ 
extern LinkedList* searchCostIndex(LinkedList* ll, CostIndex* c, int cost); 

/**
 * Delete a list of restaurants from the CostIndex
 * @param toDelete LinkedList of restaurants to delete from
 * @param c CostIndex to remove from 
 */ 
extern void deleteFromCostIndex(LinkedList* toDelete, CostIndex* c);

/**
 * Helper to deleteFromCostIndex 
 * @param toDelete LinkedList of restaurants to delete
 * @param cll cost linked list to delete from 
 */ 
extern void deleteFromCostLinkedList(LinkedList* toDelete, CostLinkedList* cll);

/**
 * Helper to deleteFromCostLinkedList
 * @param toDelte an individual restuarant to delte
 * @param cll costLinkedList to delete from 
 */ 
extern void deleteRestFromCostLinkedList(Restaurant* toDelete, CostLinkedList* cll);
 
/**
 * Prints the contents of the CostIndex to the terminal 
 * @param ci CostIndex to print 
 */ 
extern void printCostIndex(CostIndex* ci); 

/**
 * Prints the contents of a CostLinkedList 
 * Helper to printCostIndex
 * @param cll CostLinkedList to print 
 */ 
extern void printCostLinkedList(CostLinkedList * cll); 

/**
 * Frees the linked lists, nodes, and object iself of a CostIndex
 * @param ci CostIndex to free
 */ 
extern void costIndexDestructor(CostIndex* ci); 

/**
 * Frees the nodes in the linked list and linked list itself 
 * Helper to the costIndex Destructor 
 * @param cll costLinkedList to free
 */ 
extern void costLinkedListDestructor(CostLinkedList* cll); 



#endif