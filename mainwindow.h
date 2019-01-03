#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class MyCamWidget;
class MyLabel;
class QStringList;
class QIcon;
class QErrorMessage;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

signals:
    //void allreadyGetPicName();
protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void cameraSlot();
    void cameraCloseSlot();
    void openFile();
    void saveFile();
    void getRect(QPoint p1,QPoint p2);
    void goToNext();
    void goToLast();
    void writeLabel();
private:
    bool ImgShow();
    void connect_init();
    int toRange(int i);
    Ui::MainWindow *ui;
    QString openDirName;
    //the Label show the picture
    MyLabel *imgLabel;
    //the List which save the picture's name
    QStringList fileNameList;

    QString ImageName;

    QIcon *openIcon;
    QIcon *saveIcon;
    QIcon *camIcon;

    QPoint point_1,point_2;

    QString saveDirname;

    QString className = "0";

    int picCount = 0;

    bool save_sign = false;

    QAction *action_save;
    QAction *action_camera;
    MyCamWidget *cam;
};

#endif // MAINWINDOW_H
