
#include "WallVectorsCalculator.h"
#include <opencv2/imgproc.hpp>

// debug 
#include <iostream>
#include <stdio.h>

void WallVectorsCalculator::Draw(cv::Mat* image, std::vector<Line> Walls )
{
    if(image == NULL)
    {
        //throw  
    }
    // CV_8U ONBEKEND OF DIT ANDERS MOET ZIJN __> GOOGLE: LIST OF MAT TYPE IN OPEN CV
    cv::Mat outputImage = *image;
    

    for(size_t selectedWall = 0; selectedWall < Walls.size(); ++selectedWall)
    {
        cv::Point2i bP = cv::Point2i(Walls.at(selectedWall).beginPoint.x,Walls.at(selectedWall).beginPoint.y);
        cv::Point2i eP = cv::Point2i(Walls.at(selectedWall).endPoint.x,Walls.at(selectedWall).endPoint.y);

        //cv::Mat outputImage = *image;
        // zal nu nog error geven.
        cv::line(outputImage, bP, eP, cv::Scalar(30, 30, 30), 2, CV_AA);
        *image = outputImage;
    }
    return;
}

// NOG CONTROLEREN OF IMAGE BOOL IS __> EN VAN WAARDE 
void  WallVectorsCalculator::Calculate(std::vector<Line>* outputWalls, std::vector<Line> gridLines, cv::Mat image)
{
    if(outputWalls == NULL)
    {
       // trow
    }

    if(image.data == NULL)
    {
        // trow
    }

    //cv::cvtColor(image, image, CV_HSV2BGR);
    cv::cvtColor(image, image, CV_BGR2GRAY);

    std::vector<Line>* horizontalGridLines = new std::vector<Line>();
    std::vector<Line>* verticalGridLines   = new std::vector<Line>();
    SortLinesOnRotation(horizontalGridLines, verticalGridLines, gridLines);

    std::cout << "komikhier 1: " << std::endl;
    std::vector<Line> wallsOnLine;
    for(size_t line = 0; line < horizontalGridLines->size(); ++line) 
    {
        std::cout << "komikhier 2: " << std::endl;
        wallsOnLine = getAllHorizontalWallsFromLine(horizontalGridLines->at(line), verticalGridLines, image);  
        std::cout << "komikhier 3: " << std::endl;
        outputWalls->insert(outputWalls->end(),wallsOnLine.begin(),wallsOnLine.end());    
        std::cout << "komikhier 4: " << std::endl;  
    }

    for(size_t line = 0; line < verticalGridLines->size(); ++line) 
    {
        wallsOnLine = getAllVerticalWallsFromLine(verticalGridLines->at(line), horizontalGridLines, image);
        outputWalls->insert(outputWalls->end(),wallsOnLine.begin(),wallsOnLine.end());
    }

    delete horizontalGridLines;
    delete verticalGridLines;
    return;
}


std::vector<Line> WallVectorsCalculator::getAllHorizontalWallsFromLine(Line line, const std::vector<Line> *verticalLines, cv::Mat image)
{
    std::vector<Line> MazeWalls;
    Point2i beginpointReadout;
    Line currentWallSection;
    
    bool newWallSection = true;
    std::cout << "komikhier   2.1: " << std::endl;

    currentWallSection.beginPoint.y    = line.beginPoint.y ;
    currentWallSection.endPoint.y      = line.beginPoint.y ;
    beginpointReadout.y                = line.beginPoint.y ;

    std::cout << "komikhier   2.2: " << std::endl;

    for(size_t currentGridLine = 0; currentGridLine < verticalLines->size(); ++currentGridLine) 
 	{
         std::cout << "komikhier   2.3: " << std::endl;
        if(currentGridLine + 1 >= verticalLines->size())
        {
            if(currentWallSection.beginPoint.x != currentWallSection.endPoint.x)
            {
                std::cout << "komikhier   EINDE 2: " << std::endl;
                MazeWalls.push_back(currentWallSection);
            }
            return MazeWalls;
        }

        beginpointReadout.x =  verticalLines->at(currentGridLine).beginPoint.x;
        std::cout << "komikhier   2.4   beginpointReadout x = : "<<  beginpointReadout.x << std::endl;
        std::cout << "komikhier   2.4   beginpointReadout y = : "<<  beginpointReadout.y << std::endl;

        if(newWallSection)
        {
            currentWallSection.beginPoint.x =  verticalLines->at(currentGridLine).beginPoint.x;
            newWallSection = false;
            std::cout << "komikhier   2.5: " << std::endl;
        }

        currentWallSection.endPoint.x = verticalLines->at(currentGridLine + 1).beginPoint.x;
        std::cout << "komikhier   2.6: " << std::endl;

        if(!WallExistsOnPosition(beginpointReadout, currentWallSection.endPoint, image))
        {
            std::cout << "komikhier   2.7: " << std::endl;
            currentWallSection.endPoint.x = verticalLines->at(currentGridLine).beginPoint.x;
            std::cout << "komikhier   2.8: " << std::endl;
            MazeWalls.push_back(currentWallSection);
            newWallSection = true; 
            std::cout << "komikhier   2.9: " << std::endl;
        }    
    }
    // should not be called
    return MazeWalls;
}


std::vector<Line> WallVectorsCalculator::getAllVerticalWallsFromLine(Line line,  const std::vector<Line> *horizontalLines, cv::Mat image)
{
    std::vector<Line> MazeWalls;
    Point2i beginpointReadout;
    Line currentWallSection;
    
    bool newWallSection = true;

    currentWallSection.beginPoint.x    = line.beginPoint.x ;
    currentWallSection.endPoint.x      = line.beginPoint.x ;
    beginpointReadout.x                = line.beginPoint.x ;

    for(size_t currentGridLine = 0; currentGridLine < horizontalLines->size(); ++currentGridLine) 
 	{
        if(currentGridLine + 1 >= horizontalLines->size())
        {
            if(currentWallSection.beginPoint.y != currentWallSection.endPoint.y)
            {
                MazeWalls.push_back(currentWallSection);
            }
            return MazeWalls;
        }

        beginpointReadout.y =  horizontalLines->at(currentGridLine).beginPoint.y;

        if(newWallSection)
        {
            currentWallSection.beginPoint.y =  horizontalLines->at(currentGridLine).beginPoint.y;
            newWallSection = false;
        }

        currentWallSection.endPoint.y = horizontalLines->at(currentGridLine + 1).beginPoint.y;

        if(!WallExistsOnPosition(beginpointReadout, currentWallSection.endPoint, image))
        {
            currentWallSection.endPoint.y = horizontalLines->at(currentGridLine).beginPoint.y;
            MazeWalls.push_back(currentWallSection);
            newWallSection = true; 
        }
    }
    // should not be called
    return MazeWalls;
}


// pre-conditions :  image.type == CV_8U
bool WallVectorsCalculator::WallExistsOnPosition(Point2i beginPos, Point2i endPos, cv::Mat image)
{
    cv::Point2i MeasurePoint =  cv::Point2i( (beginPos.x + endPos.x) / 2,
                                             (beginPos.y + endPos.y) / 2); 
    //std::cout << "komikhier         2.10: " << std::endl;

    //std::cout << "komikhier         2.11   data value: " <<  (int)image.at<uchar>(MeasurePoint) << std::endl; 
    //std::cout << "komikhier         2.11   pix X     : " <<  MeasurePoint.x << std::endl;
    //std::cout << "komikhier         2.11   pix Y     : " <<  MeasurePoint.y << std::endl;


    if(image.at<uchar>(MeasurePoint) > 0)
    {
        return true;
    }
    return false;
}


void WallVectorsCalculator::SortLinesOnRotation(std::vector<Line>* horizontal, std::vector<Line>* vertical, std::vector<Line> inputLines)
{
    for (size_t i = 0; i < inputLines.size(); i++)
	{
        if(inputLines.at(i).beginPoint.x == inputLines.at(i).endPoint.x)
        {
            horizontal->push_back(inputLines.at(i));
        }
        else
        {
            vertical->push_back(inputLines.at(i));
        }
	}
}