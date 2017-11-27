
#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <string.h>
#include <getopt.h>		

//#define dictionary_filename "italienisch"

/* Flag set by ‘--verbose’. */
static int verbose_flag;

static char *dictionary_filename = "italienisch";
static char *score_filename = "italienisch.score";

int linecount(const char filename[]);
int split(char string[], char right[]);
int createProbabilityTable(int input[][2], int output[], int lines);
int findMostSeldom(int input[][2], int lines);
int inspectString(char *charp);

main (int argc, char *argv[])
{
	time_t t;
	srand((unsigned) time(&t));

	int correct = 0; // keeping score of the current session
	int wrong = 0;

	int questions = 5;

	int c;

  	while (1)
    {
      	static struct option long_options[] =
        {
        	/* These options set a flag. */
          	{"verbose", no_argument,       &verbose_flag, 1},
          	/* These options don’t set a flag.
             We distinguish them by their indices. */
          	{"questions",  required_argument, 0, 'q'},
          	{"data",    required_argument, 0, 'd'},
          	{0, 0, 0, 0}
        };


	    /* getopt_long stores the option index here. */
    	int option_index = 0;

      	c = getopt_long (argc, argv, "abc:d:f:",
                       long_options, &option_index);

      /* Detect the end of the options. */
      if (c == -1)
        break;

      switch (c)
        {
        case 0:
          /* If this option set a flag, do nothing else now. */
          if (long_options[option_index].flag != 0)
            break;
          fprintf (stderr, "option %s", long_options[option_index].name);
          if (optarg)
            fprintf (stderr, " with arg %s", optarg);
          printf ("\n");
          break;

        case 'q':
          fprintf (stderr, "option -q with value `%s'\n", optarg);
          questions = atoi(optarg);
          break;

        case 'd':
          fprintf (stderr, "option -d with value `%s'\n", optarg);
          dictionary_filename = optarg;
          score_filename = optarg;
          strcat(score_filename, ".score");
          break;

        case '?':
          /* getopt_long already printed an error message. */
          break;

        default:
          abort ();
        }
    }

	char * line = NULL;
	size_t len = 0;
	ssize_t read;

	FILE *fp;

	FILE *score = fopen(score_filename, "ab+");

	if (verbose_flag != 1)
	{
		freopen("/dev/null", "w", stderr);
	}

	if (score == NULL)
	{
	    printf("Could not open file %s", "score");
	    return -1;
	}


	int lines = linecount(dictionary_filename);

	int scorelines = linecount(score_filename);
	int scoresheet[lines+1][2] = {0};


	if (scorelines<1)
	{
		scoresheet[0][0]=1;
		scoresheet[0][1]=1;
		scoresheet[1][0]=1;
		scoresheet[1][1]=1;
	}

	int idx = 0;
	while ((read = getline(&line, &len, score)) != -1) 
	{
		char right[30];
		split(line, right);
		scoresheet[idx][0] = atoi(line);
		scoresheet[idx][1] = atoi(right);
		idx++;
	}

	int probTable[999];

	int probability = createProbabilityTable(scoresheet, probTable, lines);

	printf("\n");

	for (int i = 0; i < questions; ++i)
	{
		int count = 0;  // Line counter 

		int r = rand() % probability;  // choose a random line (weight)
		fprintf(stderr, "random number (out of %d): %d\n", probability,r);

		fp = fopen(dictionary_filename, "r");	

	    // Check if file exists
	    if (fp == NULL)
	    {
	        printf("Could not open file %s", dictionary_filename);
	        return -1;
	    }

	    /* 	next we determine in which line's weight range r is to be found
	    	the line is then stored in r instead of the weight, which probably sucks */

	    int runup = 0;
	    for (int j = 0; j < lines; ++j)
	    {
	    	runup += probTable[j];
	    	//fprintf(stderr, "the threshold for line %d is %d\n", j, runup );
	    	if (runup>r)
	    	{
	    		fprintf(stderr, "the weight of line %d is %d\n", j, probTable[j]);
	    		r = j;
	    		break;
	    	}
	    }



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
	        		printf("corretto!\n");
	        		scoresheet[r][0]++;
	        		correct++;
	        	}
	        	else
	        	{
	        		printf("%s\n", right);
	        		scoresheet[r][1]++;
	        		wrong++;
	        	}
	        	printf("\n");
	        }
	        count++;
	    }
	}

	printf("\n%d/%d\n", correct, questions);

	// Close the files
    fclose(fp);

    score = freopen(score_filename, "w+", score);
    for (int i = 0; i < lines; ++i)
    {
    	fprintf(score, "%d;%d\n", scoresheet[i][0], scoresheet[i][1]);
    }
    fclose(score);
}

int linecount(const char filename[])
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
    fprintf(stderr, "The file %s has %d lines\n ", filename, count);
 
    return count+1;
}

int split( char left[], char right[] )
{
	int mode = 0;
	int j = 0;
	int length = strlen(left);

	for (int i = 0; i < length; ++i)
	{
		if (mode == 0)
		{
		 	if (left[i] == ';')
			{
				mode = 1;
				left[i] = '\0';
				continue;
			}
		} 

		if (mode == 1)
		{
			right[j] = left[i];

			if ( (left[i] == '\n') || (left[i] == ';') )
			{
				right[j] = '\0';
			}
			
			j++;
		}

	}
	
}

int createProbabilityTable(int scoresheet[][2], int output[], int lines)
{
	int record = findMostSeldom(scoresheet, lines);
	int totalProbability = 0; 
	fprintf(stderr,"the best score is: %d\n", record);

	fprintf(stderr, "Probability Table:\n");

	for (int i = 0; i < lines; ++i)
	{
		int probability = 0;
		int score = scoresheet[i][0]-scoresheet[i][1];

		if(score == 0)
		{
			probability = record;
		}
		else if (score > 0)
		{
			probability = record/score;
		}
		else if (score <0)
		{
		    probability = record - score;
		}

		output[i] = probability;
		totalProbability = totalProbability + probability;
		fprintf(stderr, "%d %d %d\n", i, probability, totalProbability);
	
	}
	fprintf(stderr, "total probability:%d\n", totalProbability );
	if(totalProbability == 0)
		totalProbability = 1;
	return totalProbability;
}

int findMostSeldom(int input[][2], int lines)
{
	int result = -1; 	//the line number of the question that was answered correctly most often
	int record = -9999; //the score (right-wrong) of the "best" line
	for (int i = 0; i < lines; ++i)
	{
		if(input[i][0]-input[i][1] > record)
		{
			result = i;
			record = input[i][0]-input[i][1];
		}
	}
	return record;
}

int inspectString(char *charp)
{
	char stringArray[999];
	strcpy(stringArray, charp);
	for (int i = 0; i < strlen(stringArray); ++i)
	{
		if (i == strlen(stringArray)-1)
		{
			printf("%c %d\n", stringArray[i], stringArray[i]);
		}
		else
		{
			printf("%c %d, ", stringArray[i], stringArray[i]);

		}
	
	}
	printf("\n");
}