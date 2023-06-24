#include "./../include/processA_utilities.h"  ///< Include utilities specific to processA
#include "utility.h"  ///< Include general utility functions
#include <bmpfile.h>  ///< Include library for bitmap file operations

#define TRUE 1
#define FALSE 0
#define IMAGE_NAME_LENGTH 20  ///< Define maximum length of image names
#define IMAGE_NAME_PREFIX "image_"  ///< Define prefix for image file names
#define SHARED_MEMORY_NAME "image_memory"  ///< Define name of shared memory segment

/**
 * Program's entry point.
 *
 * @param argc The number of command line arguments.
 * @param argv The command line arguments.
 *
 * @return The exit status of the program.
 */
 
void handleScreenResize(int *isFirstResize); 
void clearConfirmationMessage();
int isArrowKey(int command);
void handleMouseCommand(int *imageId, char *capturedId, int *sharedMemoryPtr);
void handleArrowKeyCommand(int command, int *sharedMemoryPtr);
void displayPrintConfirmation();
void saveCurrentImage(int *imageId, char *capturedId, int *sharedMemoryPtr);

int main(int argc, char *argv[]) {

    int imageId = 1;  ///< Identifier for images
    char capturedId[IMAGE_NAME_LENGTH];  ///< Array to store string version of imageId

    int isFirstResize = TRUE;  ///< Flag to prevent handling first resize event

    int *sharedMemoryPtr = createSharedMemory(SHARED_MEMORY_NAME);  ///< Create shared memory segment
    if (sharedMemoryPtr == NULL) {  ///< If memory allocation failed
        fprintf(stderr, "Failed to create shared memory segment\n");  ///< Print error message
        return EXIT_FAILURE;  ///< Return with failure status
    }

    init_console_ui();  ///< Initialize user interface

    drawCircle(circle.x, circle.y, sharedMemoryPtr, FALSE, "image_saved");  ///< Draw initial circle

    while (TRUE) {  ///< Run until the program is manually stopped
        int command = getch();  ///< Get user input non-blocking

        if (command == KEY_RESIZE) {  ///< If user resized the window
            handleScreenResize(&isFirstResize);  ///< Handle screen resize
        } else if (command == KEY_MOUSE) {  ///< If user pressed mouse button
            handleMouseCommand(&imageId, capturedId, sharedMemoryPtr);  ///< Handle mouse command
        } else if (isArrowKey(command)) {  ///< If user pressed arrow key
            handleArrowKeyCommand(command, sharedMemoryPtr);  ///< Handle arrow key command
        }
    }

    endwin();  ///< Clean up and close the window
    return EXIT_SUCCESS;  ///< Return with success status
}

/**
 * Function to handle screen resizing.
 * @param isFirstResize Pointer to flag that prevents handling of first resize event
 */
void handleScreenResize(int *isFirstResize) {
    if (*isFirstResize) {  ///< If this is the first resize event
        *isFirstResize = FALSE;  ///< Set flag to false
    } else {  ///< If this is not the first resize event
        reset_console_ui();  ///< Reset user interface
    }
}

/**
 * Function to handle mouse commands.
 * @param imageId Pointer to the image identifier
 * @param capturedId Array to store string version of imageId
 * @param sharedMemoryPtr Pointer to shared memory segment
 */
void handleMouseCommand(int *imageId, char *capturedId, int *sharedMemoryPtr) {
    if (getmouse(&event) == OK) {  ///< If mouse event was successfully retrieved
        if (check_button_pressed(print_btn, &event)) {  ///< If print button was pressed
            saveCurrentImage(imageId, capturedId, sharedMemoryPtr);  ///< Save current image
            displayPrintConfirmation();  ///< Display confirmation message
            clearConfirmationMessage();  ///< Clear confirmation message after a delay
        }
    }
}

/**
 * Function to save the current image.
 * @param imageId Pointer to the image identifier
 * @param capturedId Array to store string version of imageId
 * @param sharedMemoryPtr Pointer to shared memory segment
 */
void saveCurrentImage(int *imageId, char *capturedId, int *sharedMemoryPtr) {
    char imageName[IMAGE_NAME_LENGTH] = IMAGE_NAME_PREFIX;  ///< Initialize image name with prefix
    sprintf(capturedId, "%d", *imageId);  ///< Convert imageId to string and store in capturedId
    strcat(imageName, capturedId);  ///< Append capturedId to imageName
    drawCircle(circle.x, circle.y, sharedMemoryPtr, TRUE, imageName);  ///< Draw and save circle image
    (*imageId)++;  ///< Increment imageId for next save
}

/**
 * Function to display a confirmation message.
 */
void displayPrintConfirmation() {
    mvprintw(LINES - 1, 1, "Print button pressed");  ///< Print confirmation message
    refresh();  ///< Refresh the screen to display the message
    sleep(1);  ///< Wait for a short period to allow user to read the message
}

/**
 * Function to clear the confirmation message.
 */
void clearConfirmationMessage() {
    for (int j = 0; j < COLS - BTN_SIZE_X - 2; j++) {  ///< For each character of the message
        mvaddch(LINES - 1, j, ' ');  ///< Replace character with a space
    }
}

/**
 * Function to determine if a command corresponds to an arrow key.
 * @param command The command to check
 * @return True if the command is an arrow key, false otherwise
 */
int isArrowKey(int command) {
    return command == KEY_LEFT || command == KEY_RIGHT || command == KEY_UP || command == KEY_DOWN;
}

/**
 * Function to handle commands corresponding to arrow keys.
 * @param command The command to handle
 * @param sharedMemoryPtr Pointer to shared memory segment
 */
void handleArrowKeyCommand(int command, int *sharedMemoryPtr) {
    move_circle(command);  ///< Move circle according to command
    draw_circle();  ///< Redraw circle marker
    drawCircle(circle.x, circle.y, sharedMemoryPtr, FALSE, "image_saved");  ///< Draw and save circle image
}