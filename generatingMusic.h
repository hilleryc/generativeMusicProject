#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//define

 


//structs


typedef enum Note {

	C = 0,
	DB = 1,
	D = 2,
	EB = 3,
	E = 4,
	F = 5,
	GB = 6,
	G = 7,
	AB = 8,
	A = 9,
	BB = 10,
	B = 11

} Note;

typedef enum Mode { 

	AEOLIAN = 'a',
	DORIAN = 'd',
	IONIAN = 'i',
	LOCRIAN = 'o',
	LYDIAN = 'y',
	MIXOLYDIAN = 'm',
	PHRYGIAN = 'p'

} Mode;

typedef struct ModePoints {
	
	int a;
	int d;
	int i;
	int o;
	int y;
	int m;
	int p;

} ModePoints;

typedef struct scaleNode {

	Note note;
	struct scaleNode * next;

} scaleNode;

typedef struct songChars{

	Mode mode;
	char * steps;	
	float pace;
	int octave;

} songChars;

typedef struct RGB{

	int red;
	int green;
	int blue;

} RGB;

typedef struct HSV{

	int hue;
	int saturation;
	int value;

} HSV;

//functions
HSV * convertHSV(RGB * toConvert);

float findFreq(Note note, songChars * song);

RGB * buildRGB(int R, int G, int B);

void deleteRGB(RGB * todelete);

scaleNode * buildNode(Note note);

scaleNode * buildScale(Note firstNote, songChars * song);

void findScale(ModePoints * points, songChars * song);

ModePoints * addPoints(ModePoints * points, HSV * HSVvalues);
