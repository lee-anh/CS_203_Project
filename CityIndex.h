#ifndef CIYTINDEX_H
#define CITYINDEX_H

#include <stdbool.h>

#include "IntArray.h"
#include "restaurant.h"
#include "LinkedList.h"

/**
 * @struct CityNode
 * Creates a node to be used inthe creation of the CityIndex
 * Contains the city name and the restuarant index it corresponds to
 */ 
typedef struct CityNode_struct{
    struct CityNode_struct* next; 
    struct CityNode_struct* prev;
    char* data; // city name 
    Restaurant* restIndex; // restaurant index 

} CityNode; 

/**
 * @struct CityIndex
 * Creates a lexiographically sorted doubly linked list of the cities in the knowledge base 
 */ 
typedef struct CityIndex_struct{
    int size; 
    CityNode* head;
    CityNode* tail; 
} CityIndex;

/**
 * Creates a CityIndex object
 * Takes care of the malloc'ing
 * @return pointer to CityIndex created 
 */ 
extern CityIndex* createCityIndex(); 

/**
 * Insert a new city/restuarant pair into its sorted position in the index
 * @param c CityIndex pointer
 * @param city string of the city to insert
 * @param restIndex pointer to Restaurant 
 */ 
extern void insertInCityIndex(CityIndex* c, char* city, Restaurant* restIndex);

/**
 * Remove a list of restaurants from the linked list 
 * @param toDelete LinkedList of Restaurants to delte 
 * @param c CityIndex to delete from 
 */ 
extern void deleteFromCityIndex(LinkedList* toDelete, CityIndex* c); 

/**
 * Delete an individual restuarant from the CityIndex 
 * Helper frunction to deleteFromCityIndex 
 * @param toDelete Restaurant to delete 
 * @param c CityIndex to delete from 
 */ 
extern void deleteRestFromCityIndex(Restaurant* toDelete, CityIndex* c); 
/**
 * Prints out the contents of the CityIndex
 * @param c CityIndex pointer
 */ 
extern void printCityIndex(CityIndex* c);

/**
 * Free the CityIndex
 * @param c CityIndex to free 
 */ 
extern void cityIndexDestructor(CityIndex* c);

#endif