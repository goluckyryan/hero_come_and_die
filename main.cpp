
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "constant.h"
#include "maze.h"
#include "creature.h"
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

bool initTTF() {
  if (TTF_Init() != 0) {
    std::cerr << "Error initializing SDL_ttf: " << TTF_GetError() << std::endl;
    return false;
  }
  return true;
}

// Load a font
bool loadFont(const char* fontPath, int fontSize) {
  font = TTF_OpenFont(fontPath, fontSize);
  if (font == nullptr) {
    std::cerr << "Error loading font: " << TTF_GetError() << std::endl;
    return false;
  }
  return true;
}

//^####################################
int main() {
  if (!initSDL() || !createWindowAndRenderer()) {
    return 1;
  }

  if (!initTTF() || !loadFont("UbuntuMono-B.ttf", WALLSIZE)) {
    return 1;
  }

  srand(time(0));

  Maze * maze = new Maze(MAZE_WIDTH, MAZE_HEIGHT, MAZE_FRAC);

  int heroDeathTime = 0;
  Hero hero(MAZE_WIDTH/2 , 0, 1, maze);
  maze->setWall(hero.getYI(), hero.getXI(), false);

  std::vector<Monster> mon;
  int monCount = 0;
  for( int i = 0;  i < NMONSTER; i++ ){
    Monster haha(rand()%MAZE_WIDTH, rand()%MAZE_HEIGHT, i, 1, maze);
    mon.push_back(haha);
    monCount ++;
    maze->setWall(mon[i].getYI(), mon[i].getXI(), false);
  }

  //^===================================
  bool running = true;
  while (running) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = false;
      }

      std::pair<int, int> coor = maze->handleMouseClicks(event);
      if( coor.first != -1){
        int lvl = rand() % 10 - 6 + coor.first / (MAZE_HEIGHT / 10);
        if( lvl > 0 ){
          Monster haha(coor.second, coor.first, monCount, lvl, maze);
          monCount++;
          mon.push_back(haha);
        }
      }
    }
    
    SDL_Delay(5);

    // another hero
    if( hero.getLevel() == 0 ) heroDeathTime += 5;

    if( hero.getLevel() == 0 && heroDeathTime > 1000 ){
      hero.setLevel(rand()%10 + 1);
      hero.setPosition(MAZE_WIDTH/2 , 0);
      heroDeathTime = 0;
      printf("New Hero comes, lvl = %d\n", hero.getLevel());
    }

    hero.move();
    maze->drawMaze();
    hero.draw();
    for( int i = 0; i < (int) mon.size(); i++) {
      mon[i].move();
      mon[i].draw();

      if( mon[i].getXI() == hero.getXI() && mon[i].getYI() == hero.getYI() ){
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
        if( mon[i].getXI() == mon[j].getXI() && mon[i].getYI() == mon[j].getYI() ){
          // if( mon[j].getLevel() == 0 ) continue;
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

      if( mon[i].getLevel() == 0 ) mon.erase(mon.begin() + i);

    }

    SDL_RenderPresent(renderer);  
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  delete maze;


  return 0;
}