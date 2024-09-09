#ifndef MAZE_H
#define MAZE_H

// Maze class
class Maze {
public:
  Maze(int width, int height, float frac) : width(width), height(height) {
    maze = new short*[height];
    for (int i = 0; i < height; ++i) {
      maze[i] = new short[width];
      for (int j = 0; j < width; ++j) {
        maze[i][j] = 1;
      }
    }

    // Calculate the number of walls needed
    int numRoads = MAZE_HEIGHT * MAZE_WIDTH * frac;

    // Randomly create paths
    srand(time(nullptr));
    while (numRoads > 0) {
      int i = rand() % MAZE_HEIGHT;
      int j = rand() % MAZE_WIDTH;
      if (maze[i][j]) {
        maze[i][j] = 0;
        numRoads--;
      }
    }

  }

  ~Maze() {
    for (int i = 0; i < height; ++i) delete[] maze[i];
    delete[] maze;
  }

  void setWall(int y, int x, short ID) {
    maze[y][x] = ID;
  }

  void drawMaze() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    for (int i = 0; i < MAZE_HEIGHT; ++i) {
      for (int j = 0; j < MAZE_WIDTH; ++j) {
        if (maze[i][j] == 1) {
          SDL_Rect wall = { j * WALLSIZE, i * WALLSIZE, WALLSIZE, WALLSIZE };
          SDL_RenderFillRect(renderer, &wall);
        }
      }
    }
  }

  std::pair<int, int> handleMouseClicks(SDL_Event& event) {
    if (event.type == SDL_MOUSEBUTTONDOWN) {
      int x = event.button.x / WALLSIZE;
      int y = event.button.y / WALLSIZE;

      if (x >= 0 && x < MAZE_WIDTH && y >= 0 && y < MAZE_HEIGHT && maze[y][x]) {
        maze[y][x] = 0;
        return {y,x};
      }
    }
    return {-1,-1};
  }

  short wallID(int y, int x) const {
    if( y >= 0 && x >= 0 && y < MAZE_HEIGHT - 1 && x < MAZE_WIDTH -1 ) return maze[y][x];
    return 1;
  }

  int getWidth() const { return width; }
  int getHeight() const { return height; }

private:
  int width, height;
  short** maze;
};

#endif
