#include "ImageCropper.h"
#include "ReferencePointFinder.h"
#include <iostream>

#define cropOffset 20

cv::Mat ImageCropper::CropToEdgePoints(cv::Mat image) {
	
 cv::cvtColor(image, image, CV_BGR2HSV);

	ReferencePointFinder* refFinder = new ReferencePointFinder();

	std::vector<cv::Point2i> edgePoints = refFinder->GetEdgePoints(image);

	cv::Rect roi = FindRegionOfInterest(edgePoints);	
    cv::Mat crop = image(roi);
	  cv::cvtColor(crop, crop, CV_HSV2BGR);
	return crop;
}


cv::Rect ImageCropper::FindRegionOfInterest(std::vector<cv::Point2i> referencePoints)
{
	if(referencePoints.size() < 4)
	{throw std::invalid_argument("referencePoints");}

	int low_X =  referencePoints.at(0).x;
	int high_X = referencePoints.at(0).x;
	for(int i = 1; i < referencePoints.size() ; i++)
	{
		if(referencePoints.at(i).x > high_X )
		{
			high_X = referencePoints.at(i).x;
		}

		if(referencePoints.at(i).x < low_X )
		{
			low_X = referencePoints.at(i).x;
		}
	}

	int low_y =  referencePoints.at(0).y;
	int high_y  = referencePoints.at(0).y;
	for(int i = 1; i < referencePoints.size() ; i++)
	{
		if(referencePoints.at(i).y > high_y )
		{
			high_y = referencePoints.at(i).y;
		}

		if(referencePoints.at(i).y < low_y )
		{
			low_y = referencePoints.at(i).y;
		}
	}
    cv::Rect roi;
    roi.x = low_X + cropOffset; 
    roi.y = low_y + cropOffset;
    roi.height = high_y - low_y - cropOffset*2;
	roi.width = high_X - low_X - cropOffset*2;
	return roi;
}