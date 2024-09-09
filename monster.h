#ifndef MONSTER_H
#define MONSTER_H

#include "creature.h"

class Monster : public Creature {
public:

  Monster(int xI, int yI, int ID, int level, Maze * maze) : Creature(xI, yI, maze) {
    this->ID = ID;
    this->level = level;
    // printf("monster created (%d, %d) lvl= %d\n", xI, yI, level);
  }

  void lowerLevel() { 
    Creature::lowerLevel();
    if( level == 0 ) {
      printf("monster-%d dead\n", ID);
    }
  }

  void draw() {
    if (level == 0 ) return;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255 , 255);
    SDL_Rect Monster = { x , y , WALLSIZE, WALLSIZE };
    SDL_RenderFillRect(renderer, &Monster);
  }


private:
  int ID;
};

#endif