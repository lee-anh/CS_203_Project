#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "BTCity.h" 


/**
 * Creates an empty BTCityNode 
 * Helper function - called by createBTCity and insertInBTCity
 * Mallocs and inializeeds the internal linked list
 * Sets the data and children to NULL
 * @return BTNode* the node that was created 
 */ 
BTCityNode* createBTCityNode(){
    BTCityNode *newNode = malloc(sizeof(BTCityNode));
    newNode->ll = createLinkedList(); 
    newNode->data = NULL;
    newNode->left = NULL;
    newNode->right = NULL; 
    return newNode;
}


/**
 * Creates a new BTCity
 * Mallocs, sets root to NULL and size to 0 
 * @return pointer to the BTCity that was created 
 */ 
BTCity *createBTCity()
{
    BTCity *bt = malloc(sizeof(BTCity));
    bt->root = NULL;
    bt->size = 0;
    return bt;
}


/**
 * Insert a restauarant into the BTCity
 * Find the correct node based on the location (city) of the restaurant 
 * Insert it into the linked list in the internal node 
 * @param bt BinaryTree to insert into 
 * @param x the restaurant to insert 
 * 
 * 
 */ 
void insertInBTCity(BTCity *bt, Restaurant *x)
{
    BTCityNode *curr = bt->root;
    

    if (bt->size == 0)
    {   
        BTCityNode* newNode = createBTCityNode();
        insertInLinkedList(newNode->ll, x); 
        newNode->data = x->city; 

        bt->root = newNode;
        bt->size += 1;
        return;
    }
    while (true)
    {
        // compare the names of the restaurants
        if (strcmp(x->city, curr->data) < 0)
        {
            // go left if the x is less than the curr
            if (curr->left == NULL)
            {
                BTCityNode* newNode = createBTCityNode();
                insertInLinkedList(newNode->ll, x);
                newNode->data = x->city; 

                curr->left = newNode;
                bt->size += 1;
                break;
            }
            else
            {
                curr = curr->left;
            }
        }
        else if(strcmp(x->city, curr->data) > 0)
        {
            // go right if x is greater than or equal to curr
            if (curr->right == NULL)
            {   
                BTCityNode* newNode = createBTCityNode();
                insertInLinkedList(newNode->ll, x);
                newNode->data = x->city; // MIGHT THIS CAUSE SOME ISSUES WITH VALGRIND??  
            

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
 * Delete a list of Restaurants from the BTCity by calling a helper function
 * 
 * @param toDelete the LinkedList of restaurants to delete 
 * @param bt the BTCity to delete from 
 */ 
void deleteFromBTCity(LinkedList* toDelete, BTCity* bt){
    RestNode* curr = toDelete->head; 
    while(true){
        deleteFromBTCityHelper(bt, curr->r); 
        if(curr->next != NULL){
            curr = curr->next; 
        } else {
            break; 
        }

    }
}

/**
 * Deletes a restaurant from the BTCity
 * If the internal linked list of the node becomes 0 then the full node is removed by calling a helper function
 * @param bt BTCity to delete form 
 * @param r Restaurant to remove 
 */ 
void deleteFromBTCityHelper(BTCity* bt, Restaurant* r){
    if(bt->size == 0){
        return;  
    }
    BTCityNode* curr = bt->root; 
    while(true){
        if(strcmp(r->city, curr->data) < 0){
            if(curr->left == NULL){
                return;  
            } else {
                curr = curr->left; 
            }
        } else if (strcmp(r->city, curr->data) > 0){
            if (curr->right ==  NULL){
                return; 
            } else {
                curr = curr->right; 
            }
        } else {
            //printf("Got here\n"); 
            removeRestFromLinkedList(curr->ll, r); 
            //printf("Got here 2\n"); 

            if(curr->ll->size == 0){
                //printf("Delete Node called BTCity.c 126\n"); 
               deleteNodeFromBTCity(bt->root, r->city); 
               // deleteNodeFromBTCityIterative(bt->root, r->city); 
                bt->size -= 1; 
            }
            return; 
            

        }
    }
    return; 

    
    

}

/**
 * Helper function to deletefromBTCityHelper
 * Recursively deletes the BTCity from the given tree
 * @param curr BTCityNode to delete
 * @param parent BTCityNode's parent (NULL if they don't have one)
 * @return BTCityNode* used in unravelling the recursion
 */ 
BTCityNode* deleteNodeFromBTCity(BTCityNode* bt, char* city){
    if(bt == NULL){
        return bt; 
    }
    if(strcmp(city, bt->data) < 0 ){
        bt->left = deleteNodeFromBTCity(bt->left, city); 
    } else if (strcmp(city, bt->data) > 0){
        bt->right = deleteNodeFromBTCity(bt->right, city); 
    } else {
        if(bt->left == NULL){
            BTCityNode* temp = bt->right;
            //linkedListDestructor(bt->ll); 
            //free(bt->data); 
            free(bt); 
            return temp;  
        } else if (bt->right == NULL){
            BTCityNode* temp = bt->left; 
           // linkedListDestructor(bt->ll); 
            //free(bt->data); 
            free(bt); 
            return temp; 
        }

        BTCityNode* temp = inOrderSuccessorBTCity(bt->right); 
        ///LinkedList* llToFree = bt->ll; 
        //free(bt->data); 
       //linkedListDestructor(llToFree); 
       linkedListDestructor(bt->ll); 
       //linkedListDeepDestructor(bt->ll); 
        bt->data = temp->data; 
        bt->ll = temp->ll; 
    
        bt->right = deleteNodeFromBTCity(bt->right, temp->data); 
    }
    return bt; 
}

/**
 * Helper function to deleteFromBTCity - finds the in order successor of a given node 
 * returns NULL if the node is NULL for some reason 
 * Traverses as left as possible on the BTCity
 * @param node node to find the inorder successor of 
 * @return the in order successor 
 */ 
BTCityNode* inOrderSuccessorBTCity(BTCityNode* node)
{
    BTCityNode *curr = node;
    while (curr && curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
}

/**
 * print out the BTCity (in order) to the Terminal 
 * @param bt BTCity to print out 
 */ 
void printBTCity(BTCity *bt)
{
    BTCityInOrder(bt->root);
    return;
}


/**
 * Helper function to printBTCity
 * Recursive in order traversal of tree
 * @param bt BTNode* (call on a tree's root to start the recursion)
 */ 
void BTCityInOrder(BTCityNode *bt)
{
    if (bt == NULL)
    {
        return;
    }
    BTCityInOrder(bt->left);

    //printLinkedList(bt->ll); 
    printf("%s\n", bt->data); 

    BTCityInOrder(bt->right);
}



/**
 * Helper function to BTCityDestructor which handles the freeing of internals 
 * through a recursive post order traversal 
 * @param bt node to free 
 */ 
void BTCityNodeDestructor(BTCityNode *bt)
{
    if (bt == NULL)
    {
        return;
    }
    BTCityNodeDestructor(bt->left);
    BTCityNodeDestructor(bt->right);

    // free the restaurant (data) and the node
    linkedListDestructor(bt->ll); 
    //free(bt->data); 
    free(bt);
}

/**
 * Free a BTCity
 * Calls the recursive helper function BTCityNodeDestructor to accomplish thsi 
 * @param bt Binary Tree to free 
 */ 
void BTCityDestructor(BTCity *bt)
{
    BTCityNodeDestructor(bt->root);
    free(bt);
}


/**
 * Searches the BTCity for all restuarants matching a given name and location
 * through an iterative traversal of the BTCity
 * @param bt BTCity to search
 * @param name name to search for
 * @param loc location to search for
 * @return LinkedList of matches 
 */ 
LinkedList *searchBTCity(BTCity *bt, char *city){
    LinkedList *ll = createLinkedList();
    if (bt->size == 0)
    {
        return ll;
    }

    BTCityNode *curr = bt->root;


    while (true){
        if (strcmp(city, curr->data) < 0){
            if (curr->left == NULL){
                return ll;
            } else {
                curr = curr->left;
            }
        } else if (strcmp(city, curr->data) > 0){
            if (curr->right == NULL) {
                return ll;
            } else{
                curr = curr->right;
            }
        } else {
            
            // we have found a name that matches, now make sure the city matches too
            LinkedList* toReturn =  createLinkedList();
            free(ll); 
            return appendToLinkedList(toReturn, curr->ll); 
             

        }
    }
}
