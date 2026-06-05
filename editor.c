#include <stdio.h>

// Define the size of our canvas
#define ROWS 20
#define COLS 40
#define MAX_SHAPES 100 // Maximum number of shapes the editor can hold

// Our global 2D array that acts as the picture
char canvas[ROWS][COLS];

// --- NEW DAY 2 CODE: DATA STRUCTURES ---

// Define what a "Shape" is
typedef struct {
    int id;          // Unique number to find the shape later (for modifying/deleting)
    int type;        // 1 = Line, 2 = Rectangle, 3 = Circle, 4 = Triangle
    int x1, y1;      // Starting coordinates (or center for circle)
    int x2, y2;      // Ending coordinates (for lines and rectangles)
    int x3, y3;      // Third point (only used for triangles)
    int radius;      // Only used for circles
    char symbol;     // The character used to draw it (usually '*')
    int is_active;   // 1 if the shape is visible, 0 if it has been deleted
} Shape;

// Create our "Object List" to store all the shapes
Shape objectList[MAX_SHAPES];
int currentShapeCount = 0; // Keeps track of how many shapes we have added

// ---------------------------------------

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