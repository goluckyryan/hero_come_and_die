#ifndef CONSTANT_H
#define CONSTANT_H

// Maze dimensions
const int MAZE_WIDTH = 100;
const int MAZE_HEIGHT = 100;
const float MAZE_FRAC = 0.3; // 1 = all space

const int WALLSIZE = 10;

const int NMONSTER = 0;

// Create a window and renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

enum Direction{
  UP,
  RIGHT,
  DOWN,
  LEFT
};


#endif