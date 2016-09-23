#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace cv;

void bright(const Mat& myImage, Mat& Result)
{
    CV_Assert(myImage.depth() == CV_8U);  // accept only uchar images

    Result.create(myImage.size(), myImage.type());
    const int nChannels = myImage.channels();

    for(int j = 1; j < myImage.rows - 2; ++j)
    {
      const uchar* previous = myImage.ptr<uchar>(j - 2);
      const uchar* current  = myImage.ptr<uchar>(j    );
      const uchar* next     = myImage.ptr<uchar>(j + 2);

      uchar* output = Result.ptr<uchar>(j);

      for(int i = nChannels; i < nChannels * (myImage.cols - 2); ++i)
        {
	  *output++ = saturate_cast<uchar>( 1.3*current[i] - 0.2*current[i - nChannels -1] - 0.1*current[i + nChannels -2] +0.1* previous[i] +0.1* next[i]);
	}
    }

    Result.row(0).setTo(Scalar(0));
    Result.row(Result.rows - 1).setTo(Scalar(0));
    Result.col(0).setTo(Scalar(0));
    Result.col(Result.cols - 1).setTo(Scalar(0));
}
