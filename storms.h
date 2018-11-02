
// Function to add a storm to the linked list
void insertStorm(struct Storm *, char *name);

// Print the list of storms stored in the memory
void printStorms(struct Storm *);

// Insert a single record of data to a particular storm
void insertData(struct Storm *, char *name, char *);

// Print out the data of all the storms stored in the memory
void printData(struct Storm *);

// Clears all the storm-related data stored 
void freeData(struct Storm *);

// Prints out the summary from the storm's data
void printSummary(struct Storm *);

// Prints out the day-by-day totals, wind speed range and latitude and longitude totals
void printOutputs(struct Storm *);

// Returns the number of storms contained in the linked list
int numberOfStorms(struct Storm *);
