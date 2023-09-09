#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

#define ALIVE_CELL 'X'
#define DEAD_CELL ' '
#define BLUE_TEXT "\033[34m" /* Blue text color */
#define RESET_COLOR "\033[0m"

/* Function to initialize the game board with random initial conditions */
void initializeGameBoard(char **board, int rows, int cols, int density) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            int randomNum = rand() % 101; /* Generate a random number between 0 and 100 */
            if (randomNum < density) {
                board[i][j] = ALIVE_CELL; /* Set the cell to be alive based on density */
            } else {
                board[i][j] = DEAD_CELL; /* Set the cell to be dead */
            }
        }
    }
}

/* Function to print the game board with blue characters when steady-state is reached */
void printGameBoard(char **board, int rows, int cols, int steadyState) {
    printf("\033[H"); /* Move cursor to the top left corner of the terminal */
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if (steadyState) {
                printf(BLUE_TEXT "%c" RESET_COLOR, board[i][j]); /* Print blue characters */
            } else {
                printf("%c", board[i][j]); /* Print characters without color */
            }
        }
        putchar('\n'); /* Move to the next line after each row */
    }
    fflush(stdout); /* Flush the output buffer to ensure immediate display */
}

/* Function to count the number of live neighbors for a cell */
int countLiveNeighbors(char **board, int x, int y, int rows, int cols) {
    int count = 0;
    int i, j;
    for (i = x - 1; i <= x + 1; i++) {
        for (j = y - 1; j <= y + 1; j++) {
            if (i >= 0 && i < rows && j >= 0 && j < cols && !(i == x && j == y) && board[i][j] == ALIVE_CELL) {
                count++;
            }
        }
    }
    return count;
}

/* Function to check if the current board state matches a previous state */
int isSteadyState(char **board, char ***previousStates, int numStates, int rows, int cols) {
    int i, j, k;
    for (k = 0; k < numStates; k++) {
        int match = 1;
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                if (board[i][j] != previousStates[k][i][j]) {
                    match = 0;
                    break;
                }
            }
            if (!match) {
                break;
            }
        }
        if (match) {
            return 1;
        }
    }
    return 0;
}

/* Function to update the game board according to the Game of Life rules */
void updateGameBoard(char **board, int rows, int cols) {
    int i, j;
    char **newBoard = (char **)malloc(rows * sizeof(char *));
    for (i = 0; i < rows; i++) {
        newBoard[i] = (char *)malloc(cols * sizeof(char));
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            int liveNeighbors = countLiveNeighbors(board, i, j, rows, cols);
            if (board[i][j] == ALIVE_CELL) {
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    newBoard[i][j] = DEAD_CELL;
                } else {
                    newBoard[i][j] = ALIVE_CELL;
                }
            } else {
                if (liveNeighbors == 3) {
                    newBoard[i][j] = ALIVE_CELL;
                } else {
                    newBoard[i][j] = DEAD_CELL;
                }
            }
        }
    }

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            board[i][j] = newBoard[i][j];
        }
    }

    for (i = 0; i < rows; i++) {
        free(newBoard[i]);
    }
    free(newBoard);
}

/* Function to read a key press */
char readKeyPress() {
    char buf = 0;
    struct termios old = {0};
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    return buf;
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: %s ROWS COLS DENSITY DELAY_MS\n", argv[0]);
        return 1;
    }

    int rows = atoi(argv[1]);
    int cols = atoi(argv[2]);
    int density = atoi(argv[3]);
    int delay_ms = atoi(argv[4]);

    if (density < 0 || density > 100 || delay_ms < 0) {
        printf("Invalid input. Density must be in the range 0-100, and delay_ms must be non-negative.\n");
        return 1;
    }

    /* Clear the screen */
    printf("\033[H\033[J"); /* Clear screen ANSI escape code */

    /* Allocate memory for the game board and previous states */
    char **board = (char **)malloc(rows * sizeof(char *));
    char ***previousStates = (char ***)malloc(rows * cols * sizeof(char **));
    int i, j, k;
    for (i = 0; i < rows; i++) {
        board[i] = (char *)malloc(cols * sizeof(char));
        for (j = 0; j < cols; j++) {
            previousStates[i * cols + j] = (char **)malloc(rows * sizeof(char *));
            for (k = 0; k < rows; k++) {
                previousStates[i * cols + j][k] = (char *)malloc(cols * sizeof(char));
            }
        }
    }

    /* Initialize the random number generator */
    srand(time(NULL));

    /* Initialize the game board with random initial conditions */
    initializeGameBoard(board, rows, cols, density);

    int numStates = 0;
    int steadyState = 0;

    while (1) {
        /* Check for steady state */
        if (numStates > 0) {
            steadyState = isSteadyState(board, previousStates, numStates, rows, cols);
        }

        /* Store the current state */
        for (i = 0; i < rows; i++) {
            for (j = 0; j < cols; j++) {
                previousStates[numStates][i][j] = board[i][j];
            }
        }

        /* Print the game board */
        printGameBoard(board, rows, cols, steadyState);

        /* Update the game board */
        updateGameBoard(board, rows, cols);

        /* Sleep to control the update rate */
        usleep(delay_ms * 1000);

        numStates++;
    }

    /* Free memory */
    for (i = 0; i < rows; i++) {
        free(board[i]);
    }
    free(board);

    for (i = 0; i < rows * cols; i++) {
        for (j = 0; j < rows; j++) {
            free(previousStates[i][j]);
        }
        free(previousStates[i]);
    }
    free(previousStates);

    return 0;
}