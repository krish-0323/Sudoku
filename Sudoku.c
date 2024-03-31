#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 9
#define EMPTY 0

bool isSafe(int puzzle[SIZE][SIZE], int row, int col, int num){
    
    for(int i = 0; i < SIZE; i++) if(puzzle[row][i] == num)  return false;
    for(int i = 0; i < SIZE; i++) if(puzzle[i][col] == num)  return false;

    int startRow = row - row % 3;
    int startCol = col - col % 3;

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++) if(puzzle[i + startRow][j + startCol] == num)  return false;

    return true;
}

bool findEmptyLocation(int puzzle[SIZE][SIZE], int *row, int *col){
    for (*row = 0; *row < SIZE; (*row)++)
        for (*col = 0; *col < SIZE; (*col)++)   if (puzzle[*row][*col] == EMPTY)    return true;

    return false;
}

bool solveSudoku(int puzzle[SIZE][SIZE]){
    int row, col;

    if (!findEmptyLocation(puzzle, &row, &col)){
        // If no empty location is found, Sudoku is solved
        return true;
    }

    // Generate a random permutation of numbers from 1 to 9
    int numbers[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i < 9; i++){
        int j = rand() % 9;
        int temp = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = temp;
    }

    // Try numbers from the random permutation
    for (int i = 0; i < 9; i++){
        int num = numbers[i];
        if (isSafe(puzzle, row, col, num)){
            // Assign the number if it's safe
            puzzle[row][col] = num;

            // Recursively solve the remaining Sudoku
            if (solveSudoku(puzzle))    return true;

            // If the assigned number doesn't lead to a solution,
            // backtrack and try a different number
            puzzle[row][col] = EMPTY;
        }
    }

    // No solution found
    return false;
}

void generateSudoku(int puzzle[SIZE][SIZE], int difficulty){
    // Clear the puzzle
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)      puzzle[i][j] = EMPTY;
    }

    // Generate a random Sudoku puzzle
    solveSudoku(puzzle);

    // Remove numbers to create a playable Sudoku
    int numToRemove = difficulty; // Adjust this value to control the difficulty

    while (numToRemove > 0){
        int row = rand() % SIZE;
        int col = rand() % SIZE;

        if (puzzle[row][col] != EMPTY){
            // Backup the number
            int backup = puzzle[row][col];
            puzzle[row][col] = EMPTY;

            // Check if the solution is unique
            int temp[SIZE][SIZE];
            for (int i = 0; i < SIZE; i++){
                for (int j = 0; j < SIZE; j++)    temp[i][j] = puzzle[i][j];
                
            }

            if (!solveSudoku(temp)){
                // If removing the number leads to a non-unique solution,
                // restore the number and try removing a different number
                puzzle[row][col] = backup;
            }
            else    numToRemove--;
        }
    }
}

bool isAvailable(int puzzle[SIZE][SIZE], int row, int col, int num)
{
    int rowStart = (row / 3) * 3;
    int colStart = (col / 3) * 3;
    int i, j;

    for (i = 0; i < SIZE; ++i)
    {
        if (puzzle[row][i] == num)  return false;
        if (puzzle[i][col] == num)  return false;
        if (puzzle[rowStart + (i % 3)][colStart + (i / 3)] == num)  return false;
    }
    return true;
}

void printSudoku(int puzzle[SIZE][SIZE])
{
    printf("+------+-------+------+\n");
    for (int i = 1; i < 10; ++i){
        for (int j = 1; j < 10; ++j){
            printf("|%d", puzzle[i - 1][j - 1]);
            if (j % 3 == 0 && j != 9) printf("| ");
        }
        printf("|\n");
        if (i % 3 == 0) printf("+------+-------+------+\n");
    }
}

int main(){

    printf("To generate a random sudoku puzzle Enter '1' or if you want to enter your Sudoku puzzle Enter '2'.\n\n");
    int n;
    printf("Enter your command : ");
    scanf("%d", &n);

    if (n == 1){
        int puzzle[SIZE][SIZE];
        srand(time(NULL));
        printf("Enter Difficulty of Sudoku Puzzle on Scale 40-65 : ");
        int dificulty; scanf("%d", &dificulty);
        generateSudoku(puzzle, dificulty);
        printf("Generated Sudoku Puzzle:\n\n");
        printSudoku(puzzle);
        printf("\n");
        printf("To print the solved puzzle please enter Y or if you want to exit enter N : ");

        char c;     scanf("%c", &c); scanf("%c", &c);

        if (c == 'Y' || c == 'y'){
            printf("\nSolved Sudoku Puzzle:\n\n");

            if (solveSudoku(puzzle))   printSudoku(puzzle);
            else    printf("\n\nNO SOLUTION\n\n");
        }
        else if (c == 'N' || c == 'n')  printf("Enjoy solving the Sudoku Puzzle.");

    } else if(n==2){

        int puzzle[SIZE][SIZE];
        
        for(int i=0;i<SIZE;i++)
            for(int j=0;j<SIZE;j++)     scanf("%d",&puzzle[i][j]);

        if(solveSudoku(puzzle))    printSudoku(puzzle);
        else printf("\n\nNO SOLUTION\n\n");
    }

    return 0;
}

