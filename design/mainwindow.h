#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <math.h>
#include<opencv2/face.hpp>
#include <vector>
#include <map>
#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QTimerEvent>
#include<QtSerialPort/QtSerialPort>
#include<QtSerialPort/QSerialPortInfo>
using namespace  cv;
using namespace cv::face;
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_open_LED_clicked();

    void on_close_LED_clicked();

    void on_open_RELAY_clicked();

    void on_close_RELAY_clicked();

    void on_open_FAN_clicked();

    void on_close_FAN_clicked();

    void on_open_BUZZER_clicked();

    void on_close_BUZZER_clicked();

    void on_open_camera_clicked();

    void on_end_camera_clicked();

    void on_face_train_clicked();

private:
    Ui::MainWindow *ui;
    void openUart();//声明打开串口
    QSerialPort* port;//定义串口指针
    int timer_ID;//定义人脸识别定时器ID
    void timerEvent(QTimerEvent* event);//声明定时器处理函数
    VideoCapture v;//创建视频流对象
    CascadeClassifier c;//创建级联分类器对象
    Mat src;//定义源图片
    Mat rgb;//定义rgb图片
    Mat gray;//定义灰度图片
    vector<Rect> faces;//存储人脸识别中脸部的位置
    int study_timerID;//定义模型训练定时器ID
    int check_timerID;//定义机器预测定时器ID
    vector<Mat> train_faces;//定义存储训练的人脸图片
    vector<int> train_labels;//定义存储训练的人脸标识
    int count;//定义表示训练次数变量
    int flag;//定义训练还是预测的标识
    Ptr<LBPHFaceRecognizer> recognizer;//Ptr<>说明定义指针、recognizer是定义的指针变量
};

#endif // MAINWINDOW_H
