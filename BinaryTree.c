#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
  

#include "BinaryTree.h"

/**
 * Creates an empty BTNode 
 * Helper function - called by createBinaryTree and insertInBinaryTree 
 * Mallocs and inializeeds the internal linked list
 * Sets the data and children to NULL
 * @return BTNode* the node that was created 
 */ 
BTNode* createBTNode(){
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->ll = createLinkedList(); 
    newNode->data = NULL;
    newNode->left = NULL;
    newNode->right = NULL; 
    return newNode;
}

/**
 * Creates a new Binary Tree
 * Mallocs, sets root to NULL and size to 0 
 * @return pointer to the BinaryTree that was created 
 */ 
BinaryTree *createBinaryTree()
{
    BinaryTree *bt = malloc(sizeof(BinaryTree));
    bt->root = NULL;
    bt->size = 0;
    return bt;
}

/**
 * Insert a restauarant into the Binary Tree
 * Find the correct node based on the name of the restaurant 
 * Insert it into the linked list in the internal node 
 * @param bt BinaryTree to insert into 
 * @param x the restaurant to insert 
 * 
 * 
 */ 
void insertInBinaryTree(BinaryTree *bt, Restaurant *x)
{
    BTNode *curr = bt->root;
    

    if (bt->size == 0)
    {   
        BTNode* newNode = createBTNode();
        insertInLinkedList(newNode->ll, x); 
        newNode->data = x->name; 

        bt->root = newNode;
        bt->size += 1;
        return;
    }
    while (true)
    {
        // compare the names of the restaurants
        if (strcmp(x->name, curr->data) < 0)
        {
            // go left if the x is less than the curr
            if (curr->left == NULL)
            {
                BTNode* newNode = createBTNode();
                insertInLinkedList(newNode->ll, x);
                newNode->data = x->name; 

                curr->left = newNode;
                bt->size += 1;
                break;
            }
            else
            {
                curr = curr->left;
            }
        }
        else if(strcmp(x->name, curr->data) > 0)
        {
            // go right if x is greater than or equal to curr
            if (curr->right == NULL)
            {   
                BTNode* newNode = createBTNode();
                insertInLinkedList(newNode->ll, x);
                newNode->data = x->name; // MIGHT THIS CAUSE SOME ISSUES WITH VALGRIND??  
            

                curr->right = newNode;
                bt->size += 1;
                break;
            }
            else
            {
                curr = curr->right;
            }
        } 
        else {
            // we have found an equal node 
            insertInLinkedList(curr->ll, x);
            return; 
        }
    }
}



/**
 * Delete a list of Restaurants from the Binary Tree by calling a helper function
 * 
 * @param toDelete the LinkedList of restaurants to delete 
 * @param bt the BinaryTree to delete from 
 */ 
void deleteFromBinaryTree(LinkedList* toDelete, BinaryTree* bt){
    RestNode* curr = toDelete->head; 
    while(true){
       //deleteFromBinaryTreeRecursive(bt, bt->root, curr->r); 
       deleteFromBinaryTreeHelper(bt , curr->r); 
        if(curr->next != NULL){
            curr = curr->next; 
        } else {
            break; 
        }
    }

}


/**
 * Deletes a restaurant from the binary tree 
 * If the internal linked list of the node becomes 0 then the full node is removed by calling a helper function
 * @param bt Binarytree to delete form 
 * @param r Restaurant to remove 
 */ 
void deleteFromBinaryTreeHelper(BinaryTree* bt, Restaurant* r){
    if(bt->size == 0){
        return; 
    }

    BTNode* curr = bt->root; 
    while(true){
        if(strcmp(r->name, curr->data) < 0){
            if(curr->left == NULL){
                return; 
            } else {
                curr = curr->left; 
            }
        } else if (strcmp(r->name, curr->data) > 0){
            if (curr->right == NULL){
                return; 
            } else {
                curr = curr->right; 
            }
        } else {
            // we have found a name that matches. Now delete the restaurant from that linked list 
            removeRestFromLinkedList(curr->ll, r); 

            
            // if the node is empty, then delete the node here 
            if(curr->ll->size == 0){
             // printf("Delete Node called, BinaryTree.c 128\n"); 
                deleteNodeFromBinaryTree(bt->root, NULL,  r->name); 

               // deleteNodeFromBinaryTreeIterative(bt->root, NULL, r->name); 

                bt->size -= 1; // we know that deleteNodeFromBinary Tree will actually work since we just dealt with it 
            }
            
            return; 
             
        }
    }
    return; 
}


/**
 * Helper function to delete from BinaryTreeHelper
 * Recursively deletes the Binary Node from the given tree
 * @param curr BTNode to delete
 * @param parent BTNode's parent (NULL if they don't have one)
 * @return BTNode* used in unravelling the recursion
 */ 
BTNode* deleteNodeFromBinaryTree(BTNode* curr, BTNode* parent,  char* name){
    if(curr == NULL){
        return curr; 
    }

    if(strcmp(name, curr->data) < 0 ){

        curr->left = deleteNodeFromBinaryTree(curr->left, curr,  name); 
        
    } else if (strcmp(name, curr->data) > 0 ){

        curr->right = deleteNodeFromBinaryTree(curr->right, curr,  name); 
    } else {
       // printf("Got to the equals condition\n"); 
        if(curr->left == NULL){
            BTNode* temp = curr->right; 
            
            //linkedListDestructor(curr->ll); // causing a seg fault 

            free(curr); 
            return temp;
        } else if (curr->right == NULL){
            BTNode* temp = curr->left;
           
            //linkedListDestructor(curr->ll); 
            free(curr); 
            return temp; 
        }

        // has 2 children 

        //printf("Old Node: %s\n", curr->data); 
       // LinkedList* llToFree = curr->ll; 
        linkedListDestructor(curr->ll); 
        //linkedListDeepDestructor(curr->ll); 
        
        //linkedListDeepDestructor(llToFree); 
       // printf("Got down here\n"); 
        BTNode* temp = inOrderSuccessor(curr->right); 
        curr->data = temp->data; 
        curr->ll = temp->ll; 
        //printf("Updated Node: %s\n", curr->data); 

        curr->right = deleteNodeFromBinaryTree(curr->right, curr, temp->data); 
    }
    return curr; 
}


/**
 * Helper function to deleteFromBinarytree - finds the in order successor of a given node 
 * returns NULL if the node is NULL for some reason 
 * Traverses as left as possible on the BinaryTree 
 * @param node node to find the inorder successor of 
 * @return the in order successor 
 */ 
BTNode* inOrderSuccessor(BTNode* node)//, BTNode* parent)
{
    BTNode* curr = node;
    
    if(curr == NULL){
        return NULL; 
    }

  
     while (curr->left != NULL)
    {
        //parent = curr; 
        curr = curr->left;
        
    }

 

    return curr;
}

/**
 * print out the BinaryTree (in order) to the Terminal 
 * @param bt BinaryTree to print out 
 */ 
void printBinaryTree(BinaryTree *bt)
{
    BinaryTreeInOrder(bt->root);
    return;
}


/**
 * Helper function to printBinaryTree
 * Recursive in order traversal of tree
 * @param bt BTNode* (call on a tree's root to start the recursion)
 */ 
void BinaryTreeInOrder(BTNode *bt)
{
    // InOrder(Left, Root, Right)
    if (bt == NULL)
    {
        return;
    }
    BinaryTreeInOrder(bt->left);

    if(bt->ll != NULL){
        /*
    if(bt->ll->size == 0){
        printf("EMPTY LL !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n"); 
        // shouldn't actually get here... if it is then something is going wrong. 
    }
    */
    
    printLinkedList(bt->ll); 
    } 



    BinaryTreeInOrder(bt->right);
}


/**
 * Helper function to BinaryTreeDestructor which handles the freeing of internals 
 * through a recursive post order traversal 
 * @param bt node to free 
 */ 
void BinaryNodeDestructor(BTNode *bt)
{
    if (bt == NULL)
    {
        return;
    }
    BinaryNodeDestructor(bt->left);
    BinaryNodeDestructor(bt->right);

    // free the restaurant (data) and the node
    //linkedListDestructor(bt->ll); 
    linkedListDeepDestructor(bt->ll); 
    free(bt);
}

/**
 * Free a Binary tree
 * Calls the recursive helper function BinaryNodeDestructor to accomplish thsi 
 * @param bt Binary Tree to free 
 */ 
void BinaryTreeDestructor(BinaryTree *bt)
{ 
    BinaryNodeDestructor(bt->root);
    free(bt);
}

/**
 * Searches the binary tree for all restuarants matching a given name and location
 * through an iterative traversal of the binary tree 
 * @param bt binary tree to search
 * @param name name to search for
 * @param loc location to search for
 * @return LinkedList of matches 
 */ 
LinkedList *searchBinaryTree(BinaryTree *bt, char *name, char *loc){
    //LinkedList *ll = createLinkedList();
    if (bt->size == 0)
    {
        return NULL;
    }

    BTNode *curr = bt->root;


    while (true){
        if (strcmp(name, curr->data) < 0){
            if (curr->left == NULL){
                return NULL;
            } else {
                curr = curr->left;
            }
        } else if (strcmp(name, curr->data) > 0){
            if (curr->right == NULL) {
                return NULL;
            } else{
                curr = curr->right;
            }
        } else {
            // we have found a name that matches, now make sure the city matches too
            return searchLinkedListByCity(curr->ll, loc); 

        }
    }
}


/**
 * Convert a Binary tree to a linked list 
 * Creates the linked list to return 
 * Calls a recursive helper function 
 * @param bt binary tree to convert
 * @return LinkedList of the contents of the binary tree 
 */ 
LinkedList* binaryTreeToLinkedList(BinaryTree* bt){
    LinkedList* ll = createLinkedList(); 
    BTtoLL(bt->root, ll); 
    return ll; 
}


/**
 * Recursive helper function for binarTreeToLinkedList 
 * In order traversal 
 * Calls appendToLinkedList from LinkedList.c
 * @param bt BTNode to convert
 * @param ll LinkedList to append to 
 */ 
void BTtoLL(BTNode* bt, LinkedList* ll){
    if (bt == NULL)
    {
        return;
    }
    BTtoLL(bt->left, ll);

    appendToLinkedList(ll, bt->ll); 
    
    BTtoLL(bt->right, ll);

}

/**
 * Convert a Binary Tree to an ArrayList
 * creates the ArrayList to return 
 * calls recursive helper function
 * @param bt Binary Tree to convert
 * @return ArrayList of Binary Tree contents 
 */ 
ArrayList* binaryTreeToArrayList(BinaryTree* bt){
    ArrayList* al = createArrayList(); 
    BTtoAL(bt->root, al); 
    return al; 
} 


/**
 * Recursive helper function to binaryTreeToArrayList
 * In order traversal
 * @param bt BTNode to convertr
 * @param al ArrayList to add to 
 */ 
void BTtoAL(BTNode* bt, ArrayList* al){
    if (bt == NULL)
    {
        return;
    }
    BTtoAL(bt->left, al);

    //appendToLinkedList(ll, bt->ll); 
    // linkedListToArrayList 
    appendLLtoAL(bt->ll, al); 
    
    BTtoAL(bt->right, al);
}


