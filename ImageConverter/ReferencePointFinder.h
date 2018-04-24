#ifndef REFERENCEPOINTFINDER_H
#define REFERENCEPOINTFINDER_H

#include <vector>
#include <opencv2/core/core.hpp>

class ReferencePointFinder 
{
private:
	cv::Point2i FindRefPoint(cv::Mat image);

public:

	ReferencePointFinder() {};
	cv::Point2i GetBeginPointMaze(cv::Mat image);
	cv::Point2i GetEndPointMaze(cv::Mat image);

	std::vector<cv::Point2i> GetEdgePoints(cv::Mat image);
};

#endif
