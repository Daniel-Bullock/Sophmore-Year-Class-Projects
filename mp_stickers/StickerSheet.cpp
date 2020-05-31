#include "Image.h"
#include "StickerSheet.h"


StickerSheet::StickerSheet (const Image &picture, unsigned max){
    num_stick = 0;
    max_stick = max;
    pic = new Image(picture);
    //*pic = picture;


    x_ = new unsigned[max_stick];
    y_ = new unsigned[max_stick];

    stickers = new Image*[max_stick];
    for(unsigned m = 0; m < max; m++){
        stickers[m] = NULL;

        x_[m] = 0;
        y_[m] = 0;
    }


}
void StickerSheet::delete_(){
  for(unsigned m = 0;m < max_stick; m++){
    if(stickers[m] != NULL){
      delete stickers[m];
    }
  }
  delete[] stickers;
  //delete pic;
  delete[] x_;
  delete[] y_;

}
StickerSheet::~StickerSheet (){
  delete_();
}
void StickerSheet::duplicate(const StickerSheet &other){
  num_stick = other.num_stick;
  max_stick = other.max_stick;
  x_ = new unsigned[max_stick];
  y_ = new unsigned[max_stick];
  stickers = new Image*[max_stick];
  pic = new Image(*other.pic);
  //*(pic) = *(other.pic);
  for(unsigned m = 0; m < max_stick; m++){
      if (other.stickers[m] != nullptr) {
        stickers[m] = new Image(*other.stickers[m]);
      } else {
        stickers[m] = nullptr;
      }
      //*(stickers[m]) = *(other.stickers[m]);
      x_[m] = other.x_[m];
      y_[m] = other.y_[m];


  }
}
StickerSheet::StickerSheet (const StickerSheet &other){ //deep copying?
  duplicate(other);

}
const StickerSheet & 	StickerSheet::operator= (const StickerSheet &other){
  if(this == &other){

    return *this;

  }else{
    delete pic;
    delete_();
    duplicate(other);
    return *this;

  }
}

void 	StickerSheet::changeMaxStickers (unsigned max){

      if(max == max_stick){
              return;
      }
      Image ** tempstick = new Image*[max];
      for(unsigned m = 0; m <max;m++){
          tempstick[m] = NULL;
      }
      unsigned * xtemp = new unsigned[max];
      unsigned * ytemp = new unsigned[max];
      if(num_stick < max){
            for(unsigned m = 0; m < num_stick; m++){
                //if(stickers[m] != NULL){
                        tempstick[m] = new Image(*stickers[m]);
                        xtemp[m] = x_[m];
                        ytemp[m] = y_[m];
                //}
            }
      }
      else{
          for(unsigned m = 0; m < num_stick; m++){
              //if(stickers[m] != NULL){
                tempstick[m] = new Image(*stickers[m]);
                xtemp[m] = x_[m];
                ytemp[m] = y_[m];
              //}
          }
          num_stick = max;
      }
      delete_();
      x_ = xtemp;
      //delete[] xtemp;
      xtemp = NULL;
      y_ = ytemp;
      //delete[] ytemp;
      ytemp = NULL;
      max_stick = max;
      stickers = tempstick;
      //delete[] tempstick;
      tempstick = NULL;


}



int 	StickerSheet::addSticker (Image &sticker, unsigned x, unsigned y){

    if(num_stick < max_stick){
      if(stickers[num_stick] == NULL){
        stickers[num_stick] = new Image(sticker);
      }

      x_[num_stick] = x;
      y_[num_stick] = y;
      num_stick ++;
      return num_stick - 1;
   }
   return -1;

}
bool 	StickerSheet::translate (unsigned index, unsigned x, unsigned y){
  if(index < num_stick){
    x_[index] = x;
    y_[index] = y;
  }
  return false;
}
void 	StickerSheet::removeSticker (unsigned index){

  delete stickers[index];
	for (unsigned i = index; i < max_stick - 1; i++) {
		stickers[i] = stickers[i + 1];
		x_[i] = x_[i + 1];
		y_[i] = y_[i + 1];
	}
	stickers[max_stick - 1] = NULL;
	x_[max_stick- 1] = 0;
	y_[max_stick - 1] = 0;
	num_stick--;

}
Image * 	StickerSheet::getSticker (unsigned index){
  if(index < num_stick){
    return stickers[index];

  }
  return NULL;
}
Image 	StickerSheet::render () const{

  Image resultpic(*pic);

  unsigned w = resultpic.width();
  unsigned h = resultpic.height();

  for(unsigned m = 0; m < max_stick; m++){

    if(stickers[m] != NULL){
      if(w < x_[m] + stickers[m]->width()){
        w = x_[m] + stickers[m]->width();
      }
      if(h < y_[m] + stickers[m]->height()){
        h = y_[m] + stickers[m]->height();
      }
    }
  }


  resultpic.resize(w,h);


  for(unsigned m = 0; m < max_stick; m++){
    if(stickers[m] != NULL){
      for(unsigned x= x_[m]; x< (x_[m] + stickers[m]->width());x++){
        for(unsigned y = y_[m]; y <(y_[m] + stickers[m]->height());y++){
            if(stickers[m]->getPixel(x-x_[m],y-y_[m]).a != 0){
              resultpic.getPixel(x,y) = stickers[m]->getPixel(x-x_[m],y-y_[m]);
            }

        }
      }
    }
  }



  return resultpic;

}
