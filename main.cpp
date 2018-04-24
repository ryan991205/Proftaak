
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
    imageFromFile = imageImporter->getImage("/home/ryan991205/Documents/Images/Ryan.jpg");
  }
  catch(std::invalid_argument)
  {
    imageImporter = NULL;
    std::cout << "Cannot find or open file." << std::endl;
  }

  if(imageFromFile.data != NULL)
  {
    cv::namedWindow("ImageImporterShow",1);
    cv::imshow("ImageImporterShow", imageFromFile);
  }

  cv::waitKey(0);
  return 0;
}
