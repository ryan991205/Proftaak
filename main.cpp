
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
    imageFromFile = imageImporter->getImage("1.jpg");
  }
  catch(std::invalid_argument)
  {
    imageImporter = NULL;
    std::cout << "Cannot find or open file." << std::endl;
  }

  if(imageFromFile.data != NULL)
  {
    //cv::namedWindow("ImageImporterShow",1);
    //cv::imshow("ImageImporterShow", imageFromFile);
  }

 // ColorFilter -------------------------------------------------
 
 //cv::cvtColor(imageFromFile, imageFromFile, CV_BGR2HSV);
 //cv::Mat filteredImage = ColorFilter::GetFilteredImage(Red, imageFromFile);
 //
 //if(filteredImage.data != NULL)
 // {
 //   cv::namedWindow("FilteredImageShow",1);
 //   cv::imshow("FilteredImageShow", filteredImage);
 //
 // }

 /*/ ReferencepointFinder -------------------------------------------------
  ReferencePointFinder* refFinder =  new ReferencePointFinder();
  std::vector<cv::Point2i> referencePoints = refFinder->GetEdgePoints(imageFromFile);

 */
 // ImageCropper -------------------------------------------------

  cv::Mat crop = ImageCropper::CropToEdgePoints(imageFromFile);
  cv::imshow("CroppedImage", crop);
  cv::waitKey(0);
   return 0;
}

