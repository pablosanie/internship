/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_6;
    QLCDNumber *lcdNumber_3;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_5;
    QLCDNumber *lcdNumber_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *inputLineEdit;
    QPushButton *sendButton;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_3;
    QPushButton *generatorButton;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpinBox *periodBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpinBox *perBox;
    QSpacerItem *verticalSpacer_4;
    QVBoxLayout *verticalLayout_3;
    QPushButton *stringGeneratorButton;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_4;
    QSpinBox *sizeBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *portComboBox;
    QPushButton *connectButton;
    QChartView *graph;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(606, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName("formLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lcdNumber = new QLCDNumber(centralwidget);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setTabletTracking(false);
        lcdNumber->setAutoFillBackground(false);
        lcdNumber->setFrameShadow(QFrame::Shadow::Raised);
        lcdNumber->setDigitCount(10);
        lcdNumber->setSegmentStyle(QLCDNumber::SegmentStyle::Filled);

        horizontalLayout->addWidget(lcdNumber);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName("label_6");

        horizontalLayout_9->addWidget(label_6);

        lcdNumber_3 = new QLCDNumber(centralwidget);
        lcdNumber_3->setObjectName("lcdNumber_3");
        lcdNumber_3->setTabletTracking(false);
        lcdNumber_3->setAutoFillBackground(false);
        lcdNumber_3->setFrameShadow(QFrame::Shadow::Raised);
        lcdNumber_3->setDigitCount(10);
        lcdNumber_3->setSegmentStyle(QLCDNumber::SegmentStyle::Filled);

        horizontalLayout_9->addWidget(lcdNumber_3);


        verticalLayout->addLayout(horizontalLayout_9);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");

        horizontalLayout_8->addWidget(label_5);

        lcdNumber_2 = new QLCDNumber(centralwidget);
        lcdNumber_2->setObjectName("lcdNumber_2");
        lcdNumber_2->setTabletTracking(false);
        lcdNumber_2->setAutoFillBackground(false);
        lcdNumber_2->setFrameShadow(QFrame::Shadow::Raised);
        lcdNumber_2->setDigitCount(10);
        lcdNumber_2->setSegmentStyle(QLCDNumber::SegmentStyle::Filled);

        horizontalLayout_8->addWidget(lcdNumber_2);


        verticalLayout->addLayout(horizontalLayout_8);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        inputLineEdit = new QLineEdit(centralwidget);
        inputLineEdit->setObjectName("inputLineEdit");

        horizontalLayout_3->addWidget(inputLineEdit);

        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName("sendButton");

        horizontalLayout_3->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_3);

        generatorButton = new QPushButton(centralwidget);
        generatorButton->setObjectName("generatorButton");

        verticalLayout_2->addWidget(generatorButton);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        horizontalLayout_5->addWidget(label_3);

        periodBox = new QSpinBox(centralwidget);
        periodBox->setObjectName("periodBox");
        periodBox->setMinimum(1);
        periodBox->setMaximum(5000);
        periodBox->setValue(100);

        horizontalLayout_5->addWidget(periodBox);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        horizontalLayout_4->addWidget(label_2);

        perBox = new QSpinBox(centralwidget);
        perBox->setObjectName("perBox");
        perBox->setMaximum(100);

        horizontalLayout_4->addWidget(perBox);


        horizontalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout->addLayout(verticalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        stringGeneratorButton = new QPushButton(centralwidget);
        stringGeneratorButton->setObjectName("stringGeneratorButton");

        verticalLayout_3->addWidget(stringGeneratorButton);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        horizontalLayout_7->addWidget(label_4);

        sizeBox = new QSpinBox(centralwidget);
        sizeBox->setObjectName("sizeBox");

        horizontalLayout_7->addWidget(sizeBox);


        verticalLayout_3->addLayout(horizontalLayout_7);


        verticalLayout->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        portComboBox = new QComboBox(centralwidget);
        portComboBox->setObjectName("portComboBox");

        horizontalLayout_2->addWidget(portComboBox);

        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName("connectButton");

        horizontalLayout_2->addWidget(connectButton);


        verticalLayout->addLayout(horizontalLayout_2);


        formLayout->setLayout(0, QFormLayout::ItemRole::LabelRole, verticalLayout);

        graph = new QChartView(centralwidget);
        graph->setObjectName("graph");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, graph);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 606, 23));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\276 \320\261\320\260\320\271\321\202:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\275\321\217\321\202\320\276 \320\261\320\260\320\271\321\202:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\321\202\320\265\321\200\321\217\320\275\320\276:", nullptr));
        sendButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        generatorButton->setText(QCoreApplication::translate("MainWindow", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\263\320\265\320\275\320\265\321\200\320\260\321\202\320\276\321\200 (1 \320\261\320\260\320\271\321\202)", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\270\320\276\320\264 (\320\274\321\201)", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "% \320\276\321\202\320\277\321\200\320\260\320\262\320\272\320\270", nullptr));
        stringGeneratorButton->setText(QCoreApplication::translate("MainWindow", "\320\241\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214 \320\270 \320\276\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214 \320\277\320\260\320\272\320\265\321\202", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\240\320\260\320\267\320\274\320\265\321\200", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
