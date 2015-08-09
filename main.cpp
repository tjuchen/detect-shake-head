#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "animation.h"
#include "detector.h"

using namespace cv;
using namespace std;


int main(int argc, char* argv[])
{
  VideoCapture cap(0); // open the video camera no. 0
  cout << "Video camera opened";

  if (!cap.isOpened())  // if not success, exit program
  {
    cout << "Cannot open the video cam" << endl;
    return -1;
  }

  double dWidth = cap.get(CV_CAP_PROP_FRAME_WIDTH); //get the width of frames of the video
  double dHeight = cap.get(CV_CAP_PROP_FRAME_HEIGHT); //get the height of frames of the video

  cout << "Frame size : " << dWidth << " x " << dHeight << endl;

  namedWindow("MyVideo",CV_WINDOW_AUTOSIZE); //create a window called "MyVideo"

  int frameRate = 35;

  int i = 0;
  ArrowAnimator arrowAnimator(frameRate);
  int gridWidth = 2;
  MotionDetector motionDetector(5, gridWidth, 20);
  HandMovementAnalyzer handMovementAnalyzer(gridWidth);

  cv::Mat frame;
  while (1)
  {
    i++;

    bool bSuccess = cap.read(frame); // read a new frame from video
    Size s = frame.size();
    Mat grayFrame(s.height, s.width, CV_8UC1);
    cvtColor(frame, grayFrame, CV_BGR2GRAY);

    if (!bSuccess) //if not success, break loop
    {
      cout << "Cannot read a frame from video stream" << endl;
      break;
    }

    // Hand movement detection.
    Direction handDirection = INVALID;
    Mat movingEdge;

    motionDetector.addFrame(grayFrame, 0.4);
    Position handPosition = motionDetector.detect(movingEdge);
    handMovementAnalyzer.addValue(handPosition);
    handDirection  = handMovementAnalyzer.detectMovingDirection(0.7);
    if (handDirection != INVALID) {
      // arrowAnimator.addAnimateStartFromNow(0.3, handDirection, CV_RGB(255, 0, 0));
      arrowAnimator.addAnimateStartFromNow(0.2, handDirection, CV_RGB(255, 255, 255));
    }

  
    Mat flippedFrame;
    // flip(movingEdge, flippedFrame, 1);
    // flip(movingEdge, flippedFrame, 1);
    flip(frame, flippedFrame, 1);
    arrowAnimator.playFrame(flippedFrame, true);
    // imshow("MyVideo", res); //show the frame in "MyVideo" window

    if (waitKey(1000 / frameRate) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
    {
      cout << "esc key is pressed by user" << endl;
      break; 
    }
  }
  return 0;

}
