/* Your code here! */
#pragma once

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"
#include "dsets.h"
#include <vector>
#include <stack>

using namespace cs225;
using namespace std;

class SquareMaze{

public:

      SquareMaze ();

    	void makeMaze(int width, int height);

    	bool canTravel(int x, int y, int dir) const;

    	void setWall(int x, int y, int dir, bool exists);

    	vector<int> solveMaze();

    	PNG * drawMaze() const;

    	PNG * drawMazeWithSolution();



      PNG * drawMazeCreative () const;

  

       PNG * drawMazeWithSolutionCreative();


private:

      vector<bool> rights;    //the right walls as described in makeMaze doxygen
      vector<bool> downs;     //the down walls as described in makeMaze doxygen
      int width_;
      int height_;
      DisjointSets sets;
      vector<vector<vector<bool>>> walls;
      bool helper_bounds(int x, int y) const;






};


//#endif
