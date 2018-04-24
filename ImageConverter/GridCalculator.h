#ifndef GRIDCALCULATOR_H
#define GRIDCALCULATOR_H

#include <opencv2/core/core.hpp>     // Core Fetures of Open CV

class GridCalculator {
private: 
cv::Mat filterLines_blackHat(int kernelSize, int threshold);


public:
GridCalculator(cv::Mat image, int lineThreshold);


};

#endif
