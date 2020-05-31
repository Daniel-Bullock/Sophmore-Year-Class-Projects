#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  Image picture;
  Image s1;
  Image s2;
  Image s3;
  picture.readFromFile("black_hole.png");
  s1.readFromFile("foellinger.png");
  s2.readFromFile("scared.png");
  s3.readFromFile("cplus.png");

  StickerSheet creation(picture, 4);

  creation.addSticker(s1, 100, 100);
  creation.addSticker(s2, 200, 200);
  creation.addSticker(s3, 300, 300);

  Image out = creation.render();



  out.writeToFile("myImage.png");


  return 0;
}
