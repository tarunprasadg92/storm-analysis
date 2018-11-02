#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "storms.h"

//==============================================================================
//
//                          PRINT STORMS FUNCTION
//
//               Prints the list of storms stored in the memory
//==============================================================================

void printStorms(struct Storm *head)
{
    // Check for empty headers
    if ((head == NULL) || (head->next == NULL))
    {
        printf("Header is empty.\n");
        exit(EXIT_FAILURE);
    }

    // Temporary pointer to the storm
    struct Storm *temp = head->next;
    int record_counter = 0;

    // Traverse until the end and print out the name
    while (temp != head)
    {
        char *storm_name = strtok(temp->name, ".");
        printf("%s", storm_name);
        
        struct Data *temp_data = temp->data;
        
        while (temp_data != NULL)
        {
            record_counter += 1;
            temp_data = temp_data->next;
        }
        
        printf(" - %d records\n", record_counter);
        record_counter = 0;
        temp = temp->next;
    }
}

//==============================================================================
//
//                           INSERT STORM FUNCTION
//
//             Function to insert a storm into the linked list
//==============================================================================

void insertStorm(struct Storm *head, char *name)
{
    // Check for empty header
    if (head == NULL)
    {
        printf("Header node is empty.\n");
    }

    // Allocate memory for the new storm and check for memory allocation failure
    struct Storm *new_storm = (struct Storm *)malloc(sizeof(struct Storm));
    if (new_storm == NULL)
    {
        printf("\nMemory Allocation to create a new storm failed\n");
        exit(EXIT_FAILURE);
    }

    // Initialization of the new storm
    new_storm->name = strdup(name);
    new_storm->next = NULL;
    new_storm->previous = NULL;
    new_storm->data = NULL;

    // First entry into the list of storms
    if (head->next == NULL)
    {
        head->next = new_storm;
        new_storm->next = head;
        head->previous = new_storm;
        new_storm->previous = head;
    }
    
    // Subsequent entries appended to the end of the list
    else
    {
        struct Storm *temp = head->previous;
        temp->next = new_storm;
        new_storm->next = head;
        new_storm->previous = temp;
        head->previous = new_storm;
    }
}

//==============================================================================
//
//                           INSERT DATA FUNCTION
//
//               Function to add a single record of data to a storm
//==============================================================================

void insertData(struct Storm *head, char *name, char *data)
{
    // Check for empty headers
    if ((head == NULL) || (head->next == NULL))
        printf("\nHeader is empty.");

    // Iterate over the storm names
    struct Storm *temp = head->next;
    while (temp != NULL)
    {
        // Compare to find the given storm name
        if (strcmp(temp->name, name) == 0)
        {
            // Memory allocation for new record and check for memory allocation failure
            struct Data *new_data = (struct Data *)malloc(sizeof(struct Data));
            if (new_data == NULL)
            {
                printf("\nMemory Allocation for data node failed\n");
                exit(EXIT_FAILURE);
            }

            //  Splitting the line read into individual tokens and store them 
            char *token;
            token = strtok(data, " ");

            new_data->latitude = atof(strtok(NULL, " "));
            new_data->longitude = atof(strtok(NULL, " "));
            char *time_token = strtok(NULL, " ");
            new_data->wind_speed = atoi(strtok(NULL, " "));
            new_data->pressure = atoi(strtok(NULL, " "));
            new_data->storm_type = strdup(strtok(NULL, " "));
            new_data->timestamp.month = atoi(strtok(time_token, "/"));
            new_data->timestamp.day = atoi(strtok(NULL, "/"));
            new_data->timestamp.hour = atoi(strtok(NULL, "Z/"));

            new_data->next = NULL;
            new_data->previous = NULL;

            //  Traverse through the data records and store them at the end
            struct Data *data_temp = temp->data;
            if (data_temp == NULL)
                temp->data = new_data;
            else
            {
                while (data_temp->next != NULL)
                    data_temp = data_temp->next;
                data_temp->next = new_data;
                new_data->previous = data_temp;
            }

            return;
        }
        else
            temp = temp->next;
    }
}

//==============================================================================
//
//                          PRINT DATA FUNCTION
//
//          Print out the data of all the storms stored in the memory
//==============================================================================

void printData(struct Storm *head)
{
    // Check for empty header
    if ((head == NULL) || (head->next == NULL))
        printf("\nHeader is empty.");

    // Traverse through the storm linked list
    struct Storm *temp = head->next;
    while (temp != head)
    {
        printf("\nPrinting out data about %s storm\n", temp->name);

        // Traverse through each record of a storm and print
        struct Data *data_temp = temp->data;
        while (data_temp != NULL)
        {
            printf("\nLatitude : %f", data_temp->latitude);
            printf("\nLongitude : %f", data_temp->longitude);
            printf("\nWind Speed : %d", data_temp->wind_speed);
            printf("\nPressure : %d", data_temp->pressure);
            printf("\nStorm Type : %s", data_temp->storm_type);
            printf("\nMonth : %d", data_temp->timestamp.month);
            printf("\nDay : %d", data_temp->timestamp.day);
            printf("\nHours : %d\n", data_temp->timestamp.hour);

            data_temp = data_temp->next;
        }
        printf("\n=========================================================\n");
        temp = temp->next;
    }
}

//==============================================================================
//
//                              FREE DATA FUNCTION
//
//                      Clear the data stored about storms
//==============================================================================

void freeData(struct Storm *head)
{
    // Check for empty header
    if ((head == NULL) || (head->next == NULL))
        printf("\nHeader is empty.");

    // Traverse through the storms linked list
    struct Storm *temp = head->next;
    while (temp != head)
    {
        // Traverse through the records of each storm
        struct Data *data_temp = temp->data;
        while (data_temp != NULL)
        {
            struct Data *next_data_pointer = data_temp->next;
            free(data_temp);
            data_temp = next_data_pointer;
        }
        struct Storm *next_storm_pointer = temp->next;
        free(temp);
        temp = next_storm_pointer;
    }
}

//==============================================================================
//
//                           PRINT SUMMARY FUNCTION
//
//                  Print out the summary of the given data
//==============================================================================

void printSummary(struct Storm *head)
{
    // Check for empty headers
    if ((head == NULL) || (head->next == NULL))
        printf("\nHeader is empty.");

    // Traverse through the storms list
    struct Storm *temp = head->next;
    while (temp != head)
    {
        // Pointer to a record of data 
        struct Data *data_temp = temp->data;

        // variables to compute the start time of a storm
        int start_month = data_temp->timestamp.month;
        int start_day = data_temp->timestamp.day;
        int start_time = data_temp->timestamp.hour;

        // Variables to compute the maximum and minimum latitutde and longitude
        float latitude_min = 50.0;
        float longitude_min = 0.0;
        float latitude_max = 10.0;
        float longitude_max = -110.0;

        // variables to compute the maximum wind speed
        int max_wind = 0;
        int max_wind_month = 0;
        int max_wind_day = 0;
        int max_wind_hour = 0;

        // variables to find the type of the storm
        int level = 1;
        char *type;
        char *type_1 = "TROPICAL-DEPRESSION";
        char *type_2 = "TROPICAL-STORM";

        //  Traverse over every record of the storm
        while (data_temp->next != NULL)
        {
            // Find the minimum latitude
            if (latitude_min > data_temp->latitude)
                latitude_min = data_temp->latitude;

            // Find the maximum latitude
            if (latitude_max < data_temp->latitude)
                latitude_max = data_temp->latitude;

            // Find the minimum longitude
            if (longitude_min > data_temp->longitude)
                longitude_min = data_temp->longitude;

            // Find the maximum longitude
            if (longitude_max < data_temp->longitude)
                longitude_max = data_temp->longitude;

            // Find the maximum wind speed
            if (max_wind < data_temp->wind_speed)
            {
                max_wind = data_temp->wind_speed;
                max_wind_month = data_temp->timestamp.month;
                max_wind_day = data_temp->timestamp.day;
                max_wind_hour = data_temp->timestamp.hour;
            }

            // Find the type of storm
            type = strdup(data_temp->storm_type);
            if (strcmp(type, type_1) == 0)
            {
                if (level < 2)
                    level = 1;
            }
            else if (strcmp(type, type_2) == 0)
            {
                if (level < 3)
                    level = 2;
            }
            else
                level = 3;

            data_temp = data_temp->next;
        }

        // Variables to compute the end time of a storm
        int end_month = data_temp->timestamp.month;
        int end_day = data_temp->timestamp.day;
        int end_time = data_temp->timestamp.hour;

        // Print out the summary from the computations
        printf("\n**********************************************************\n");
        char *storm_name = strtok(temp->name, ".");
        printf("Name : %s\n", storm_name);
        // Determine the type of storm
        if (level == 2)
            printf("Type : Tropical-Storm\n");
        else if (level == 1)
            printf("Type : Tropical-Depression\n");
        else
            printf("Type : Hurricane\n");
        printf("Start : %d/%d at %d:00 hours, End : %d/%d at %d:00 hours.\n", start_month, start_day, start_time, end_month, end_day, end_time);
        printf("Range : Latitude: %f to %f; Longitude: %f to %f.\n", latitude_min, latitude_max, longitude_min, longitude_max);
        printf("Maximum sustained winds : %d MPH on %d/%d at %d:00 hours.\n", max_wind, max_wind_month, max_wind_day, max_wind_hour);
        printf("**********************************************************\n");

        temp = temp->next;
    }
}

//==============================================================================
//
//                           NUMBER OF STORMS FUNCTION
//
//                 Return the number of storms stored in the memory
//==============================================================================

int numberOfStorms(struct Storm *head)
{
    // Check for empty header
    if ((head == NULL) || (head->next == NULL))
        return 0;

    // Traverse over the list and increment the counter, return final counter value
    struct Storm *temp = head->next;
    int number = 1;
    while (temp->next != head)
    {
        number += 1;
        temp = temp->next;
    }
    return number;
}

//==============================================================================
//
//                            PRINT OUTPUTS FUNCTION
//
//    Function to print the day-by-day storm totals, wind speed ranges and 
//                         latitude-longitude totals
//==============================================================================

void printOutputs(struct Storm *head)
{
    // Check for empty header
    if ((head == NULL) || (head->next == NULL))
        printf("\nHeader is empty.");

    // Temporary pointer to traverse the data
    struct Storm *temp = head->next;

    // Day-by-day storm totals array
    int *storm_total = (int *)calloc(6 * 31, sizeof(int));

    // Sustained winds array and variables that aid in computation
    int number_of_storms = numberOfStorms(head);
    int *sustained_winds = (int *)calloc(20 * number_of_storms, sizeof(int));
    char storm_names[number_of_storms][25];
    int storm_number = 0;

    // Latitude-Longitude totals array
    int *lat_long_totals = (int *)calloc(110 * 39, sizeof(int));

    // Traverse over all the storms
    while (temp != head)
    {

        strcpy(storm_names[storm_number], temp->name);

        // Traverse over all the records of each storm
        struct Data *data_temp = temp->data;
        while (data_temp->next != NULL)
        {
            // Get the month and day of each storm
            int month = data_temp->timestamp.month;
            int day = data_temp->timestamp.day;

            // Increment the appropriate index in the array
            int index = ((month - 6) * 31) + (day - 1);
            if ((month >= 0) && (month < 12))
                storm_total[index] += 1;

            // Get the wind speed value and increment the appropriate value based on the index
            int wind_col = data_temp->wind_speed / 10;
            sustained_winds[(storm_number * 20) + wind_col] += 1;

            // Get the latitude and longitude values and increment the appropriate index in the array
            int lati = (int)data_temp->latitude;
            int longi = (int)data_temp->longitude;
            lat_long_totals[(lati * 39) + longi] += 1;

            data_temp = data_temp->next;
        }
        storm_number += 1;
        temp = temp->next;
    }

    // Block to print the mpnthly totals of the storms
    printf("\n\nMonthly totals for typical hurricane season from June 1 to November 30(Month Vs Day)\n\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("Month\\Day ");

    int iterator;
    for (iterator = 1; iterator <= 31; iterator++)
        printf("|%3d", iterator);
    printf("\n");
    printf("----------------------------------------------------------------------------------------------------------------------------------------\n");

    char *months[] = {"June" , "July" , "August" , "September" , "October" , "November"};
    int row, col;

    for (row = 0; row < 6; row++)
    {
        printf("%10s|", months[row]);
        for (col = 0; col < 31; col++)
        {
            printf("%3d|", *(storm_total + (row * 31) + col));
        }
        printf("\n");
        printf("----------------------------------------------------------------------------------------------------------------------------------------\n");
    }

    // Block to print the sustained winds table
    printf("\n\nSustained Winds (Storm Name Vs WindSpeed)\n");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    printf("Storm \\ Speed|");

    for (iterator = 0; iterator < 20; iterator++)
    {
        printf("%4d|", ((iterator * 10) + 9));
    }
    printf("\n");
    printf("-------------------------------------------------------------------------------------------------------------------\n");
    for (row = 0; row < number_of_storms; row++)
    {
        printf("%13s|", storm_names[row]);
        for (col = 0; col < 20; col++)
        {
            printf("%4d|", *(sustained_winds + (row * 20) + col));
        }
        printf("\n");
        printf("-------------------------------------------------------------------------------------------------------------------\n");
    }

    // Block to print the latitude and longitude totals
    printf("\n\nLatitude Longitude Totals (Longitude Vs Latitude)\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n  |");
    for (iterator = 11; iterator < 50; iterator++)
    {
        printf("%2d|", iterator);
    }
    printf("\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    for (row = 0; row < 110;row++)
    {
        printf("%2d|", row);
        for (col = 0; col < 39; col++)
        {
            printf("%2d|", *(lat_long_totals + (row * 39) + col));
        }
        printf("\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
    }

    // Freeing the data allocated for creating the tables
    free(storm_total);
    free(sustained_winds);
    free(lat_long_totals);
}


//##############################################################################
//
//                               MAIN FUNCTION
//
//##############################################################################

int main(int argc, char **argv)
{
    int argument_counter = 1;

    // Program to exit when the user has not given enought arguments
    if (argc <= 1)
    {
        printf("No arguments found to process.\n");
        exit(0);
    }
    
    // Process to be repeated for every year<argument>
    while (argument_counter < argc)
    {
        // char *default_path = "/home/tarun/CS819/1_Assignment/";
        char *default_path = "/home/tarun/MS-CS/1_Semester/CS819/1_Assignment/";

        char data_file[70];
        char data_folder[70];

        // Create string for file path of data.txt
        strcpy(data_file, default_path);
        strcat(data_file, argv[argument_counter]);
        strcat(data_file, "/data.txt");

        // Create string for file path of data files
        strcpy(data_folder, default_path);
        strcat(data_folder, argv[argument_counter]);
        strcat(data_folder, "/");

        // Create and allocate a header to point to the storms
        struct Storm *head = (struct Storm *)malloc(sizeof(struct Storm));
        head->name = "Header";
        head->next = NULL;
        head->previous = NULL;
        head->data = NULL;

        // Initialize variables to read data from data.txt
        FILE *fp;
        char *storm_name = NULL;
        size_t len = 0;
        ssize_t read;

        fp = fopen(data_file, "r");
        if (fp == NULL)
        {
            printf("\nError opening %s\n", data_file);
            exit(EXIT_FAILURE);
        }

        // Process to be repeated for every file name given in data.txt
        while ((read = getline(&storm_name, &len, fp)) != -1)
        {
            // Elimination of '\n' from the character stream
            if (storm_name[strlen(storm_name) - 1] == '\n')
            {
                storm_name[strlen(storm_name) - 2] = '\0';
            }

            // Create string to each storm data file
            char storm_file[80];
            strcpy(storm_file, data_folder);
            strcat(storm_file, storm_name);

            // Insert every storm into a master linked-list
            insertStorm(head, storm_name);

            // File handlers to open and read every storm's specific file
            FILE *storm_file_fp = fopen(storm_file, "r");
            if (storm_file_fp == NULL)
            {
                printf("\nError opening %s\n", storm_file);
                // perror(storm_file_fp);
                exit(EXIT_FAILURE);
            }

            // Initialization of variables to read data from each storm file
            size_t s_len = 0;
            ssize_t s_read;
            char *data = NULL;

            // Process to be repeated for every record of data in the file
            while ((s_read = getline(&data, &s_len, storm_file_fp)) != -1)
            {
                if (data[strlen(data) - 1] == '\n')
                {
                    data[strlen(data) - 2] = '\0';
                }

                // Insert the record into the master-linked list under the storm
                insertData(head, storm_name, data);
            }
            free(data);
        }
        
        printStorms(head);

        //  Printing all the data obtained from the data files
        printData(head);

        // Prints out a summary of the data obtained from the data files
        printSummary(head);

        // Prints out the day-by-day storm totals, wind speed ranges and latitude-longitude storm totals
        printOutputs(head);

        // Clears the data stored in the memory
        freeData(head);

        free(storm_name);
        fclose(fp);

        argument_counter++;
    }

    printf("\n");
    return 0;
}
