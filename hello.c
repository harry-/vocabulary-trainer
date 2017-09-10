#include <stdio.h>
 

 
main()
{
  char sentence[100]="mein satz\n";
  printf("ameisen\teichelhäher\ttannenhäher\n");
  printf("birken\ttannen\t\tfcht\en\n");

  float fahrenheit, celsius;
  int lower, upper, step;

  lower=0; /*lower limit of table*/
  upper=300;
  step=20;

  fahrenheit = lower;
  while (fahrenheit<=upper) {
  	celsius = 5*(fahrenheit-32)/9;
  	printf("%3.0f\t%6.2f\n", fahrenheit, celsius);
  	fahrenheit = fahrenheit + step;

  }
  #define STEP 10
  #define LOWER 0
  #define HIGHER 100


  int steppy;
  for (steppy=HIGHER; steppy>=LOWER ; steppy=steppy-STEP)
  {
  	printf("%3d \t %.1f\n", steppy, (5.0/9.0)*(steppy-32));
  }

int c;
  long counter;
  counter=0;

 /* while ((c = getchar()) != EOF)
  {
     if (c == '\n')
     	counter++;
  }
  printf("%ld\n",  counter);*/


 printf("EOF: %d\n", EOF );

 int cc = 'B';
 printf("character value: %d\n", '\a' );

 printf("\a");

 #define IN 1
 #define OUT 0

 int  nl, nw, nc, state;
 state = OUT;
 nl = nw = nc = 0;

 while ((c = getchar()) != EOF)
 {
 	++nc;
 	if (c == '\n')
 		++nl;
 	if (c == ' ' || c == '\n' || c == '\t')
 		state = OUT;
 	else if (state == OUT)
 	{
 		state = IN;
 		++nw;
 	}
 }
  printf("%d %d %d\n", nl, nw, nc);

  char wtflol;
  char wtflol2[10];
  wtflol = 'o';
  wtflol2[0] = 'h';
  printf("%c\n", wtflol);
  printf("%s\n", wtflol2);
}

