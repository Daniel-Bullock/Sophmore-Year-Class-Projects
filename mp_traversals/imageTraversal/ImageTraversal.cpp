#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  moves_ = NULL;
  end_ = false;
}

ImageTraversal::Iterator::Iterator(ImageTraversal* moves, Point start, PNG png, double tolerance) {
  /** @todo [Part 1] */

    moves_ = moves;
    start_ = start;
    true_start = start_;
    png_ = png;
    tolerance_ = tolerance;


    for(unsigned i = 0; i < png_.width() * png_.height(); i++){
      seen.push_back(false);
    }

    end_ = false;

    if (bounds(start_)){
      seen[start_.x + start_.y * png_.width()] = true;
    } else {
      end_ = true;
    }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */

  //ordered points
  Point a = Point(start_.x + 1, start_.y);
  Point b = Point(start_.x, start_.y + 1);
  Point c = Point(start_.x-1, start_.y);
  Point d = Point(start_.x, start_.y - 1);


  if (bounds(a)){
    moves_->add(a);
  }
  if (bounds(b)){
     moves_->add(b);
  }
  if (bounds(c)){
     moves_->add(c);
  }
  if (bounds(d)){
    moves_->add(d);
  }


  if (moves_->empty()) {
    make_end(true);
    return *this;
  }

  Point next = moves_->pop();
  while (seen[next.x + next.y * png_.width()]) {
    if (moves_->empty()) {
      make_end(true);
      return *this;
    }
    next = moves_->pop();
  }

  start_ = next;

  seen[start_.x + start_.y * png_.width()] = true;

  return *this;

}





/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return start_;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */

  if(end_!= other.end_){
    return true;
  }
  else{
    return false;
  }

}


//helper functions



void ImageTraversal::Iterator::make_end(bool end){
  end_ = end;
}

bool ImageTraversal::Iterator::bounds(Point p) {

  if (p.x >= png_.width() || p.y >= png_.height()) {
    return false;
  }

  HSLAPixel one = (png_.getPixel(true_start.x, true_start.y));
  HSLAPixel two = (png_.getPixel(p.x, p.y));


  if (calculateDelta(one, two) >= tolerance_){
    return false;
  }else{
    return true;
  }

}
