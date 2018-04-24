#include <opencv2/core.hpp>           // data structures and arithmetic routines.
#include <opencv2/highgui.hpp>        // Image display, sliders, buttons, mouse & IO.
#include <opencv2/imgproc.hpp>        // image processing functions.
#include <opencv2/features2d.hpp>     // two dimentsional feature tracking support.
#include "opencv2/imgcodecs.hpp"

#include "ReferencePointFinder.h"
#include "ColorFilter.h"
#include <iostream>


#define EXPECTED_REFERENCEVECTORS 4



cv::Point2i ReferencePointFinder::FindRefPoint(cv::Mat image)
{
	std::vector<cv::Vec3f> referenceVectors;
	cv::HoughCircles(image, referenceVectors, CV_HOUGH_GRADIENT, 1, image.rows/8, 100, 20, 0, 0);

	if(referenceVectors.size() != 1)
	{
		throw std::out_of_range("referenceVectors");
	}

	cv::Point2i center(std::ceil(referenceVectors[0][0]), std::ceil(referenceVectors[0][1]));
	return center;
}


cv::Point2i ReferencePointFinder::GetBeginPointMaze(cv::Mat image) 
{
	cv::Mat filteredImage = ColorFilter::GetFilteredImage(Blue,image);
	return FindRefPoint(filteredImage);
}


cv::Point2i ReferencePointFinder::GetEndPointMaze(cv::Mat image)
{
	cv::Mat filteredImage = ColorFilter::GetFilteredImage(Green,image);
	return FindRefPoint(filteredImage);
}


std::vector<cv::Point2i> ReferencePointFinder::GetEdgePoints(cv::Mat image) 
{
	cv::Mat filteredImage = ColorFilter::GetFilteredImage(Red,image);

	std::vector<cv::Vec3f> referenceVectors;
	cv::HoughCircles(filteredImage, referenceVectors, CV_HOUGH_GRADIENT, 1, filteredImage.rows/8, 100, 20, 0, 0);
	

  	if(referenceVectors.size() != EXPECTED_REFERENCEVECTORS)
  	{
		
    	throw std::out_of_range("referenceVectors");
  	}

 	 std::vector<cv::Point2i> referencePoints;

  	// calculate centerPoint of referencepoints
  	for(size_t current_referenceVectors = 0; current_referenceVectors < referenceVectors.size(); ++current_referenceVectors) 
 	{
 		cv::Point2i center(std::ceil(referenceVectors[current_referenceVectors][0]), std::ceil(referenceVectors[current_referenceVectors][1]));
    	referencePoints.push_back(center);
  }
  return referencePoints;
}










