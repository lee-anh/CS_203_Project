
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


#include "FileWriter.h" 


/**
 * Write the contents of the knowledge base to a text file 
 * Gets an arraylist version of the knowledge base and iterates through that to print out the 
 * knowledge base 
 * @param fileName of the text file to append to or create if it does not exist 
 * @param bt the knowledge base 
 */ 
void binaryTreeToFile(char* fileName, BinaryTree* bt){
    
   // binaryNodeToFile(fileName, bt->root); 
    // write the new line between each here?
    ArrayList* al = binaryTreeToArrayList(bt); 

    for(int i = 0; i < al->size; i++){
        restaurantToFile(fileName, at(al, i)); 
    }
}

/**
 * Write one restuarant to the file 
 * Writes directly to the file for some fields
 * Calls helper functions for others 
 * @param file name of the txt file to append to or create if it doesn't exist 
 */ 
void restaurantToFile(char* fileName, Restaurant* rest){
    FILE *file; 
    if ((file = fopen(fileName, "a")) == NULL)
    {
        printf("Error opening file\n");
        exit(1); // exits from the whole program
    }
    // name
    fprintf(file, "%s\n", rest->name); 
    // city 
    fprintf(file, "%s\n", rest->city); 
    // categories
    writeCategories(file, rest); 
    // time 
    writeTimes(file, rest); 
    // cost
    writeCost(file, rest); 
    // rank 
    fprintf(file, "%.1f\n", rest->rank); 
    // print reviewers
    fprintf(file, "%d\n\n", rest->reviewers); 

    // close the file 
    fclose(file); 
}
/**
 * Write the categories of the restuarant to the file 
 * in the correct format that the readIn file was in 
 * @param file open file ojbect
 * @param rest restaurant to write 
 */ 
void writeCategories(FILE* file, Restaurant* rest){
    int numCats = rest->numCategory; 
    for(int i = 0; i < numCats; i++){
        fprintf(file, "%s", rest->category[i]); 
        if(i != (numCats-1)){
            fprintf(file, ", "); 
        } else {
            fprintf(file, "\n"); 
        }
    }
}


/**
 * Write the times of the restuarant to the file 
 * in the correct format the read in file was in 
 * converts some int parameters to their corresponding days of the week 
 * @param file open file ojbect
 * @param rest restaurant to write 
 */ 
void writeTimes(FILE* file, Restaurant* rest){
    // figure out how many times there are to write
    int counter = 0; 
    for(int i = 0; i < 7; i++){
        if(strstr(rest->times[i][0], ":") != NULL){
            counter++; 
        }
    }
    int counter2 = 0; 
    for(int i = 0; i < 7; i++){
        if(strstr(rest->times[i][0], ":") != NULL){
            // print the correct day 
            if(i == 0){
                fprintf(file, "Sunday "); 
            } else if (i == 1){
                fprintf(file, "Monday "); 
            } else if (i == 2){
                fprintf(file, "Tuesday "); 
            } else if (i == 3){
                fprintf(file, "Wednesday "); 
            } else if (i == 4){
                fprintf(file, "Thursday "); 
            } else if (i == 5){
                fprintf(file, "Friday "); 
            } else if (i == 6){
                fprintf(file, "Saturday "); 
            }

            // print the open/close time 
            fprintf(file, "%s ", rest->times[i][0]); 
            fprintf(file, "%s", rest->times[i][1]); 
            // print a comma and space if necessay 
            if (counter2 < counter){
                fprintf(file, ", "); 
                counter2++; 
            }
        }
    }
}

/**
 * Write the cost of the restuarant to the file 
 * converts cost back into the dollar signs that hte readin file was in 
 * @param file open file ojbect
 * @param rest restaurant to write 
 */ 
void writeCost(FILE* file, Restaurant* rest){
    fprintf(file, "\n"); 
    if(rest->cost == 1){
        fprintf(file, "$\n"); 
    } else if (rest->cost == 2){
        fprintf(file, "$$\n"); 
    } else if (rest->cost == 3){
        fprintf(file, "$$$\n"); 
    }
}
