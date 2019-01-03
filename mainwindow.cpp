#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mylabel.h"
#include <QLabel>
#include <QFileDialog>
#include <QDebug>
#include <QStringList>
#include <QAction>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "mycamwidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    point_1(QPoint(0,0)),point_2(QPoint(0,0))
{
    ui->setupUi(this);
    //
    //if you wanna change the default save path you can change here
    //
    saveDirname = qEnvironmentVariable("HOME");
    openIcon = new QIcon(":/open/open.png");
    saveIcon = new QIcon(":/save/save.png");
    camIcon = new QIcon(":/open/cam.jpg");
    imgLabel = new MyLabel(this);
    action_save = new QAction(this);
    action_camera = new QAction(this);
    action_save->setObjectName("action_save");
    action_camera->setObjectName("action_camera");
    action_save->setIcon(*saveIcon);
    action_camera->setIcon(*camIcon);
    action_save->setToolTip(tr("Save the Label"));
    action_camera->setToolTip(tr("open the camera"));
    imgLabel->move(90,90);
    imgLabel -> resize(416,416);
    ui -> action_Open -> setIcon(*openIcon);
    ui -> action_SaveDir -> setIcon(*openIcon);
    ui -> mainToolBar -> addAction(action_save);
    ui -> mainToolBar -> addAction(action_camera);
    setWindowTitle(QString("Proundly Designed By Brain"));
    connect_init();
    ui -> lineEdit_class ->setText(className);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete imgLabel;
    delete openIcon;
    delete saveIcon;
    delete action_save;
}

void MainWindow::connect_init()
{
    connect(ui->action_Open,SIGNAL(triggered(bool)),this,SLOT(openFile()));
    connect(ui->action_SaveDir,SIGNAL(triggered(bool)),this,SLOT(saveFile()));
    connect(imgLabel,SIGNAL(sentRect(QPoint,QPoint)),this,SLOT(getRect(QPoint,QPoint)));
    connect(ui ->Btn_next,SIGNAL(clicked(bool)),this,SLOT(goToNext()));
    connect(ui ->Btn_pre,SIGNAL(clicked(bool)),this,SLOT(goToLast()));
    connect(this->action_save,SIGNAL(triggered(bool)),this,SLOT(writeLabel()));
    connect(this->action_camera,SIGNAL(triggered(bool)),this,SLOT(cameraSlot()));
}

void MainWindow::openFile()
{
    qDebug() << "open a directory which include the pictures";
    openDirName = QFileDialog::getExistingDirectory(this,tr("please pick up a Dir"),"/home/brain/");
    QDir dir(openDirName);
    QStringList fileFilter;
    fileFilter << "*.jpg" << "*.png";
    fileNameList = dir.entryList(fileFilter, QDir::Files|QDir::Readable, QDir::Name);
    qDebug() << "__totally " << fileNameList.count() << "pictures.__" << endl;
    if(ImgShow())
        QMessageBox::about(this,tr("Tip"),tr("Don't forget to rechange your class!!!"));
}

bool MainWindow::ImgShow()
{
    ImageName =  openDirName + QString("/") + fileNameList[picCount];
    setWindowTitle(ImageName);
    //qDebug() << ImageName;
    QImage qimg;
    qimg.load(ImageName);
    if(qimg.isNull())
    {
        QMessageBox::critical(this,tr("ERROR"),
                              tr("please select a directory within pictures"),QMessageBox::YesAll);
        return false;
    }
    imgLabel -> setPixmap(QPixmap::fromImage(qimg));
    save_sign = false;
    return true;
}

void MainWindow::getRect(QPoint p1, QPoint p2)
{
    ui -> statusBar -> showMessage(tr("Point1: %1,%1  Point2: %3,%4 ").
                                   arg(QString::number(p1.x())).arg(QString::number(p1.y())).
                                   arg(QString::number(p2.x())).arg(QString::number(p2.y())));
    point_1 = p1;
    point_2 = p2;
    //qDebug() << p1.x() << " " << p1.y() << " " << p2.x() << " " << p2.y() << endl;
    //qDebug() << "get";
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event -> modifiers() == Qt::ControlModifier){
        if(event -> key() == Qt::Key_S)
            writeLabel();
    }
}

void MainWindow::writeLabel()
{
    if(fileNameList.isEmpty()//if didn't paint a rectanle you can not save
            ||point_1.isNull()||point_2.isNull()
            ||(point_1.x() == 0 && point_1.y() == 0 && point_2.x() == 0 && point_2.y() == 0))
        return;
    QString com(",");
    QString space(" ");
    QString labelLine,existImageName;
    QFile out_file(QString(saveDirname + "/train.txt"));
    out_file.open(QIODevice::ReadWrite|QIODevice::Append);
    out_file.seek(0);
    while(!out_file.atEnd())
    {
        labelLine = out_file.readLine(100);
        existImageName = labelLine.split(space).at(0);
        qDebug() << existImageName;
        if(existImageName == ImageName)
        {
            if(QMessageBox::warning(this,tr("Warnning"),
                                 tr("you have already save this Label,You Sure to save angin?"),
                                 QMessageBox::Yes,QMessageBox::No) == QMessageBox::No)
                return;
            else
                break;
        }
    }
    out_file.seek(out_file.size());
    QTextStream text_strm(&out_file);
    className = ui -> lineEdit_class ->text()!=className? ui -> lineEdit_class ->text():className;
    text_strm << ImageName << space <<
                 toRange(point_1.x()) << com << toRange(point_1.y()) << com
              << toRange(point_2.x()) << com << toRange(point_2.y()) << com << className << "\n";
    out_file.close();
    save_sign = true;
}

void MainWindow::saveFile()
{
    saveDirname = QFileDialog::getExistingDirectory(this,tr("Save to"),saveDirname);
}

void MainWindow::goToNext()
{
    if(picCount == fileNameList.count() - 1)
    {
        QMessageBox::critical(this,tr("ERROR"),
                                        tr("aleardy the Last"),QMessageBox::YesAll);
        return;
    }
    if(!save_sign)
    {
        int ret = QMessageBox::question(this,tr("Warnning"),
                                        tr("you have not save the label,you sure to skip?"),
                                        QMessageBox::Yes,QMessageBox::No);
        if(ret == QMessageBox::No)
            return;
    }
    picCount++;
    ImgShow();
}
void MainWindow::goToLast()
{
    if(picCount == 0)
    {
        QMessageBox::critical(this,tr("ERROR"),
                                        tr("aleardy the first"),QMessageBox::YesAll);
        return;
    }
    if(!save_sign)
    {
        int ret = QMessageBox::question(this,tr("Warnning"),
                                        tr("you have not save the label,you sure to skip?"),
                                        QMessageBox::Yes,QMessageBox::No);
        if(ret == QMessageBox::No)
            return;
    }
    picCount--;
    ImgShow();
}

int MainWindow::toRange(int i)
{
    if(i < 0)
        return 0;
    else if(i > 416)
        return 416;
    else
        return i;
}

void MainWindow::cameraSlot()
{
    cam = new MyCamWidget();
    connect(cam,SIGNAL(closeSignal()),this,SLOT(cameraCloseSlot()));//important
    cam->resize(400,300);
    cam->show();
}

void MainWindow::cameraCloseSlot()
{
    delete cam;
}
