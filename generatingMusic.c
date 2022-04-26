#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "generatingMusic.h"

//inputs are RGB values

int main(char * name)
{

	FILE * inFile = fopen(name, "r");

	/*if(argc != 4)
	{
		fprintf(stderr, "Need three numbers");
		return EXIT_FAILURE;
	}*/

	int rot;
	int grun;
	int blau;
	float freq = 0;	

	RGB * avgValues;
	songChars * song = malloc(sizeof(songChars));
	HSV * HSVvalues = malloc(sizeof(HSV));
	points * ModePoints = malloc(sizeof(points));
	
	//rot = (int) strtol(argv[1], NULL, 10);
	//grun = (int) strtol(argv[2], NULL, 10);
	//blau = (int) strtol(argv[3], NULL, 10);


	while(fscanf(inFile, "%d %d %d", &rot, &grun, &blau) == 3)
	{
		avgValues = buildRGB(rot, grun, blau);
		HSVvalues = convertHSV(avgValues);

		addPoints(ModePoints, HSVvalues);	 	
	
	}

	int random;
	Note firstNote;
	srand(time(NULL));
	random = rand() % 12;
	
	switch(random)
	{
		case 0:  	firstNote = A; break;
		case 1:		firstNote = BB; break;
		case 2: 	firstNote = B; break;
		case 3:		firstNote = C; break;
		case 4:		firstNote = DB; break;
		case 5:		firstNote = D; break;
		case 6:		firstNote = EB; break;
		case 7:		firstNote = E; break;
		case 8:		firstNote = F; break;
		case 9:		firstNote = GB; break;
		case 10:	firstNote = G; break;
		case 11:	firstNote = AB; break;
	}
	
	//freq = findFreq(firstNote, song);

	//HSVvalues = convertHSV(avgValues);

	findScale(ModePoints, song);
	
	scaleNode * beginningScale = buildScale(firstNote, song);	
	


	//For finding the note to use during operation, could use random seed, then seed%12 - 1
	//FOR THE PURPOSES OF TESTING FUNCTIONS/OPERATIONS
	/*
	char * printNote;
	printf("Scale: ");
	while(beginningScale != NULL)
	{
		switch(beginningScale -> note)
		{
			case C:  	printNote = "C"; break;
			case DB:	printNote = "Db"; break;
			case D: 	printNote = "D"; break;
			case EB:	printNote = "Eb"; break;
			case E:		printNote = "E"; break;
			case F:		printNote = "F"; break;
			case GB:	printNote = "Gb"; break;
			case G:		printNote = "G"; break;
			case AB:	printNote = "Ab"; break;
			case A:		printNote = "A"; break;
			case BB:	printNote = "Bb"; break;
			case B:		printNote = "B"; break;
		} 
		printf("%s,", printNote);
		beginningScale = beginningScale -> next;
	}
	printf("\n");

	printf("Song Mode: %c\n", song -> mode);
	printf("Steps: %s\n", song -> steps);

	printf("R Value: %d\nG Value: %d\nB Value: %d\n", avgValues -> red, avgValues -> green, avgValues -> blue);	
	printf("Frequency: %f\n", freq);
	*/
	//FINISHED WITH TESTING
	fclose(inFile);
	deleteRGB(avgValues);
	free(song);
	free(HSVvalues);
	free(ModePoints);

	return EXIT_SUCCESS;
}
 



//Finding note frequency from note

float findFreq(Note note, songChars * song)
{
	int freq;

	
	//Might to also have an input be a chosen octave that tells what octave band the note should be calculated for
	//Finding base frequency
	
	switch(note)
	{
		case C:  	freq = 16.35; break;
		case DB:	freq = 17.32; break;
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
	}	

	int random;
	srand(time(NULL));
	random = rand() % 10;
	
	song -> octave = random;

	if(song != NULL)
	{
		switch(song -> octave)
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
	


	return freq;
}

points * addPoints(points * ModePoints, HSV * HSVvalues)
{

	//Placeholder for setting conditions for the RGB values to convert to what scale
	if(HSVvalues -> hue >= 100 && HSVvalues -> hue <= 280)
	{
		if(HSVvalues -> value > HSVvalues -> saturation)
		{
			if(HSVvalues->saturation >= 0 && HSVvalues->saturation < 60)
			{
				ModePoints -> d = ModePoints -> d + 1;
				ModePoints -> y = ModePoints -> y + 1;
			}
			else if(HSVvalues->saturation >=60 && HSVvalues->saturation <80) 
			{
				ModePoints -> y = ModePoints -> y + 1;
				ModePoints -> m = ModePoints -> m + 1;
			}
			else 
			{
				ModePoints -> m = ModePoints -> m + 1;
				ModePoints -> i = ModePoints -> i + 1;
			}
		}
		else 
		{
			if(HSVvalues -> value <= 100 && HSVvalues -> value > 80)
			{
				ModePoints -> i = ModePoints -> i + 1;
			}
			else if(HSVvalues -> value <= 80 && HSVvalues -> value > 40)
			{
				ModePoints -> p = ModePoints -> p + 1;
				ModePoints -> a = ModePoints -> a + 1;
			}
			else if(HSVvalues -> value <= 40 && HSVvalues -> value > 20)
			{
				ModePoints -> o = ModePoints -> o + 1;
				ModePoints -> a = ModePoints -> a + 1;
			}
			else 
			{
				ModePoints -> o = ModePoints -> o + 1;
			}
		}	
	}
	else if(HSVvalues -> hue < 100 || HSVvalues -> hue >= 340)
	{
		if(HSVvalues -> value > HSVvalues -> saturation)
		{
			if(HSVvalues->saturation >= 0 && HSVvalues->saturation < 80)
			{
				ModePoints -> y = ModePoints -> y + 1;
			}
			else 
			{
				ModePoints -> i = ModePoints -> i + 1;
			}
		}
		else 
		{
			if(HSVvalues -> value <= 100 && HSVvalues -> value > 80)
			{
				ModePoints -> i = ModePoints -> i + 1;
			}
			else if(HSVvalues -> value <= 80 && HSVvalues -> value > 40)
			{
				ModePoints -> p = ModePoints -> p + 1;
				ModePoints -> a = ModePoints -> a + 1;
			}
			else if(HSVvalues -> value <= 40 && HSVvalues -> value > 20)
			{
				ModePoints -> o = ModePoints -> o + 1;
				ModePoints -> a = ModePoints -> a + 1;
			}
			else 
			{
				ModePoints -> o = ModePoints -> o + 1;
			}
		}
	}
	else 
	{
		if(HSVvalues -> value > HSVvalues -> saturation)
		{
			if(HSVvalues->saturation >= 0 && HSVvalues->saturation < 80)
			{
				ModePoints -> y = ModePoints -> y + 1;
			}
			else 
			{
				ModePoints -> i = ModePoints -> i + 1;
			}
		}
		else 
		{
			if(HSVvalues -> value <= 100 && HSVvalues -> value > 80)
			{
				ModePoints -> i = ModePoints -> i + 1;
			}
			else if(HSVvalues -> value <= 80 && HSVvalues -> value > 40)
			{
				ModePoints -> p = ModePoints -> p + 1;
				ModePoints -> a = ModePoints -> a + 1;
			}
			else if(HSVvalues -> value <= 40 && HSVvalues -> value > 20)
			{
				ModePoints -> o = ModePoints -> o + 1;
				ModePoints -> a = ModePoints -> a + 1;
			}
			else 
			{
				ModePoints -> o = ModePoints -> o + 1;
			}
		}
	}

	return ModePoints;

}


//Finding what scale will be used based on the RGB characteristics 
void findScale(points * ModePoints, songChars * song)
{
	//put in read file here repeatedly to get new value to place and call this function
	//to add points to each mode then choose which one with the highest
	
	Mode scaleMode = 'a';
	int max = ModePoints -> a;
	int i;	
	
	if(ModePoints -> d > max)
	{
		max = ModePoints -> d;
		scaleMode = 'd';
	}
	if(ModePoints -> i > max)
	{
		max = ModePoints -> i;
		scaleMode = 'i';
	}
	if(ModePoints -> o > max)
	{
		max = ModePoints -> o;
		scaleMode = 'o';
	}
	if(ModePoints -> y > max)
	{
		max = ModePoints -> y;
		scaleMode = 'y';
	}
	if(ModePoints -> m > max)
	{
		max = ModePoints -> m;
		scaleMode = 'm';
	}
	if(ModePoints -> p > max)
	{
		max = ModePoints -> p;
		scaleMode = 'p';
	}

	song -> mode = scaleMode;

	switch(song -> mode)
	{
		case AEOLIAN: 		song -> steps = "WHWWHW";
					song -> pace = 77;
					break;
		case DORIAN: 		song -> steps = "WHWWWH";
					song -> pace = 70;
					break;
		case IONIAN: 		song -> steps = "WWHWWW";
					song -> pace = 80;	
					break;
		case LOCRIAN: 		song -> steps = "HWWHWW";
					song -> pace = 100;
					break;
		case LYDIAN: 		song -> steps = "WWWHWW";
					song -> pace = 130;
					break;
		case MIXOLYDIAN: 	song -> steps = "WWHWWH";
					song -> pace = 140;
					break;
		case PHRYGIAN: 		song -> steps = "HWWWHW";
					song -> pace = 120;
					break;
	}

	return;
}


//Building the scale of notes from the mode that was found
scaleNode * buildScale(Note firstNote, songChars * song)
{
	scaleNode * beginning;
	int i;
	int j = 0;
	Note nextNote = firstNote;
	scaleNode * nextNode;	
	scaleNode * cycleNode;

	beginning = buildNode(firstNote);
	cycleNode = beginning;

	for(i = 0; i < 6; i++)
	{

		if((song -> steps)[j] == 'W')
		{
			nextNote = nextNote + 2;
		}
		else
		{
			nextNote = nextNote + 1;
		}
	
		if(nextNote == 12)
		{
			nextNote = 0;
		}
		else if(nextNote == 13)
		{
			nextNote = 1;
		}
	
		j = j + 1;			
		nextNode = buildNode(nextNote);	
		cycleNode -> next = nextNode;
		cycleNode = nextNode;  	
	}
		
	return beginning;
}

//Building node for the scale that is built
scaleNode * buildNode(Note note)
{

	scaleNode * newNode;
	newNode = malloc(sizeof(scaleNode));
	newNode -> next = NULL;

	newNode -> note = note;

	return newNode;
}

//converting RGB value to HSV
HSV * convertHSV(RGB * toConvert)
{

	float Rp = toConvert -> red / 255;
	float Gp = toConvert -> green / 255;
	float Bp = toConvert -> blue / 255;
	float Cmax = max(max(Rp, Gp), max(Gp, Bp)); 
	float Cmin = min(min(Rp, Gp), min(Gp, Bp));
	float delta = Cmax - Cmin;


	HSV * HSVvalues = malloc(sizeof(HSV)); 

	if(Cmax == Rp)
	{
		HSVvalues -> hue = 60 * ((Gp-Bp)/delta)*mod(6);
	}
	else if(Cmax == Gp)
	{
		HSVvalues -> hue = 60 * (((Bp - Rp)/delta) + 2);
	}
	else if(Cmax == Bp)
	{
		HSVvalues -> hue = 60 * (((Rp - Gp)/delta) + 4);
	}
	else if(delta == 0)
	{
		HSVvalues -> hue = 0;
	}

	if(Cmax == 0)
	{
		HSVvalues -> saturation = 0; 
	}
	else 
	{
		HSVvalues -> saturation = delta/Cmax;
	}

	
	HSVvalues -> value = Cmax;

	return HSVvalues;
}
//setting values for the RGB struct to easily store those values
RGB * buildRGB(int rot, int grun, int blau)
{
	RGB * values = malloc(sizeof(RGB));
	
	values -> red = rot;
	values -> green = grun;
	values -> blue = blau;

	return values;
}

//deleting the RGB structs
void deleteRGB(RGB * todelete)
{
	
	if(todelete == NULL)
	{
		return;
	}

	free(todelete);

	return;
}




