#ifndef NEWCONTROLLER_H
#define NEWCONTROLLER_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "restaurant.h"
#include "FileReader.h"
#include "FileWriter.h"
#include "BinaryTree.h" 
#include "Indexor.h"


/**
 * @struct Query
 * Creates a container to hold a user's search query 
 */ 
typedef struct Query_struct{
    int day;
    char* time;
    char* city;
    char** category;
    int numCategories;
    bool catDisjunct; 
    int cost; 

} Query; 

/**
 * Creates a Query object 
 * Takes care of the malloc'ing
 * @return pointer to created Query object 
 */ 
extern Query* createQuery();

/**
 * Frees the contents of a Query and the object itself
 * @param q Query to free
 */ 
extern void queryDestructor(Query* q);

/**
 * Prints the contents of a query 
 * @param q pointer to Query to print 
 */ 
extern void printQuery(Query *q);

/**
 * Function that drive the program, called in main.c 
 */ 
extern void newControl(); 

/**
 * Decide which command to execute given user input 
 * @param query user's input 
 * @param bt knowledge base
 * @param index indexing structure 
 */ 
extern void processQuery(char *query, BinaryTree* bt, Indexor* index);

/**
 * Get input from the user
 * @return user input 
 */ 
extern char* getQuery(); 

/**
 * Queries user for a name and location and prints out restaurants that match
 * @param bt knowledge base
 */ 
extern void eSearch(BinaryTree* bt); 

/**
 * Queries user for a file name and write the knowledge base to that file 
 * @param bt knowledge base 
 */ 
extern void wCommand(BinaryTree* bt); 

/**
 * Queries user for info about a restuarant to add, 
 * adds the restuarnat to the knowledge base and the indexing structure
 * @param bt knowledge base
 * @param index indexing structure 
 */ 
extern void aCommand(BinaryTree* bt, Indexor* index); 

/**
 * Queries user for the name and city of a restuarant
 * Removes all restaurants that match that description
 * @param bt knowledge base
 * @param index indexing structure 
 */ 
extern void rCommand(BinaryTree* bt, Indexor* index); 

/**
 * Queries user for info about a restaurant
 * prints out all of the restaurants that match that description 
 * @param bt knowledge base
 * @param index indexing structure 
 */ 
extern void sCommand(BinaryTree* bt, Indexor* index); 

/**
 * Queries user for info about a restuarant to modify
 * modifies all restaurants that match the name and city of the speicified restaurant 
 * @param bt knowledge base
 * @param index indexing structure 
 */ 
extern void mCommand(BinaryTree* bt, Indexor* index); 

/**
 * Helper function that queries user for restaurant info 
 * @return a restuarant object 
 */ 
extern Restaurant* getRestaurantFromUser(); 

/**
 * Given a category query, parse it and add the category array to the Query object
 * Helper to searchQuery
 * @param qCategory query
 * @param q Query object to add to 
 * 
 * @return true if it's a list of disjuncts, false if it's a list of conjuncts
 */ 
extern void processCategory(char* qCategory, Query* q); 

/**
 * Parse a query into conjunct categoires
 * @param qCategory string of user input to parse
 * @param q Query object to modify 
 */ 
extern void processConjuncts(char* qCategory, Query* q); 

/**
 * Parse a query into conjunct categoires
 * @param qCategory string of user input to parse
 * @param q Query object to modify 
 */ 
extern void processDisjuncts(char* qCategory, Query* q); 

/**
 * Given a cost query, parse it and add the cost to the Query object 
 * Helper to searchQuery
 * @param qCost query
 * @param q Query object to add to 
 */ 
extern void processCost(char* qCost, Query* q); 

/**
 * Given a time query, parse it and add the time info to the Query object
 * Helper to searchQuery
 * @param qTime query
 * @param q Query object 
 */ 
extern void processTime(char* qTime, Query* q); 

/**
 * Removes unecessary spaces from a user's query
 * @param query to trim 
 */
extern void trimQuery(char* s); 



// modify and delete command involve different data structures
// will have to fix the bullet hole before doing that 
#endif 