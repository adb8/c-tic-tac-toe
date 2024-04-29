#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void playerTurn(char board[3][3], char player) {
    int row, col;
    int result;
    char str[100];
    printf("Your turn...\n");
    fgets(str, sizeof(str), stdin);
    result = sscanf(str, "%d %d", &row, &col);
    while (result != 2 || strlen(str) > 4 || row > 3 || row < 1 || col > 3 || col < 1 || board[row - 1][col - 1] != ' ') {
        printf("Invalid move! Try again...\n");
        fgets(str, sizeof(str), stdin);
        result = sscanf(str, "%d %d", &row, &col);
    }
    printf("You chose row %d and column %d\n", row, col);
    board[row - 1][col - 1] = player;
}

void computerTurn(char board[3][3], char computer) {
    srand(time(NULL));
    printf("Computer's turn...\n");
    int row, col;
    bool madeMove = false;
    int madeRow, madeCol;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == computer) {
                madeRow = i;
                madeCol = j;
                madeMove = true;
                break;
            }
        }
    }
    if (!madeMove) {
        do {
            row = rand() % 3;
            col = rand() % 3;
        } while (board[row][col] != ' ');
    } else {
        int possibleMoves[8][2] = {
            {madeRow - 1, madeCol - 1},
            {madeRow - 1, madeCol},
            {madeRow - 1, madeCol + 1},
            {madeRow, madeCol - 1},
            {madeRow, madeCol + 1},
            {madeRow + 1, madeCol - 1},
            {madeRow + 1, madeCol},
            {madeRow + 1, madeCol + 1}};
        int options = 8;
        int index = rand() % 8;
        do {
            row = possibleMoves[index % 8][0];
            col = possibleMoves[index % 8][1];
            options--;
            index++;
            if (options == 0) {
                do {
                    row = rand() % 3;
                    col = rand() % 3;
                } while (board[row][col] != ' ');
                break;
            }
        } while (row < 0 || row > 2 || col < 0 || col > 2 || board[row][col] != ' ');
    }
    printf("Computer chose row %d and column %d\n", row + 1, col + 1);
    board[row][col] = computer;
}

char checkForWinner(char board[3][3], char player, char computer) {
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && board[row][0] != ' ') {
            if (board[row][0] == player) {
                printf("You win!");
            } else if (board[row][0] == computer) {
                printf("Computer wins!");
            }
            return true;
        }
    }
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] != ' ') {
            if (board[0][col] == player) {
                printf("You win!");
            } else if (board[0][col] == computer) {
                printf("Computer wins!");
            }
            return true;
        }
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
        if (board[0][0] == player) {
            printf("You win!");
        } else if (board[0][0] == computer) {
            printf("Computer wins!");
        }
        return true;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
        if (board[0][2] == player) {
            printf("You win!");
        } else if (board[0][2] == computer) {
            printf("Computer wins!");
        }
        return true;
    }
    return false;
}

void printBoard(char board[3][3]) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf("%c", board[row][col]);
            printf("|");
        }
        printf("\n");
        if (row < 2) {
            printf("------\n");
        }
    }
}

int main() {
    char board[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}};
    char player = 'X';
    char computer = 'O';
    char currentPlayer = player;
    int spacesLeft = 9;
    bool winnerFound = false;

    printf("Welcome to Tic Tac Toe!\n");
    printf("Computer is %c\n", computer);
    printf("You are %c\n", player);
    printf("Enter the row and column number of where you want to make a move\n");

    while (spacesLeft > 0 && !winnerFound) {
        if (currentPlayer == player) {
            playerTurn(board, player);
        } else if (currentPlayer == computer) {
            computerTurn(board, computer);
        }
        spacesLeft--;
        printBoard(board);
        winnerFound = checkForWinner(board, player, computer);
        if (currentPlayer == player) {
            currentPlayer = computer;
        } else {
            currentPlayer = player;
        }
    }
    if (!winnerFound) {
        printf("It's a tie!\n");
        printf("Thanks for playing!");
    }
    return 0;
}