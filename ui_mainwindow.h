/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Open;
    QAction *action_SaveDir;
    QWidget *centralWidget;
    QPushButton *Btn_pre;
    QPushButton *Btn_next;
    QLineEdit *lineEdit_class;
    QLabel *labelClassTip;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        action_Open = new QAction(MainWindow);
        action_Open->setObjectName(QStringLiteral("action_Open"));
        action_SaveDir = new QAction(MainWindow);
        action_SaveDir->setObjectName(QStringLiteral("action_SaveDir"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        Btn_pre = new QPushButton(centralWidget);
        Btn_pre->setObjectName(QStringLiteral("Btn_pre"));
        Btn_pre->setGeometry(QRect(630, 180, 80, 24));
        Btn_next = new QPushButton(centralWidget);
        Btn_next->setObjectName(QStringLiteral("Btn_next"));
        Btn_next->setGeometry(QRect(630, 250, 80, 24));
        lineEdit_class = new QLineEdit(centralWidget);
        lineEdit_class->setObjectName(QStringLiteral("lineEdit_class"));
        lineEdit_class->setGeometry(QRect(630, 110, 81, 21));
        labelClassTip = new QLabel(centralWidget);
        labelClassTip->setObjectName(QStringLiteral("labelClassTip"));
        labelClassTip->setGeometry(QRect(560, 110, 71, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addSeparator();
        menu_File->addSeparator();
        menu_File->addAction(action_Open);
        menu_File->addAction(action_SaveDir);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        action_Open->setText(QApplication::translate("MainWindow", "&Open", nullptr));
        action_SaveDir->setText(QApplication::translate("MainWindow", "&SaveDir", nullptr));
        Btn_pre->setText(QApplication::translate("MainWindow", "PRE", nullptr));
        Btn_next->setText(QApplication::translate("MainWindow", "NEXT", nullptr));
        labelClassTip->setText(QApplication::translate("MainWindow", "Class Name:", nullptr));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
