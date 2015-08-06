#include "animation.h"

bool Animator::addAnimateStartFromNow(double duration) {
  if (currentFrameNum_ < totalFrameNum_) {
    // cannot start a new animation if old didn't need
    return false;
  }
  totalFrameNum_ = duration * frameRate_;
  currentFrameNum_ = 0;
  return true;
}


void Animator::playFrame(Mat& img, bool show) {
  if (currentFrameNum_ >= totalFrameNum_) {
    return;
  }
  animate(img, currentFrameNum_ * 1.0 / totalFrameNum_);
  if (show) {
    imshow("MyVideo", img); //show the frame in "MyVideo" window
  }
  ++currentFrameNum_;
}

void ArrowAnimator::drawArrow(Mat& img, const Direction direction, const Point& center) {
  Size s = img.size();
  int length = 150;
  int thickness = 10;
  int lineType = 0;
  double tipLength = 0.5;

  int angle;
  switch (direction) {
    case RIGHT:
      angle = 0;
      break;
    case DOWN:
      angle = 90;
      break;
    case LEFT:
      angle = 180;
      break;
    case UP:
      angle = 270;
      break;
    default:
      cout << "unknown direction";
      return;
  }

  double angleRad = angle * CV_PI / 180.0;
  Point arrowDirection = Point(length * cos(angleRad), length * sin(angleRad));

  // Point center = Point(s.width / 2, s.height / 2);
  arrowedLine(img, center + arrowDirection*0.5, center + arrowDirection,
      CV_RGB(255, angle, 0), thickness, lineType, 0, tipLength);

}

void ArrowAnimator::animateArrow(Mat& img, const Direction moveTo, const double degree) {
  Size s = img.size();
  int centerX = s.width / 2;
  int centerY = s.height / 2;
  switch (moveTo) {
    case RIGHT:
      centerX  = degree * s.width;
      break;
    case DOWN:
      centerY = degree * s.height;
      break;
    case LEFT:
      centerX  = (1 - degree) * s.width;
      break;
    case UP:
      centerY = (1 - degree) * s.height;
      break;
    default:
      cout << "unknown direction";
      return;
  }

  Point center = Point(centerX, centerY);
  drawArrow(img, moveTo, center);
}

