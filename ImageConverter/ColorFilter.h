#ifndef COLORFILTER_H
#define COLORFILTER_H

#include <opencv2/core/core.hpp>     // Core Fetures of Open CV
#include <opencv2/imgproc.hpp>  	// image processing functions.

enum Color { Blue, Green, Red, Gray };

 class ColorFilter 
{

public:
	static cv::Mat GetFilteredImage(Color color, cv::Mat image);
};

#endif
