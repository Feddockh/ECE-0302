#include "image.h"
#include "deque.hpp"
#include <iostream>
#include <string>

// Coordinates datatype definition
struct coordinates{
  int row, col;
  coordinates() {};
  coordinates(int r, int c) {
    row = r;
    col = c;
  }
};

// Functions
bool atEdge(coordinates);
bool cutTest(Image<Pixel> &, coordinates);

// Global height and width
int width, height;

int main(int argc, char *argv[]) {

  // A note on image cordinates, the origin is at the top left corner
  // Also, indexing begins at 0, not 1

  // Read in the input and output images for later
  Image<Pixel> input;
  try {
    input = readFromFile(argv[1]);
  } catch (const std::exception& e) {
    std::cerr << "Error reading image from file" << std::endl;
    return EXIT_FAILURE;
  }

  // Store the width and height of the image to the global variables
  width = input.width();
  height = input.height();

  // Explore coordinates at the front of the deque
  // Add next coordinates to explore to the back of the deque
  Deque<coordinates> frontier;
  coordinates start, end;

  // Find the starting position by iterating through all of the rows and columns
  int redSquares = 0;
  for (int col=0;col<width;col++) {
    for (int row=0;row<height;row++) {

      // Check if there are any invalid pixel colors in the maze
      if (input(row,col) != WHITE && input(row,col) != BLACK && input(row,col) != RED) {
        std::cerr << "Error - Invalid pixel colors in maze" << std::endl;
        return EXIT_FAILURE;
      }

      // Find starting positions (red squares)
      if (input(row,col) == RED) {

        // Check if there are too many starting positions
        redSquares++;
        if (redSquares > 1) {
          std::cerr << "Error - Too many red pixels (start positions) in image" << std::endl;
          return EXIT_FAILURE;
        }

        // Set the starting row and column
        start.row = row;
        start.col = col;

        // Try to push the starting position to the frontier deque
        try {
          frontier.pushFront(start);
        } catch (const std::exception& e) {
          std::cerr << "Error adding start position to frontier deque" << std::endl;
          return EXIT_FAILURE;
        }
      }
    }
  }

  // Begin breadth-first-search
  bool exitFound;
  while (true) {

    // Check if the frontier deque is empty (no exits)
    try {
      if (frontier.isEmpty()) {
        exitFound = false;
        break;
      }
    } catch (const std::exception& e) {
      std::cerr << "Error determining whether the deque was empty" << std::endl;
      return EXIT_FAILURE;
    }

    // Check if the frontier value is at the edge (exit)
    try {
      if (atEdge(frontier.front())) {
        exitFound = true;
        end.row = frontier.front().row;
        end.col = frontier.front().col;
        break;
      }
    } catch (const std::exception& e) {
      std::cerr << "Error reading from frontier deque" << std::endl;
      return EXIT_FAILURE;
    }

    // Use cutTest to eliminate any coordinates from the deque that have already been explored
    if(cutTest(input,frontier.front())) {
      try {
        frontier.popFront();
      } catch (const std::exception& e) {
        std::cerr << "Error popping the front of the frontier deque" << std::endl;
        return EXIT_FAILURE;
      }
      continue;
    }

    // Collect all valid next positions in the specified order
    coordinates x = frontier.front();
    try {
      if (input(x.row-1,x.col) == WHITE)
        frontier.pushBack(coordinates(x.row-1,x.col));
      if (input(x.row+1,x.col) == WHITE)
        frontier.pushBack(coordinates(x.row+1,x.col));
      if (input(x.row,x.col-1) == WHITE)
        frontier.pushBack(coordinates(x.row,x.col-1));
      if (input(x.row,x.col+1) == WHITE)
        frontier.pushBack(coordinates(x.row,x.col+1));
    } catch (const std::exception& e) {
      std::cerr << "Error reading pixel color or pushing to back of the frontier deque" << std::endl;
      return EXIT_FAILURE;
    }

    // Mark the current coordinate as explored using blue and pop from the deque
    try {
      input(x.row,x.col) = BLUE;
      frontier.popFront();
    } catch (const std::exception& e) {
      std::cerr << "Error setting pixel color or popping front of frontier deque" << std::endl;
      return EXIT_FAILURE;
    }
  }

  // Reset the start position to red
  input(start.row, start.col) = RED;

  // Set the end position as green (only if exit was found)
  if (exitFound) input(end.row, end.col) = GREEN;

  // Recolor all blue squares of input to white
  for (int col=0;col<width;col++) {
    for (int row=0;row<height;row++) {
      if (input(row,col) == BLUE) input(row,col) = WHITE;
    }
  }

  /* Do I have to delete this check?
  // Check that the current input image matches the expected output image
  bool match = true;
  Image<Pixel> output = readFromFile(argv[2]);
  for (int col=0;col<width;col++) {
    for (int row=0;row<height;row++) {
      if (input(row,col) != output(row,col)) match = false;
    }
  }

  if (match) std::cout << "Solution Found" << std::endl;
  else std::cout << "No Solution Found" << std::endl;
  */


  // Print out whether or not a solution was found
  if (exitFound) std::cout << "Solution Found" << std::endl;
  else std::cout << "No Solution Found" << std::endl;

  // Print out result with the specified file name
  try {
    writeToFile(input, argv[2]);
  } catch (const std::exception& e) {
    std::cerr << "Error writing output file" << std::endl;
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

bool atEdge(coordinates x) {
  if (x.row == 0 || x.row == height-1) return true;
  if (x.col == 0 || x.col == width-1) return true;
  return false;
}

bool cutTest(Image<Pixel> &input, coordinates x) {
  if(input(x.row, x.col) == BLUE)
    return true;
  else 
    return false;
}


/*
Questions to ask
- Read as "maze_input.png" and print out as "maze_output.png"?
- Does "No solution found" mean exit failure because error?
- What is standard error?
- Does std::exception catch all exceptions thrown?

Things to add:
- Exit failure tests
  - Program cannot read/write images
  - Input image contains colors other than black, white, or red
  - Input maze has more than one red pixel
*/

/*
try {
} catch (const std::exception& e) {
}
*/