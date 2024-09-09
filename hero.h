#ifndef HERO_H
#define HERO_H

#include "creature.h"

class Hero : public Creature {
public:
  Hero(int xI, int yI, int level, Maze * maze) : Creature(xI, yI, maze) {
    this->level = level;
  }

  void lowerLevel() { 
    Creature::lowerLevel();
    if( level == 0 ) {
      printf("hero death\n");
    }
  }

  void draw() {
    if( level == 0 ) return;
    SDL_SetRenderDrawColor(renderer, 255, 50*level, 0, 255);
    SDL_Rect hero = { x , y , WALLSIZE, WALLSIZE };
    SDL_RenderFillRect(renderer, &hero);
  }

private:

};

#endif