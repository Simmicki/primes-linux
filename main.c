// Copyright © 2021-2025 Michael Simonsen
// Programname: primes

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <stdint.h>
#include <time.h>
#include <sys/stat.h> // remember / in linux file system

FILE *savefile;
unsigned long long i = 2;
unsigned long long j;
unsigned long long num1 = 2;
unsigned long long num2 = 0xFFFFFFFFFFFFFFFFU;
//unsigned long long num2 = 200;
unsigned long long flag_var;
struct stat status;

void sigint_handler(int sig_num) /* Signal Handler for SIGINT */
{
	setbuf(stdout, NULL);
	printf("\nInterrupt signal (%d) modtaget.\n",sig_num);
	printf("Nået til: %llu\n",i);
	printf("Gemmer fremgang i prime.ini\n");
	savefile = fopen ("prime.ini","w+");
	fstat(fileno(savefile),&status);
//	printf("File was last modified : %s",ctime(&status.st_mtime));
	fprintf(savefile,"%llu\n",i);
	fclose(savefile);
	printf("Fil gemt, afslutter nu !\n");
	exit(0);
}

int main()
{
   signal(SIGINT, sigint_handler);
	setbuf(stdout, NULL); /* Remove cout buffer */
	savefile=fopen ("prime.ini","r"); /* check if config file exist */
	if (savefile)
	{
		printf("Konfigurationsfil fundet\n");
		fstat(fileno(savefile),&status);
		printf("Filen blev sidst ændret : %s",ctime(&status.st_mtime));
		printf("læser: prime.ini\n");
		fscanf(savefile,"%llu",&i);
		fclose(savefile);
		num1=i;
		printf("fortsætter med: %llu\n\n",num1);
	}
	else
	{ /* create config file */
		printf("Kan ikke finde prime.ini\n");
		printf("opretter den nu\n");
		savefile = fopen ("prime.ini","w");
		fprintf(savefile,"%d\n",2);
		fclose(savefile);
		puts("fil oprettet");
	}

// Calculate and display prime numbers
   printf("Primtal fra %llu:\n", num1);
   for(i=num1+1; i<num2; ++i)
   {
	  flag_var=0;
	  for(j=2; j<=i/2; ++j)
	  {
		 if(i%j==0)
		 {
			flag_var=1;
			break;
		 }
	  }
	  if(flag_var==0)
		 printf("%-24llu",i);
  }
  return 0;
}
