#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "constant.h"
#include "maze.h"
#include "hero.h"
#include "monster.h"

//^###############################
// Initialize SDL
bool initSDL() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return false;
  }
  return true;
}

bool createWindowAndRenderer() {
  window = SDL_CreateWindow("Maze Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, MAZE_WIDTH * WALLSIZE, MAZE_HEIGHT * WALLSIZE, 0);
  if (window == nullptr) {
    std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
    return false;
  }

  return true;
}

int main() {
  if (!initSDL() || !createWindowAndRenderer()) {
    return 1;
  }
  srand(time(0));

  Maze * maze = new Maze(MAZE_WIDTH, MAZE_HEIGHT, MAZE_FRAC);
  Hero hero(MAZE_WIDTH/2, MAZE_HEIGHT/2, maze);
  maze->setWall(hero.getX(), hero.getY(), false);

  std::vector<Monster> mon;
  int monCount = 0;
  for( int i = 0;  i < NMONSTER; i++ ){
    Monster haha(rand()%MAZE_WIDTH, rand()%MAZE_HEIGHT, i, 1, maze);
    mon.push_back(haha);
    monCount ++;
    maze->setWall(mon[i].getX(), mon[i].getY(), false);
  }

  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }

      std::pair<int, int> coor = maze->handleMouseClicks(event);
      if( coor.first != -1){
        int lvl = rand() % 10 - 6;
        if( lvl > 0 ){
          Monster haha(coor.second, coor.first, monCount, lvl, maze);
          monCount++;
          mon.push_back(haha);
        }
      }
    }
    
    SDL_Delay(100);

    hero.moveRandomly();
    maze->drawMaze();
    hero.draw();
    for( int i = 0; i < (int) mon.size(); i++) {
      if( mon[i].getLevel() == 0 ) continue;
      mon[i].moveRandomly();
      mon[i].draw();

      if( mon[i].getX() == hero.getX() && mon[i].getY() == hero.getY() ){
        printf("mon-%d (%d) catches hero (%d)\n", i, mon[i].getLevel(), hero.getLevel());
        if( hero.getLevel() >= mon[i].getLevel() ){
          hero.addLevel( +1 );
          mon[i].lowerLevel();
          printf("hero win -> level %d\n", hero.getLevel());
        }else{
          hero.lowerLevel();
          printf("hero defeated -> level %d\n", hero.getLevel());
        }
      }

      for( int j = 0; j < i; j++) {
        if( mon[i].getX() == mon[j].getX() && mon[i].getY() == mon[j].getY() ){
          if( mon[j].getLevel() == 0 ) continue;
          printf("mon-%d (%d) meet mon-%d (%d)\n", i, mon[i].getLevel(), j, mon[j].getLevel());
          if( mon[j].getLevel() >= mon[i].getLevel() ){
            mon[j].addLevel(+1);
            mon[i].lowerLevel();
            printf("mon-%d win -> level %d \n", j, mon[j].getLevel());
            printf("mon-%d loss -> level %d \n", i, mon[i].getLevel());
          }else{
            mon[i].addLevel(+1);
            mon[j].lowerLevel();
            printf("mon-%d win -> level %d \n", i, mon[i].getLevel());
            printf("mon-%d loss -> level %d \n", j, mon[j].getLevel());
          }
        }
      }

    }

    SDL_RenderPresent(renderer);  
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  delete maze;


  return 0;
}