#ifndef TIMEINDEX_H
#define TIMEINDEX_H




/**
 * @struct TimeNode 
 * node for the TimeLinkedList structure 
 * Contains time open, clsose and corresponding restaurant index 
 */ 
typedef struct TimeNode_struct{
    struct TimeNode_struct* next; 
    struct TimeNode_struct* prev;
    char* open;
    char* close;
    Restaurant* restIndex;

} TimeNode; 

/**
 * @struct TimeLinkedList 
 * Sorted doubly linked list 
 */ 
typedef struct TimeLinkedList_struct{
    int size;
    TimeNode* head;
    TimeNode* tail;
} TimeLinkedList;

/**
 * @struct TimeIndex
 * Contains a TimeLinkedList for each day of the week 
 */ 
typedef struct TimeIndex_struct{
    TimeLinkedList* sun; 
    TimeLinkedList* mon;
    TimeLinkedList* tues; 
    TimeLinkedList* wed;
    TimeLinkedList* thurs; 
    TimeLinkedList* fri;
    TimeLinkedList* sat; 

} TimeIndex;

/**
 * Creates an empty TimeIndex 
 * @return TimeIndex created 
 */ 
extern TimeIndex* createTimeIndex(); 

/**
 * Creates a TimeLinkedList
 * Helper to createTimeIndex
 * @param tll to inialize fields of 
 */ 
extern void createTimeLinkedList(TimeLinkedList* tll); 

/**
 * Deterimnes which TimeLinkedList to insert this time into 
 * @param t TimeIndex
 * @param dayNum numerical value of the day
 * @param openTime time restaurant opens
 * @param closeTime time restaurant closes
 * @param restIndex restaurant index
 */ 
extern void insertInTimeIndex(TimeIndex *t, int dayNum, char* openTime, char* closeTime, Restaurant* restIndex);

/**
 * Sorted insert into TimeLinkedList by opening time (low to high)
 * Helper to insertInTimeIndex 
 * @param tll TimeLinkedList to insert into 
 * @param openTime time restaurant opens
 * @param closeTime time restaurant closes
 * @param restIndex restaurant index
 */ 
extern void insertInTimeLinkedList(TimeLinkedList *tll, char* openTime, char* closeTime, Restaurant* restIndex); 

/**
 * Determines which linked list to search based on dayNum 
 * @param t TimeIndex to search 
 * @param dayNum to search
 * @param time to search
 * 
 * @return IntArray of all the restIndices that match the time 
 */ 

extern LinkedList* searchTimeIndex(LinkedList* ll, TimeIndex* t, int dayNum, char* time); 


/**
 * Searches the TimeLinkedList for a specified time 
 * @param tll TimeLinkedList tosearch
 * @param time to search for
 * 
 * @return IntArray of restaurant indices that match up 
 */ 
extern LinkedList* searchTimeLinkedList(LinkedList* ll, TimeLinkedList* tll, char* time);


/**
 * Deletes all of the restaurants in a list from the TimeIndex
 * @param toDelete linked list of restaurants
 * @param t Time index to remove from 
 */ 
extern void deleteFromTimeIndex(LinkedList* toDelete, TimeIndex* t); 

/**
 * Delete all of the restaurants in a list from a TimeLinkedList
 * @param toDelete linked list of restaurants
 * @param tll time linked list to remove from 
 */ 
extern void deleteFromTimeLinkedList(LinkedList* toDelete, TimeLinkedList* tll); 

/**
 * Delete an individual restaurant from the time linked list 
 * @param toDelete restuarant
 * @param tll time linked list to delete from 
 */ 
extern void deleteRestFromTimeLinkedList(Restaurant* toDelete, TimeLinkedList* tll); 


/**
 * Prints the contents of the time index 
 * @param t TimeIndex to print 
 */ 
extern void printTimeIndex(TimeIndex* t);
/**
 * Prints the contents of a time linked list 
 * Helper to printTimeIndex
 * @param tll TimeLinkedList
 */  
extern void printTimeLinkedList(TimeLinkedList* tll); 



/**
 * Frees TimeIndex
 * @param t TimeIndex to free
 */ 
extern void timeIndexDestructor(TimeIndex* t);

/**
 * Frees TimeLinkedList
 * @param tll TimeLinkedList to free 
 */ 
extern void timeLinkedListDestructor(TimeLinkedList* tll); 





#endif