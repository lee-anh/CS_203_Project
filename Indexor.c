#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

#include "Indexor.h"
#include "LinkedList.h"
#include "restaurant.h"

/**
 * Creates an Indexor objects and intializes the indices to NULL
 * @return pointer to Indexor object created 
 */ 
Indexor *createIndex()
{
    Indexor *x = malloc(sizeof(Indexor));
    x->cities = NULL;
    x->costs = NULL;
    x->categories = NULL;
    x->times = NULL;
    return x;
}

/**
 * The indices are created here
 * For each of the restaurants in the knowledge base, 
 * each of the costs, cities, categories, and times are inserted into their respective indexing structures
 * @param bt knowledge base
 * @param index Indexor to assign the created indices to
 */ 
void indexRestaurants(BinaryTree* bt, Indexor *index)
{
 
    index->cities = createBTCity(); 
    index->categories = createCityIndex(); 
    index->costs = createCostIndex(); 
    index->times = createTimeIndex(); 
    
    // in order traversal through the binary tree of restauarants (can't be avoided!)
    
    indexRestaurantsRecursive(bt->root, index); 


}

/**
 * Recursive helper function to insert restaurants into the index 
 * In order traversal of the knowledge base 
 * @param bt BTNode* to insert 
 * @param index the indexing structure 
 */
void indexRestaurantsRecursive(BTNode* bt, Indexor* index){

    if(bt == NULL){
        return; 
    }

    // recursive call 
    indexRestaurantsRecursive(bt->left, index); 

    // functionality here 
    RestNode* curr = bt->ll->head; 
    for(int i = 0; i < bt->ll->size; i++){
        insertOneRestToIndex(curr->r, index); 

        if (i != bt->ll->size-1){
            curr = curr->next; 
        }
    }
    

    // recursive call 
    indexRestaurantsRecursive(bt->right, index); 

}

/**
 * Inserts restaruants information into the corresponding indices
 * that are part of the indexing structure 
 * @param curr restaurant to insert 
 * @param index indexing structure to insert into 
 */ 
void insertOneRestToIndex(Restaurant* curr, Indexor* index){

    
    // category
    for (int j = 0; j < curr->numCategory; j++){
        insertInCityIndex(index->categories, curr->category[j], curr);
    }

    // times
    for (int j = 0; j < 7; j++) {
        if (strcmp(curr->times[j][0], "") != 0){
             insertInTimeIndex(index->times, j, curr->times[j][0], curr->times[j][1], curr);
        }
    }
    // cost
    insertInCostIndex(index->costs, curr->cost, curr);
    
    // city 
  
   insertInBTCity(index->cities, curr);
    


}

/**
 * Remove a linkedlist of restuarants from the indexing structure
 * Calls delete functions from different files 
 * @param  toDelete linkedList of resaturants to delete
 * @param index indexing structure to remove from 
 */ 
void deleteFromIndex(LinkedList* toDelete, Indexor* index){
    deleteFromBTCity(toDelete, index->cities); 
    //deleteFromBTCity(index->cities, name, city); 

    // delete from category index
    deleteFromCityIndex(toDelete, index->categories);
    //printCityIndex(index->categories); 


    // delete from time index
    deleteFromTimeIndex(toDelete, index->times); 
    //printTimeIndex(index->times); 


    // delete from cost index 
    deleteFromCostIndex(toDelete, index->costs); 
    //printCostIndex(index->costs); 
    
}

/**
 * print the contents  of each indexing structure
 * by calling print functions from different indexing structures/files 
 * @param index indexing sturcutre to print 
 */ 
void printIndexor(Indexor* index){
    printBTCity(index->cities); 
    printCityIndex(index->categories);
    printCostIndex(index->costs);
    printTimeIndex(index->times); 
}


/**
 * Calls the respecitve search functions of the different indices
 * Filters through a LinkedList, "shaving" down the results each time 
 * Outputs the results of the search to the terminal 
 * @param bt knowledge base
 * @param index indexing structure
 * @param day to search for (0 = Sunday, ... 7 = Saturday)
 * @param time to search for
 * @param city to search for 
 * @param category list of categories to search for 
 * @param numCategories in the list 
 * @param disjunct true if you want a disjunctive search of the categories, false if you want conjunct categories 
 * @param cost to search for 
 */ 
extern void searchIndexDriver(BinaryTree* bt, Indexor* index, int day, char* time, char* city, char** category, int numCategories, bool disjunct, int cost){
    LinkedList* results; 
    // search the city (using the binary tree)
    // if city is a wild card, then we need to start with a base list, so start with the linked list form of the names binary tree 
    // don't forget to free this stuff!! 
    if(strstr(city, "*") == NULL){
        results = searchBTCity(index->cities, city); 
        
    } else {
        // assign results to a linked list of all the restaurants
        results = binaryTreeToLinkedList(bt); 
    }

    // if I am only searching for exact matches, 
    // then the indexing structures may be slowing me down!!!
    // except they technically whittle it down each time in an efficient manner? 
    
    // search the times
    if(strstr(time, "*") == NULL){
        results = searchTimeIndex(results, index->times, day, time); 
    }

    // search cost (remember that cost is a special search, essentially $$$ acts like a wildcard... )
    if(cost != 1000 && cost != 3){
        // results = search cost index 
        results = searchCostIndex(results, index->costs, cost); 
    }

    // search the categories (remember to consider if there are ORs)
    if(numCategories > 0){
        if(disjunct == false){
            results = categoryConjuncts(results, category, numCategories); //searchCityIndexConjuncts(results, index->categories, category, numCategories); 
        } else {
            results = categoryDisjuncts(results, category, numCategories); // searchCityIndexDisjuncts(results, index->categories, category, numCategories);
        }
    }
    

    // finally, print the results and free the memory 
    if(results->size >0){
        printLinkedList(results); 
    } else {
        printf("No results matched your search :(\n"); 
    }
     
    linkedListDestructor(results); 
}


/**
 * Handles the search of conjuctive categories 
 * Finds all the restuarants that match all of the categories or more 
 * @param ll of restaurants to search
 * @param cats array of categories that are conjunctive to search for 
 * @param num the number of elements in the cats array 
 */ 
LinkedList* categoryConjuncts(LinkedList* ll, char** cats, int num){
    LinkedList* toReturn = createLinkedList(); 
    RestNode* curr = ll->head;
    while(true){
        // if we get all of the categories in num, then we should add it to the right list 
        if(num <= curr->r->numCategory){

            int tally = 0; 

            for(int i = 0; i < num; i++){
                for(int j = 0; j < curr->r->numCategory; j++){
                    
                    if (strcmp(curr->r->category[j], cats[i]) == 0){
                        tally++; 
                        break; 
                    }
                }
            }
            
            if(tally == num){
                insertInLinkedList(toReturn, curr->r); 
            }
    
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
 * Handles the search of disjuncts categories 
 * Finds all of the restaruants that match at least one of the listed categories 
 * @param ll of restaurants to search
 * @param cats array of categories that are disjuncts to search for 
 * @param num the number of elements in the cats array 
 */ 
LinkedList* categoryDisjuncts(LinkedList* ll, char** cats, int num){
    // for each element in the ll
    // if it has a category that matches with the list of 
    // why would I even need to look this up in the category index? 
    LinkedList* toReturn = createLinkedList(); 
    RestNode* curr = ll->head;
    while(true){

        for(int i = 0; i < curr->r->numCategory; i++){
            bool match = false; 
            for(int j = 0; j < num; j++){
                if(strcmp(curr->r->category[i], cats[j]) == 0){
                    match = true; 
                    break; 
                }
            }
            if(match == true){
                insertInLinkedList(toReturn, curr->r); 
                break; 
            }
        }
        
        if(curr->next != NULL){
            curr = curr->next; 
        } else {
            break; 
        }
    }
    for(int i = 0; i < num; i++){

    }
    linkedListDestructor(ll); 
    return toReturn; 

    
}



/**
 * Calls all the destructors for each index
 * Finally, frees the container itself 
 */ 
void indexDestructor(Indexor *index)
{

    BTCityDestructor(index->cities);
    costIndexDestructor(index->costs);
    timeIndexDestructor(index->times);
    cityIndexDestructor(index->categories);
    

    free(index);
}
