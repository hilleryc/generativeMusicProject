#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
//#include <ext.h>
#include "generatingMusic.h"

//inputs are RGB values

int main(int argc, char ** argv)
{


	if(argc != 3)
	{
		fprintf(stderr, "Need good file name");
		return EXIT_FAILURE;
	}

	FILE * inFile = fopen(argv[1], "r");

	if(inFile == NULL)
	{
		printf("No file\n");
	}
	
	int rot;
	int grun;
	int blau;
	//float freq = 0;	

	RGB * avgValues;
	songChars * song = malloc(sizeof(songChars));
	HSV * HSVvalues;
	ModePoints * points = malloc(sizeof(ModePoints));
	


	while(fscanf(inFile, "%d %d %d", &rot, &grun, &blau) == 3)
	{
		avgValues = buildRGB(rot, grun, blau);
		HSVvalues = convertHSV(avgValues);

		//printf("HSV values: %f %f %f\n", HSVvalues -> hue, HSVvalues -> saturation, HSVvalues -> value);
		
		addPoints(points, HSVvalues);	
		deleteRGB(avgValues);
		free(HSVvalues); 	
	
	}

	/*printf("a points: %d\n", points -> a);
	printf("d points: %d\n", points -> d);
	printf("i points: %d\n", points -> i);
	printf("o points: %d\n", points -> o);
	printf("y points: %d\n", points -> y);
	printf("m points: %d\n", points -> m);
	printf("p points: %d\n", points -> p);
	*/	

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
	
	int random1;
	srand(time(NULL));
	random1 = rand() % 10;
	
	song -> octave = random1;
	
	//freq = findFreq(firstNote, song);
	//HSVvalues = convertHSV(avgValues);

	findScale(points, song);
	scaleNode * beginningScale = buildScale(firstNote, song);	
	

	//For finding the note to use during operation, could use random seed, then seed%12 - 1
	//FOR THE PURPOSES OF TESTING FUNCTIONS/OPERATIONS
	
	/*
	char * printNote1;
	printf("Scale: ");
	scaleNode * copy = beginningScale;
	while(copy != NULL)
	{
		switch(copy -> note)
		{
			case C:  	printNote1 = "C"; break;
			case DB:	printNote1 = "Db"; break;
			case D: 	printNote1 = "D"; break;
			case EB:	printNote1 = "Eb"; break;
			case E:		printNote1 = "E"; break;
			case F:		printNote1 = "F"; break;
			case GB:	printNote1 = "Gb"; break;
			case G:		printNote1 = "G"; break;
			case AB:	printNote1 = "Ab"; break;
			case A:		printNote1 = "A"; break;
			case BB:	printNote1 = "Bb"; break;
			case B:		printNote1 = "B"; break;
		} 
		printf("%s ", printNote1);
		copy = copy -> next;
	}
	printf("\n");
	printf("Song Mode: %c\n", song -> mode);
	printf("Steps: %s\n", song -> steps);

	printf("R Value: %f\nG Value: %f\nB Value: %f\n", avgValues -> red, avgValues -> green, avgValues -> blue);	
	printf("Frequency: %f\n", freq);
	*/
	//FINISHED WITH TESTING

	fclose(inFile);

	FILE * outFile = fopen(argv[2], "w");

	if(outFile == NULL)
	{
		printf("No out file\n");
	}

	scaleNode * scaleCopy = beginningScale;
	char * printNote;
	//printf("Scale: ");
	while(scaleCopy != NULL)
	{
		switch(scaleCopy -> note)
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
		fprintf(outFile, "%s ", printNote);
		scaleCopy = scaleCopy -> next;
	}

	fprintf(outFile, "%f ", song -> pace);
	fprintf(outFile, "%d\n", song -> octave);
	
	fclose(outFile);
	
	scaleNode * afterNode = beginningScale -> next;
	while(afterNode != NULL)
	{
		free(beginningScale);
		beginningScale = afterNode;
		afterNode = afterNode -> next;
	}
	free(beginningScale);
	//deleteRGB(avgValues);
	free(song);
	//free(HSVvalues);
	free(points);

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

ModePoints * addPoints(ModePoints * points, HSV * HSVvalues)
{

	//Placeholder for setting conditions for the RGB values to convert to what scale
	if(HSVvalues -> hue >= 100 && HSVvalues -> hue <= 280)
	{
		if(HSVvalues -> value > HSVvalues -> saturation)
		{
			if(HSVvalues->saturation >= 0 && HSVvalues->saturation < 60)
			{
				points -> d = points -> d + 1;
				points -> y = points -> y + 1;
			}
			else if(HSVvalues->saturation >=60 && HSVvalues->saturation <80) 
			{
				points -> y = points -> y + 1;
				points -> m = points -> m + 1;
			}
			else 
			{
				points -> m = points -> m + 1;
				points -> i = points -> i + 1;
			}
		}
		else 
		{
			if(HSVvalues -> value <= 100 && HSVvalues -> value > 80)
			{
				points -> i = points -> i + 1;
			}
			else if(HSVvalues -> value <= 80 && HSVvalues -> value > 40)
			{
				points -> p = points -> p + 1;
				points -> a = points -> a + 1;
			}
			else if(HSVvalues -> value <= 40 && HSVvalues -> value > 20)
			{
				points -> o = points -> o + 1;
				points -> a = points -> a + 1;
			}
			else 
			{
				points -> o = points -> o + 1;
			}
		}	
	}
	else if(HSVvalues -> hue < 100 || HSVvalues -> hue >= 340)
	{
		if(HSVvalues -> value > HSVvalues -> saturation)
		{
			if(HSVvalues->saturation >= 0 && HSVvalues->saturation < 80)
			{
				points -> y = points -> y + 1;
			}
			else 
			{
				points -> i = points -> i + 1;
			}
		}
		else 
		{
			if(HSVvalues -> value <= 100 && HSVvalues -> value > 80)
			{
				points -> i = points -> i + 1;
			}
			else if(HSVvalues -> value <= 80 && HSVvalues -> value > 40)
			{
				points -> p = points -> p + 1;
				points -> a = points -> a + 1;
			}
			else if(HSVvalues -> value <= 40 && HSVvalues -> value > 20)
			{
				points -> o = points -> o + 1;
				points -> a = points -> a + 1;
			}
			else 
			{
				points -> o = points -> o + 1;
			}
		}
	}
	else 
	{
		if(HSVvalues -> value > HSVvalues -> saturation)
		{
			if(HSVvalues->saturation >= 0 && HSVvalues->saturation < 80)
			{
				points -> y = points -> y + 1;
			}
			else 
			{
				points -> i = points -> i + 1;
			}
		}
		else 
		{
			if(HSVvalues -> value <= 100 && HSVvalues -> value > 80)
			{
				points -> i = points -> i + 1;
			}
			else if(HSVvalues -> value <= 80 && HSVvalues -> value > 40)
			{
				points -> p = points -> p + 1;
				points -> a = points -> a + 1;
			}
			else if(HSVvalues -> value <= 40 && HSVvalues -> value > 20)
			{
				points -> o = points -> o + 1;
				points -> a = points -> a + 1;
			}
			else 
			{
				points -> o = points -> o + 1;
			}
		}
	}

	return points;

}


//Finding what scale will be used based on the RGB characteristics 
void findScale(ModePoints * points, songChars * song)
{
	//put in read file here repeatedly to get new value to place and call this function
	//to add points to each mode then choose which one with the highest
	
	Mode scaleMode = 'a';
	int max = points -> a;
	//int i;	
	
	if(points -> d > max)
	{
		max = points -> d;
		scaleMode = 'd';
	}
	if(points -> i > max)
	{
		max = points -> i;
		scaleMode = 'i';
	}
	if(points -> o > max)
	{
		max = points -> o;
		scaleMode = 'o';
	}
	if(points -> y > max)
	{
		max = points -> y;
		scaleMode = 'y';
	}
	if(points -> m > max)
	{
		max = points -> m;
		scaleMode = 'm';
	}
	if(points -> p > max)
	{
		max = points -> p;
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

	float Rp = (toConvert -> red)/255;
	float Gp = (toConvert -> green)/255;
	float Bp = (toConvert -> blue)/255;
	float Cmax = fmaxf(fmaxf(Rp, Gp), fmaxf(Gp, Bp)); 
	float Cmin = fminf(fminf(Rp, Gp), fminf(Gp, Bp));
	float delta = Cmax - Cmin;

	//printf("green: %f\n", toConvert -> green);
	//printf("Gp: %f\n", Gp);
	//printf("Cmax value: %f\n", Cmax);

	HSV * HSVvalues = malloc(sizeof(HSV)); 

	if(Cmax == Rp)
	{
		HSVvalues -> hue = 60 * fmod(((Gp-Bp)/delta),6);
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
		HSVvalues -> saturation = (delta/Cmax) * 100;
	}

	
	HSVvalues -> value = Cmax * 100;
 
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




