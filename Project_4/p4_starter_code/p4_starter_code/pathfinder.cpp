#include "image.h"
#include "deque.hpp"
#include <iostream>
#include <string>
//#include <chrono> // DELETE LATER
//#include <thread> // DELETE LATER

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
bool cutTest(Image<Pixel>, coordinates);

// Global height and width
int width, height;

int main(int argc, char *argv[]) {

  // For timing
  //using namespace std::this_thread; // DELETE LATER
  //using namespace std::chrono; // DELETE LATER

  // A note on image cordinates, the origin is at the top left corner
  // Also, indexing begins at 0, not 1

  // Read in the input and output images for later
  Image<Pixel> input = readFromFile(argv[1]);
  Image<Pixel> output = readFromFile(argv[2]);

  // Store the width and height of the image to the global variables
  width = input.width();
  height = input.height();

  // Explore coordinates at the front of the deque
  // Add next coordinates to explore to the back of the deque
  Deque<coordinates> frontier;
  coordinates start, end;

  // Find the starting position
  for (int col=0;col<width;col++) {
    for (int row=0;row<height;row++) {
      if (input(row,col) == RED) {
        start.row = row;
        start.col = col;
        std::cout << "red found" << std::endl;
        frontier.pushFront(start);
      }
    }
  }

  // Begin breadth-first-search
  bool success;
  int i = 0;
  while (true) {
    
    // Check if the frontier deque is empty (no exits)
    if (frontier.isEmpty()) {
      success = false;
      std::cout << "empty" << std::endl;
      break;
    }

    // Check if the frontier value is at the edge (exit)
    if (atEdge(frontier.front())) {
      success = true;
      end.row = frontier.front().row;
      end.col = frontier.front().col;
      break;
    }

    // Use cutTest to eliminate any coordinates from the deque that have already been explored
    if(cutTest(input,frontier.front())) {
      frontier.popFront();
      continue;
    }

    // Collect all valid next positions in the specified order
    coordinates x = frontier.front();
    if (input(x.row-1,x.col) == WHITE)
      frontier.pushBack(coordinates(x.row-1,x.col));
    if (input(x.row+1,x.col) == WHITE)
      frontier.pushBack(coordinates(x.row+1,x.col));
    if (input(x.row,x.col-1) == WHITE)
      frontier.pushBack(coordinates(x.row,x.col-1));
    if (input(x.row,x.col+1) == WHITE)
      frontier.pushBack(coordinates(x.row,x.col+1));

    // Mark the current coordinate as explored using blue and pop from the deque
    input(x.row,x.col) = BLUE;
    frontier.popFront();

    // Display output image in progress
    if (i > 1000) {
      writeToFile(input,"cycle.png"); // DELETE LATER
      std::cout << "row " << x.row << " col " << x.col << std::endl;
      i = 0;
    }
    i++;
    //sleep_for(milliseconds(500)); // DELETE LATER
  }

  // fix later, but the second test needs to be compared
  success = true;

  if (success) {

    // Set start position as red and end position as green
    input(start.row, start.col) = RED;
    input(end.row, end.col) = GREEN;

    writeToFile(input,"cycle.png"); // DELETE LATER

    // Recolor all blue squares of input to white
    for (int col=0;col<width;col++) {
      for (int row=0;row<height;row++) {
        if (input(row,col) == BLUE) input(row,col) = WHITE;
      }
    }

    // Check that the current input image matches the expected output image
    bool match = true;
    for (int col=0;col<width;col++) {
      for (int row=0;row<height;row++) {
        if (input(row,col) != output(row,col)) match = false;
      }
    }

    if (match) std::cout << "match" << std::endl;
    else std::cout << "no match" << std::endl;

  }
}

bool atEdge(coordinates x) {
  if (x.row == 0 || x.row == height-1) return true;
  if (x.col == 0 || x.col == width-1) return true;
  return false;
}

bool cutTest(Image<Pixel> input, coordinates x) {
  if(input(x.row, x.col) == BLUE)
    return true;
  else 
    return false;
}
