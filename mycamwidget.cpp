#include "mycamwidget.h"
#include <QFileDialog>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QStringList>
#include <QKeyEvent>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
using namespace cv;
MyCamWidget::MyCamWidget(QWidget *parent) : QWidget(parent)
{
//    QList<QCameraInfo> cam_list = QCameraInfo::availableCameras();
//    if(cam_list.count() > 0){
//        foreach (const QCameraInfo &cameraInfo, cam_list) {
//            qDebug() << cameraInfo.description();
//        }
//        camera = new QCamera(cam_list.at(0));
//    }
//    viewfinder = new QCameraViewfinder(this);
//    camera -> setViewfinder(viewfinder);
//    viewfinder ->resize(400,300);
//    ImageCapture = new QCameraImageCapture(camera);
//    camera ->start();
    setWindowTitle("Welcom to Camera Widget");
    ImgPath = qEnvironmentVariable("HOME") + QString("/Image");
    capture = new VideoCapture(1);
    ImgSize = QString::number(capture->get(cv::CAP_PROP_FRAME_WIDTH)) +
            QString(",") + QString::number(capture->get(CAP_PROP_FRAME_HEIGHT));
    ImgName = QString("Image");
    Btn_camStart = new QPushButton(this);
    Btn_close = new QPushButton(this);
    imgSavePathtip = new QLabel(this);
    LineEdit_imgSavePath = new QLineEdit(this);
    LineEdit_ImgSize = new QLineEdit(this);
    ImgSizetip = new QLabel(this);
    LineEdit_ImgName = new QLineEdit(this);
    ImgNametip = new QLabel(this);
    Btn_dirOpen = new QPushButton(this);
    camLabel = new QLabel(this);
    qImg = new QImage();
    timer = new QTimer(this);
    setting_init();
    connect_init();
//    srcMat = new Mat();
//    dstMat = new Mat();
}

MyCamWidget::~MyCamWidget()
{
    delete capture;
}

void MyCamWidget::connect_init()
{
    connect(Btn_camStart,&QPushButton::clicked,this,&MyCamWidget::CamSlot);
    connect(Btn_dirOpen,&QPushButton::clicked,this,&MyCamWidget::dirOpenSlot);
    connect(Btn_close,&QPushButton::clicked,this,&MyCamWidget::on_close);
    connect(LineEdit_imgSavePath,&QLineEdit::textChanged,this,&MyCamWidget::LineEdit_Open_change_slot);
    connect(LineEdit_ImgSize,&QLineEdit::textChanged,this,&MyCamWidget::LineEdit_ImgSize_change_slot);
    connect(LineEdit_ImgName,&QLineEdit::textChanged,this,&MyCamWidget::LineEdit_ImgName_change_slot);
    connect(timer,SIGNAL(timeout()),this,SLOT(camShow()));
}

void MyCamWidget::setting_init()
{
    imgSavePathtip->setText("Image save Path:");
    imgSavePathtip->move(10,20);

    LineEdit_imgSavePath->resize(215,30);
    LineEdit_imgSavePath->move(110,10);
    LineEdit_imgSavePath->setText(ImgPath);

    ImgSizetip->setText("OutPut Size:");
    ImgSizetip->move(330,55);

    LineEdit_ImgSize->resize(80,30);
    LineEdit_ImgSize->move(410,45);
    LineEdit_ImgSize->setText(ImgSize);

    ImgNametip->setText("OutPut Name:");
    ImgNametip->move(330,95);

    LineEdit_ImgName->resize(80,30);
    LineEdit_ImgName->move(410,85);
    LineEdit_ImgName->setText(ImgName);

    Btn_dirOpen->setText("OpenDir");
    Btn_dirOpen->move(330,10);
    Btn_dirOpen->resize(50,30);

    Btn_camStart->resize(65,30);
    Btn_camStart->move(330,210);
    Btn_camStart->setText(QString("GET START"));

    Btn_close->resize(65,30);
    Btn_close->move(330,250);
    Btn_close->setText(QString("CLOSE"));

    camLabel->move(5,45);
    camLabel->resize(320,240);
    camLabel->setStyleSheet("background-color: rgb(170, 85, 127);");
    camLabel->setScaledContents(true);
}

void MyCamWidget::camShow()
{
    if(!capture->isOpened()){
        qDebug() << "ERROR!Unable to open camera\n";
        return;
    }
    capture->read(srcMat);
    if(srcMat.empty()){
        qDebug() << "ERROR!blank frame grabbed\n";
        //break;
    }
    cvtColor(srcMat,dstMat,COLOR_BGR2RGB);
    *qImg = QImage((const unsigned char*)(dstMat.data), dstMat.cols, dstMat.rows, QImage::Format_RGB888);
    camLabel->setPixmap(QPixmap::fromImage(*qImg));
}

void MyCamWidget::closeEvent(QCloseEvent *event)
{
    emit closeSignal();
}

void MyCamWidget::keyPressEvent(QKeyEvent *event)
{
    QString Name = ImgPath + QString("/") + ImgName + QString::number(count) + QString(".jpg");
    if(event -> key() == Qt::Key_Return)
    {
        if(camOpenSign)
        {
            int width,height;
            Mat resizedMat;
            QString temp;
            QStringList strList = ImgSize.split(",");
            temp = strList[0];
            width = temp.toInt();
            temp = strList[1];
            height = temp.toInt();
            qDebug() << Name << ImgSize << width << "  " << height;
            cv::resize(srcMat,resizedMat,Size(width,height),0,0);
            imshow("Picture you saved",srcMat);
            imwrite(Name.toStdString(),resizedMat);
            setWindowTitle(Name);
        }
        count++;
    }
}

void MyCamWidget::CamSlot()
{
    camOpenSign = true;
    timer->start(33);
}

void MyCamWidget::dirOpenSlot()
{
    ImgPath = QFileDialog::getExistingDirectory(this,"please pick up a Dir",ImgPath);
    LineEdit_imgSavePath->setText(ImgPath);
}

void MyCamWidget::on_close()
{
    camOpenSign = false;
    close();
}

void MyCamWidget::LineEdit_Open_change_slot()
{
    ImgPath = LineEdit_imgSavePath->text();
}

void MyCamWidget::LineEdit_ImgSize_change_slot()
{
    ImgSize = LineEdit_ImgSize->text();
}

void MyCamWidget::LineEdit_ImgName_change_slot()
{
    ImgName = LineEdit_ImgName->text();
}
