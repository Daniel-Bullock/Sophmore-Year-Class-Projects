#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "Image.h"
#include <string>
using std::string;


  void Image::lighten(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          getPixel(x, y).l += 0.1;
          if(getPixel(x, y).l > 1){
            getPixel(x, y).l = 1;
          }else if(getPixel(x, y).l < 0){
            getPixel(x, y).l = 0;
          }
      }
    }
  }
  void Image::lighten(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          getPixel(x, y).l += amount;
          if(getPixel(x, y).l > 1){
            getPixel(x, y).l = 1;
          }else if(getPixel(x, y).l < 0){
            getPixel(x, y).l = 0;
          }
      }
    }
  }
  void Image::darken(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          getPixel(x, y).l -= 0.1;
          if(getPixel(x, y).l > 1){
            getPixel(x, y).l = 1;
          }else if(getPixel(x, y).l < 0){
            getPixel(x, y).l = 0;
          }
      }
    }
  }
  void Image::darken(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          getPixel(x, y).l -= amount;
          if(getPixel(x, y).l > 1){
            getPixel(x, y).l = 1;
          }else if(getPixel(x, y).l < 0){
            getPixel(x, y).l = 0;
          }
      }
    }
  }
  void Image::saturate(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          getPixel(x, y).s += 0.1;
          if(getPixel(x, y).s > 1){
            getPixel(x, y).s = 1;
          }else if(getPixel(x, y).s < 0){
            getPixel(x, y).s = 0;
          }
      }
    }
  }
  void Image::saturate(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          getPixel(x, y).s += amount;
          if(getPixel(x, y).s > 1){
            getPixel(x, y).s = 1;
          }else if(getPixel(x, y).s < 0){
            getPixel(x, y).s = 0;
          }
      }
    }
  }
  void Image::desaturate(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          getPixel(x, y).s -= 0.1;
          if(getPixel(x, y).s > 1){
            getPixel(x, y).s = 1;
          }else if(getPixel(x, y).s < 0){
            getPixel(x, y).s = 0;
          }
      }
    }
  }
  void Image::desaturate(double amount){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          getPixel(x, y).s -= amount;
          if(getPixel(x, y).s > 1){
            getPixel(x, y).s = 1;
          }else if(getPixel(x, y).s < 0){
            getPixel(x, y).s = 0;
          }
      }
    }
  }
  void Image::grayscale(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
        getPixel(x, y).s = 0;
      }
    }
  }
  void Image::rotateColor(double degrees){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {
          getPixel(x, y).h += degrees;
          if(getPixel(x, y).h > 360){
            getPixel(x, y).h -= 360;
          }else if(getPixel(x, y).h < 0){
            getPixel(x, y).h += 360;
          }
      }
    }
  }
  void Image::illinify(){
    for (unsigned x = 0; x < width(); x++) {
      for (unsigned y = 0; y < height(); y++) {

        if(getPixel(x, y).h > 102.5 && getPixel(x, y).h < 282.5){
          getPixel(x, y).h = 216;
        }
        else{
          getPixel(x, y).h = 11;
        }


      }
    }
  }
  void Image::scale(double factor){
      unsigned int scaledw = this->width() * factor;
      unsigned int scaledh = this->height() * factor;
      PNG * newpic = new PNG(scaledw, scaledh);

      for (unsigned int x = 0; x < scaledw; x++){
        for (unsigned int y = 0; y < scaledh; y++){

          cs225::HSLAPixel & scaledpix = newpic->getPixel(x, y);
          unsigned int xadjust = this->width() * x / scaledw; //operation order matters for some reason???
          unsigned int yadjust = this->height() * y / scaledh;
          scaledpix = this->getPixel(xadjust, yadjust);

        }
      }

      //scaledpix->resize(scaledw,scaledh);

      this->resize(scaledw, scaledh);


      for (unsigned int x = 0; x < scaledw; x++){
        for (unsigned int y = 0; y < scaledh; y++){
          cs225::HSLAPixel & oldp = newpic->getPixel(x, y);
          cs225::HSLAPixel & newp = this->getPixel(x, y);
          newp = oldp;
        }
      }
      delete newpic;
      newpic = NULL;


  }

  void Image::scale(unsigned w,unsigned h){
    double wxh = (int)w/(double)width();
    double hxw = (int)h/(double)height();
    if(wxh < hxw){
      scale(wxh);
    }
    else{
      scale(hxw);
    }
  }
