#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

#include <cmath>

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */

  //double h = pow((pow(x,2)+pow(y,2)-1),3)-pow(x,2)*pow(y,3);
  //double h = 50;
  double h = sin(pow(x,2)+pow(y,2));
  return HSLAPixel(h,1,.5);
}
