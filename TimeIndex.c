#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "IntArray.h"
#include "restaurant.h"
#include "LinkedList.h"
#include "TimeIndex.h"

/**
 * Creates an empty time index
 * Handles the intialization of each TimeLinkedList underneath
 * @return pointer to TimeIndex created 
 */ 
TimeIndex* createTimeIndex(){
    TimeIndex* t = malloc(sizeof(TimeIndex));
    TimeLinkedList* sunday = malloc(sizeof(TimeLinkedList));
    TimeLinkedList* monday = malloc(sizeof(TimeLinkedList));
    TimeLinkedList* tuesday = malloc(sizeof(TimeLinkedList));
    TimeLinkedList* wednesday = malloc(sizeof(TimeLinkedList));
    TimeLinkedList* thursday = malloc(sizeof(TimeLinkedList));
    TimeLinkedList* friday = malloc(sizeof(TimeLinkedList));
    TimeLinkedList* saturday = malloc(sizeof(TimeLinkedList));

    createTimeLinkedList(sunday);
    createTimeLinkedList(monday);
    createTimeLinkedList(tuesday);
    createTimeLinkedList(wednesday);
    createTimeLinkedList(thursday);
    createTimeLinkedList(friday);
    createTimeLinkedList(saturday);

    t->sun = sunday;
    t->mon = monday;
    t->tues = tuesday;
    t->wed = wednesday;
    t->thurs = thursday;
    t->fri = friday; 
    t->sat = saturday; 
    return t; 

}

/**
 * Creates a TimeLinkedList (really just inialization)
 * tll should be malloced in createTimeIndex already
 * @param tll already malloc'd TimeLinkedList 
 * 
 */ 
void createTimeLinkedList(TimeLinkedList* tll){
    tll->size = 0;
    tll->head = NULL;
    tll->tail = NULL; 
}

/**
 * Determines which TimeLinkedLIst to insert time into based on dayNum
 * Sunday = 0, Monday = 1, ... , Saturday = 6
 * 
 */ 
void insertInTimeIndex(TimeIndex *t, int dayNum, char* openTime, char* closeTime, Restaurant* restIndex){
    if(dayNum == 0){
        insertInTimeLinkedList(t->sun, openTime, closeTime, restIndex); 
    } else if (dayNum == 1){
        insertInTimeLinkedList(t->mon, openTime, closeTime, restIndex); 
    } else if (dayNum == 2){
        insertInTimeLinkedList(t->tues, openTime, closeTime, restIndex); 
    } else if (dayNum == 3){
        insertInTimeLinkedList(t->wed, openTime, closeTime, restIndex); 
    } else if (dayNum == 4){
        insertInTimeLinkedList(t->thurs, openTime, closeTime, restIndex); 
    } else if (dayNum == 5){
        insertInTimeLinkedList(t->fri, openTime, closeTime, restIndex); 
    } else if (dayNum == 6){
        insertInTimeLinkedList(t->sat, openTime, closeTime, restIndex); 
    }
}


/**
 * Sorted insert into TimeLinkedList by opening time (low to high)
 * Handles insertions into empty linked list, head/middle/tail of linkedlist 
 * @param tll TimeLinkedList to insert into 
 * @param openTime time restaurant opens
 * @param closeTime time restaurant closes
 * @param restIndex restaurant index
 */ 
void insertInTimeLinkedList(TimeLinkedList *tll, char* openTime, char* closeTime, Restaurant* restIndex){
    TimeNode* tNode = malloc(sizeof(TimeNode));
    tNode->open = openTime;
    tNode->close = closeTime;
    tNode->restIndex = restIndex;
    tNode->next = NULL;
    tNode->prev = NULL;

    // empty insertion
    if(tll->size == 0){
        tll->head = tNode;
        tll->tail = tNode;
        tll->size += 1;
        return; 
    }

    TimeNode* curr = tll->head;
    int tCount = tll->size;
    for(int i = 0; i < tCount; i++){
        int res = strcmp(curr->open, tNode->open);
        if(res >= 0){
            if(i == 0){
                // insert at head 
                tNode->next = curr;
                curr->prev = tNode;
                tll->head = tNode;
            } else {
                // insert in body
                tNode->prev = curr->prev;
                tNode->next = curr;

                if(curr->prev != NULL){
                    curr->prev->next = tNode;
                }

                curr->prev = tNode;

            }
            tll->size += 1;
            return; 
        }
        if( i != tCount-1){
            // continue traversing 
            curr = curr->next;
        } else {
            // last element, insert at end
            tNode->prev = curr;
            curr->next = tNode;
            tll->tail = tNode;
            tll->size += 1;
        }
    }
}

/**
 * Determines which linked list to search based on numerical dayNum 
 * Sunday = 0, Monday = 1, ... , Saturday = 6
 * @param t TimeIndex to search 
 * @param dayNum to search
 * @param time to search
 * 
 * @return IntArray of all the restIndices that match the time 
 */ 

LinkedList* searchTimeIndex(LinkedList*ll, TimeIndex* t, int dayNum, char* time){
    LinkedList* toReturn; 
    if(dayNum == 0){
        toReturn = searchTimeLinkedList(ll, t->sun, time);
    } else if (dayNum == 1){
        toReturn = searchTimeLinkedList(ll, t->mon, time);
    } else if (dayNum == 2){
        toReturn = searchTimeLinkedList(ll, t->tues, time);
    } else if (dayNum == 3){
        toReturn = searchTimeLinkedList(ll, t->wed, time);
    } else if (dayNum == 4){
        toReturn = searchTimeLinkedList(ll, t->thurs, time);
    } else if (dayNum == 5){
        toReturn = searchTimeLinkedList(ll, t->fri, time);
    } else if (dayNum == 6){
        toReturn = searchTimeLinkedList(ll, t->sat, time);
    } 
    return toReturn; 
}


/**
 * Searches the TimeLinkedList
 * Makes sure that specified time lands in between the open/close time
 * @param tll TimeLinkedList to search
 * @param time to search for
 * 
 * @return IntArray of restaurant indices that match up 
 */ 

LinkedList* searchTimeLinkedList(LinkedList* ll, TimeLinkedList* tll, char* time){
    LinkedList* toReturn = createLinkedList();
    // determine if the time lies in the range for each one

    // This is not the right approach... 
    // We are using the indices to make this whole thing more efficient 
    // How can we use the time index to make this more efficient 

    // maybe try: 
    // now that we have the right time linked list
    // if it is in the ll as well, then add it toReturn 
    // that is quadratic runtime but it's a short list 
    TimeNode* curr = tll->head;
    for(int i = 0; i < tll->size; i++){
        if(strcmp(curr->open, time) <= 0 && strcmp(curr->close, time) >= 0 ){
            if(isInLinkedList(ll, curr->restIndex) == true){
                 insertInLinkedList(toReturn, curr->restIndex); 
            }
          
        } 
        if(i != tll->size - 1){
            curr = curr->next; 
        }
    }
    //LinkedList* temp = ll; 

    linkedListDestructor(ll); 
    //ll = toReturn; 
    return toReturn; 
}


/**
 * Deletes all of the restaurants in a list from the TimeIndex
 * Calls deleteFromTimeLinkedList 7 times - once for every day of the week 
 * @param toDelete linked list of restaurants
 * @param t Time index to remove from 
 */ 
void deleteFromTimeIndex(LinkedList* toDelete, TimeIndex* t){
    // for each of the Time Indexes 
    deleteFromTimeLinkedList(toDelete, t->sun); 
    deleteFromTimeLinkedList(toDelete, t->mon);
    deleteFromTimeLinkedList(toDelete, t->tues);
    deleteFromTimeLinkedList(toDelete, t->wed);
    deleteFromTimeLinkedList(toDelete, t->thurs);
    deleteFromTimeLinkedList(toDelete, t->fri);
    deleteFromTimeLinkedList(toDelete, t->sat);


}

/**
 * Delete all of the restaurants in a list from a TimeLinkedList
 * Taverses the linked list 
 * @param toDelete linked list of restaurants
 * @param tll time linked list to remove from 
 */ 
void deleteFromTimeLinkedList(LinkedList* toDelete, TimeLinkedList* tll){
    RestNode* curr = toDelete->head; 
    while(true){
        deleteRestFromTimeLinkedList(curr->r, tll); 
        if(curr->next != NULL){
            curr = curr->next; 
        } else {
            break; 
        }
    }
}

/**
 * Delete an individual restaurant from the time linked list 
 * Handles deletion of head, tail, and from body 
 * @param toDelete restuarant
 * @param tll time linked list to delete from 
 */ 

void deleteRestFromTimeLinkedList(Restaurant* toDelete, TimeLinkedList* tll){
    TimeNode* curr = tll->head; 
    while(true){
        if(curr->restIndex == toDelete){
            // delete using the correct case 
            TimeNode* temp = curr; 
            if(curr == tll->head){
                // head node 
                TimeNode* newHead = curr->next;
                newHead->prev = NULL;
                tll->head = newHead; 

                curr = newHead; // increment 
            } else if (curr == tll->tail){
                // tail node 
                TimeNode* newTail = curr->prev; 
                newTail->next = NULL;
                tll->tail = newTail; 

                tll->size -= 1;
                free(temp); 
                break; // no need to increment... we've reached the end
            } else {
                // body node 
                TimeNode* prev = curr->prev;
                TimeNode* next = curr->next;

                prev->next = next;
                next->prev = prev;
                
                curr = next; // increment s

            }
            // decrement the size 
            tll->size -= 1;
            free(temp); 

            
        } else {
            if(curr->next != NULL){
                curr = curr->next; 
            } else {
                break; 
            }

        }
        
    }
}

/**
 * Prints the contents of the time index by calling the print TimeLinkedList function 
 * @param t TimeIndex to print 
 */ 
void printTimeIndex(TimeIndex* t){
    printf("Sunday: \n");
    printTimeLinkedList(t->sun);
    printf("Monday: \n");
    printTimeLinkedList(t->mon);
    printf("Tuesday: \n");
    printTimeLinkedList(t->tues);
    printf("Wednesday: \n");
    printTimeLinkedList(t->wed);
    printf("Thursday: \n");
    printTimeLinkedList(t->thurs);
    printf("Friday: \n");
    printTimeLinkedList(t->fri);
    printf("Satday: \n");
    printTimeLinkedList(t->sat);
    
}

/**
 * Prints the contents of a time linked list by traversing through
 * @param tll TimeLinkedList
 */ 
void printTimeLinkedList(TimeLinkedList* tll){
    TimeNode* curr = tll->head; 

    while(true){
        printf("Rest Name: %s, Open: %s, Close %s \n", curr->restIndex->name, curr->open, curr->close); 
        if(curr->next != NULL){
            curr = curr->next; 
        } else {
            break; 
        }
    }
    /*
    for(int i = 0; i < tll->size; i++){
        printf("Rest Name: %s, Open: %s, Close %s \n", curr->restIndex->name, curr->open, curr->close); 
        if(i != tll->size-1){
            curr = curr->next; 
        }
    }
    */
    printf("\n");
}

/**
 * Frees TimeIndex and the underlying timeLinkedLists 
 * @param t TimeIndex to free
 */ 
void timeIndexDestructor(TimeIndex* t){
    timeLinkedListDestructor(t->sun);
    timeLinkedListDestructor(t->mon);
    timeLinkedListDestructor(t->tues);
    timeLinkedListDestructor(t->wed);
    timeLinkedListDestructor(t->thurs);
    timeLinkedListDestructor(t->fri);
    timeLinkedListDestructor(t->sat);

    free(t);


}

/**
 * Frees TimeLinkedList by freeing each node and the linked list itself 
 * @param tll TimeLinkedList to free 
 */ 
void timeLinkedListDestructor(TimeLinkedList* tll){
    TimeNode* curr = tll->head;
    int tSize = tll->size;
    for(int i = 0; i < tSize; i++){
        TimeNode* temp = NULL;
        if(i != tSize-1){
            temp = curr->next;
        }
        free(curr);
        curr = temp; 
    }
    free(tll);
} 