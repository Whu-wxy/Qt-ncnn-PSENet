#include "ncnndlg.h"
#include <QDesktopWidget>

QString selectedFileName = "/storage/emulated/0/DetectorData/test.jpg";

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT void JNICALL
Java_com_amin_NCNNDemo_NCNNDemo_fileSelected(JNIEnv */*env*/,
                                             jobject /*obj*/,
                                             jstring results)
{
    selectedFileName = QAndroidJniObject(results).toString();
}

#ifdef __cplusplus
}
#endif



NCNNDlg::NCNNDlg(QWidget *parent)
    : QDialog(parent)
{
    QDesktopWidget * deskTop = qApp->desktop();
    QRect rect = deskTop->availableGeometry();
    this->setFixedSize(rect.width(), rect.height());

    QVBoxLayout* mainl = new QVBoxLayout(this);
    QGridLayout* mainLay = new QGridLayout();

    imgLabel = new QLabel(this);
    QImage bkground(":/img/src/test.jpg");
    bkground = bkground.scaled(this->size(), Qt::KeepAspectRatio);
    imgLabel->setPixmap(QPixmap::fromImage(bkground));

    captureBtn = new QPushButton("拍照");
    captureBtn->setChecked(true);
    albumBtn = new QPushButton("相册");
    processBtn = new QPushButton("处理");
    saveBtn = new QPushButton("保存");
    btnGroup = new QButtonGroup(this);
    btnGroup->addButton(captureBtn,0);
    btnGroup->addButton(albumBtn,1);
    btnGroup->addButton(processBtn,2);
    btnGroup->addButton(saveBtn,3);
    btnGroup->setExclusive(true);

    mainLay->addWidget(captureBtn    ,1,0,1,1);
    mainLay->addWidget(albumBtn      ,1,1,1,1);
    mainLay->addWidget(processBtn    ,1,2,1,1);
    mainLay->addWidget(saveBtn       ,1,3,1,1);

    mainl->addStretch();
    mainl->addWidget(imgLabel);
    mainl->addStretch();
    mainl->addLayout(mainLay);

    connect(btnGroup,SIGNAL(buttonClicked(int)),this,SLOT(btnClicked(int)));
}

NCNNDlg::~NCNNDlg()
{

}


void NCNNDlg::btnClicked(int btnID)
{
    if(btnID == 0)
    {
        selectedFileName = "#";
        QAndroidJniObject::callStaticMethod<void>("com/amin/NCNNDemo/NCNNDemo",
                                                  "captureAnImage",
                                                  "()V");
        while(selectedFileName == "#")
            qApp->processEvents();

        if(selectedFileName != "#")
        {
            if(QFile(selectedFileName).exists())
            {
                outputImg.release();

                QImage bkground(selectedFileName);
                bkground = bkground.scaled(this->size(), Qt::KeepAspectRatio);
                imgLabel->setPixmap(QPixmap::fromImage(bkground));
            }
        }
    }
    else if(btnID == 1)
    {
        selectedFileName = "#";
        QAndroidJniObject::callStaticMethod<void>("com/amin/NCNNDemo/NCNNDemo",
                                                  "openAnImage",
                                                  "()V");

        while(selectedFileName == "#")
            qApp->processEvents();

        if(QFile(selectedFileName).exists())
        {
            outputImg.release();

            QImage bkground(selectedFileName);
            bkground = bkground.scaled(this->size(), Qt::KeepAspectRatio);
            imgLabel->setPixmap(QPixmap::fromImage(bkground));
        }
    }
    else if(btnID == 2)
    {
        if(selectedFileName.length()==0 || selectedFileName == "#")
        {
            QMessageBox::information(this, "提示", "请打开一张图片");
            return;
        }

        qDebug()<<"open img from: "<<selectedFileName;
        //处理图片
        Mat frame = imread(selectedFileName.toStdString());
        Mat frame2Detect = frame.clone();
        if(!detector.hasLoadNet())
            return;
        map<int, vector<Point>> contoursMap;
        clock_t start, finish;
        start = clock();

        if(detector.detect(frame2Detect, contoursMap))//处理图片
        {
            float h_scale = frame.rows * 1.0 / frame2Detect.rows;
            float w_scale = frame.cols * 1.0 / frame2Detect.cols;
            qDebug()<<"h_scale: "<<h_scale;
            qDebug()<<"w_scale: "<<w_scale;

            map<int, vector<cv::Point>>::iterator iter;//定义一个迭代指针iter
            for(iter=contoursMap.begin(); iter!=contoursMap.end(); iter++)
            {
                if(iter->first == 0)
                    continue;

                vector<cv::Point> pts = iter->second;

                RotatedRect rect = minAreaRect(pts);
                rect.size.width = rect.size.width * w_scale;
                rect.size.height = rect.size.height * h_scale;
                rect.center.x = rect.center.x * w_scale;
                rect.center.y = rect.center.y * h_scale;

                Point2f cornerPts[4];
                rect.points(cornerPts);//外接矩形的4个顶点
                for (int i = 0; i < 4; i++)//绘制外接矩形
                {
                    line(frame, cornerPts[i], cornerPts[(i + 1) % 4], cv::Scalar(0, 255, 0), 2);
                }
            }
            finish = clock();
            qDebug()<<"Detect all time: "<<(double)(finish - start) / CLOCKS_PER_SEC;

            /// show segmentation map in image, If necessary, uncomment them
//            cv::resize(frame2Detect, frame2Detect, frame.size(), 0, 0);
//            for (int y=0; y < frame2Detect.rows; ++y)
//                for (int x=0; x < frame2Detect.cols; ++x) {
//                    int idx = frame2Detect.at<uchar>(y, x);
//                    if (idx == 0) continue;
//                    frame.at<Vec3b>(y, x)[1] += 50;
//                }

            outputImg = frame.clone();

            QImage img = MatToQImage(frame);
            img = img.scaled(this->size(), Qt::KeepAspectRatio);
            imgLabel->setPixmap(QPixmap::fromImage(img));
        }
    }
    else if(btnID == 3)
    {
        if(outputImg.empty()) return;

        QFileInfo info(selectedFileName);
        if(!info.exists()) return;

        AndroidSetup setup;
        QString dataDir = setup.getAppDataDir();
        QString savePath = dataDir + QDir::separator() + QDateTime::currentDateTime().toString("ncnn_yyMdhms") + ".jpg";

        imwrite(savePath.toStdString(), outputImg);

        QMessageBox::information(this, "提示", "保存成功");
    }
}
