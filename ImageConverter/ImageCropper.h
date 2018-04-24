#ifndef IMAGECROPPER_H
#define IMAGECROPPER_H

#include <opencv2/core/core.hpp>     // Core Fetures of Open CV
#include <opencv2/imgproc.hpp>  	// image processing functions.

class ImageCropper {

public:
	static cv::Mat CropToEdgePoints(cv::Mat image);
	static cv::Rect FindRegionOfInterest(std::vector<cv::Point2i> referencePoints);
};

#endif
