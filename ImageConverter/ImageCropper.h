#ifndef IMAGECROPPER_H
#define IMAGECROPPER_H

#include <opencv2/core/core.hpp>  

class ImageCropper {

public:
	void CropToEdgePoints(cv::Mat image);
};

#endif
