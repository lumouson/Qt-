/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *open_LED;
    QPushButton *close_LED;
    QPushButton *open_RELAY;
    QPushButton *close_RELAY;
    QPushButton *open_FAN;
    QPushButton *close_FAN;
    QPushButton *open_BUZZER;
    QPushButton *close_BUZZER;
    QLabel *label_show;
    QPushButton *open_camera;
    QPushButton *end_camera;
    QPushButton *face_train;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(537, 512);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        open_LED = new QPushButton(centralWidget);
        open_LED->setObjectName(QStringLiteral("open_LED"));
        open_LED->setGeometry(QRect(10, 10, 89, 24));
        close_LED = new QPushButton(centralWidget);
        close_LED->setObjectName(QStringLiteral("close_LED"));
        close_LED->setGeometry(QRect(10, 40, 89, 24));
        open_RELAY = new QPushButton(centralWidget);
        open_RELAY->setObjectName(QStringLiteral("open_RELAY"));
        open_RELAY->setGeometry(QRect(110, 10, 89, 24));
        close_RELAY = new QPushButton(centralWidget);
        close_RELAY->setObjectName(QStringLiteral("close_RELAY"));
        close_RELAY->setGeometry(QRect(110, 40, 89, 24));
        open_FAN = new QPushButton(centralWidget);
        open_FAN->setObjectName(QStringLiteral("open_FAN"));
        open_FAN->setGeometry(QRect(210, 10, 89, 24));
        close_FAN = new QPushButton(centralWidget);
        close_FAN->setObjectName(QStringLiteral("close_FAN"));
        close_FAN->setGeometry(QRect(210, 40, 89, 24));
        open_BUZZER = new QPushButton(centralWidget);
        open_BUZZER->setObjectName(QStringLiteral("open_BUZZER"));
        open_BUZZER->setGeometry(QRect(320, 10, 89, 24));
        close_BUZZER = new QPushButton(centralWidget);
        close_BUZZER->setObjectName(QStringLiteral("close_BUZZER"));
        close_BUZZER->setGeometry(QRect(320, 40, 89, 24));
        label_show = new QLabel(centralWidget);
        label_show->setObjectName(QStringLiteral("label_show"));
        label_show->setGeometry(QRect(50, 150, 421, 201));
        open_camera = new QPushButton(centralWidget);
        open_camera->setObjectName(QStringLiteral("open_camera"));
        open_camera->setGeometry(QRect(10, 80, 89, 24));
        end_camera = new QPushButton(centralWidget);
        end_camera->setObjectName(QStringLiteral("end_camera"));
        end_camera->setGeometry(QRect(110, 80, 89, 24));
        face_train = new QPushButton(centralWidget);
        face_train->setObjectName(QStringLiteral("face_train"));
        face_train->setGeometry(QRect(270, 80, 89, 24));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 537, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        open_LED->setText(QApplication::translate("MainWindow", "\345\274\200LED", Q_NULLPTR));
        close_LED->setText(QApplication::translate("MainWindow", "\345\205\263LED", Q_NULLPTR));
        open_RELAY->setText(QApplication::translate("MainWindow", "\345\274\200\351\227\250\347\246\201", Q_NULLPTR));
        close_RELAY->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\250\347\246\201", Q_NULLPTR));
        open_FAN->setText(QApplication::translate("MainWindow", "\345\274\200\351\243\216\346\211\207", Q_NULLPTR));
        close_FAN->setText(QApplication::translate("MainWindow", "\345\205\263\351\243\216\346\211\207", Q_NULLPTR));
        open_BUZZER->setText(QApplication::translate("MainWindow", "\345\274\200\350\234\202\351\270\243\345\231\250", Q_NULLPTR));
        close_BUZZER->setText(QApplication::translate("MainWindow", "\345\205\263\350\234\202\351\270\243\345\231\250", Q_NULLPTR));
        label_show->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        open_camera->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        end_camera->setText(QApplication::translate("MainWindow", "\345\205\263\351\227\255\346\221\204\345\203\217\345\244\264", Q_NULLPTR));
        face_train->setText(QApplication::translate("MainWindow", "\345\275\225\345\205\245\344\272\272\350\204\270", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
