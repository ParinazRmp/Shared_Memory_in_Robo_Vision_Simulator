/*Adding the header files:*/

/*1-Standard C Library*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

/*2-File Descriptor Management*/
#include <fcntl.h>

/*3-Bitmap Management*/
#include <bmpfile.h>

/*4-Shared Memory Management*/
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

/*Define Macros:*/

/*Bitmap Macros:*/
#define IMAGE_WIDTH  1600
#define IMAGE_HEIGHT  600
#define IMAGE_DEPTH  4

/*
  Declaring functions:

  1-bmpfile_t * createImage(int width, int height, int depth)
    Description: A function to create a bitmap image with dimensions (width x height x depth).

  2-void destroyImage(bmpfile_t *bmp)
    Description: A function to remove the 'bmp' image from the memory.

  3-int getImageSize()
    Description: A function to calculate the size of the image.

  4-int* createSharedMemory(const char *sharedMemoryName)
    Description: A function to create a named shared memory. 

  5-void writeSharedMemory(int *ptr, bmpfile_t *bmp)
    Description: A function to save the current 'bmp' image into the shared memory.

  6-bmpfile_t* readSharedMemory(int *ptr)
    Description: A function to create a Bitmap image from data that is saved in the shared.

  7-void clearSharedMemory(int *ptr)
    Description: A function to clear the current shared memeory.  

  8-void destroySharedMemory(const char *sharedMemoryName)
    Description: A function to unlink the shared memory.

  9-void detectCircle(bmpfile_t *bmp, float *centerX, float *centerY)
    Description: A function to detect the coordinate of circle's center in the bmp image.

  10-void drawCircle(int centerX, int centerY, int *ptr, bool capture,  const char *filename)
    Description: A function to draw a circle (centerX, centerY) in the 'bmp' image.

  11-void error(char *msg)
    Description: A function to print the error message in the  standard error output terminal.
*/

/*Bitmap Image Operations*/
bmpfile_t * createImage(int width, int height, int depth);
void destroyImage(bmpfile_t *bmp);
int getImageSize();

/*Shared Memory OPerations*/
int* createSharedMemory(const char *sharedMemoryName);
void writeSharedMemory(int *ptr, bmpfile_t *bmp);
bmpfile_t* readSharedMemory(int *ptr);
void clearSharedMemory(int *ptr);
void destroySharedMemory(const char *sharedMemoryName);

/*Image Processing Operations*/
void detectCircle(bmpfile_t *bmp, float *centerX, float *centerY);
void drawCircle(int centerX, int centerY, int *ptr, bool capture,  const char *filename);

/*Error Handeling Operations*/
void error(char *msg);


/*A function to create a bitmap image with dimensions (width x height x depth).*/
bmpfile_t * createImage(int width, int height, int depth){
  //Creates a Bitmap image based on the gicen size
  return bmp_create(width, height, depth);
}

/*A function to remove the 'bmp' image from the memory.*/
void destroyImage(bmpfile_t *bmp){
  //Destroys the bitmap image 
  bmp_destroy(bmp);
 }

/*A function to calculate the size of the image.*/
 int getImageSize(){
  //Computes the current image size
  return IMAGE_WIDTH*IMAGE_HEIGHT*sizeof(int);
}

/*A function to create a named shared memory. */
int* createSharedMemory(const char *sharedMemoryName){
  //Creates a named shared memory object with 'O_CREAT | O_RDWR' flags and '0666' permission
  int shm_fd = shm_open(sharedMemoryName, O_CREAT | O_RDWR, 0666);

  //Error Handling
  if(shm_fd == -1 ){  
    printf("Shared memory creation failed!");
    exit(1);
  }

  //Configures the size of the shared memory object
  if(ftruncate(shm_fd, getImageSize()) == -1)
    printf("Trancate failed\n");

  //Maps the memory address of the calling process to the address of the shared memory 
  int *ptr = (int *)mmap(NULL, getImageSize(), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

   //Error Handling
  if (ptr == MAP_FAILED) {
    printf("Map failed\n");
  }

    //Returns the 'ptr' that points to the address of the shared memory
    return ptr;
}

/*A function to save the current 'bmp' image into the shared memory.*/
void writeSharedMemory(int *ptr, bmpfile_t *bmp){
  //Creates a pixel object
  rgb_pixel_t *pixel;

  //Writes on the shared memory
  for(int row=0;row<IMAGE_HEIGHT;row++){
    for(int col=0;col<IMAGE_WIDTH;col++){
      //Read the current pixel from the bitmap image
      pixel = bmp_get_pixel(bmp, col, row);
      //Writes the pixel value (just the green color (mono color mode)) on the shared memory that addressed by the ptr
      ptr[row*IMAGE_WIDTH + col] = pixel->green;
    }
  }
}

/*A function to create a Bitmap image from data that is saved in the shared.*/
bmpfile_t* readSharedMemory(int *ptr){

  //Create a pixel object
  rgb_pixel_t pixel;
  pixel.blue = 255;
  pixel.red = 255;
  pixel.alpha = 0;

  //Creats an empty bitmap image
  bmpfile_t *bmp = createImage(IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_DEPTH);

  //Reads from the shared memory
  for(int row=0; row<IMAGE_HEIGHT; row++){
    for(int col=0; col<IMAGE_WIDTH; col++){
      //Read the pixel value (just the green color (mono color mode)) from the shared memory that addressed by the ptr 
      pixel.green = ptr[row*IMAGE_WIDTH + col];
      //Set the pixel on the bitmap image
      bmp_set_pixel(bmp, col, row, pixel);
    }
  }

  //Creates an output image
  bmp_save(bmp, "out");

  //Returns the bmp
  return bmp;
}

/*A function to clear the current shared memeory.  */
void clearSharedMemory(int *ptr){
  //Clears the shared memory that addressed by the ptr 
  for(int i=0; i<getImageSize(); i++){
    ptr[i] = 0;
  }
}

/*A function to unlink the shared memory.*/
void destroySharedMemory(const char *sharedMemoryName){
  //Removes the shared memory object
  shm_unlink(sharedMemoryName);
}

/*A function to detect the coordinate of circle's center in the bmp image.*/
void detectCircle(bmpfile_t *bmp, float *centerX, float *centerY){

  //Sets the initial value for the detected minimum and maximum coordinates of the circle
  int row_min = IMAGE_WIDTH;
  int row_max = 0;
  int col_min = IMAGE_HEIGHT;
  int col_max= 0; 

  //Finds the minimum and maximum coordinates of the circle 
  for(int row = 0; row < IMAGE_HEIGHT; row++) {
    for(int col = 0; col < IMAGE_WIDTH; col++) {
      rgb_pixel_t *pixel = bmp_get_pixel(bmp, col, row);
        if((pixel->blue == 255) && (pixel->green == 100) && (pixel->red == 255)){

          if(col<col_min){
              col_min = col;
          }

          if(col>col_max){
              col_max = col;
          }

          if(row<row_min){
              row_min = row;
          }

          if(row>row_max){
              row_max = row;
          }
        }
     }
   }

  //Computes the coordinates of the circle's center
  *centerX = (col_min + col_max)/2.0;
  *centerY = (row_min + row_max)/2.0;
 }

/*A function to draw a circle (centerX, centerY) in the 'bmp' image.*/
void drawCircle(int centerX, int centerY, int *ptr, bool capture, const char *filename){
    //Data structure for storing the bitmap file
    bmpfile_t *bmp;
    
    //Data type for defining pixel colors (BGRA)
    rgb_pixel_t pixel = {0, 100, 0, 0}; 

  /* Instantiate bitmap, passing three parameters:
    - width of the image (in pixels)
    - Height of the image (in pixels)
    - Depth of the image (1 for greyscale images, 4 for colored images)
  */
    bmp = createImage(IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_DEPTH);
  
  //Draws a circle based on the given center and radius:
  int radius = 20;
  for(int x = -radius; x <= radius; x++) {
    for(int y = -radius; y <= radius; y++) {
      //If distance is smaller, point is within the circle
      if(sqrt(x*x + y*y) < radius) {
        //Color the pixel at the specified (x,y) position with the given pixel values
        bmp_set_pixel(bmp, centerX*20 + x, centerY*20 + y, pixel); 
      }
    }
  }
  
  //If image capture flag is enabled
  if (capture){
    //Save the bitmap image as .bmp file 
     bmp_save(bmp, filename);
  }

  //Updates the Shared Memory
  writeSharedMemory(ptr, bmp);
  
  //Free resources before termination
  bmp_destroy(bmp);
}

/*A function to print the error message in the  standard error output terminal*/
void error(char *msg){
  perror(msg);
}