/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *txtEditout;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_3;
    QPushButton *pushButton;
    QLabel *lblOpenFile;
    QPushButton *pushButton_2;
    QLabel *lblSaveFile;
    QLabel *lblDirectory;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout_2;
    QPushButton *btnLoad2;
    QPushButton *btnSave;
    QPushButton *btnClear;
    QSpacerItem *verticalSpacer;
    QTextEdit *txtEdit;
    QPushButton *btnLoad;
    QPushButton *btnsave1;
    QPushButton *btn_temp;
    QTextEdit *txtEditout_2;
    QTextEdit *txtEditout_3;
    QPushButton *pushButton_4;
    QLabel *label_2;
    QLabel *label;
    QPushButton *result_temp;
    QPushButton *result_state;
    QLabel *label_3;
    QLabel *label_4;
    QTextEdit *textEditgetdata;
    QPushButton *btnOpenDoor;
    QPushButton *btnCloseDoor;
    QPushButton *btnchangepassword;
    QTextEdit *textEditchangepassword;
    QMenuBar *menubar;
    QMenu *menuTest_Data;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(719, 427);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        txtEditout = new QTextEdit(centralwidget);
        txtEditout->setObjectName(QString::fromUtf8("txtEditout"));
        txtEditout->setGeometry(QRect(0, 230, 171, 51));
        txtEditout->setMaximumSize(QSize(500000, 16777215));
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 182, 89));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_3 = new QPushButton(layoutWidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 2, 0, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        lblOpenFile = new QLabel(layoutWidget);
        lblOpenFile->setObjectName(QString::fromUtf8("lblOpenFile"));

        gridLayout->addWidget(lblOpenFile, 1, 1, 1, 1);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 1, 0, 1, 1);

        lblSaveFile = new QLabel(layoutWidget);
        lblSaveFile->setObjectName(QString::fromUtf8("lblSaveFile"));

        gridLayout->addWidget(lblSaveFile, 2, 1, 1, 1);

        lblDirectory = new QLabel(layoutWidget);
        lblDirectory->setObjectName(QString::fromUtf8("lblDirectory"));

        gridLayout->addWidget(lblDirectory, 0, 1, 1, 1);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 344, 203));
        gridLayout_2 = new QGridLayout(layoutWidget1);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        btnLoad2 = new QPushButton(layoutWidget1);
        btnLoad2->setObjectName(QString::fromUtf8("btnLoad2"));

        gridLayout_2->addWidget(btnLoad2, 3, 1, 1, 1);

        btnSave = new QPushButton(layoutWidget1);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        gridLayout_2->addWidget(btnSave, 0, 1, 1, 1);

        btnClear = new QPushButton(layoutWidget1);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));

        gridLayout_2->addWidget(btnClear, 5, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 108, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 4, 1, 1, 1);

        txtEdit = new QTextEdit(layoutWidget1);
        txtEdit->setObjectName(QString::fromUtf8("txtEdit"));

        gridLayout_2->addWidget(txtEdit, 0, 0, 6, 1);

        btnLoad = new QPushButton(layoutWidget1);
        btnLoad->setObjectName(QString::fromUtf8("btnLoad"));

        gridLayout_2->addWidget(btnLoad, 1, 1, 1, 1);

        btnsave1 = new QPushButton(layoutWidget1);
        btnsave1->setObjectName(QString::fromUtf8("btnsave1"));

        gridLayout_2->addWidget(btnsave1, 2, 1, 1, 1);

        btn_temp = new QPushButton(centralwidget);
        btn_temp->setObjectName(QString::fromUtf8("btn_temp"));
        btn_temp->setGeometry(QRect(350, 60, 89, 25));
        txtEditout_2 = new QTextEdit(centralwidget);
        txtEditout_2->setObjectName(QString::fromUtf8("txtEditout_2"));
        txtEditout_2->setGeometry(QRect(350, 120, 171, 81));
        txtEditout_2->setMaximumSize(QSize(500000, 16777215));
        txtEditout_3 = new QTextEdit(centralwidget);
        txtEditout_3->setObjectName(QString::fromUtf8("txtEditout_3"));
        txtEditout_3->setGeometry(QRect(530, 120, 181, 81));
        txtEditout_3->setMaximumSize(QSize(500000, 16777215));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(530, 60, 89, 25));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 210, 91, 17));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(350, -30, 361, 99));
        label->setMaximumSize(QSize(16777215, 16777215));
        label->setSizeIncrement(QSize(50, 50));
        label->setBaseSize(QSize(50, 50));
        label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
        result_temp = new QPushButton(centralwidget);
        result_temp->setObjectName(QString::fromUtf8("result_temp"));
        result_temp->setGeometry(QRect(350, 90, 101, 25));
        result_state = new QPushButton(centralwidget);
        result_state->setObjectName(QString::fromUtf8("result_state"));
        result_state->setGeometry(QRect(530, 90, 101, 25));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(430, 220, 111, 21));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(200, 210, 131, 17));
        textEditgetdata = new QTextEdit(centralwidget);
        textEditgetdata->setObjectName(QString::fromUtf8("textEditgetdata"));
        textEditgetdata->setGeometry(QRect(180, 230, 221, 161));
        btnOpenDoor = new QPushButton(centralwidget);
        btnOpenDoor->setObjectName(QString::fromUtf8("btnOpenDoor"));
        btnOpenDoor->setGeometry(QRect(408, 324, 101, 41));
        btnCloseDoor = new QPushButton(centralwidget);
        btnCloseDoor->setObjectName(QString::fromUtf8("btnCloseDoor"));
        btnCloseDoor->setGeometry(QRect(550, 330, 101, 41));
        btnchangepassword = new QPushButton(centralwidget);
        btnchangepassword->setObjectName(QString::fromUtf8("btnchangepassword"));
        btnchangepassword->setGeometry(QRect(560, 210, 121, 31));
        btnchangepassword->setFocusPolicy(Qt::WheelFocus);
        textEditchangepassword = new QTextEdit(centralwidget);
        textEditchangepassword->setObjectName(QString::fromUtf8("textEditchangepassword"));
        textEditchangepassword->setGeometry(QRect(420, 240, 261, 71));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 719, 22));
        menuTest_Data = new QMenu(menubar);
        menuTest_Data->setObjectName(QString::fromUtf8("menuTest_Data"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuTest_Data->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "save File", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Open Diretory", nullptr));
        lblOpenFile->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Open FIle", nullptr));
        lblSaveFile->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        lblDirectory->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
        btnLoad2->setText(QApplication::translate("MainWindow", "Load2", nullptr));
        btnSave->setText(QApplication::translate("MainWindow", "Save", nullptr));
        btnClear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        btnLoad->setText(QApplication::translate("MainWindow", "Load", nullptr));
        btnsave1->setText(QApplication::translate("MainWindow", "Save2", nullptr));
        btn_temp->setText(QApplication::translate("MainWindow", "get Temp", nullptr));
        pushButton_4->setText(QApplication::translate("MainWindow", "get state", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Result Test", nullptr));
        label->setText(QApplication::translate("MainWindow", "Nh\341\272\255n D\341\273\257 Li\341\273\207u LIFI T\341\273\253 Camera v\303\240 Beaglebone Black", nullptr));
        result_temp->setText(QApplication::translate("MainWindow", "Decode temp", nullptr));
        result_state->setText(QApplication::translate("MainWindow", "Decode state", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\304\220\341\273\225i M\341\272\255t Kh\341\272\251u", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "ReceivedData", nullptr));
        btnOpenDoor->setText(QApplication::translate("MainWindow", "Open Door", nullptr));
        btnCloseDoor->setText(QApplication::translate("MainWindow", "Close Door", nullptr));
        btnchangepassword->setText(QApplication::translate("MainWindow", "Change password", nullptr));
        menuTest_Data->setTitle(QApplication::translate("MainWindow", "Test Data", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
