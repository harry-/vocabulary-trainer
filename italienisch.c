
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <string.h>

int linecount(char filename[]);
int split(char string[], char right[]);

main()
{
	time_t t;
	srand((unsigned) time(&t));

	FILE *fp;

	for (int i = 0; i < 10; ++i)
	{
		int lines;
		int count = 0;  // Line counter 

		lines = linecount("italienisch");
		//printf("lines: %d\n", lines);

		int r = rand() % lines;  // choose a random line
		//printf("random line: %d\n", r);

		fp = fopen("italienisch", "r");	

	    // Check if file exists
	    if (fp == NULL)
	    {
	        printf("Could not open file %s", "italienisch");
	        return -1;
	    }

	    char * line = NULL;
	    size_t len = 0;
	    ssize_t read;

	     // step through the file

	    while ((read = getline(&line, &len, fp)) != -1) 
	    {
	        //printf("Retrieved line of length %zu :\n", read);
	        //printf("%s", line);

	        //printf("line: %d\n", count);

	        if (count == r)
	        {
	        	//printf("\n%s\n", line);

	        	char right[100];

	        	split(line, right);
	        	printf("%s\n", line);

	        	char input[100];
	        	scanf(" %[^\n]", input);
	        	//printf("%s\n", input);

	        	if (strcmp(input, right) == 0)
	        	{
	        		printf("Yes!\n");
	        	}
	        	else
	        	{
	        		printf("%s\n", right);
	        	}
	        }
	        count++;
	    }
	}
	// Close the file
    fclose(fp);
}

int linecount(char filename[100])
{
    FILE *fp;
    int count = 0;  // Line counter (result)
    char c;  // To store a character read from file
 
    fp = fopen(filename, "r");
 
    // Check if file exists
    if (fp == NULL)
    {
        printf("Could not open file %s", filename);
        return -1;
    }
 
    // Extract characters from file and store in character c
    for (c = getc(fp); c != EOF; c = getc(fp))
        if (c == '\n') // Increment count if this character is newline
            count = count + 1;
 
    // Close the file
    fclose(fp);
    //printf("The file %s has %d lines\n ", filename, count);
 
    return count;
}

int split( char left[], char right[] )
{
	int mode = 0;
	int j = 0;
	int length = strlen(left);

	for (int i = 0; i < length; ++i)
	{
		if (left[i] == ';')
		{
			mode = 1;
			left[i] = '\0';
			continue;
		}

		if (mode == 1)
		{
			right[j] = left[i];

			if (left[i] == '\n')
			{
				right[j] = '\0';
			}
			
			j++;
		}

	}
	
}