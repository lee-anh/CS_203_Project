#ifndef BTCITY
#define BTCITY

#include <stdbool.h>

#include "restaurant.h"
#include "LinkedList.h"

/**
 * @struct BTCityNOde
 * Creates a node for BTCity binary tree
 * Holds pointers to the left child and right child
 * Holds a string which is used as the comparator of the BTCity
 * Holds a LinkedList of restaurants to handle duplicates
 */
typedef struct BTCityNode_struct {
    struct BTCityNode_struct* left;
    struct BTCityNode_struct* right; 
    char* data;
    LinkedList* ll; 

} BTCityNode;


/**
 * @struct BTCity 
 * Holds the root 
 * Holds the size = the number of BTNodes in the data structure 
 */ 
typedef struct BTCity {
    BTCityNode* root;
    int size;

} BTCity;

/**
 * Creates an empty BTCityNode 
 * Helper function (don't call on it's own)
 * Takes care of mallocing and initalizing interal linkedlist
 * @return BTCityNode* the node that was created 
 */ 
extern BTCityNode* createBTCityNode(); 

/**
 * Creates a new BTCity tree
 * Takes care of mallocing 
 * @return pointer to the BTCity that was created 
 */ 
extern BTCity* createBTCity();

/**
 * Insert a restauarant into the BTCity Binary Tree
 * @param bt BTCity to insert into 
 * @param x the restaurant to insert 
 */ 
extern void insertInBTCity( BTCity*, Restaurant* r);


/**
 * Delete a list of Restaurants from the BTCity Binary Tree
 * @param toDelete the LinkedList of restaurants to delete 
 * @param bt the BTCity to delete from 
 */ 
extern void deleteFromBTCity(LinkedList* ll, BTCity* bt);

/**
 * Helper function to deletefromBinaryTree
 * @param bt BTCity to remove from 
 * @param r restaurant to remove 
 */ 
extern void deleteFromBTCityHelper(BTCity* bt, Restaurant* r); 

/**
 * Helper function to deleteFromBTCityHelper 
 * @param curr BTCityNode to delete
 * @param parent BTCityNode's parent (NULL if they don't have one)
 * @return BTCityNode* used in unravelling the recursion
 */ 
extern BTCityNode*  deleteNodeFromBTCity(BTCityNode* bt, char* city); 

/**
 * Helper function to deleteNodeFromBTCity- finds the in order successor of a given node 
 * @param node node to find the inorder successor of 
 * @return the in order successor 
 */ 
extern BTCityNode* inOrderSuccessorBTCity(BTCityNode* node); 


/**
 * print out the BinaryTree (in lexiographic order)
 * @param bt BinaryTree to print out 
 */ 
extern void printBTCity(BTCity* bt); // calls in order 

/**
 * Helper function to printBTCity
 * Recursive in order traversal of tree
 * @param bt BTCityNode* (call on a tree's root to start the recursion)
 */ 
extern void BTCityInOrder( BTCityNode* bt);

/**
 * Helper function to BTCityDestructor which handles the freeing of internals 
 * @param bt node to free 
 */ 
extern void BTCityNodeDestructor( BTCityNode* bt ); 

/**
 * Main function to call if you wish to free the memory associated with a BTCity Tree
 * @param bt BTCity to free 
 */ 
extern void BTCityDestructor( BTCity* bt); 

/**
 * Searches the BTCity for all restuarants matching a given name and location
 * @param bt BTCity to search
 * @param name name to search for
 * @param loc location to search for
 * @return LinkedList of matches 
 */ 
extern LinkedList* searchBTCity(BTCity* bt, char* city); 

#endif 