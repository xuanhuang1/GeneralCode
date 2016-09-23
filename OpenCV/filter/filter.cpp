#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include "filter.h"

using namespace cv;

int main(int argc, char ** agrv){
  Mat src,f1,f2,f3,f4,f5,f6;
  std::cout<< "---------filter---------"<<std::endl;

  src = imread("/home/xhuang1/CS246/hw4Midterm/pro2/beyisbae.png");

  if(!src.data){
    std::cerr << "Error loading src \n"<<std::endl;
  }

  namedWindow("src", 1);
  namedWindow("blur", 2);
  namedWindow("bright", 3);
  namedWindow("ghost", 4);
  namedWindow("bright+ghost", 5);
  namedWindow("bright+blur", 6);
  namedWindow("ghost+blur", 7);

  blur(src, f1);
  bright(src, f2);
  ghost(src, f3);
  bright(f3, f4);
  bright(f2, f5);
  ghost(f1, f6);

  imshow("src", src);
  imshow("blur", f1);
  imshow("bright", f2);
  imshow("bright+blur", f5);
  imshow("bright+ghost", f4);
  imshow("ghost", f3);
  imshow("ghost+blur", f6);

  //Wirte image
  // imwrite( "secretMessage.png", result );

  waitKey(0);
  return 0;
}

