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
#include <QKeyEvent>
#include <opencv2/highgui/highgui.hpp>
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
    capture = new VideoCapture(0);
    Btn_camStart = new QPushButton(this);
    Btn_close = new QPushButton(this);
    imgSavePathtip = new QLabel(this);
    imgSavePath = new QLineEdit(this);
    Btn_dirOpen = new QPushButton(this);
    camLabel = new QLabel(this);
    qImg = new QImage();
    timer = new QTimer(this);
    setting_init();
    connect_init();
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
    connect(timer,SIGNAL(timeout()),this,SLOT(camShow()));
}

void MyCamWidget::setting_init()
{
    imgSavePathtip->setText("Image save Path:");
    imgSavePathtip->move(10,20);
    imgSavePath->resize(215,30);
    imgSavePath->move(110,10);
    imgSavePath->setText(ImgPath);
    Btn_dirOpen->setText("OpenDir");
    Btn_dirOpen->move(330,10);
    Btn_dirOpen->resize(50,30);
    Btn_camStart->resize(65,30);
    Btn_camStart->move(330,250);
    Btn_camStart->setText(QString("GET START"));
    Btn_close->resize(65,30);
    Btn_close->move(330,210);
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
    Mat srcMat,dstMat;
    capture->read(srcMat);
    if(srcMat.empty()){
        qDebug() << "ERROR!blank frame grabbed\n";
        //break;
    }
    cvtColor(srcMat,dstMat,COLOR_BGR2RGB);
    dstMat.resize(320,240);
    *qImg = QImage((const unsigned char*)(dstMat.data), dstMat.cols, dstMat.rows, QImage::Format_RGB888);
    camLabel->setPixmap(QPixmap::fromImage(*qImg));
}

void MyCamWidget::closeEvent(QCloseEvent *event)
{
    emit closeSignal();
}

void MyCamWidget::keyPressEvent(QKeyEvent *event)
{
    if(event -> key() == Qt::Key_Return)
    {
        if(camOpenSign)
            qDebug() << "test________";
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
    imgSavePath->setText(ImgPath);
}

void MyCamWidget::on_close()
{
    camOpenSign = false;
    close();
}
