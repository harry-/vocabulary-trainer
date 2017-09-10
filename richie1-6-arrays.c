#include <stdio.h>

main ()
{
	int digits, spaces, idx, character, words;

	digits = spaces =  words = 0;
	int letters[26];
	int wordlength[99];

	for (int idx = 0; idx < 26; ++idx)
	{
		letters[idx] = 0;
	}

	for (int idx = 0; idx < 99; ++idx)
	{
		wordlength[idx] = 0;
	}

	while ((character = getchar()) != EOF)
	{
		if (character >= 'a' && character <= 'z')
		{
			++letters[character - 'a'];
			++wordlength[words];
		}
		else if (character >= '0' && character <= '9')
		{
			++digits;
			++wordlength[words];
		}
		else if (character == ' ')
		{
			++spaces;
			++words;

		}
		else if (character == '\n')
		{
			++words;
		}
	}

	printf("\nBuchstaben:\n");

	for (int i = 0; i < 26; ++i)
	{
		printf("%c ", i+'a');
	}
	printf("\n");
	int most;
	most = 0;

	for (int i = 0; i < 26; ++i)
	{
		printf("%d ", letters[i]);
		if (most < letters[i])
		{
			most = letters[i];
		}
	}
	printf("\n");
	for (int j = 1; j <= most; ++j)
	{	
		for (int i = 0; i < 26; ++i)
		{
			if (letters[i] >= j)
				printf("▓ ");
			else 
				printf("  ");
		}
		printf("\n");
	}

	printf("Wörter\n");
	for (int i = 0; i < words; ++i)
	{
		printf("Wort %d: %d\t", i+1, wordlength[i]);

		for (int j = 0; j < wordlength[i]; ++j)
		{
			printf("▄");
		}
		printf("\n");
	}

	printf("Ziffern: %d\nLeerzeichen: %d\n", digits, spaces);

}