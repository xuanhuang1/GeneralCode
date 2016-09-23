#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;

void ghost(const Mat& myImage, Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images

    Result.create(myImage.size(), myImage.type());
    const int nChannels = myImage.channels();

    for(int j = 1; j < myImage.rows - 1; ++j)
    {
      const uchar* previous = myImage.ptr<uchar>(j - 1);
      const uchar* current  = myImage.ptr<uchar>(j    );
      const uchar* next     = myImage.ptr<uchar>(j + 1);

      uchar* output = Result.ptr<uchar>(j);

      for(int i = nChannels; i < nChannels * (myImage.cols - 1); ++i)
        {
	  if(j%180 > 90){
	    *output++ = saturate_cast<uchar>( -2*current[i] + 0.4* current[i - nChannels -1] - 2*current[i - nChannels] + 2.5*current[i + nChannels -2] +0.5* previous[i] +0.5* next[i]);
	  }else{
	    *output++ = saturate_cast<uchar>( current[i]);
	  }
	}
    }

    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows - 1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols - 1).setTo(Scalar(0));
}
