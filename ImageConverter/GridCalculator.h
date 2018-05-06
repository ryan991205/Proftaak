#ifndef GRIDCALCULATOR_H
#define GRIDCALCULATOR_H

#include <opencv2/core/core.hpp>     // Core Fetures of Open CV

class GridCalculator {
private: 
cv::Mat FilterImage(cv::Mat image, int kernelSize, int blackwhiteThreshold);
std::vector<cv::Vec2f> GenerateGridLines(cv::Mat filteredImage, int lineThreshold);
cv::Mat PlotLinesOnImage(cv::Mat image, std::vector<cv::Vec2f> lines);


public:
GridCalculator();

std::vector<cv::Vec2f> GenerateGridLines(cv::Mat input_image, cv::Mat *output_image, int kernelSize, 
                                                         int blackWhiteThreshold, int lineThreshold);

};

#endif
