#include <stdio.h>

// Define the size of our canvas
#define ROWS 20
#define COLS 40

// Our global 2D array that acts as the picture
char canvas[ROWS][COLS];

// Function to fill the canvas with blank spaces '_'
void clearCanvas() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            canvas[i][j] = '_';
        }
    }
}

// Function to print the canvas to the screen
void displayPicture() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("%c ", canvas[i][j]);
        }
        printf("\n"); // Move to the next line after each row
    }
}

int main() {
    // 1. Initialize the canvas
    clearCanvas();
    
    // 2. Show it to the user
    printf("--- My 2D Graphics Editor ---\n");
    displayPicture();

    return 0;
}