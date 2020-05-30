#ifndef DETECTOR_H
#define DETECTOR_H

#include <QObject>
#include <QTime>
#include <QDebug>
#include <QDir>
#include <QtGlobal>

#include "opencv2/opencv.hpp"//添加Opencv相关头文件
#include "ncnn/net.h"
#include "ncnn/mat.h"
#include "ncnn/cpu.h"
#include "ncnn/layer.h"

using namespace std;
using namespace cv;

class Detector : public QObject
{
    Q_OBJECT
public:
    explicit Detector(QObject *parent = 0);
    ~Detector();

signals:

public slots:

private:
    ncnn::Net net;
    //ncnn::Extractor* extractor;

    bool bLoad;

public:
    bool    detect(Mat & frame, map<int, vector<Point>>& contours_map);

    void    pse_decode(ncnn::Mat& features,
                                  std::map<int, std::vector<cv::Point>>& contours_map,
                                  const float thresh,
                                  const float min_area, int min_map_id=0
                                  );

    bool    hasLoadNet(){return bLoad; }
    bool    moveFiles();

    void    pretty_print(const ncnn::Mat& m);
    Mat     resize_img(cv::Mat src, int long_size);
};

#endif // DETECTOR_H
