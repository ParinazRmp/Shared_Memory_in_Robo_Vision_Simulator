#include "./../include/processB_utilities.h" // Include local headers for process B utilities
#include "utility.h" // Include headers for general utilities
#include <bmpfile.h> // Include headers for the BMP file library

// Start of the main function
int main(int argc, char const *argv[]) {
    // Initialize variables for the center coordinates of the circle
    float centerX;
    float centerY;

    // Create a shared memory segment and save the pointer to this segment
    int *sharedMemoryPtr = createSharedMemory("image_memory");
    // If the shared memory pointer is null, print an error message and terminate the program
    if (!sharedMemoryPtr) {
        perror("Failed to create shared memory");
        return EXIT_FAILURE;
    }

    // Initialize a variable to prevent triggering a resize event at startup
    int first_resize = TRUE;

    // Initialize the user interface
    init_console_ui();

    // Start of an infinite loop
    while (TRUE) {
        // Read the bitmap image from the shared memory segment
        bmpfile_t *bmp = readSharedMemory(sharedMemoryPtr);
        // If the bmp file is null, print an error message and skip to the next iteration of the loop
        if (!bmp) {
            perror("Failed to read from shared memory");
            continue;
        }

        // Detect the circle in the bitmap image and get its center coordinates
        detectCircle(bmp, &centerX, &centerY);

        // Destroy the bmp file to free up memory
        destroyImage(bmp);

        // Get user input in a non-blocking manner
        int cmd = getch();

        // If the user input indicates a resize event
        if (cmd == KEY_RESIZE) {
            // If this is the first resize event, just set the first_resize flag to FALSE
            if (first_resize) {
                first_resize = FALSE;
            } 
            // If this is not the first resize event, reset the user interface
            else {
                reset_console_ui();
            }
        } 
        // If the user input is not a resize event
        else {
            // Display the 2D motion of the circle's center
            mvaddch(centerY / 20.0, centerX / 20.0, 'o');
            // Refresh the screen to reflect the changes
            refresh();
        }
    }

    // Destroy the shared memory segment
    destroySharedMemory("image_memory");

    // Terminate the program successfully
    return EXIT_SUCCESS;
}
