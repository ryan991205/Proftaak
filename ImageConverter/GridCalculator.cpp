#include "GridCalculator.h"
#include <opencv2/imgproc.hpp>

//Operations is 4

cv::Mat GridCalculator::filterLines_blackHat(int kernelSize, int threshold)
{
    cv::Mat element = getStructuringElement(morph_elem, Size(2*morph_size + 1, 2*morph))


}

GridCalculator::GridCalculator(cv::Mat image, int lineThreshold)
{

}
