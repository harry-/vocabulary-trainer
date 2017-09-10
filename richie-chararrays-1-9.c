#include <stdio.h>
#include <string.h>

int getline(char line[]);
void copy(char to[], char from[]);
void reverse(char in[], char out[]);



int main()
{
	int len, maxlen;

	char line[999];
	char reversed[999];
	char longest[999];

	

	//char line[] = {'h', 'a', 'l', 'l', 'o', '!', '\0'};
	while ((len = getline(line)) > 0)
	{
		if (len > maxlen)
		{
			maxlen = len;
			copy(line, longest);
		}
	}
	printf("%s\n", longest);

	reverse(reversed, longest);
	printf("%s\n", reversed);


}

int getline(char line[])
{
	int c, i;
	i = 0;
	while((c = getchar()) != EOF)
	{
		
		line[i]=c;
		
		if (c == '\n')	
		{
			line[i] = '\0';
			//putchar('\a');
			return i;
		}
		i++;

	}

	line[i]=0;
}

void copy(char from[], char to[])
{
	int i = 0;

	while((to[i] = from[i]) != '\0')
		i++;
}

void reverse(char out[], char in[])
{
   for (int i = 0; i < strlen(in); ++i)
   {
   		out[strlen(in)-i] = in[i];
   }
}