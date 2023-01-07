#ifndef BINARYTREE
#define BINARYTREE

#include "restaurant.h"
#include "LinkedList.h"
#include "ArrayList.h"

/**
 * @struct BTNode
 * Creates a node for the Binary Tree
 * Holds pointers to the left child and right child
 * Holds a string which is used as the comparator of the BinaryTree
 * Holds a LinkedList of restaurants to handle duplicates
 */ 
typedef struct BTNode_struct {
    struct BTNode_struct* left;
    struct BTNode_struct* right; 
    char* data;
    LinkedList* ll; 

} BTNode;

/**
 * @struct BinaryTree 
 * Holds the root BT Node
 * Holds the size = the number of BTNodes in the data structure 
 */ 
typedef struct BinaryTree {
    BTNode* root;
    int size;

} BinaryTree;


/**
 * Creates an empty BTNode 
 * Helper function (don't call on it's own)
 * Takes care of mallocing and initalizing interal linkedlist
 * @return BTNode* the node that was created 
 */ 
extern BTNode* createBTNode(); 

/**
 * Creates a new Binary Tree
 * Takes care of mallocing 
 * @return pointer to the BinaryTree that was created 
 */ 
extern BinaryTree* createBinaryTree();

/**
 * Insert a restauarant into the Binary Tree
 * @param bt BinaryTree to insert into 
 * @param x the restaurant to insert 
 */ 
extern void insertInBinaryTree( BinaryTree* bt, Restaurant* x);

/**
 * Delete a list of Restaurants from the Binary Tree
 * @param toDelete the LinkedList of restaurants to delete 
 * @param bt the BinaryTree to delete from 
 */ 
extern void deleteFromBinaryTree(LinkedList* toDelete, BinaryTree* bt); 

/**
 * Helper function to deletefromBinaryTree
 * @param bt BinaryTree to remove from 
 * @param r restaurant to remove 
 */ 
extern void deleteFromBinaryTreeHelper(BinaryTree* bt, Restaurant* r); 

/**
 * Helper function to delete from BinaryTreeHelper
 * @param curr BTNode to delete
 * @param parent BTNode's parent (NULL if they don't have one)
 * @return BTNode* used in unravelling the recursion
 */ 
extern BTNode* deleteNodeFromBinaryTree(BTNode* curr, BTNode* parent,  char* name); 


/**
 * Helper function to deleteNodeFromBinaryTree - finds the in order successor of a given node 
 * @param node node to find the inorder successor of 
 * @return the in order successor 
 */ 
extern BTNode* inOrderSuccessor(BTNode* node);//, BTNode* parent); 


/**
 * print out the BinaryTree (in lexiographic order)
 * @param bt BinaryTree to print out 
 */ 
extern void printBinaryTree(BinaryTree* bt); // calls in order 

/**
 * Helper function to printBinaryTree
 * Recursive in order traversal of tree
 * @param bt BTNode* (call on a tree's root to start the recursion)
 */ 
extern void BinaryTreeInOrder( BTNode* bt);

/**
 * Helper function to BinaryTreeDestructor which handles the freeing of internals 
 * @param bt node to free 
 */ 
extern void BinaryNodeDestructor( BTNode* bt ); 

/**
 * Main function to call if you wish to free the memory associated with a BinaryTree
 * @param bt Binary Tree to free 
 */ 
extern void BinaryTreeDestructor( BinaryTree* bt); 



/**
 * Searches the binary tree for all restuarants matching a given name and location
 * @param bt binary tree to search
 * @param name name to search for
 * @param loc location to search for
 * @return LinkedList of matches 
 */ 
extern LinkedList* searchBinaryTree(BinaryTree* bt, char* name, char* loc); 

/**
 * Convert a Binary tree to a linked list 
 * @param bt binary tree to convert
 * @return LinkedList of the contents of the binary tree 
 */ 
extern LinkedList* binaryTreeToLinkedList(BinaryTree* bt); 

/**
 * Recursive helper function for binarTreeToLinkedList 
 * @param bt BTNode to convert
 * @param ll LinkedList to append to 
 */ 
extern void BTtoLL(BTNode* bt, LinkedList* ll); 

/**
 * Convert a Binary Tree to an ArrayList
 * @param bt Binary Tree to convert
 * @return ArrayList of Binary Tree contents 
 */ 
extern ArrayList* binaryTreeToArrayList(BinaryTree* bt);

/**
 * Recursive helper function to binaryTreeToArrayList
 * @param bt BTNode to convertr
 * @param al ArrayList to add to 
 */ 
extern void BTtoAL(BTNode* bt, ArrayList* al); 

#endif 