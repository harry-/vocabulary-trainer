#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>



int main(int argc, char *argv[])
{
 
    char *pointer;
  


    char string [5];

    pointer = string;

    printf("%s\n", string);

    printf("strlen: %d\n", strlen(string));

   for (int i = 0; i <= 4; ++i)
   {
   		
   		printf("\ncharacter%d:%d\n", i, string[i]);

   		char a = 'a';
		int mask = 0x80; /* 10000000 */
		while (mask>0) 
		{
		    printf("%d", (string[i] & mask) > 0 );
		    mask >>= 1; /* move the bit down */
		}

   }



	printf("\n");

	char word[10] = "123456789";
	char *wordpointer;

	wordpointer = word;

	for (int i = 0; i < strlen(word); ++i)
	{
		printf("%s\n", wordpointer);
		wordpointer++;
	}

	printf("%d\n", sizeof(int*) );

	int a = 12;

	int *b = &a;
	a++;

	printf("%d\n", *b);

	int longint = 4399L;

	printf("%d\n", longint);



}


