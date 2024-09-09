#ifndef MONSTER_H
#define MONSTER_H

#include "creature.h"
#include <chrono>

class Monster : public Creature {
public:

  Monster(int xI, int yI, int ID, int level, Maze * maze) : Creature(xI, yI, maze) {
    this->ID = ID;
    this->level = level;
    startTime = std::chrono::steady_clock::now();
    // printf("monster created (%d, %d) lvl= %d\n", xI, yI, level);
  }

  void lowerLevel() { 
    Creature::lowerLevel();
    if( level == 0 ) {
      printf("monster-%d dead\n", ID);
    }
  }

  void checkLifetime() {
    auto currentTime = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsedTime = currentTime - startTime;

    if (elapsedTime.count() > 5) { // Check if 5 seconds have passed
      level -= 1;
      startTime = std::chrono::steady_clock::now();
    }
  }

  void draw() {
    if (level == 0 ) return;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255 , 255);
    SDL_Rect Monster = { x , y , WALLSIZE, WALLSIZE };
    SDL_RenderFillRect(renderer, &Monster);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, std::to_string(level).c_str(), {0, 0, 0});
    if (textSurface == nullptr) {
      std::cerr << "Error rendering text: " << TTF_GetError() << std::endl;
      return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (textTexture == nullptr) {
      std::cerr << "Error creating text texture: " << SDL_GetError() << std::endl;
      return;
    }

    SDL_Rect textRect = { x, y, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);

  }


private:
  int ID;
  std::chrono::time_point<std::chrono::steady_clock> startTime;
};

#endif