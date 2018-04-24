#include "ImageCropper.h"

void ImageCropper::CropToEdgePoints(cv::Mat image) 
{
	int16_t maxWidth = image.rows;
	int16_t maxHight = image.cols;




	cv::Rect CropBox;

	cv::Mat croped = image(CropBox);
}
