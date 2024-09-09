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
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect hero = { x , y , WALLSIZE, WALLSIZE };
    SDL_RenderFillRect(renderer, &hero);

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

};

#endif