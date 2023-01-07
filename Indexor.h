#ifndef INDEXOR_H
#define INDEXOR_H


#include "BinaryTree.h"
#include "CostIndex.h"
#include "CityIndex.h"
#include "TimeIndex.h"
#include "LinkedList.h"
//#include "BTString.h"
#include "BTCity.h"

#include <stdbool.h>

/**
 * @struct Indexor
 * A container for all the indexing structures 
 */ 
typedef struct Indexor_struct{

    //BTString* cities;
    BTCity* cities; 
    CostIndex* costs; 
    CityIndex* categories;
    TimeIndex* times; 
    
} Indexor; 

/**
 * Cretes an Indexor object 
 * Handles malloc'ing w/in function
 * @return pointer to Indexor object created 
 */ 
extern Indexor* createIndex(); 

/**
 * Inserts all the restaurants in the knowledge base into the indices 
 * @param bt knowledge base
 * @param index Indexor 
 */ 
extern void indexRestaurants(BinaryTree* bt, Indexor* index); 


/**
 * Recursive helper function to insert restaurants into the index 
 * @param bt BTNode* to insert 
 * @param index the indexing structure 
 */ 
extern void indexRestaurantsRecursive(BTNode* bt, Indexor* index); 

/**
 * Inserts information to the corresponding indices
 * @param curr restaurant to insert 
 * @param index indexing structure to insert into 
 */ 
extern void insertOneRestToIndex(Restaurant* curr, Indexor* index); 

/**
 * Remove a linkedlist of restuarants from the indexing structure
 * @param  toDelete linkedList of resaturants to delete
 * @param index indexing structure to remove from 
 */ 
extern void deleteFromIndex(LinkedList* toDelete, Indexor* index); 

/**
 * print the contents  of each indexing structure
 * @param index indexing sturcutre to print 
 */ 
extern void printIndexor(Indexor* index); 

/**
 * Calls the respecitve search functions of the different indices
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
extern void searchIndexDriver(BinaryTree* bt, Indexor* index, int day, char* time, char* city, char** category, int numCategories, bool disjunct, int cost); 

/**
 * Handles the search of conjuctive categories 
 * @param ll of restaurants to search
 * @param cats array of categories that are conjunctive to search for 
 * @param num the number of elements in the cats array 
 */ 
extern LinkedList* categoryConjuncts(LinkedList* ll, char** cats, int num); 

/**
 * Handles the search of disjuncts categories 
 * @param ll of restaurants to search
 * @param cats array of categories that are disjuncts to search for 
 * @param num the number of elements in the cats array 
 */ 
extern LinkedList* categoryDisjuncts(LinkedList* ll, char** cats, int num); 

/**
 * Frees the contents of the indices (all of th indices in the Indexor object)
 * @param index to free 
 */ 
extern void indexDestructor(Indexor* index); 

#endif 