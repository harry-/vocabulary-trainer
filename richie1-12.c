#include <stdio.h>
 
main()
{
	int character;
	while ((character = getchar()) != EOF)
	{
		if (character == ' ')
			character = '\n';
		
		putchar(character);
	}
}
