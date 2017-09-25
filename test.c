#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

int split( char left[], char right[] );

int main(int argc, char *argv[])
{
    int intarray[10] = {1,2,3,4,5,6,7,8,9,10};
    int *pointer;
    pointer = intarray;

    printf("%d\n", intarray[10]);

    printf("%d\n", pointer[0]);
    pointer++;
    printf("%d\n", pointer[1]);

    intarray++;
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

			//if ( (left[i] == '\n') || (left[i] == ';') )
			if ( (left[i] == ';') )
			{
				right[j] = '\0';
			}
			
			j++;
		}

	}
	
}