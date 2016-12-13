
#ifndef __RCUBE_CV_H__
#define __RCUBE_CV_H__

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

// Other stuff
#include "qsort.hpp"

// Rubik's Cube stuff
#include "sticker.hpp"
#include "rface.hpp"
#include "rcube.hpp"

// Useful for drawing, used by RCube
#define STICKER_SIZE 50

class RCube;
bool pointSortY(cv::Point2f a, cv::Point2f b);
bool pointSortX(cv::Point2f a, cv::Point2f b);
bool assignRCubeCV(RCube& rubiks);

#endif
