#ifndef WALLVECTORSCALCULATOR_H
#define WALLVECTORSCALCULATOR_H

#include <vector>
#include <exception>
#include <opencv2/core/core.hpp>

#include "scannerCore.h"

class WallVectorsCalculator 
{
private:
    bool WallExistsOnPosition(Point2i beginPos, Point2i endPos, cv::Mat image);
    std::vector<Line> getAllHorizontalWallsFromLine(Line line, const std::vector<Line> *directionGrid, cv::Mat image);
    std::vector<Line> getAllVerticalWallsFromLine(Line line, const std::vector<Line> *directionGrid, cv::Mat image);
    void SortLinesOnRotation(std::vector<Line>* horizontal,std::vector<Line>* vertical , std::vector<Line> inputLines);
    
public:
    void Calculate(std::vector<Line>* outputWalls, std::vector<Line> gridLines, cv::Mat image);
    void Draw(cv::Mat* image, std::vector<Line> Walls);
};

#endif

