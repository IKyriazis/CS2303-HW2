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
	int rows, // will hold the amount of rows equivalent to the number
			  // of lines in the file

		cols, // holds the amount of columns - equivalent to the max characters
		      // in a line

		   i, // x coordinate counter variable for traversing 2d array
		   j; // y coordinate counter variable for traversing 2d array

	char c; // holds the current character for file reading
	cols = calcLongestLine(file); // stores the longest line of the file
								  // so we know how many columns the array
								  // should have

	rows = calcNumberLines(file); // stores the amount of lines in the file
								  // so we know how many rows we should have

	char **start = make2Dchar(rows, cols); // allocate memory for a 2d array
										   // cols wide and rows tall

	// if we get a null pointer, print a message to the user
	if (!start) {
		printf("Unable to allocate start array");
	}
	rewind(file); // make sure we start from the beginning of the file

	// Pre-condition:
	// The file hasn't been read or parsed
	for (i = 0; i < rows; i++) {
		// Invariant 3:
		// i+1 is equal to the amount of lines read
		for (j = 0; j < cols; j++) {
			// Invariant 4:
			// j+1 is equal to the amount of characters read on the ith line

			// if the character is not the EOF signal then it must be
			// something we can parse
			if ((c = fgetc(file)) != EOF) {
				// if the character is an 'x' then put that in the array
				if (c == 'x') {
					start[i][j] = 'x';
				}
				// otherwise, if its an 'o' put that in the array as a blank
				else if (c == 'o'){
					start[i][j] = ' ';
				}
				// otherwise, if its a new line character and we're in the
				// 0th column, then go back a column because we don't want
				// the new line in our array
				else if (c == '\n' && j == 0) {
					j--;
				}
				// otherwise, if it's a new line character and we're halfway
				// through a column fill in the rest of the row with blanks
				else {
					// Pre-condition:
					// j is less than the amount of total columns left in
					// the row
					while (j < cols) {
						// Invariant 5:
						// cols - j is always equal to the amount of columns
						// that are filled up in this ith row
						start[i][j] = ' ';
						j++; // since we have filled in this column, go to the next one
					}
					// Post-condition:
					// j is equal to the amount of columns in the row
				}
			}
		}
	}
	// Post-condition:
	// the file has been read and parsed up to the EOF signal

	// return the parsed file as a pointer to an array
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

	int i, j; // create x and y coordinates for traversing the 2d array

	char **centered = make2Dchar(rows, cols); // allocate memory for a 2d array
											  // that will eventually be the
											  // the 'start' array but bigger
											  // and centered
	// Pre-condition:
	// every single row in the allocated array has garbage values
	for (i = 0; i < rows; i++) {
		// Invariant 6:
		// i+1 is equal to the number of rows we have overwritten

		// Pre-condition:
		// every column in the allocated array has garbage values
		for (j = 0; j < cols; j++) {
			// Invariant 7:
			// j+1 is equal to the number of columns we have overwritten
			// in the ith row
			centered[i][j] = ' '; // overwrite the array with blanks
		}
		// Post-condition:
		// All of the columns in the ith row have been overwritten with blanks
	}
	// Post-condition:
	// All of the rows have been overwritten with blanks

	// Pre-condition:
	// the rows of the array we want to center haven't been centered yet
	for (i = 0; i < startRows; i++) {
		//Invariant 8:
		// i+1 is equal to the amount of rows we've centered

		// Pre-condition:
		// the columns of the array we want centered haven't been centered yet
		for (j = 0; j < startCols; j++) {
			// Invariant 9:
			// j+1 is equal to the amount of columns we've centered in the ith row

			// the center row starts at the amount of start rows subtracted
			// from the amount of total rows all divided by 2
			centered[((rows - startRows) / 2) + i]
					// the center column starts at the amount of start columns
					// subtracted from the amount of total columns all divided by 2
					[((cols - startCols) / 2) + j] = start[i][j];
		}
		// Post-condition:
		// all columns of the ith row have been made to scale to the smaller array
	}
	// Post-condition:
	// All rows are now scaled to the smaller array. The starting pattern
	// is now centered.

	// return a pointer to the centered array
	return centered;
}

/**
 * Calculates the number of occupied cells in neighboring cells
 * @param x The x coordinate of the cell we want to check
 * @param y the y coordinate of the cell we want to check
 * @param rows the amount of rows in the grid
 * @param cols the amount of columns in the grid
 * @param arr the 2d array that the cell is in
 *
 * https://stackoverflow.com/questions/652106/finding-neighbours-in-a-two-dimensional-array
 */
unsigned int getNeighbors(unsigned int x, unsigned int y,
						  char **arr, unsigned int rows, unsigned int cols) {
	unsigned int neighbors;
	char **buff = make2Dchar(rows + 2, cols + 2);
	buff = centerPattern(rows, cols, arr, rows + 2, cols + 2);
	if (!buff) {
		printf("failed to allocate array buff");
	}

	neighbors = buff[(x+1)-1][(y+1)-1] +
				buff[(x+1)-1][(y+1)] +
				buff[(x+1)-1][(y+1)+1] +

				buff[(x+1)][(y+1)-1] +
				buff[(x+1)][(y+1)+1] +

				buff[(x+1)+1][(y+1)-1] +
				buff[(x+1)+1][(y+1)] +
				buff[(x+1)+1][(y+1)+1];

	return neighbors;

	free(buff);
}

/**
 * Plays a single generation of the Game of Life
 * @param rows The amount of rows in the grid
 * @param cols The amount of columns in the grid
 * @param Old The generation to read from
 * @param New The generation to write to
 */
void playOne(unsigned int rows, unsigned int cols, char **old, char **new) {
	unsigned int i, j, neighbors;
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			neighbors = getNeighbors(i, j, old, rows, cols);
			if ((old[i][j] == 'x') &&
				((neighbors == 0 || neighbors == 1)
			 || ((neighbors <= 8) && (neighbors >= 4)))) {
				new[i][j] = ' ';
			}
			else if ((old[i][j] == 'x') && (neighbors == 2 || neighbors == 3)) {
				new[i][j] = 'x';
			}
			else if ((old[i][j] == ' ') && (neighbors == 3)) {
				new[i][j] = 'x';
			}

		}
	}
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

	/*switch (argc) {
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

	} */


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
	int startRows, startCols, i, j;
	startRows = calcNumberLines(input);
	startCols = calcLongestLine(input);
	gridA = centerPattern(startRows, startCols, start, rows, cols);
	printf("The pattern you have specified looks like this: \n");
	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			printf("%c", gridA[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < gens; i++) {

	}

	/*Once opened, you can read from the file one character at a time with fgetc().
	 * You can read one line at a time using fgets().
	 * You can read from standard input (the keyboard) with getchar().
	*/

	return EXIT_SUCCESS;
}
