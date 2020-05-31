/**
 * @file testsquaremaze.cpp
 * Performs basic tests of SquareMaze.
 * @date April 2007
 * @author Jonathan Ray
 */

#include <iostream>
#include "dsets.h"
#include "maze.h"
#include "cs225/PNG.h"

/*int main()
{
    SquareMaze m;
    m.makeMaze(10, 10);
    std::cout << "MakeMaze complete" << std::endl;

    cs225::PNG* unsolved = m.drawMaze();
    unsolved->writeToFile("unsolved.png");
    delete unsolved;
    std::cout << "drawMaze complete" << std::endl;

    std::vector<int> sol = m.solveMaze();
    std::cout << "solveMaze complete" << std::endl;

    cs225::PNG* solved = m.drawMazeWithSolution();
    solved->writeToFile("solved.png");
    delete solved;
    std::cout << "drawMazeWithSolution complete" << std::endl;

    return 0;
}*/
int main()
{
    SquareMaze m;
    m.makeMazeCreative(20, 20);
    std::cout << "MakeMaze complete" << std::endl;

    cs225::PNG* unsolved = m.drawMazeCreative();
    unsolved->writeToFile("creative.png");
    delete unsolved;
    std::cout << "drawMaze complete" << std::endl;

    /*std::vector<int> sol = m.solveMaze();
    std::cout << "solveMaze complete" << std::endl;

    cs225::PNG* solved = m.drawMazeWithSolution();
    solved->writeToFile("creative.png");
    delete solved;
    std::cout << "drawMazeWithSolution complete" << std::endl;*/

    return 0;
}
