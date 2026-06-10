#include <stdio.h>
#include <stdlib.h>
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
//DAY 4: DRAWING SHAPES
// Function to read memory and draw the shapes onto the canvas
// Function to read memory and draw the shapes onto the canvas
void paintCanvas() {
    // Loop through every shape currently saved in memory
    for (int i = 0; i < currentShapeCount; i++) {
        Shape s = objectList[i];

        // Only draw it if it is active (not deleted)
        if (s.is_active == 1) {
            
            // --- DRAW LINE (Type 1) ---
            if (s.type == 1) {
                // Bresenham's Line Algorithm
                int x0 = s.x1, y0 = s.y1;
                int x1 = s.x2, y1 = s.y2;
                int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
                int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
                int err = dx + dy, e2;

                while (1) {
                    if (y0 >= 0 && y0 < ROWS && x0 >= 0 && x0 < COLS) {
                        canvas[y0][x0] = s.symbol;
                    }
                    if (x0 == x1 && y0 == y1) break;
                    e2 = 2 * err;
                    if (e2 >= dy) { err += dy; x0 += sx; }
                    if (e2 <= dx) { err += dx; y0 += sy; }
                }
            }
            
            // --- DRAW RECTANGLE (Type 2) ---
            else if (s.type == 2) {
                // Loop through the height and width of the rectangle
                for (int row = s.y1; row <= s.y2; row++) {
                    for (int col = s.x1; col <= s.x2; col++) {
                        // Safety check: Make sure we don't draw outside the canvas
                        if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
                            // Draw only the borders of the rectangle
                            if (row == s.y1 || row == s.y2 || col == s.x1 || col == s.x2) {
                                canvas[row][col] = s.symbol;
                            }
                        }
                    }
                }
            }
            
            // --- DRAW CIRCLE (Type 3) ---
            else if (s.type == 3) {
                // Since our menu asks for X and Y for ending coordinates, 
                // if it's a circle, the user's first number (x2) acts as our radius!
                int radius = s.x2; 
                
                for (int row = 0; row < ROWS; row++) {
                    for (int col = 0; col < COLS; col++) {
                        // Calculate distance from center (x1, y1)
                        int dx = col - s.x1;
                        int dy = row - s.y1;
                        int distSquared = (dx * dx) + (dy * dy);
                        int radSquared = radius * radius;
                        
                        // Check if the current grid spot is on the circle's edge
                        // We use + radius and - radius to give the line a little bit of thickness 
                        // so it doesn't look completely broken on a text grid.
                        if (distSquared >= radSquared - radius && distSquared <= radSquared + radius) {
                            canvas[row][col] = s.symbol;
                        }
                    }
                }
            }
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


// --- NEW DAY 3 CODE: INTERACTIVITY ---

// Function to get shape details from the user and save it to memory
void addShape() {
    if (currentShapeCount >= MAX_SHAPES) {
        printf("Memory full! Cannot add more shapes.\n");
        return;
    }

    Shape newShape;
    newShape.id = currentShapeCount + 1; // Give it a unique ID
    newShape.is_active = 1;              // Mark it as visible

    printf("\nChoose shape type (1=Line, 2=Rectangle, 3=Circle): ");
    scanf("%d", &newShape.type);

    printf("Enter starting X and Y coordinates (e.g., 5 10): ");
    scanf("%d %d", &newShape.x1, &newShape.y1);

    printf("Enter ending X and Y (or radius for circle): ");
    scanf("%d %d", &newShape.x2, &newShape.y2);

    printf("Enter the character to draw with (e.g., *): ");
    scanf(" %c", &newShape.symbol); // Space before %c is important to catch the Enter key!

    // Save the new shape into our global array
    objectList[currentShapeCount] = newShape;
    currentShapeCount++;

    printf("Shape #%d saved to memory!\n", newShape.id);
}

int main() {
    int choice;

    // The infinite loop keeps the program running until the user types 2
    while (1) {
        clearCanvas();
        
        // TODO: Tomorrow we will add the function here that actually paints the shapes!
        paintCanvas();
        printf("\n--- My 2D Graphics Editor ---\n");
        displayPicture();
        printf("Total Shapes in Memory: %d\n", currentShapeCount);
        
        printf("\nMenu:\n");
        printf("1. Add a Shape\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            addShape();
        } else if (choice == 2) {
            printf("Exiting editor. Goodbye!\n");
            break; // Breaks out of the while loop to end the program
        } else {
            printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
