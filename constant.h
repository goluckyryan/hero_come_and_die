#ifndef CONSTANT_H
#define CONSTANT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Maze dimensions
const int MAZE_WIDTH = 70;
const int MAZE_HEIGHT = 70;
const float MAZE_FRAC = 0.3; // 1 = all space

const int WALLSIZE = 20;

const int NMONSTER = 0;

// Create a window and renderer
SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
TTF_Font* font = nullptr;

enum Direction{
  UP,
  RIGHT,
  DOWN,
  LEFT
};


#endif