#include "GridCalculator.h"
#include <opencv2/imgproc.hpp>

#define MORPH_OPERATOR_BLACKHAT     0x04
#define MORPH_ELEMENT_RECT          0x00
#define BLUR_AMOUNT_PX              0x03
#define LINE_DEGREES                0x02


GridCalculator::GridCalculator()
{
}


std::vector<cv::Vec2f> GridCalculator::GenerateGridLines(cv::Mat input_image, cv::Mat *output_image, int kernelSize, 
                                                         int blackWhiteThreshold, int lineThreshold)
{
    if(kernelSize < 1 || kernelSize > 25 )
    {
        throw std::out_of_range("kernelSize");
    }

    if(blackWhiteThreshold < 0 || blackWhiteThreshold > 255)
    {
        throw std::out_of_range("threshold");
    }

    if(input_image.data == NULL)
    {
        throw std::invalid_argument("input_image");
    }

    if(output_image == NULL)
    {
        throw std::invalid_argument("output_image");
    }

    cv::Mat filteredImage           =  FilterImage(input_image,kernelSize,blackWhiteThreshold);
    std::vector<cv::Vec2f> lines    =  GenerateGridLines(filteredImage,lineThreshold);
    filteredImage                   =  PlotLinesOnImage(filteredImage, lines);

    *output_image = filteredImage;
    return lines;
}


cv::Mat GridCalculator::FilterImage(cv::Mat image, int kernelSize, int blackwhiteThreshold)
{
    cv::Mat filteredImage;
    cv::Mat element = getStructuringElement(MORPH_ELEMENT_RECT, cv::Size(2 * kernelSize + 1, 2 * kernelSize + 1), 
                                            cv::Point(kernelSize, kernelSize));

	morphologyEx(image, filteredImage, MORPH_OPERATOR_BLACKHAT, element);
    cv::cvtColor(filteredImage, filteredImage, CV_RGB2GRAY);

    std::vector<cv::Vec2f> lines;

    cv::medianBlur(filteredImage, filteredImage, BLUR_AMOUNT_PX);
	filteredImage = filteredImage > blackwhiteThreshold;

    cv::cvtColor(filteredImage, filteredImage, CV_GRAY2BGR);

    return filteredImage;    
}


std::vector<cv::Vec2f> GridCalculator::GenerateGridLines(cv::Mat filteredImage, int lineThreshold)
{
    cv::Mat grayImage;
    cv::cvtColor(filteredImage, grayImage, CV_RGB2GRAY);
    std::vector<cv::Vec2f> lines;
    cv::HoughLines(grayImage, lines, 1, CV_PI / LINE_DEGREES, lineThreshold, 0, 0);
    return lines;
}


cv::Mat GridCalculator::PlotLinesOnImage(cv::Mat image, std::vector<cv::Vec2f> lines)
{
    for (size_t i = 0; i < lines.size(); i++)
	{
		float rho = lines[i][0], theta = lines[i][1];
		cv::Point pt1, pt2;
		double a = cos(theta), b = sin(theta);
		double x0 = a * rho, y0 = b * rho;
		pt1.x = cvRound(x0 + 1000 * (-b));
		pt1.y = cvRound(y0 + 1000 * (a));
		pt2.x = cvRound(x0 - 1000 * (-b));
		pt2.y = cvRound(y0 - 1000 * (a));
		cv::line(image, pt1, pt2, cv::Scalar(0, 0, 255), 1, CV_AA);
	}
}