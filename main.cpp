
#include <iostream>
#include <stdio.h>
#include <stdexcept>

#include <opencv2/core.hpp>           // data structures and arithmetic routines.
#include <opencv2/highgui.hpp>        // Image display, sliders, buttons, mouse & IO.
#include <opencv2/imgproc.hpp>        // image processing functions.
#include <opencv2/features2d.hpp>     // two dimentsional feature tracking support.
#include "opencv2/imgcodecs.hpp"

#include "Camera.h"
#include "ImageImporter.h"
#include "ImageConverter/ColorFilter.h"
#include "ImageConverter/ReferencePointFinder.h"
#include "ImageConverter/ImageCropper.h"
#include "ImageConverter/scannerCore.h"
#include "ImageConverter/WallVectorsCalculator.h"
#include "ImageConverter/GridCalculator.h"

void ScanSettings( int, void* );

int kernelSize            = 5;
int blackWhiteThreshold   = 38;
int lineThreshold         = 80;

int const max_kernelSize            = 10;
int const max_blackWhiteThreshold   = 100;
int const max_lineThreshold         = 200;

const char* Window_ScannerOutput = "Scanner Output:";

  cv::Mat Image;
  cv::Mat CropedImage;
  Point2i beginPoint, endPoint, offset;
  std::vector<Line> lines;

int main( int argc, char** argv ) 
{
  // haal errors weg en zet deze in file
  std::freopen ("RuntimeErrors.txt","w",stderr);



  // Camera -------------------------------------------------------
  cv::Mat cameraImage;
  try
  {
    Camera* cam  = new Camera(0);
    cameraImage = cam->getImage();
  }
  catch(std::out_of_range)
  {
    std::cout << "selected invalid Camera ID" << std::endl;
  }
  catch(std::runtime_error)
  {
    std::cout << "Cannot Open Camera" << std::endl;
  }

  if(cameraImage.data != NULL)
  {
    cv::namedWindow("cameraShow",0);
    cv::imshow("cameraShow", cameraImage);
  }

// End Camera --------------------------------------------------

// ImageImporter -------------------------------------------------

  cv::Mat imageFromFile;  
  ImageImporter* imageImporter = NULL;
  try
  {
    imageImporter = new ImageImporter();
    imageFromFile = imageImporter->getImage("2.jpg");
  }
  catch(std::invalid_argument)
  {
    imageImporter = NULL;
    std::cout << "Cannot find or open file." << std::endl;
  }

  if(imageFromFile.data != NULL)
  {
    Image = imageFromFile;
  }
// End ImageImporter ----------------------------------------------

// Start userinterface ---------------------------------------------
  cv::namedWindow( Window_ScannerOutput, CV_WINDOW_AUTOSIZE );

  cv::createTrackbar( "KernelSize:  ", Window_ScannerOutput, &kernelSize, max_kernelSize,ScanSettings);
  cv::createTrackbar( "BW   Threshold:  ", Window_ScannerOutput, &blackWhiteThreshold, max_blackWhiteThreshold,ScanSettings);
  cv::createTrackbar( "Line Threshold:  ", Window_ScannerOutput, &lineThreshold, max_lineThreshold,ScanSettings);
// ------------------------------------------------------------------


  cv::waitKey(0);
   return 0;
}


void ScanSettings( int, void* )
{
  cv::cvtColor(Image, Image, CV_BGR2HSV);
  try
  {
    offset = ImageCropper::CropToEdgePoints(&CropedImage,Image.clone());
  }
  catch(std::exception& e)
  {
    std::cout << "ERROR ! @#" << std::endl;
  }

  cv::Mat gridImage;
  lines.clear();
  lines = GridCalculator::Calculate(Image,NULL,kernelSize,blackWhiteThreshold,lineThreshold);
  std::cout << "SIZE: " << lines.size()<< std::endl;
  for(size_t selectedline = 0; selectedline < lines.size(); ++selectedline)
  { 
        lines.at(selectedline).beginPoint.x -= offset.x;
        lines.at(selectedline).beginPoint.y -= offset.y;
        lines.at(selectedline).endPoint.x  -= offset.x;
        lines.at(selectedline).endPoint.y   -= offset.y;
  }

  WallVectorsCalculator MazeCalculator = WallVectorsCalculator();
  
  std::vector<Line> walls;
  MazeCalculator.Calculate(&walls,lines,CropedImage);








  cv::cvtColor(Image, Image, CV_HSV2BGR);
  cv::cvtColor(CropedImage, CropedImage, CV_HSV2BGR);

  cv::Mat out = GridCalculator::Plot(CropedImage,lines);
  MazeCalculator.Draw(&out,walls);

  cv::imshow(Window_ScannerOutput, out);
}




