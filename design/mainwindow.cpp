/*mainwindow.cpp*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    openUart();
    timer_ID = 0;
    flag = 1;//Ŀǰû��ѧϰ�У�����Ԥ��
    count = 0;
    if(v.open(0))//������ͷ
        qDebug()<<"open Camera OK";
    else
        qDebug()<<"open Camera ERROR";
    if(c.load("D:/lesen/haarcascade_frontalface_alt.xml"))//��������ʶ�������ļ�
        qDebug()<<"config_file OK";
    else
        qDebug()<<"config_file ERROR";
    QFile file("D:/opencv/heads/myface.xml");//�����ļ����������ֵ��D:/opencv/heads/myface.xml
    if(file.exists())//�ж�ѵ��ģ���ļ��Ƿ����
    {
        qDebug()<<"myface exits!";
        recognizer = FaceRecognizer::load<LBPHFaceRecognizer>("D:/opencv/heads/myface.xml");//���ڵĻ�����֮ǰ��ѵ��ģ���ļ�
        ui->face_train->setEnabled(false);
        qDebug()<<"load myface OK";
    }
    else
    {
        qDebug()<<"myface NOT exits";
        recognizer = LBPHFaceRecognizer::create();//�����ڵĻ�����һ��ʶ����
        ui->face_train->setEnabled(true);
        qDebug()<<"creat LBPHFaceRecognizer OK";
    }
    recognizer->setThreshold(90);//����1��Ԥ����Ŷȼ�ֵ��Ԥ����Ŷȳ�����ֵ��Ԥ��ʧ�ܡ�
    check_timerID = startTimer(3000);//����Ԥ�⿪ʼ
    ui->open_LED->setEnabled(false);
    ui->open_RELAY->setEnabled(false);
    ui->open_FAN->setEnabled(false);
    ui->open_BUZZER->setEnabled(false);//���ð�ť���ֻ�ɫ(��ť����Ϊ������)
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
    port = new QSerialPort(uartName);//����Ϊcom1�Ĵ�������
    port->setBaudRate(QSerialPort::Baud9600);//���ò�����
    port->setParity(QSerialPort::NoParity);//��������У��λ
    port->setDataBits(QSerialPort::Data8);//��������λ
    port->setStopBits(QSerialPort::OneStop);//����ֹͣλ
    port->setFlowControl(QSerialPort::NoFlowControl);//����������
    if(port->open(QSerialPort::ReadWrite))//�򿪴���
        QMessageBox::warning(this,"Uart","open serialPort OK");//����򿪳ɹ�������ʾ
    else
        QMessageBox::warning(this,"Uart","open serialPort ERROR");//�����ʧ�ܸ�����ʾ
}
void MainWindow::timerEvent(QTimerEvent *event)//��ʱ��������
//��timer_ID��study_timerID��check_timerID����ʱ�䵽ʱ��������˺���
{
    /***����ʶ����ʾ��label��***/
    if(timer_ID == event->timerId())//30ms
    {
        v.read(src);//�Ѷ���������ͷͼƬ�洢��ԭͼsrc��
        flip(src,src,1);//��ͼƬ���з�ת������label�г��ֳ������Ǻ�ʵ�ʶ����෴��
        cvtColor(src,rgb,CV_BGR2RGB);//Ҫ��label����ʾͼƬ��Ҫ��bgrͼƬת��ΪrgbͼƬ
        cvtColor(rgb,gray,CV_BGR2GRAY);//�������õ���rgbͼƬת��Ϊgray�Ҷ�ͼΪ�˴�������ʶ��ʱ�����ǵ�ͨ���ģ�������С
        c.detectMultiScale(gray,faces,1.1,3,0,Size(24,24));//����ʶ��
        for(uint i=0;i<faces.size();i++)//ѭ������Ļ�еĶ����
            rectangle(rgb,faces[i],Scalar(255,0,0),2,LINE_8,0);//������⵽�����������
        cv::resize(rgb,rgb,Size(400,300));//����rgbͼƬ�Ĵ�С
        ui->label_show->resize(QSize(400,300));//����label�Ĵ�С
        QImage img(rgb.data,rgb.cols,rgb.rows,rgb.cols*rgb.channels(),QImage::Format_RGB888);
        //Ҫ��label����ʾͼƬ���Mat���͵�rgbͼƬת��ΪQImage����ͼƬ
        ui->label_show->setPixmap(QPixmap::fromImage(img));//Ҫ��label����ʾͼƬ���QImageͼƬת��ΪQPixmap����
    }
    /***����⵽����������ѵ��***/
    if(study_timerID == event->timerId())//1s
    {
        qDebug()<<"start model_train";
        Mat face;
        if(faces.empty())return;//���vector<Rect> faces���ǿյ�ֱ�ӷ���
        face = src(faces[0]);//��src������λ�õĲ���ͼ��face
        cv::resize(face,face,Size(100,100));//������λ�õĲ���ͼ�Ĵ�С����Ϊ100*100
        cvtColor(face,face,CV_BGR2GRAY);//��faceͼ���лҶ�ת��
        train_faces.push_back(face);//��faceͼ�洢��vector<Mat> train_faces��
        train_labels.push_back(1);//��label��ǩ�洢��vector<int> train_labels��
        count++;//ÿ��һ���ж�ѵ����ͼ����+1
        if(count==3)//ѵ����100��Ϊֹ
        {
            count = 0;
            recognizer->update(train_faces,train_labels);//ͼƬģ��ѵ��
            recognizer->save("D:/opencv/heads/myface.xml");//����ѵ����ģ��
            killTimer(study_timerID);//�رն�ʱ��
            QMessageBox::warning(this,"train","train OK");//��ʾ
            flag = 1;//ѵ����֮����Խ���Ԥ����1
            train_faces.clear();//���ͼƬ����
            train_labels.clear();//ͼƬ��ǩ����
        }
    }
    /*����������Ԥ��*/
    if(check_timerID == event->timerId())//3s
    {
        if(flag == 1)//ѵ�����˵Ļ����Խ���Ԥ����
        {
            qDebug()<<"start pridict";
            QFile file("D:/opencv/heads/myface.xml");//�ж��Ƿ���ѵ����ģ��
            if(file.exists())//���ѵ��ģ�͵��ļ�����
            {
                if(faces.empty() || recognizer->empty())return;
                Mat face = src(faces[0]);//��src�ļ��е�����λ��ͼƬ�洢��face��
                cvtColor(face,face,CV_BGR2GRAY);//����λ��ͼƬ���лҶȴ���
                cv::resize(face,face,Size(100,100));//��������ͼƬ��С
                int label = -1;//��ǩΪ-1ʱƥ�䲻��ѵ����ͼƬ��ǩ
                double confidence = 0.0;
                recognizer->predict(face,label,confidence);//����Ԥ��
                cout<<"label:"<<label<<'\t'<<"confidence:"<<confidence<<endl;
                if(label != -1)
                {
                    ui->open_LED->setEnabled(true);
                    ui->open_RELAY->setEnabled(true);
                    ui->open_FAN->setEnabled(true);
                    ui->open_BUZZER->setEnabled(true);//�����ư�ť���ڴ�״̬
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
    cout<<"��ʼ¼������"<<endl;
    flag = 0;
    study_timerID = startTimer(1000);
}
