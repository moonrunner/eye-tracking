//
//  jzplib_draw.h
//  OPENCV_HOTSHOTS
//
//  Created by Zhiping Jiang on 14-7-18.
//
//

#ifndef __OPENCV_HOTSHOTS__jzplib_draw__
#define __OPENCV_HOTSHOTS__jzplib_draw__

#include <iostream>
#include <opencv2/opencv.hpp>
#include <map>

using namespace std;
using namespace cv;


void drawBox(cv::Mat& image, CvRect box, cv::Scalar color = cvScalarAll(255), int thick=1);

void drawPoints(cv::Mat& image, std::vector<cv::Point2f> points,cv::Scalar color=cv::Scalar::all(255));

void drawRotatedRect(Mat image, RotatedRect eyeRRect);
void drawStringAtPoint(Mat img, const string text, Point position);
void drawStringAtTopLeftCorner(Mat img, const string text);
Mat  plotColumnVector(Mat data);
void drawColorHistGram(Mat hist);
void imagesc(string windowName, Mat image, int colormap = COLORMAP_JET) ;

void plotVectors(string windowName, Mat values);

void plotLiveData(string windowName, double value, int length = 200);

#endif /* defined(__OPENCV_HOTSHOTS__jzplib_draw__) */
