#include "image.h"
#include "deque.hpp"
#include <iostream>

int compress(int col, int row);
int compress(int position[]);
void expand(int compress, int position[]);
int expandRow(int compress);
int expandCol(int compress);
bool atEdge(int col, int row);
bool atEdge(int position[]);
bool atEdge(int compress);
bool contains(Deque<int> list, int compress);

int width;
int height;

int main(int argc, char *argv[]) {  
  // TODO

  // A note on image cordinates, the origin is at the top left corner
  // Also, indexing begins at 0, not 1
  Image<Pixel> input = readFromFile(argv[1]);
  width = input.width();
  height = input.height();

  Deque<int> frontier;
  Deque<int> explored;

  // Find the starting position
  for (int row=0;row<height;row++) {
    for (int col=0;col<width;col++) {
      if (input(col,row) == RED) {
        std::cout << "red found" << std::endl;
        std::cout << "row " << row << " col " << col << std::endl;
        frontier.pushFront(compress(col,row));
      }
    }
  }

  // Check that our compression/expansion system is working correctly
  std::cout << "row " << expandRow(frontier.front())
    << " col " << expandCol(frontier.front()) << std::endl;

  // Begin breadth first search
  while (!frontier.isEmpty()) {
    
    Deque<int> next;

    // Check all current values in frontier for edges and move to explored after
      // Save all of the valid and unexplored next positions to the back of the list
    while (!frontier.isEmpty()) {
      // Retrieve the column and row
      int col = expandCol(frontier.front());
      int row = expandRow(frontier.front());

      std::cout << "row " << row << " col " << col << std::endl;

      // Check whether the position is at an edge
      if (atEdge(col,row)) {
        std::cout << "at edge" << std::endl;
        //return 0;
      }

      // Collect all valid next positions in the specified order
      if (input(col,row-1) == WHITE && !contains(explored,compress(col,row-1)))
        next.pushBack(compress(col,row-1));
      if (input(col,row+1) == WHITE && !contains(explored,compress(col,row+1)))
        next.pushBack(compress(col,row+1));
      if (input(col-1,row) == WHITE && !contains(explored,compress(col-1,row)))
        next.pushBack(compress(col-1,row));
      if (input(col+1,row) == WHITE && !contains(explored,compress(col+1,row)))
        next.pushBack(compress(col+1,row));
      
      // Move position (compressed) to the explored list
      explored.pushBack(frontier.front());
      frontier.popFront();
    }

    // Once all of the positions in frontier have been searched,
    //  we can swap the next and frontier deques
    //  next will be destroyed at the end of the loop
    while(!next.isEmpty()) {
      frontier.pushBack(next.front());
      next.popFront();
    }
  }

}

bool contains(Deque<int> list, int compress) {
  Deque<int> temp = list;
  while (!temp.isEmpty()) {
    if (temp.back() == compress) return true;
    temp.popBack();
  }
  return false;
}

int compress(int col, int row) {
  int compress = row * width + col;
  return compress;
}

int compress(int position[]) {
  int col = position[0];
  int row = position[1];
  int compress = row * width + col;
  return compress;
}

void expand(int compress, int position[]) {
  position[0] = expandCol(compress);
  position[1] = expandRow(compress);
}

int expandRow(int compress) {
  int row = compress/width;
  return row;
}

int expandCol(int compress) {
  int col = compress%width;
  return col;
}

bool atEdge(int col, int row) {
  if (col == 0 || col == width) return true;
  if (row == 0 || row == height) return true;
  return false;
}

bool atEdge(int position[]) {
  int col = position[0];
  int row = position[1];
  if (col == 0 || col == width) return true;
  if (row == 0 || row == height) return true;
  return false;
}

bool atEdge(int compress) {
  int col = expandCol(compress);
  int row = expandRow(compress);
  if (col == 0 || col == width) return true;
  if (row == 0 || row == height) return true;
  return false;
}






/* 
problem.initial() returns the initial state of the problem
problem.goal(state) returns true if state is the goal state, else false
problem.actions(state) returns a list of states resulting from possible transitions from state (next state)


Psuedocode for Bredth-First-Search

function breadth_first_search (problem) {   // function returns a solution or failure
  s = problem.initial()
  if (problem.goal(s)) return s

  frontier = fifo queue with s as the first element
  explored = an empty set

  while (true) {
    if (frontier.empty()) return failure
    s = pop next state from frontier
    add s to explored
    for (each state s_next in problem.actions(s)) {
      if (s_next not in explored or frontier) {
        if (problem.goal(s_next)) then return s_next
        insert s_next into the frontier
      }
    }
  }
}


Order of actions to be considered in breadth-first-search
  1. previousRow(r-1,c)
  2. nextRow(r+1,c)
  3. previousColumn(r,c-1)
  4. nextColumn(r,c+1)
*/