#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char ** argv)
{



	char * firstNote = argv[1];
	char * secNote = argv[2];
	char * thirdNote = argv[3];
	char * fourthNote = argv[4];
	char * fifthNote = argv[5];
	char * sixthNote = argv[6];
	char * seventhNote = argv[7];

	int octave = (int) strtol(argv[8], NULL, 10);
	char * note;

	int random;
	srand(time(NULL));
	random = rand() % 7;
	
	switch(random)
	{
		case 0:		note = firstNote; break;
		case 1:		note = secNote;   break;
		case 2:		note = thirdNote; break;
		case 3:		note = fourthNote;break;
		case 4:		note = fifthNote; break;
		case 5: 	note = sixthNote; break;
		case 6:		note = seventhNote;break;
	}	
	





	float freq;

	
	//Might to also have an input be a chosen octave that tells what octave band the note should be calculated for
	//Finding base frequency

	

	char * C = "C";
	char * DB = "DB";
	char * D = "D";
	char * EB = "EB";
	char * E = "E";
	char * F = "F";
	char * GB = "GB";
	char * G = "G";
	char * AB = "AB";
	char * A = "A";
	char * BB = "BB";
	//char *  B = "B";


	if(strcmp(note, C) == 0)
	{
		freq = 16.35;
	}
	else if(strcmp(note, DB) == 0)
	{
		freq = 17.32;
	}
	else if(strcmp(note, D) == 0)
	{
		freq = 18.35;
	}
	else if(strcmp(note, EB) == 0)
	{
		freq = 19.45;
	}
	else if(strcmp(note, E) == 0)
	{
		freq = 20.60;
	}
	else if(strcmp(note, F) == 0)
	{
		freq = 21.83;
	}
	else if(strcmp(note, GB) == 0)
	{
		freq = 23.12;
	}
	else if(strcmp(note, G) == 0)
	{
		freq = 24.50;
	}
	else if(strcmp(note, AB) == 0)
	{
		freq = 25.96;
	}
	else if(strcmp(note, A) == 0)
	{
		freq = 27.50;
	}
	else if(strcmp(note, BB) == 0)
	{
		freq = 29.14;
	}
	else
	{
		freq = 30.87;
	}
	
	
	/*switch(note)
	{
		case "C":  	freq = 16.35; break;
		case "DB":	freq = 17.32; break;
		case D: 	freq = 18.35; break;
		case EB:	freq = 19.45; break;
		case E:		freq = 20.60; break;
		case F:		freq = 21.83; break;
		case GB:	freq = 23.12; break;
		case G:		freq = 24.50; break;
		case AB:	freq = 25.96; break;
		case A:		freq = 27.50; break;
		case BB:	freq = 29.14; break;
		case B:		freq = 30.87; break;
	}*/	

	//int random;
	//srand(time(NULL));
	//random = rand() % 10;
	
	//song -> octave = random;

	if(octave)
	{
		switch(octave)
		{
			case 0:	freq = freq;		break;
			case 1:	freq = freq * 2;	break;
			case 3: freq = freq * 3;	break;
			case 4: freq = freq * 4;	break;
			case 5: freq = freq * 5; 	break;
			case 6: freq = freq * 6; 	break;
			case 7: freq = freq * 7; 	break;
			case 8: freq = freq * 8;	break;
			case 9: freq = freq * 9;	break;
		}
	}
	else
	{
	}

	printf("Frequency: %f\n", freq);

	return EXIT_SUCCESS;
	
}

