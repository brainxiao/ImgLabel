#ifndef MYCAMWIDGET_H
#define MYCAMWIDGET_H

#include <QWidget>
#include <opencv2/opencv.hpp>
//
//use the QCamera class , but not work
//
//class QCamera;
//class QCameraViewfinder;
//class QCameraImageCapture;
class QPushButton;
class QLabel;
class QLineEdit;
class QImage;

#include <opencv2/opencv.hpp>
class MyCamWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyCamWidget(QWidget *parent = nullptr);
    ~MyCamWidget();
signals:
    void closeSignal();
private slots:
    void CamSlot();
    void camShow();
    void on_close();
    void dirOpenSlot();
    void LineEdit_Open_change_slot();
    void LineEdit_ImgSize_change_slot();
    void LineEdit_ImgName_change_slot();
protected:
    void closeEvent(QCloseEvent *event);
    void keyPressEvent(QKeyEvent *event);
private:
    void connect_init();
    void setting_init();
//    QCamera *camera;
//    QCameraViewfinder *viewfinder;
//    QCameraImageCapture *ImageCapture;

    cv::VideoCapture *capture;//to get the camera capture
    QPushButton *Btn_camStart;
    QPushButton *Btn_close;
    QPushButton *Btn_dirOpen;
    QLabel *imgSavePathtip;
    QLabel *ImgSizetip;
    QLabel *ImgNametip;
    QLineEdit *LineEdit_imgSavePath;
    QLineEdit *LineEdit_ImgSize;
    QLineEdit *LineEdit_ImgName;
    QString ImgPath;
    QString ImgSize;
    QString ImgName;
    QLabel *camLabel;
    QImage *qImg;
    QTimer *timer;
    bool camOpenSign = false;
    cv::Mat srcMat,dstMat;
    int count = 1;

};

#endif // MYCAMWIDGET_H
