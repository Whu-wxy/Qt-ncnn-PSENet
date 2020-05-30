#ifndef IMGUTILS_H
#define IMGUTILS_H

#include <QImage>
#include <QObject>

#include "opencv2/opencv.hpp"//添加Opencv相关头文件
#include "opencv2/highgui/highgui.hpp"

#include "iostream"
#include <math.h>

using namespace std;
using namespace cv;

void showMatImage(Mat image, QString win_name="image", int width=800, int height=600);

cv::Mat QImageToMat(QImage image);

QImage MatToQImage(cv::Mat mtx);

#endif // IMGUTILS_H
