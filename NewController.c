#include "NewController.h"
 


/**
 * Creates the Query object and inializes fields to some default values
 * 
 * @return Query created 
 */ 
Query *createQuery()
{
    Query *q = malloc(sizeof(Query));
    q->day = -1;
    q->time = "";
    q->city = "";
    q->category = NULL;
    q->numCategories = -1; 
    q->catDisjunct = false; 
    q->cost = -1;
}

/**
 * Frees anything that was malloc'd in the Query
 * Frees the Query itself 
 * Assumes that the city, time, and categories were dynamically allocated and assigned at some point 
 */ 
void queryDestructor(Query *q)
{
    free(q->city);
    free(q->time);
    for(int i = 0; i < q->numCategories; i++){
        free(q->category[i]); 
    }
    free(q->category); 
    free(q);
}


/**
 * Prints the contents query, primarly used for debugging 
 * @param q Query to print
 */ 
void printQuery(Query *q)
{
    printf("Your query: \n");
    printf("City: %s\n", q->city); 
    printf("Day: %d, Time: %s\n", q->day, q->time);
    printf("Num categories %d\n", q->numCategories); 
    printf("Categories: ");
    for (int i = 0; i < q->numCategories; i++)
    {
        printf("*%s* ", q->category[i]);
    }
    if(q->catDisjunct == true){
        printf("Disjuncts\n");
    } else {
        printf("Conjuncts\n"); 
    }
    printf("\nCost: %d\n", q->cost);
}

/**
 * The function that drives the program, called in main.c 
 * The file name of the from which the knowledge base is constructed
 * is specified here 
 */ 
void newControl(){
    BinaryTree *rests = readIn("restaurants.txt"); 
    Indexor *index = createIndex(); 
    indexRestaurants(rests, index); 
    
    while(true){
        char* queryy = getQuery(); 
        processQuery(queryy, rests, index); 
        free(queryy); 
    }

    return; 
}


/**
 * Decide which command to execute given user input 
 * @param query user's input 
 * @param bt knowledge base
 * @param index indexing structure 
 */ 
void processQuery(char *query, BinaryTree* bt, Indexor* index){
   // check the more complex commands by checking the first letters 
   if(strcmp(query, "p") == 0){
        printBinaryTree(bt); 
       //printIndexor(index); 
    } else if (strcmp(query, "x") == 0){
        free(query); 
        BinaryTreeDestructor(bt);
        indexDestructor(index);
        printf("Goodbye!\n"); 
        exit(0); 

    } else if (strcmp(query, "e") == 0){
        eSearch(bt); 

    } else if (strcmp(query, "w") == 0){
        wCommand(bt); 

    } else if (strcmp(query, "a") == 0 ){
        aCommand(bt, index);

    } else if (strcmp(query, "r") == 0){
        rCommand(bt, index); 

    } else if (strcmp(query, "s") == 0){
        sCommand(bt, index); 

    } else if (strcmp(query, "m") == 0){
        mCommand(bt, index); 
    } else {
        printf("Invalid command. Valid input: \np - print all restaurants\ns - search for restaurants\ne - find restaurants by name and location\na - add a restaurant\nr - remove a restaurant\nm - modify an existing restaurant\nw - write knowledge base to a file\n"); 
    }

}

/**
 * Reads in the user's query into a string that is returned
 * 100 characters are read in (more than enough for a query)
 * 
 * @return char* of the user's query, read in from the terminal 
 */ 
char* getQuery(){
    char *query = malloc(sizeof(char) * 50);
    printf("Query: ");
    scanf(" %50[^\n]s", query);
    return query;
} 


/**
 * Queries user for a name and location and prints out restaurants that match
 * 
 * Searches the knowledge base for restaurants that match 
 * @param b knowledge base
 */ 
void eSearch(BinaryTree* bt){
    
    char* name = calloc(100, sizeof(char));  

    printf("Name: "); 
    scanf(" %100[^\n]s", name);
    trimQuery(name); 


    char* city = calloc(100, sizeof(char));
    printf("City: ");
    scanf(" %100[^\n]s", city);
    trimQuery(city); 

    LinkedList* ll = searchBinaryTree(bt, name, city); 

  
   
    if(ll == NULL){
        printf("No results matched your search :(\n"); 
    } else {
        
        printLinkedList(ll); 
        linkedListDestructor(ll); 
    }

    
    free(name); 
    free(city); 
}


/**
 * Queries user for a file name and write the knowledge base to that file 
 * Calls binaryTreeToFile (FileWriter.c)
 * @param bt knowledge base 
 */ 
void wCommand(BinaryTree* bt){
    // extract the fileName parameter 
    char* filename = calloc(100, sizeof(char)); 
    printf("Filename: "); 
    scanf(" %100[^\n]s", filename);
    trimQuery(filename); 
    
    
    binaryTreeToFile(filename, bt); 
    free(filename); 
}

/**
 * Queries user for info about a restuarant to add, 
 * adds the restuarnat to the knowledge base and the indexing structure
 * Also prints out the restuarant so user can confirm it's how they want the restuarnt to look 
 * @param bt knowledge base
 * @param index indexing structure 
 */ 
void aCommand(BinaryTree* bt, Indexor* index){
    // extract all the information 
    // add it to the binary tree! 
    // name, location, hours, cost, rank, reviews 
    Restaurant* r = getRestaurantFromUser(); 
    
    printf("The restaurant you just added: \n"); 
    printRestaurant(r); 

    // insert that into the Binary Tree 
    insertInBinaryTree(bt, r); 

    // add to indexing structure!! 
    insertOneRestToIndex(r, index); 

    //printBinaryTree(bt); 
    //printIndexor(index); 

}

/**
 * Queries user for the name and city of a restuarant
 * Removes all restaurants that match that description
 * Searches binary tree first for restaurants that match to get a list of matches
 * then removes all the restaurants in the list from the knowledge base and the indexing structure 
 * @param bt knowledge base
 * @param index indexing structure 
 */ 
void rCommand(BinaryTree* bt, Indexor* index){
    char* name = calloc(100, sizeof(char));  
    printf("Name: "); 
    scanf(" %100[^\n]s", name);
    trimQuery(name); 

    char* city = calloc(100, sizeof(char));
    printf("City: "); 
    scanf(" %100[^\n]s", city);
    trimQuery(city); 

    // get a linked list of restaurants to delete 
    
    LinkedList* ll = searchBinaryTree(bt, name, city);

    free(name);
    free(city); 
    if(ll == NULL){
        printf("Sorry, there wasn't a restaurant that matched your parameters to remove\n"); 
        return; 
    }
    //printLinkedList(ll);
    // delete from knowledge base 
    deleteFromBinaryTree(ll, bt);
    deleteFromIndex(ll, index); 
    

  

    linkedListDeepDestructor(ll); 
    
  


}


/**
 * Queries user for info about a restaurant
 * prints out all of the restaurants that match that description 
 * Can process conjunct/disjuncts for categories
 * @param bt knowledge base
 * @param index indexing structure 
 */ 
void sCommand(BinaryTree* bt, Indexor* index){
    Query *q = createQuery();
    
    char *qCity = malloc(sizeof(char) * 100);
    printf("City: ");
    scanf(" %100[^\n]s", qCity);
    trimQuery(qCity); 

    q->city = qCity; 
    

    char *qCategory = malloc(sizeof(char) * 100);
    printf("Categories: ");
    
    scanf(" %100[^\n]s", qCategory);
    trimQuery(qCategory); 
    if(strstr(qCategory, "*")){
        q->numCategories = 0; 
        
    } else {
       
        processCategory(qCategory, q); 
    }
    

    // process the cost
    char *qCost = malloc(sizeof(char) * 50);
    printf("Cost ($, $$, $$$): ");
    scanf(" %50[^\n]s", qCost);
    trimQuery(qCost); 
    
    processCost(qCost, q);
     
    // process the time
    char *qTime = malloc(sizeof(char) * 50);
    printf("Time (<day> <hr> ex. Monday 13:00): ");
    scanf(" %50[^\n]s", qTime);
    trimQuery(qTime); 

    if(strstr(qTime, "*")){
        q->time = calloc(2, sizeof(char)); 
        q->time[0] = '*'; 
    } else {
        processTime(qTime, q);
    }
    

    searchIndexDriver(bt, index, q->day, q->time, q->city, q->category, q->numCategories, q->catDisjunct, q->cost); 
    //printQuery(q);

    free(qCategory); 
    free(qCost);
    free(qTime);
    queryDestructor(q);
}

/**
 * Queries user for info about a restuarant to modify
 * modifies all restaurants that match the name and city of the speicified restaurant 
 * First searches for the restuarants to modify
 * Then removees them 
 * Then adds them back in with all of the new information 
 * @param bt knowledge base
 * @param index indexing structure 
 */ 
void mCommand(BinaryTree* bt, Indexor* index){
    Restaurant* r = getRestaurantFromUser(); 
    LinkedList* ll = searchBinaryTree(bt, r->name, r->city);
    if(ll == NULL){
        printf("No restaurants matched the one you wanted to modify.\n"); 
        return; 
    }
    int numToModify = ll->size; 
    deleteFromBinaryTree(ll, bt);
    deleteFromIndex(ll, index); 

    Restaurant* mini = createRestaurant(r->name, r->city, r->category, r->numCategory, r->times, r->rank, r->cost, r->reviewers);
    //insertInBinaryTree(bt, mini); 
    //insertOneRestToIndex(mini, index); 
    
    // need to insert multiple restaurants 
    //printf("num to modify %d/n", numToModify); 
    
    for(int i = 0; i < numToModify; i++){
        Restaurant* copy = createCopyOfRest(mini); 

        //printRestaurant(min); 
        insertInBinaryTree(bt, copy); 
        insertOneRestToIndex(copy, index); 

    }
    
    
    //restaurantDestructor(toInsert); 

    free(r);

    //restaurantDestructor(r);  
    //linkedListDestructor(ll); 
    linkedListDeepDestructor(ll); 
    

    
    
}


/**
 * Helper function that queries user for restaurant info 
 * @return a restuarant object 
 */ 
Restaurant* getRestaurantFromUser(){
    Restaurant *r = malloc(sizeof(Restaurant)); 
    createEmptyRestuarant(r); 
    

    
    // name 
    char* name = calloc(100, sizeof(char));  
    printf("Name: "); 
    scanf(" %100[^\n]s", name);
    trimQuery(name); 
    //setName(r, name);
    free(r->name); 
    r->name = name;  
    //free(name); 

   
    // city 
    char* city = calloc(100, sizeof(char));
    printf("City: "); 
    scanf(" %100[^\n]s", city);
    trimQuery(city); 
    //setCity(r, city); 
    free(r->city); 
    r->city = city; 
    //free(city); 

    
        
    // categories
    char* cats = calloc(255, sizeof(char)); 
    printf("Categories: "); 
    scanf(" %255[^\n]s", cats); 
    trimQuery(cats); 
    readCategories(r, cats); 
    free(cats); 

    // hours
    char* hours = calloc(255, sizeof(char)); 
    printf("Times: "); 
    scanf(" %255[^\n]s", hours); 
    //trimQuery(hours); 
    readTimes(r, hours); 
    free(hours); 

    // cost
    // from FileReader.c .. 
    char* cost = calloc(10, sizeof(char)); 
    printf("Cost: ");
    scanf(" %10[^\n]s", cost); 
    trimQuery(cost); 
    readCost(r, cost); // should be able to take care of it just like that 
    free(cost); 

    // rank 
    char* rank = calloc(10, sizeof(char));
    printf("Rank: ");
    scanf(" %10[^\n]s", rank); 
    trimQuery(rank); 
    r->rank = atof(rank); 
    free(rank);


    // reviewers 
    char* reviewers = calloc(10, sizeof(char));
    printf("Reviewers: "); 
    scanf(" %10[^\n]s", reviewers); 
    trimQuery(reviewers); 
    r->reviewers = atoi(reviewers); 
    free(reviewers); 


    return r; 

}

/**
 * Parses the category query
 * Assumes comma separated, no space in between 
 * Figures out the number of categories and mallocs based off of that 
 * Called in searchQuery
 * @param qCategory string containing the user's query 
 * @param q Query object
 */ 
void processCategory(char *qCategory, Query *q){
    if(strstr(qCategory, "OR") != NULL){
        // we are processing disjuncts 
        processDisjuncts(qCategory, q); 
        q->catDisjunct = true;  
    } else {
        // we are processing conjuncts 
        // or we only have one category that we are searching for
        processConjuncts(qCategory, q); 
        q->catDisjunct = false; 
    }
}
/**
 * Parse a query into conjunct categoires
 * Uses comma as the delimiter 
 * @param qCategory string of user input to parse
 * @param q Query object to modify 
 */ 
void processConjuncts(char* qCategory, Query*q)
{
    // parse that string
    // check restaurant class to see whether we are suppose to malloc the strings that go in the array
    int counter = 1;

    //char* temp = calloc(strlen(qCategory), sizeof(char));
    //strcpy(temp, qCategory);

    char* ptr = qCategory;  
    // I think I will set it to temp even though temp is slowing going to get destroyed? 
    while(*ptr != '\0'){
        ptr = strstr(ptr, ",");
        if(ptr != NULL){
            counter++; 
            ptr++;
            ptr++; 
        } else {
            break; 
        }
    } 

    // allocate array
    char **cats = calloc(counter, sizeof(char *));
    for (int i = 0; i < counter; i++){
        cats[i] = calloc(100, sizeof(char));
    }

    char* ptr2 = qCategory;
    char* ptr3 = qCategory; 
    
   for(int i = 0; i < counter; i++){
        
        if(i != counter-1){
            ptr2 = strstr(ptr2, ","); 
            strncpy(cats[i], ptr3, (strlen(ptr3) - strlen(ptr2))); 
            ptr2 += 2; 
            ptr3 = ptr2;
            
            
        } else {
            // we need to grab the last topic
            strcpy(cats[i], ptr3); 
        }
    }
    
    q->numCategories = counter;
    q->category = cats;


}


/**
 * Parse a query into conjunct categoires
 * Uses "OR" as the delimiter 
 * @param qCategory string of user input to parse
 * @param q Query object to modify 
 */ 
void processDisjuncts(char* qCategory, Query* q){
    // parse that string
    // check restaurant class to see whether we are suppose to malloc the strings that go in the array
    int counter = 1;

    //char* temp = calloc(strlen(qCategory), sizeof(char));
    //strcpy(temp, qCategory);

    char* ptr = qCategory;  
    // I think I will set it to temp even though temp is slowing going to get destroyed? 
    while(*ptr != '\0'){
        ptr = strstr(ptr, "OR");
        if(ptr != NULL){
            counter++; 
            ptr++;
            ptr++; 
        } else {
            break; 
        }
    } 

    // allocate array
    char **cats = calloc(counter, sizeof(char *));
    for (int i = 0; i < counter; i++){
        cats[i] = calloc(100, sizeof(char));
    }

    char* ptr2 = qCategory;
    char* ptr3 = qCategory; 
    
   for(int i = 0; i < counter; i++){
        
        if(i != counter-1){
            ptr2 = strstr(ptr2, "OR"); 
            strncpy(cats[i], ptr3, (strlen(ptr3) - strlen(ptr2) - 1)); 
            ptr2 += 3; 
            ptr3 = ptr2;
            
            
        } else {
            // we need to grab the last topic
            strcpy(cats[i], ptr3); 
        }
    }
    
    q->numCategories = counter;
    q->category = cats;
}

/**
 * Assigns a numerical value to the cost
 * $ = 1
 * $$ = 2
 * $$$ = 3
 * 0 if the querr mistakenly did not contain any $ amount 
 * @param qCost string containing cost value
 * @param q Query objec t
 */ 
void processCost(char *qCost, Query *q)
{
    int dollars = 0;
    if (strstr(qCost, "$$$"))
    {
        dollars = 3;
    }
    else if (strstr(qCost, "$$"))
    {
        dollars = 2;
    }
    else if (strstr(qCost, "$"))
    {
        dollars = 1;
    } 
    else if (strstr(qCost, "*")){
        dollars = 1000; 
    }
    q->cost = dollars;
}

/**
 * Determines what day was in qTime and assigns a numerical value
 * for (Sunday, Monday,..., Saturday) the ints (0, 1,..., 6) are assigned
 * Assumes input was formatted correctly day/hr ex. Monday/12:00
 * @param qTime string containing time info 
 * @param q Query object 
 */ 
void processTime(char *qTime, Query *q)
{
    // first process the day
    int day = -1;
    if (strstr(qTime, "Sunday")){ 
        day = 0;
    }
    else if (strstr(qTime, "Monday")){
        day = 1;
    }
    else if (strstr(qTime, "Tuesday")){
        day = 2;
    }
    else if (strstr(qTime, "Wednesday")){
        day = 3;
    }
    else if (strstr(qTime, "Thursday")){
        day = 4;
    }
    else if (strstr(qTime, "Friday")){
        day = 5;
    }
    else if (strstr(qTime, "Saturday")){
        day = 6;
    }

    char *time = calloc(6, sizeof(char));

    int a = 0;
    char *start = qTime;
    while (start[a] != ' ')
    {
        qTime++;
        a++;
        if (a > 50)
        {
            // if it gets here, something was invalid about the input
            break;
        }
    }
    qTime++;

    for (int i = 0; i < 5; i++)
    {
        time[i] = qTime[i];
    }

    // looking for a null terminating here from the calloc
    if (time[4] == '\0')
    {
        for (int i = 4; i > 0; i--)
        {
            time[i] = time[i - 1];
        }
        time[0] = '0';
    }

    q->day = day;
    q->time = time;
}

/**
 * Get rid of any extra spaces that the user may have put at the end
 * Replace spaces with \0 null terminating char 
 * @param s string to possibly trim 
 */ 
void trimQuery(char* s){
    while(s[strlen(s)-1] == ' '){
        s[strlen(s)-1] = '\0'; 
    }
}
