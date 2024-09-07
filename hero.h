#ifndef HERO_H
#define HERO_H

class Hero {
public:
  Hero(int x, int y, Maze * maze) : x(x), y(y), maze(maze) {
    level = 1;
  }

  int getX() const { return x; }
  int getY() const { return y; }
  int getLevel() const { return level; }

  void move(int dx, int dy) {
    x += dx;
    y += dy;
  }

  void addLevel(short lvl) { level += lvl;}
  void lowerLevel() { 
    level -= 1;
    if( level == 0 ) {
      x = -1;
      y = -1;
      printf("hero death\n");
    }
  }

  void draw() {
    if( level == 0 ) return;
    SDL_SetRenderDrawColor(renderer, 255, 50*level, 0, 255);
    SDL_Rect hero = { x * WALLSIZE, y * WALLSIZE, WALLSIZE, WALLSIZE };
    SDL_RenderFillRect(renderer, &hero);
  }

  // Randomly move the hero
  void moveRandomly() {
    if( level == 0 ) return;
    int randomDirection = rand() % 4;
    int randomStep = 1;
    switch (randomDirection) {
      case 0: // Up
        // printf("-------- Up \n");
        if (y > 0 && maze->wallID(y - 1, x) != 1) {
          y -= randomStep;
          // printf("Up - %d (%d, %d)\n", randomStep, x, y);
        }
        break;
      case 1: // Right
        // printf("-------- Right \n");
        if (x < MAZE_WIDTH - 1 && maze->wallID(y, x + 1) != 1) {
          x += randomStep;
          // printf("Right - %d (%d, %d)\n", randomStep, x, y);
        }
        break;
      case 2: // Down
        // printf("-------- Down \n");
        if (y < MAZE_HEIGHT - 1 && maze->wallID(y + 1, x) != 1) {
          y += randomStep;
          // printf("Down - %d (%d, %d)\n", randomStep, x, y); 
        }
        break;
      case 3: // Left
        // printf("-------- Left \n");
        if (x > 0 && maze->wallID(y,x - 1) != 1) {
          x -= randomStep;
          // printf("Left - %d (%d, %d)\n", randomStep, x, y);
        }
        break;
    }    
    // maze->setWall(y,x, ID);
  }

private:
  int x, y;
  int level; // level == 0 : death
  const short ID = 1000;
  Maze * maze;
};

#endif