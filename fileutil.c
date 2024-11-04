#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "fileutil.h"

#define MAX_ARR 1000
#define MAX_STR 100

//function to load a file into an array
char ** loadFileAA(char *filename, int *size)
{
	//open the file
	//if cannot open, print error and exit
	FILE *in = fopen(filename, "r");
	if (!in)
	{
	    perror("Can't open file");
	    exit(1);
	}
	
	// Allocate memory for an array of strings (arr)
	int capacity = MAX_ARR;
	char ** arr = malloc(capacity * sizeof(char *));
	//init string to hold next line from file
	char line[MAX_STR];
	//count of number of lines written to the array
	int lineNum = 0;
	
	
	// Read the file line by line.
	while(fgets(line, MAX_STR, in))
    {  
        //trim newline if needed
        if(line[strlen(line) - 1] == '\n') line[strlen(line) - 1] = '\0';

		//check capacity of array, expand if needed
		if(lineNum == capacity)
		{
			capacity += MAX_ARR;
			arr = realloc(arr, capacity * sizeof(char *));
		}

		//allocate size of array to hold string
		arr[lineNum] = malloc(strlen(line) + 1);
		//copy line to array 
        strcpy(arr[lineNum], line);

		lineNum++;
    }

    // Close the file.
	fclose(in);

	//set size to number of lines in array
	*size = lineNum;
	
	// Return pointer to the array of strings.
	return arr;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearchAA(char *target, char **lines, int size)
{
	
	for(int i = 0; i < size; i++)
	{	        
        //if target is a substring of lines[i], return lines[i]
        if(strstr(lines[i], target)) return lines[i];
	}

	return NULL;
}

// Free the memory used by the array
void freeAA(char ** arr, int size)
{
	//for each element in the array, free allocated memory
	for(int i = 0; i < size; i++)
	{
		free(arr[i]);
	}

	//free the array
	free(arr);
}

