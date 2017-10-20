#include "ColorDetect.hpp"

int main(int argc, char** argv )
{

  VideoCapture stream1(0);
  namedWindow("Camera Feed", CV_WINDOW_AUTOSIZE);

  if(!stream1.isOpened())
  {
    cout << "Error: Cannot open camera.\n";
    return -1;
  }

  makeTrackbarWindow();

  Mat cameraFrame;
  Mat HSVFrame;
  Mat threshholdedFrame;
  string rangetext[50];

  stream1.read(cameraFrame);

  while (true) //This is the loop that outputs the camera feed and does analysis
  {

    if(!(stream1.read(cameraFrame)))
    {
      cout << "Error: Cannot read from camera feed.\n";
      break;
    }

    cvtColor(cameraFrame, HSVFrame, COLOR_BGR2HSV);
    inRange(HSVFrame, Scalar(hueLow, satLow, valLow), Scalar(hueHigh, satHigh, valHigh), threshholdedFrame);

    drawColorRange(cameraFrame);
    imshow("Camera Feed", cameraFrame);
    imshow("Color-picked Feed", threshholdedFrame);

    if(waitKey(30) == 27)
      break; //waitKey() is a function that adds a delay for the HighGui can do it's job
  }

  return 0;
}

void makeTrackbarWindow()
{
  namedWindow("Control", WINDOW_NORMAL);

  createTrackbar("hue low",  "Control", &hueLow,  hueHigh);
  createTrackbar("hue high", "Control", &hueHigh, hueHigh);
  createTrackbar("sat low",  "Control", &satLow,  satHigh);
  createTrackbar("sat high", "Control", &satHigh, satHigh);
  createTrackbar("val low",  "Control", &valLow,  valHigh);
  createTrackbar("val high",  "Control", &valHigh, valHigh);

}

void drawColorRange(Mat gradientimg)
{
  Scalar low  = Scalar(hueLow, satLow, valLow);
  Scalar high = Scalar(hueHigh, satHigh, valHigh);
  Scalar inter;                       //intermediate variable for rendering palette
  int width = 70;                     //width of pallete squares

  //This for-loop generates and stores a pallete of seven colors:
  //start, final, 5 intermediate.
  for(int i = 0; i < 7; i++)
  {
    Scalar inter(low.val[0] + (high.val[0] - low.val[0])/7*i,    //H;
                 low.val[1] + (high.val[1] - low.val[1])/7*i,    //S
                 low.val[2] + (high.val[2] - low.val[2])/7*i);   //V

    //Draw the rectangle:
    rectangle(gradientimg, Point(i*width, 0), Point(width*(1+i), width), ScalarHSV2BGR(inter), -1);
  }
}

Scalar ScalarHSV2BGR(Scalar color)
{
    Mat rgb;
    Mat hsv(1, 1, CV_8UC3, Scalar(color[0], color[1], color[2]));
    cvtColor(hsv, rgb, CV_HSV2BGR);
    return Scalar(rgb.data[0], rgb.data[1], rgb.data[2]);
}
