#ifndef FILEWRITER_H
#define FILEWRITER_H

#include <stdio.h>
#include "restaurant.h"
#include "BinaryTree.h"
#include "LinkedList.h"
#include "ArrayList.h"

/**
 * Write the contents of the knowledge base to a text file 
 * @param fileName of the text file to append to or create if it does not exist 
 * @param bt the knowledge base 
 */ 
extern void binaryTreeToFile(char* fileName, BinaryTree* bt); 

/**
 * Write one restuarant to the file 
 * @param file name of the txt file to append to or create if it doesn't exist 
 */ 
extern void restaurantToFile(char* fileName, Restaurant* rest); 

/**
 * Write the categories of the restuarant to the file 
 * @param file open file ojbect
 * @param rest restaurant to write 
 */ 
extern void writeCategories(FILE* file, Restaurant* rest); 

/**
 * Write the times of the restuarant to the file 
 * @param file open file ojbect
 * @param rest restaurant to write 
 */ 
extern void writeTimes(FILE* file, Restaurant* rest);

/**
 * Write the cost of the restuarant to the file 
 * @param file open file ojbect
 * @param rest restaurant to write 
 */ 
extern void writeCost(FILE* file, Restaurant* rest); 



#endif 