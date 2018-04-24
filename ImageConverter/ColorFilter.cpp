
#include "ColorFilter.h"
#include <opencv2/imgproc.hpp>  	// image processing functions.

cv::Mat ColorFilter::GetFilteredImage(Color color, cv::Mat image) 
{
	// TODO: ADD COLOR VALUES TO THE CORRECT COLOR ! 

  cv::Mat lowFilteredImage;
  cv::Mat highFilteredImage;

  switch(color)
  {
	case Blue:
		cv::inRange(image, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowFilteredImage);
  		cv::inRange(image, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), highFilteredImage);
	break;

	case Green:
		cv::inRange(image, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowFilteredImage);
  		cv::inRange(image, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), highFilteredImage);
	break;

	case Red:
		cv::inRange(image, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowFilteredImage);
  		cv::inRange(image, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), highFilteredImage);
	break;

	case Gray:
		cv::inRange(image, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), lowFilteredImage);
  		cv::inRange(image, cv::Scalar(160, 100, 100), cv::Scalar(179, 255, 255), highFilteredImage);
	break;
  }

  // combine low/high filter
  cv::Mat FileredImage;
  cv::addWeighted( lowFilteredImage, 1.0, highFilteredImage, 1.0, 0.0, FileredImage);

  return FileredImage;











}
