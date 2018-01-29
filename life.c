/* Game of Life
*/

#include <stdio.h>
#include <stdlib.h>
#include "twoD.h"
#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))


/** Computes the length of the longest line in a file
 * @param file The file to read the lines from
 * @return The number of characters in the biggest line
 */
int calcLongestLine(FILE* file) {
	rewind(file);
	char c;
	int maxline = 0;
	int curline = 0;
	while((c = fgetc(file)) != EOF) {
		if (c == '\n') {
			if (curline > maxline) {
				maxline = curline;
			}
			curline = 0;
		}
		if (c != '\n') {
			curline++;
		}
	}
	return maxline;
}

/** Computes how many lines in a text file
 * @param file The file to read the lines from
 * @return The number of lines in the file
 */
int calcNumberLines(FILE* file) {
	rewind(file);
	int nl = 0;
	char c;
	while((c = getc(file)) != EOF) {
		if (c == '\n') {
			nl++;
		}
	}
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
char** centerPattern(int startRows, int startCols, char **start, int rows, int cols) {
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
