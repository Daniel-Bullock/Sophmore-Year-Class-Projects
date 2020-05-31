/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    MosaicCanvas * mosaic = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> colors;
    map<Point<3>, int> mapColors;

    for (unsigned i = 0; i < theTiles.size(); i++) {
      colors.push_back(convertToXYZ(theTiles[i].getAverageColor()));
      mapColors[convertToXYZ(theTiles[i].getAverageColor())] = i;
    }

    KDTree<3> tree(colors);
    for (int i = 0; i < theSource.getRows(); i++) {
      for (int j = 0; j < theSource.getColumns(); j++) {
        TileImage *toSet = &theTiles[mapColors[tree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i,j)))]];
        mosaic->setTile(i, j, toSet);
      }
    }

    return mosaic;
}
