
#ifndef IMAGEIMPORTER_H_
#define IMAGEIMPORTER_H_

#include <string>
#include <stdexcept>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui.hpp> 

class ImageImporter
{
  private:

  public:

  ImageImporter();
  ~ImageImporter();

  cv::Mat getImage(const std::string& fileName);
};

#endif