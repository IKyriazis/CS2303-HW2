/* Game of Life - Ioannis Kyriazis
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
 * @param y the y coordinate of the cell we want to check
 * @param x The x coordinate of the cell we want to check
 * @param rows the amount of rows in the grid
 * @param cols the amount of columns in the grid
 * @param arr the 2d array that the cell is in
 *
 * https://stackoverflow.com/questions/652106/
 * finding-neighbours-in-a-two-dimensional-array
 *
 * ^That link helped a bit
 */
unsigned int getNeighbors(unsigned int y, unsigned int x,
						  char **arr, unsigned int rows, unsigned int cols) {

	// create a 2d array with a buffer of one cells as a border to avoid
	// going out of bounds
	char **buff = centerPattern(rows, cols, arr, rows + 2, cols + 2);

	// if we fail to allocate the memory let the user know
	if (!buff) {
		printf("failed to allocate array buff");
	}
	unsigned int neighbors = 0; // initialize the amount of neighbors with size 0

	// These 8 if statements check the neighbors of the given cell
	// if there is a neighbor, add 1 to the amount of neighbors it has
	if (buff[(x+1)-1][(y+1)-1] == 'x') {
		neighbors += 1;
	}
	if (buff[(x+1)-1][(y+1)] == 'x') {
		neighbors += 1;
	}
	if (buff[(x+1)-1][(y+1)+1] == 'x') {
		neighbors += 1;
	}
	if (buff[(x+1)][(y+1)-1] == 'x') {
		neighbors += 1;
	}
	if (buff[(x+1)][(y+1)+1] == 'x') {
		neighbors += 1;
	}
	if (buff[(x+1)+1][(y+1)-1] == 'x') {
		neighbors += 1;
	}
	if (buff[(x+1)+1][(y+1)] == 'x') {
		neighbors += 1;
	}
	if (buff[(x+1)+1][(y+1)+1] == 'x') {
		neighbors += 1;
	}

	// de-allocate the array we used since we don't need it anymore
	free(buff);

	// return the amount of neighbors the specified cell has
	return neighbors;

}

/**
 * Plays a single generation of the Game of Life
 * @param rows The amount of rows in the grid
 * @param cols The amount of columns in the grid
 * @param Old The generation to read from
 * @param New The generation to write to
 */
void playOne(unsigned int rows, unsigned int cols, char **old, char **new) {
	// create row and column counter variables and a variable to store our
	// calculation for the amount of neighbors the cell has
	unsigned int i, j, neighbors;

	// Pre-condition:
	// No rows have been scanned for life
	for (i = 0; i < rows; i++) {
		// Invariant 10:
		// i+1 is equivalent to the amount of rows we have searched through

		// Pre-condition:
		// No columns have been searched in this ith row
		for (j = 0; j < cols; j++) {
			// Invariant 11:
			// j+1 is equivalent to the amount of columns that have been
			// searched through

			// calculate the number of neighbors the specific cell has
			neighbors = getNeighbors(j, i, old, rows, cols);

			// if the cell is occupied, and has 0-1 or 4-8 neighbors, kill it
			// by writing a blank to the new array in the same spot
			if ((old[i][j] == 'x') &&
				((neighbors == 0 || neighbors == 1)
			 || ((neighbors <= 8) && (neighbors >= 4)))) {
				new[i][j] = ' ';
			}

			// otherwise if the cell is occupied and has either 2 or 3
			// neighbors, let it live by writing an 'x' to the same spot
			// on the new array
			else if ((old[i][j] == 'x') && (neighbors == 2 || neighbors == 3)) {
				new[i][j] = 'x';
			}
			// otherwise, if the cell is unoccupied and has exactly 3 neighbors,
			// birth a new one by writing an 'x' to the new array at the same
			// spot
			else if ((old[i][j] == ' ') && (neighbors == 3)) {
				new[i][j] = 'x';
			}
			else {
				new[i][j] = ' ';
			}
		}
		// Post-condition:
		// All columns in the ith row of the old and new array have been read and written
	}
	// Post-condition:
	// All rows of the new and old grids have been read from and written to
}

/**
 * Prints the given grid
 * @param rows The amount of rows
 * @param cols The amount of columns
 * @param grid The grid to print
 *
 */
void printGrid(unsigned int rows, unsigned int cols, char **grid) {
	int i,j; // y and x counters for loop

	// Pre-condition:
	// No rows have been printed
	for (i = 0; i < rows; i++) {
		// Invariant 12:
		// i+1 is equal to the amount of rows printed

		// Pre-condition:
		// No columns in ith row have been printed
		for (j = 0; j < cols; j++) {
			// Invariant 13:
			// j+1 is equal to the number of columns printed in the ith row
			printf("%c", grid[i][j]);
		}
		// Post-condition:
		// all columns in ith row have been printed
		printf("\n");
	}
	// Post-condition:
	// all rows in grid have been printed
}

/**
 * Checks to see if two arrays are the same
 * @param rows The amount of rows in the arrays (will be identical)
 * @param cols The amount of columns in the arrays (will be identical)
 * @param arr1 The first array
 * @param arr2 The second array
 * @return 0 if same arrays or 1 if the arrays are different
 */
unsigned int isDifferent(unsigned int rows, unsigned int cols,
					char **arr1, char **arr2) {

	unsigned int i, j; // counter variables for rows and cols

	unsigned int different = 0;

	for (i = 0; i < rows; i++) {
		for (j = 0; j < cols; j++) {
			if (arr1[i][j] != arr2[i][j]) {
				different = 1;
				break;
			}
		}
	}
	return different;

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
	if (argc == 7) {
		if ((char) argv[5][0] == 'y') {
			doPrint = 1;
		}
		else if ((char) argv[5][0] == 'n') {
			doPrint = 0;
		}
		else {
			printf("Please check your arguments and try again");
		}
		if ((char) argv[6][0] == 'y') {
			doPause = 1;
		}
		else if (argv[6][0] == 'n') {
			doPause = 0;
		}
		else {
			printf("Please check your arguments and try again");
		}
	}



	/* Allocate 3 2d arrays to hold 3 grids
	*/
	gridA = make2Dchar(rows, cols);
	char **gridB = make2Dchar(rows, cols);
	char **gridC = make2Dchar(rows, cols);
	//check that it succeeded.
	if (!gridA) {
		printf("Unable to allocate array A");
	}
	if (!gridB) {
		printf("Unable to allocate array B");
	}
	if (!gridC) {
		printf("Unable to allocate array C");
	}


	/* Eventually, need to try to open the input file.
	*/
	input = fopen(inputFileName, "r");
	if (!input) {
		printf("Unable to open input file: %s\n", inputFileName);
		return EXIT_FAILURE;
	}

	// convert the file into an array to easily manipulate it
	char **start = fileToArray(input);

	// calculate how many rows and columns the file's array should be
	int startRows, startCols;
	startRows = calcNumberLines(input);
	startCols = calcLongestLine(input);

	// center the file's array onto gridA
	gridA = centerPattern(startRows, startCols, start, rows, cols);

	// Show the user what pattern they specified
	printf("The pattern you have specified looks like this: \n");
	printGrid(rows, cols, gridA);

	if (argc == 5) {
		int i;
		char **p = gridA;
		char **q = gridB;
		char **temp = gridC;
		for (i = 0; i < gens; i++) {
			playOne(rows, cols, p, q);
			temp = p;
			p = q;
			q = temp;
			if (!isDifferent(rows, cols, gridA, gridB)
			 || !isDifferent(rows, cols, gridB, gridC)
			 || !isDifferent(rows, cols, gridA, gridC)) {

				printf("Exit because steady state has been detected\n"
									"Generations achieved: %d", i);
				return EXIT_SUCCESS;
			}
			else if (i == gens - 1) {
				printf("Max generations reached: %d\n", i);
				return EXIT_SUCCESS;
			}
		}
		printGrid(rows, cols, p);
	}
	else if (argc == 7) {
		int i;
		char **p = gridA;
		char **q = gridB;
		char **temp = gridC;
		if (doPrint && doPause) {
			for (i = 0; i < gens; i++) {
				playOne(rows, cols, p, q);
				temp = p;
				p = q;
				q = temp;
				if (!isDifferent(rows, cols, gridA, gridB)
				 || !isDifferent(rows, cols, gridB, gridC)
				 || !isDifferent(rows, cols, gridA, gridC)) {

					printf("Exit because steady state has been detected\n"
								"Generations achieved: %d", i);
					return EXIT_SUCCESS;
				}
				else if (i == gens - 1) {
					printf("Max generations reached: %d\n", i);
					return EXIT_SUCCESS;
				}
				printGrid(rows, cols, p);
				getchar();
			}
		}
		else if (doPrint && !doPause) {
			for (i = 0; i < gens; i++) {
				playOne(rows, cols, p, q);
				temp = p;
				p = q;
				q = temp;
				if (!isDifferent(rows, cols, gridA, gridB)
				 || !isDifferent(rows, cols, gridB, gridC)
				 || !isDifferent(rows, cols, gridA, gridC)) {

					printf("Exit because steady state has been detected\n"
											"Generations achieved: %d", i);
					return EXIT_SUCCESS;
				}
				else if (i == gens - 1) {
					printf("Max generations reached: %d\n", i);
					return EXIT_SUCCESS;
				}
				printGrid(rows, cols, p);
			}
		}
		else if (!doPrint && doPause) {
			for (i = 0; i < gens; i++) {
				playOne(rows, cols, p, q);
				temp = p;
				p = q;
				q = temp;
				if (!isDifferent(rows, cols, gridA, gridB)
				 || !isDifferent(rows, cols, gridB, gridC)
				 || !isDifferent(rows, cols, gridA, gridC)) {

					printf("Exit because steady state has been detected\n"
							"Generations achieved: %d", i);
					return EXIT_SUCCESS;
				}
				else if (i == gens - 1) {
					printf("Max generations reached: %d\n", i);
					return EXIT_SUCCESS;
				}
				getchar();
			}
		}
		else {
			int i;
			char **p = gridA;
			char **q = gridB;
			char **temp = gridC;
			for (i = 0; i < gens; i++) {
				playOne(rows, cols, p, q);
				temp = p;
				p = q;
				q = temp;
				if (!isDifferent(rows, cols, gridA, gridB)
				 || !isDifferent(rows, cols, gridB, gridC)
				 || !isDifferent(rows, cols, gridA, gridC)) {

					printf("Exit because steady state has been detected\n"
												"Generations achieved: %d", i);
					return EXIT_SUCCESS;
				}
				else if (i == gens - 1) {
					printf("Max generations reached: %d\n", i);
					return EXIT_SUCCESS;
				}
			}
			printGrid(rows, cols, p);
		}
	}


	return EXIT_SUCCESS;
}
