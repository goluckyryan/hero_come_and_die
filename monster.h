#ifndef MONSTER_H
#define MONSTER_H

class Monster {
public:
  Monster(){};
  Monster(int x, int y, int ID, int level, Maze * maze) : x(x), y(y), ID(ID), maze(maze) {
    this->level = level;
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
      printf("monster-%d dead\n", ID);
    }
  }

  void draw() {
    if (level == 0 ) return;
    SDL_SetRenderDrawColor(renderer, 0, 30* level, 255 - 30* level, 255);
    SDL_Rect Monster = { x * WALLSIZE, y * WALLSIZE, WALLSIZE, WALLSIZE };
    SDL_RenderFillRect(renderer, &Monster);
  }

  // Randomly move the Monster
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
    // maze->setWall(y,x, level*10);
  }

private:
  int x, y;
  int level; // level == 0 : death;
  int ID;
  Maze * maze;
};

#endif