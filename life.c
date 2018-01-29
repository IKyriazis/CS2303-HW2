/* Game of Life
*/

#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"


/** Computes the length of the longest line in a file
 * @param file The file to read the lines from
 * @return The number of characters in the biggest line
 */
int calcLongestLine(FILE* file) {
	rewind(file); // start the file from the beginning to avoid errors
	char c; // allocate a variable to store the current character from the file
	int maxline = 0; // start the biggest line counter from 0 since
					 // we haven't read any lines yet

	int curline = 0; // startthe current line counter from 0 since
					 // we haven't read any lines yet

	// Pre-condition:
	// c has no proper value since the file has not been read
	while((c = fgetc(file)) != EOF) {
		// Invariant 1:
		// C will always be the next character in the file until
		// the EOF is signalled
		if (c == '\n') {
			// If there is a next line character that means that
			// there is a new line. When there is a new line,
			// check to see if the current line is greater than the
			// current longest line
			if (curline > maxline) {
				// if it is then replace the current maximum line with
				// the line we just read
				maxline = curline;
			}
			// reset the current line to length of 0 since we are just
			// starting a new line
			curline = 0;
		}
		// if the current character is not a new line character, then
		// it must be on the same line as the other characters
		if (c != '\n') {
			// increment the length of the current line because
			// we haven't moved onto the next line
			curline++;
		}
	}
	// Post-condition:
	// the entire file has been read because c == EOF

	// return the longest line that this function has read
	return maxline;
}

/** Computes how many lines in a text file
 * @param file The file to read the lines from
 * @return The number of lines in the file
 */
int calcNumberLines(FILE* file) {
	rewind(file); // start the file from the beginning to avoid errors
	int nl = 0; // initialize the new line counter with 0 because we
				// haven't gone through the file yet

	char c; // create a character value to store the current character
	        // value in
	// Pre-condition:
	// c has no proper value because the loop hasn't started yet
	while((c = getc(file)) != EOF) {
		// Invariant 2:
		// C will always be the next character in the file until
		// the EOF is signaled

		// if the current character is a new line then...
		if (c == '\n') {
			// ...increment the number of lines variable to correctly count
			// the number of lines
			nl++;
		}
	}
	// Post-condition:
	// c has a value equivalent to EOF since the file signaled end of file

	// return nl back to the user since that is how many lines this function read
	return nl;
}

/** Turns the given file into an array
 * @param file The file to read from
 * @return The pointer to a 2D array that represents the given file
 */

char** fileToArray(FILE* file) {
	int rows, cols, i, j;
	char c;
	cols = calcLongestLine(file);
	rows = calcNumberLines(file);
	char **start = make2Dchar(rows, cols);
	if (!start) {
		printf("Unable to allocate start array");
	}
	rewind(file);
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if ((c = fgetc(file)) != EOF) {
				if (c == 'x') {
					start[i][j] = 'x';
				}
				else if (c == 'o'){
					start[i][j] = ' ';
				}
				else if (c == '\n' && j == 0) {
					j--;
				}
				else {
					while (j < cols) {
						start[i][j] = ' ';
						j++;
					}
				}
			}
		}
	}
	return start;
}


/**
 * Overlays the starting pattern onto the user-defined grid
 * @param startRows The amount of rows in the starting pattern
 * @param startCols The amount of columns in the starting pattern
 * @param start The array that we want to overlay
 * @param rows The amount of rows
 * @param cols The amount of columns
 * @return An array with rows rows and cols columns, with start in the center
 */
char** centerPattern(unsigned int startRows, unsigned int startCols,
						char **start, unsigned int rows, unsigned int cols) {
	int i, j;
	char **centered = make2Dchar(rows, cols);
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			centered[i][j] = ' ';
		}
	}
	for (i = 0; i < startRows; i++) {
		for (j = 0; j < startCols; j++) {
			centered[((rows / 2) - (startRows / 2)) + i][((cols  / 2) -  (startCols / 2)) + j] = start[i][j];
		}
	}
	return centered;
}

/**
 * Plays a single generation of the Game of Life
 * @param x The amount of rows in the grid
 * @param y The amount of columns in the grid
 * @param Old The generation to read from
 * @param New The generation to write to
 */
void playOne(unsigned int x, unsigned int y, char **old, char **new) {

}



/** Main function.
 * @param argc Number of words on the command line.
 * @param argv Array of pointers to character strings containing the
 *    words on the command line.
 * @return 0 if success, 1 if invalid command line or unable to open file.
 *
 */
int main(int argc, char **argv) {
	printf("Game of Life\n");

	char *inputFileName; // Name of file containing initial grid
	FILE *input; // Stream descriptor for file containing initial grid
	int rows; // Number of rows in the grid
	int cols; // Number of columns in the grid
	int gens; // Number of generations to produce
	int doPrint; // 1 if user wants to print each generation, 0 if not
	int doPause; // 1 if user wants to pause after each generation, 0 if not
	char **gridA; // A 2D array to hold the pattern

	// See if there are the right number of arguments on the command line
	if ((argc < 5) || (argc > 7)) {
		// If not, tell the user what to enter.
		printf("Usage:\n");
		printf("  ./life rows columns generations inputFile [print] [pause]\n");
		return EXIT_FAILURE;
	}

	/* Save the command-line arguments.
	   Also need to check if print and/or pause arguments were entered,
	   and if so, what they were.
	   A switch statement might be handy here.
	*/
	rows = atoi(argv[1]); // Convert from character string to integer.
	cols = atoi(argv[2]);
	gens = atoi(argv[3]);
	inputFileName = argv[4];
	/*
	switch (argc) {
		int i;
		case 5:
			for (i = 0; i < gens; i++) {
				playOne();
			}
		case 7:
			if (argv[5] == 'y' && argv[6] == 'y') {
				for (i = 0; i < gens; i++) {
					printCurrentGen();
					playOne();
					getchar();
				}
			}
			else if (argv[5] == 'y' && argv[6] == 'n'){
				for (i = 0; i < gens; i++) {
					printCurrentGen();
					playOne();
				}
			}
			else if (argv[5] == 'n' && argv[6] == 'y') {
				for (i = 0; i < gens; i++) {
					playOne();
					getchar();
				}
			}
			else {
				for (i = 0; i < gens; i++) {
					playOne();
				}
			}

	}
	*/

	/* Here is how you would allocate an array to hold the grid.
	*/
	gridA = make2Dchar(rows, cols);
	//check that it succeeded.
	if (!gridA) {
		printf("Unable to allocate array");
	}


	/* Eventually, need to try to open the input file.
	*/
	input = fopen(inputFileName, "r");
	if (!input) {
		printf("Unable to open input file: %s\n", inputFileName);
		return EXIT_FAILURE;
	}
	char **start = fileToArray(input);
	int startRows, startCols;
	startRows = calcNumberLines(input);
	startCols = calcLongestLine(input);
	gridA = centerPattern(startRows, startCols, start, rows, cols);



	/*Once opened, you can read from the file one character at a time with fgetc().
	 * You can read one line at a time using fgets().
	 * You can read from standard input (the keyboard) with getchar().
	*/

	return EXIT_SUCCESS;
}
