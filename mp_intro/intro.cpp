#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>

#include <math.h>



void rotate(std::string inputFile, std::string outputFile) {
  // TODO: Part 2
  cs225::PNG* original = new cs225::PNG();
  cs225::PNG* rotated = new cs225::PNG();
  original->readFromFile(inputFile);
  rotated->readFromFile(inputFile);

  for (unsigned x = 0; x < original->width(); x++) {
    for (unsigned y = 0; y < original->height(); y++) {

      rotated->getPixel(x,y) = original->getPixel(original->width() - x-1, original->height() - y-1);

    }
  }
  rotated->writeToFile(outputFile);

}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  // TODO: Part 3
  for(unsigned int x = (width / 4); x < (width / 4 * 3); x++){
      for(unsigned int y = (height / 3); y < (height / 5 * 2 ); y++){
        cs225::HSLAPixel & pix = png.getPixel(x, y);
        pix.h = 165;
        pix.l = pix.l + 0.2;
      }
  }
  for (float x = 0; x < width; x++) {
    for (float y = 0; y < height; y++) {

        cs225::HSLAPixel & pixel = png.getPixel(x, y);

        pixel.l = pixel.l * x/100;
        pixel.h = 150 * x* y / 100;


        pixel.s = .8;
        int cx = 100;
        int cy = 100;
        int ex = x-cx;
        int ey = y-cy;
        double distance = sqrt(ex*ex+ey*ey);
        if (distance >= 160){
          pixel.s = pixel.s * .2;
        }
        else{
          pixel.s = pixel.s * (1-(distance*.005));
        }


    }
  }


  return png;
}
