#ifndef CREATURE_H
#define CREATURE_H

#include "constant.h"
#include "maze.h"


class Creature {
public:
  Creature(int xI, int yI, Maze * maze) : xI(xI), yI(yI), maze(maze) {
    level = 1;
    direction = Direction::DOWN;
    x = xI * WALLSIZE;
    y = yI * WALLSIZE;
    dx = 0;
    dy = 1;
  }

  int getXI() const { return xI; }
  int getYI() const { return yI; }
  int getLevel() const { return level; }

  void setPosition(int xI, int yI){
    x = xI * WALLSIZE;
    y = yI * WALLSIZE;
  }

  void move() {
    if( x % WALLSIZE == 0 && y % WALLSIZE == 0 ) changeDireaction();
    x += dx;
    y += dy;
    xI = x / WALLSIZE;
    yI = y / WALLSIZE;
  }

  void setLevel(short lvl) { level = lvl;}
  void addLevel(short lvl) { level += lvl;}
  void lowerLevel() { 
    level -= 1;
    if( level == 0 ) {
      x = -100;
      y = -100;
    }
  }

  virtual void draw() {}

  void changeDireaction(){
    bool OK = false;
    //check if there any space
    if( maze->wallID(yI - 1, xI) == 1 && 
        maze->wallID(yI, xI + 1) == 1 && 
        maze->wallID(yI + 1, xI) == 1 &&
        maze->wallID(yI,xI - 1) == 1 ) {
      dx = 0;
      dy = 0;
      direction = Direction::DOWN;
      return;
    }

    do{
      int randomDirection = rand() % 4;
      direction = static_cast<Direction>(randomDirection);
      switch (direction) {
        case Direction::UP: 
          if (maze->wallID(yI - 1, xI) != 1)  {
            OK = true;
            dx = 0;
            dy = -1;
            // printf("Up - (%d, %d) (%d, %d)\n", dx, dy, x, y);
          }
          break;
        case Direction::RIGHT: 
          if (maze->wallID(yI, xI + 1) != 1) {
            OK = true;
            dx = 1;
            dy = 0;
            // printf("Right - (%d, %d) (%d, %d)\n", dx, dy, x, y);
          }
          break;
        case Direction::DOWN: 
          if ( maze->wallID(yI + 1, xI) != 1) {
            OK = true;
            dx = 0;
            dy = 1;
            // printf("Down - (%d, %d) (%d, %d)\n", dx, dy, x, y);
          }
          break;
        case Direction::LEFT: 
          if ( maze->wallID(yI,xI - 1) != 1) {
            OK = true;
            dx = -1;
            dy = 0;
            // printf("Left - (%d, %d) (%d, %d)\n", dx, dy, x, y);
          }
          break;
      }
    }while( !OK );
  }

protected:
  int xI, yI;
  int x, y;
  int dx, dy;
  int level; // level == 0 : death
  Direction direction;
  Maze * maze;
};

#endif