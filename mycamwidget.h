#ifndef MYCAMWIDGET_H
#define MYCAMWIDGET_H

#include <QWidget>
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
    QLineEdit *imgSavePath;
    QString ImgPath;
    QLabel *camLabel;
    QImage *qImg;
    QTimer *timer;
    bool camOpenSign = false;

};

#endif // MYCAMWIDGET_H
