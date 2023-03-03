/*mainwindow.cpp*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openUart();
    timer_ID = 0;
    flag = 1;//目前没有学习中，可以预测
    count = 0;
    if(v.open(0))//打开摄像头
        qDebug()<<"open Camera OK";
    else
        qDebug()<<"open Camera ERROR";
    if(c.load("D:/lesen/haarcascade_frontalface_alt.xml"))//加载人脸识别配置文件
        qDebug()<<"config_file OK";
    else
        qDebug()<<"config_file ERROR";
    QFile file("D:/opencv/heads/myface.xml");//定义文件变量并设初值：D:/opencv/heads/myface.xml
    if(file.exists())//判断训练模型文件是否存在
    {
        qDebug()<<"myface exits!";
        recognizer = FaceRecognizer::load<LBPHFaceRecognizer>("D:/opencv/heads/myface.xml");//存在的话就用之前的训练模型文件
        ui->face_train->setEnabled(false);
        qDebug()<<"load myface OK";
    }
    else
    {
        qDebug()<<"myface NOT exits";
        recognizer = LBPHFaceRecognizer::create();//不存在的话创建一个识别器
        ui->face_train->setEnabled(true);
        qDebug()<<"creat LBPHFaceRecognizer OK";
    }
    recognizer->setThreshold(90);//参数1：预测可信度极值，预测可信度超出极值则预测失败。
    check_timerID = startTimer(3000);//机器预测开始
    ui->open_LED->setEnabled(false);
    ui->open_RELAY->setEnabled(false);
    ui->open_FAN->setEnabled(false);
    ui->open_BUZZER->setEnabled(false);//先让按钮呈现灰色(按钮设置为不可用)
    ui->close_LED->setEnabled(false);
    ui->close_RELAY->setEnabled(false);
    ui->close_FAN->setEnabled(false);
    ui->close_BUZZER->setEnabled(false);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openUart()
{
    QString uartName = "com1";
    port = new QSerialPort(uartName);//创建为com1的串口名字
    port->setBaudRate(QSerialPort::Baud9600);//设置波特率
    port->setParity(QSerialPort::NoParity);//设置有无校验位
    port->setDataBits(QSerialPort::Data8);//设置数据位
    port->setStopBits(QSerialPort::OneStop);//设置停止位
    port->setFlowControl(QSerialPort::NoFlowControl);//设置流控制
    if(port->open(QSerialPort::ReadWrite))//打开串口
        QMessageBox::warning(this,"Uart","open serialPort OK");//如果打开成功给出提示
    else
        QMessageBox::warning(this,"Uart","open serialPort ERROR");//如果打开失败给出提示
}
void MainWindow::timerEvent(QTimerEvent *event)//定时器处理函数
//若timer_ID、study_timerID、check_timerID定的时间到时，则会进入此函数
{
    /***人脸识别显示到label中***/
    if(timer_ID == event->timerId())//30ms
    {
        v.read(src);//把读到的摄像头图片存储到原图src中
        flip(src,src,1);//将图片进行翻转，否则label中呈现出来的是和实际动作相反的
        cvtColor(src,rgb,CV_BGR2RGB);//要在label中显示图片需要将bgr图片转换为rgb图片
        cvtColor(rgb,gray,CV_BGR2GRAY);//将后续用到的rgb图片转换为gray灰度图为了处理人脸识别时数据是单通道的，数据量小
        c.detectMultiScale(gray,faces,1.1,3,0,Size(24,24));//人脸识别
        for(uint i=0;i<faces.size();i++)//循环找屏幕中的多个脸
            rectangle(rgb,faces[i],Scalar(255,0,0),2,LINE_8,0);//并给检测到的人脸画红框
        cv::resize(rgb,rgb,Size(400,300));//更改rgb图片的大小
        ui->label_show->resize(QSize(400,300));//更改label的大小
        QImage img(rgb.data,rgb.cols,rgb.rows,rgb.cols*rgb.channels(),QImage::Format_RGB888);
        //要在label中显示图片需把Mat类型的rgb图片转换为QImage类型图片
        ui->label_show->setPixmap(QPixmap::fromImage(img));//要在label中显示图片需把QImage图片转换为QPixmap类型
    }
    /***将检测到的人脸进行训练***/
    if(study_timerID == event->timerId())//1s
    {
        qDebug()<<"start model_train";
        Mat face;
        if(faces.empty())return;//如果vector<Rect> faces中是空的直接返回
        face = src(faces[0]);//把src中人脸位置的部分图给face
        cv::resize(face,face,Size(100,100));//把人脸位置的部分图的大小设置为100*100
        cvtColor(face,face,CV_BGR2GRAY);//将face图进行灰度转换
        train_faces.push_back(face);//把face图存储到vector<Mat> train_faces中
        train_labels.push_back(1);//把label标签存储到vector<int> train_labels中
        count++;//每进一次中断训练的图个数+1
        if(count==3)//训练到100张为止
        {
            count = 0;
            recognizer->update(train_faces,train_labels);//图片模型训练
            recognizer->save("D:/opencv/heads/myface.xml");//保存训练的模型
            killTimer(study_timerID);//关闭定时器
            QMessageBox::warning(this,"train","train OK");//提示
            flag = 1;//训练完之后可以进行预测置1
            train_faces.clear();//清空图片数组
            train_labels.clear();//图片标签数组
        }
    }
    /*将人脸进行预测*/
    if(check_timerID == event->timerId())//3s
    {
        if(flag == 1)//训练完了的话可以进行预测了
        {
            qDebug()<<"start pridict";
            QFile file("D:/opencv/heads/myface.xml");//判断是否有训练的模型
            if(file.exists())//如果训练模型的文件存在
            {
                if(faces.empty() || recognizer->empty())return;
                Mat face = src(faces[0]);//将src文件中的人脸位置图片存储到face中
                cvtColor(face,face,CV_BGR2GRAY);//人脸位置图片进行灰度处理
                cv::resize(face,face,Size(100,100));//重新设置图片大小
                int label = -1;//标签为-1时匹配不到训练的图片标签
                double confidence = 0.0;
                recognizer->predict(face,label,confidence);//机器预测
                cout<<"label:"<<label<<'\t'<<"confidence:"<<confidence<<endl;
                if(label != -1)
                {
                    ui->open_LED->setEnabled(true);
                    ui->open_RELAY->setEnabled(true);
                    ui->open_FAN->setEnabled(true);
                    ui->open_BUZZER->setEnabled(true);//将控制按钮处于打开状态
                    ui->close_LED->setEnabled(true);
                    ui->close_RELAY->setEnabled(true);
                    ui->close_FAN->setEnabled(true);
                    ui->close_BUZZER->setEnabled(true);
                }
                else  qDebug()<<"myface.xml NOT exits";
            }
        }
    }
}
void MainWindow::on_open_LED_clicked()
{
    qDebug()<<"open_LED";
    char cmd = '0';
    port->write(&cmd,1);
}
void MainWindow::on_close_LED_clicked()
{
    qDebug()<<"close_LED";
    char cmd = '1';
    port->write(&cmd,1);
}
void MainWindow::on_open_RELAY_clicked()
{
    qDebug()<<"open_RELAY";
    char cmd = '2';
    port->write(&cmd,1);
}
void MainWindow::on_close_RELAY_clicked()
{
    qDebug()<<"close_RELAY";
    char cmd = '3';
    port->write(&cmd,1);
}
void MainWindow::on_open_FAN_clicked()
{
    qDebug()<<"open_FAN";
    char cmd = '4';
    port->write(&cmd,1);
}
void MainWindow::on_close_FAN_clicked()
{
    qDebug()<<"close_FAN";
    char cmd = '5';
    port->write(&cmd,1);
}
void MainWindow::on_open_BUZZER_clicked()
{
    qDebug()<<"open_BUZZER";
    char cmd = '6';
    port->write(&cmd,1);
}
void MainWindow::on_close_BUZZER_clicked()
{
    qDebug()<<"close_BUZZER";
    char cmd = '7';
    port->write(&cmd,1);
}
void MainWindow::on_open_camera_clicked()
{
    timer_ID = startTimer(30);
    ui->open_camera->setEnabled(false);
}
void MainWindow::on_end_camera_clicked()
{
    killTimer(timer_ID);
    timer_ID = 0;
    ui->open_camera->setEnabled(true);
}
void MainWindow::on_face_train_clicked()
{
    cout<<"开始录入人脸"<<endl;
    flag = 0;
    study_timerID = startTimer(1000);
}
