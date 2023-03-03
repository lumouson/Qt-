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
    void openUart();//�����򿪴���
    QSerialPort* port;//���崮��ָ��
    int timer_ID;//��������ʶ��ʱ��ID
    void timerEvent(QTimerEvent* event);//������ʱ��������
    VideoCapture v;//������Ƶ������
    CascadeClassifier c;//������������������
    Mat src;//����ԴͼƬ
    Mat rgb;//����rgbͼƬ
    Mat gray;//����Ҷ�ͼƬ
    vector<Rect> faces;//�洢����ʶ����������λ��
    int study_timerID;//����ģ��ѵ����ʱ��ID
    int check_timerID;//�������Ԥ�ⶨʱ��ID
    vector<Mat> train_faces;//����洢ѵ��������ͼƬ
    vector<int> train_labels;//����洢ѵ����������ʶ
    int count;//�����ʾѵ����������
    int flag;//����ѵ������Ԥ��ı�ʶ
    Ptr<LBPHFaceRecognizer> recognizer;//Ptr<>˵������ָ�롢recognizer�Ƕ����ָ�����
};

#endif // MAINWINDOW_H
