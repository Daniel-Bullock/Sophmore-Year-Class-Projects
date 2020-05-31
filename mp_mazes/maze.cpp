#include "maze.h"
#include <iostream>
#include <time.h>
#include <math.h>


SquareMaze::SquareMaze() {
  width_ = 0;
  height_ = 0;
  DisjointSets sets;
}

void SquareMaze::makeMaze(int width, int height) {
  width_ = width;
  height_ = height;

  //fill vector
  walls = vector<vector<vector<bool>>>(width);
  for (int x=0; x<width_; x++) {
    walls[x] = vector<vector<bool>>(height);
    for (int y=0; y<height_; y++) {
      walls[x][y] = vector<bool>(2);
      walls[x][y][0] = true;
      walls[x][y][1] = true;
    }
  }

  int size = width * height;
  sets.addelements(size);

  //srand(time(NULL));
  int newsets = width*height;
  while (newsets > 1) {
    int wrand = rand() % width;
    int hrand = rand() % height;
    int fiftyfifty = rand() % 2;

    if (walls[wrand][hrand][fiftyfifty] == true) {
      if (fiftyfifty == 1 && hrand < height_-1) {
        if (sets.find(wrand*height_+hrand)!= sets.find(wrand*height+hrand+1)) {
          newsets--;
          sets.setunion(wrand*height_+hrand, wrand*height+hrand+1);
          walls[wrand][hrand][fiftyfifty] = false;
        }
      } else if (fiftyfifty == 0 && wrand < width_-1) {
          if (sets.find(wrand*height_+hrand) != sets.find((wrand+1)*height+hrand)) {
            newsets--;
            sets.setunion(wrand*height_+hrand, (wrand+1)*height+hrand);
            walls[wrand][hrand][fiftyfifty] = false;
          }
      }
    }
  }
}

bool SquareMaze::helper_bounds(int x, int y) const {
  if (x >= 0 && x < width_ && y >= 0 && y < height_) {
    return true;
  } else {
    return false;
  }
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
  // dir = 0, rightward step (+1 to x)
  // dir = 1, downward step (+1 to y)
  // dir = 2, a leftward step (-1 to x)
  // dir = 3, an upward step (-1 to y)
  // cannot step off maze or through a wall
  //std::cout << x << " " << y << std::endl;
  if(!helper_bounds(x,y)){
    return false;
  }

  if (dir == 3 && helper_bounds(x, y-1) && walls[x][y-1][1] == false) {
    return true;
  } else if(dir == 2 && helper_bounds(x-1, y) && walls[x-1][y][0]==false) {
    return true;
  } else if(dir == 1 && helper_bounds(x, y+1) && walls[x][y][1] == false) {
    return true;
  } else if(dir == 0 && helper_bounds(x+1, y) && walls[x][y][0] == false) {
    return true;
  } else{
    return false;
  }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
  // This function should be fast (constant time)
  // setWall should not prevent cycles from occurring, but should simply set a wall to be present or not present
  if (x >= 0 && y >= 0 && x < width_ && y < height_) {
      walls[x][y][dir] = exists;
  }
}


vector<int> SquareMaze::solveMaze() {
  // dir = 0, rightward step (+1 to x)
  // dir = 1, downward step (+1 to y)
  // dir = 2, a leftward step (-1 to x)
  // dir = 3, an upward step (-1 to y)
  vector<vector<bool>> visited = vector<vector<bool>>(width_);
  for (int x = 0; x < width_; x++) {
    visited[x] = vector<bool>(height_);
    for (int y = 0; y<  height_; y++) {
      visited[x][y] = false;
    }
  }

  stack<vector<int>> s;
  stack<int> sDirection;
  vector<int> bottomXs;
  vector<vector<int>> pathsToBottom;
  vector<bool> visitedBottoms = vector<bool>(width_);
  s.push({0,0});
  visited[0][0] = true;

  while (pathsToBottom.size() != (unsigned)width_) {
    int x = s.top()[0];
    int y = s.top()[1];

    if (canTravel(x, y, 0) && !visited[x+1][y]) {
      s.push({x+1, y});
      sDirection.push(0);
      visited[x+1][y] = true;
    } else if (canTravel(x, y, 1) && !visited[x][y+1]) {
      s.push({x, y+1});
      sDirection.push(1);
      visited[x][y+1] = true;
    } else if (canTravel(x, y, 2) && !visited[x-1][y]) {
      s.push({x-1, y});
      sDirection.push(2);
      visited[x-1][y] = true;
    } else if (canTravel(x, y, 3) && !visited[x][y-1]) {
      s.push({x, y-1});
      sDirection.push(3);
      visited[x][y-1] = true;
    } else {
      while ((!canTravel(x,y,0) || visited[x+1][y]) &&
      (!canTravel(x,y,1) || visited[x][y+1])
       && (!canTravel(x,y,2) || visited[x-1][y])
       && (!canTravel(x,y,3) || visited[x][y-1])) {
        s.pop();
        sDirection.pop();

        x = s.top()[0];
        y = s.top()[1];
      }
    }

    if (s.top()[1] == height_-1 && !visitedBottoms[s.top()[0]]) {
      visitedBottoms[s.top()[0]] = true;
      pathsToBottom.push_back({});
      bottomXs.push_back(s.top()[0]);

      int x = pathsToBottom.size()-1;
      while (!sDirection.empty()) {
        pathsToBottom[x].insert(pathsToBottom[x].begin(), sDirection.top());
        //s.pop();
        sDirection.pop();
      }

      for (unsigned i = 0; i < pathsToBottom[x].size(); i++) {
        sDirection.push(pathsToBottom[x][i]);
      }
    }
  }

  unsigned longestPathToBottom = 0;
  for (unsigned i = 0; i < pathsToBottom.size(); i++) {
    if (pathsToBottom[longestPathToBottom].size() < pathsToBottom[i].size() ||
        (pathsToBottom[longestPathToBottom].size() == pathsToBottom[i].size() &&
        bottomXs[longestPathToBottom] > bottomXs[i])) {
      longestPathToBottom = i;
    }
  }

  return pathsToBottom[longestPathToBottom];
}

PNG * SquareMaze::drawMaze() const{
    // Set the dimensions of the PNG to (width*10+1,height*10+1)
    // right wall exists, then blacken the pixels with coordinates ((x+1)*10,y*10+k) for k from 0 to 10
    // bottom wall exists, then blacken the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10
    unsigned int w = (width_ * 10) + 1;
    unsigned int h = (height_ * 10) + 1;
    PNG * maze = new PNG(w, h);

    for(unsigned int i = 10; i < w; i++){
      maze->getPixel(i, 0) = HSLAPixel(0,0,0,1);
    }

    for(unsigned int i = 0; i < h; i++){
      maze->getPixel(0,i) = HSLAPixel(0,0,0,1);
    }

    for (unsigned i = 0; i < unsigned(width_); i++) {
      for (unsigned j = 0; j < unsigned(height_); j++) {
        if (walls[i][j][0]) {
          unsigned x = (i+1) * 10;
          unsigned y = j * 10;
          for (int k=0; k<=10; k++) {
            maze->getPixel(x, y+k) = HSLAPixel(0,0,0,1);
          }
        }

        if (walls[i][j][1]) {
          unsigned x = i * 10;
          unsigned y = (j+1) * 10;
          for (int k=0; k<=10; k++) {
            maze->getPixel(x+k, y) = HSLAPixel(0,0,0,1);
          }
        }
      }
    }

    //Might be accidentally removing edges from bottom
    //If so, lets paint over it
    for (unsigned i = 0; i < w; i++) {
        maze->getPixel(i, height_*10) = HSLAPixel(0,0,0,1);
    }

    return maze;
}

PNG * SquareMaze::drawMazeWithSolution() {
  // Start at pixel (5,5)
  // Red is 0,1,0.5,1 in HSLA
  // Make the exit by undoing the bottom wall of the destination square:
  //      call the destination maze coordinates (x,y),
  //      and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9

  PNG * maze = drawMaze();
  vector<int> directions = solveMaze();

  unsigned x = 5;
  unsigned y = 5;
  for (unsigned i = 0; i < directions.size(); i++) {
    if (directions[i] == 0) {
      for (unsigned i = x; i < x + 10; i++) {
        maze->getPixel(i, y) = HSLAPixel(0,1,0.5,1); // Red
      }
      x += 10;
    } else if (directions[i] == 1) {
      for (unsigned i = y; i < y + 10; i++) {
        maze->getPixel(x, i) = HSLAPixel(0,1,0.5,1); // Red
      }
      y += 10;
    } else if (directions[i] == 2) {
      for (unsigned i = x; i > x - 10; i--) {
        maze->getPixel(i, y) = HSLAPixel(0,1,0.5,1); // Red
      }
      x -= 10;
    } else {
      for (unsigned i = y; i > y - 10; i--) {
        maze->getPixel(x, i) = HSLAPixel(0,1,0.5,1); // Red
      }
      y -= 10;
    }
  }

  //cout << x << " " << y << std::endl;
  maze->getPixel(x, y) = HSLAPixel(0,1,0.5,1);
  y += 5;
  x -= 4;

  for (unsigned i = x; i < x+9; i++) {
      maze->getPixel(i, y) = HSLAPixel(0,0,1,1);
  }

  return maze;
}

PNG * SquareMaze::drawMazeCreative () const {

  PNG* m = new PNG(width_ * 10 + 1, height_ * 10 + 1);

  HSLAPixel greenpixel (143,.70, 0.56, 1.0);

  for (unsigned i = 10; i < m->width(); i++) {
    m->getPixel(i, 0) = greenpixel;
  }

  for (unsigned i = 0; i < m->height(); i++) {
    //left borde
    m->getPixel(0, i) = greenpixel;
  }

  for(int i = 0; i < width_; i++) {
    for(int j = 0; j < height_; j++) {

      HSLAPixel sin(pow(i,2)+pow(j,2), 1, 0.74, 1);

      if (walls[i][j][0]) {
        for (int k = 0; k<=10; k++) {
           m->getPixel((i + 1) * 10, j * 10 + k) = sin;
        }
      }

      if (walls[i][j][1]) {
        for (int k = 0; k <= 10; k++) {
          // INSERT COLOR OF WALL
          m->getPixel(i * 10 + k, (j + 1) * 10) = sin;
        }
      }

    }
  }

  for (unsigned i = 0; i < m->width(); i++){
    m->getPixel(i, m->height() - 1) = greenpixel;
  }
  for (unsigned i = (m->width())/2; i < m->width(); i++){
    m->getPixel(i, (m->height())/1.5) = greenpixel;
  }

  for (unsigned i = 0; i < (m->height())/1.5; i++){
    m->getPixel((m->width())/2-1, i) = greenpixel;
  }
  for (unsigned i = (m->height())/2; i < m->height(); i++){
    m->getPixel(m->width() - 1, i) = greenpixel;
  }

  for(unsigned i = (m->width())/2;i<m->width();i++){
    for (unsigned j = 0; j < m->height()/1.5; j++){
      m->getPixel(i, j) = HSLAPixel(0,0,0,1);
    }
  }

  return m;
}






PNG * SquareMaze::drawMazeWithSolutionCreative() {
  // Start at pixel (5,5)
  // Red is 0,1,0.5,1 in HSLA
  // Make the exit by undoing the bottom wall of the destination square:
  //      call the destination maze coordinates (x,y),
  //      and whiten the pixels with coordinates (x*10+k, (y+1)*10) for k from 1 to 9

  PNG * maze = drawMazeCreative();
  vector<int> directions = solveMaze();

  unsigned x = 5;
  unsigned y = 5;
  for (unsigned i = 0; i < directions.size(); i++) {
    if (directions[i] == 0) {
      for (unsigned i = x; i < x + 10; i++) {
        maze->getPixel(i, y) = HSLAPixel(0,1,0.5,1); // Red
      }
      x += 10;
    } else if (directions[i] == 1) {
      for (unsigned i = y; i < y + 10; i++) {
        maze->getPixel(x, i) = HSLAPixel(0,1,0.5,1); // Red
      }
      y += 10;
    } else if (directions[i] == 2) {
      for (unsigned i = x; i > x - 10; i--) {
        maze->getPixel(i, y) = HSLAPixel(0,1,0.5,1); // Red
      }
      x -= 10;
    } else {
      for (unsigned i = y; i > y - 10; i--) {
        maze->getPixel(x, i) = HSLAPixel(0,1,0.5,1); // Red
      }
      y -= 10;
    }
  }

  //cout << x << " " << y << std::endl;
  maze->getPixel(x, y) = HSLAPixel(0,1,0.5,1);
  y += 5;
  x -= 4;

  for (unsigned i = x; i < x+9; i++) {
      maze->getPixel(i, y) = HSLAPixel(0,0,1,1);
  }

  return maze;
}
