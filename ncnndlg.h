#ifndef NCNNDLG_H
#define NCNNDLG_H

#include <QDialog>
#include <QtWidgets>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFile>
#include <QButtonGroup>
#include <QDebug>
#include <iostream>
#include <QtAndroidExtras>
#include <QMessageBox>
#include <QApplication>
#include <QFileInfo>

#include "opencv2/opencv.hpp"//添加Opencv相关头文件
#include "opencv2/core/core.hpp"

#include "imgutils.h"
#include "androidsetup.h"
#include "time.h"
#include "detector.h"

#include "ncnn/net.h"
#include "ncnn/mat.h"
#include "ncnn/cpu.h"
#include "ncnn/layer.h"

using namespace cv;
using namespace std;

class NCNNDlg : public QDialog
{
    Q_OBJECT

public:
    NCNNDlg(QWidget *parent = 0);
    ~NCNNDlg();


private:
    QLabel*     imgLabel;
    QButtonGroup* btnGroup;
    QPushButton* captureBtn;
    QPushButton* albumBtn;
    QPushButton* processBtn;
    QPushButton* saveBtn;

    Detector    detector;

    Mat     outputImg;

protected slots:
    void btnClicked(int);
};

#endif // NCNNDLG_H
