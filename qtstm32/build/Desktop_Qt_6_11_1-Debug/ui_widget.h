/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCharts/QChartView>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QFormLayout *formLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLCDNumber *lcdNumber;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *inputLineEdit;
    QPushButton *sendButton;
    QPushButton *generatorButton;
    QHBoxLayout *horizontalLayout_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpinBox *periodBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpinBox *perBox;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *portComboBox;
    QPushButton *connectButton;
    QChartView *graph;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        formLayout = new QFormLayout(Widget);
        formLayout->setObjectName("formLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(Widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lcdNumber = new QLCDNumber(Widget);
        lcdNumber->setObjectName("lcdNumber");
        lcdNumber->setTabletTracking(false);
        lcdNumber->setAutoFillBackground(false);
        lcdNumber->setFrameShadow(QFrame::Shadow::Raised);
        lcdNumber->setSegmentStyle(QLCDNumber::SegmentStyle::Filled);

        horizontalLayout->addWidget(lcdNumber);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        inputLineEdit = new QLineEdit(Widget);
        inputLineEdit->setObjectName("inputLineEdit");

        horizontalLayout_3->addWidget(inputLineEdit);

        sendButton = new QPushButton(Widget);
        sendButton->setObjectName("sendButton");

        horizontalLayout_3->addWidget(sendButton);


        verticalLayout->addLayout(horizontalLayout_3);

        generatorButton = new QPushButton(Widget);
        generatorButton->setObjectName("generatorButton");

        verticalLayout->addWidget(generatorButton);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_3 = new QLabel(Widget);
        label_3->setObjectName("label_3");

        horizontalLayout_5->addWidget(label_3);

        periodBox = new QSpinBox(Widget);
        periodBox->setObjectName("periodBox");
        periodBox->setMinimum(1);
        periodBox->setMaximum(5000);
        periodBox->setValue(100);

        horizontalLayout_5->addWidget(periodBox);


        horizontalLayout_6->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");

        horizontalLayout_4->addWidget(label_2);

        perBox = new QSpinBox(Widget);
        perBox->setObjectName("perBox");
        perBox->setMaximum(100);

        horizontalLayout_4->addWidget(perBox);


        horizontalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        portComboBox = new QComboBox(Widget);
        portComboBox->setObjectName("portComboBox");

        horizontalLayout_2->addWidget(portComboBox);

        connectButton = new QPushButton(Widget);
        connectButton->setObjectName("connectButton");

        horizontalLayout_2->addWidget(connectButton);


        verticalLayout->addLayout(horizontalLayout_2);


        formLayout->setLayout(0, QFormLayout::ItemRole::LabelRole, verticalLayout);

        graph = new QChartView(Widget);
        graph->setObjectName("graph");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, graph);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "\320\237\320\276\321\201\321\202\321\203\320\277\320\270\320\273\320\276 \320\261\320\260\320\271\321\202:", nullptr));
        sendButton->setText(QCoreApplication::translate("Widget", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", nullptr));
        generatorButton->setText(QCoreApplication::translate("Widget", "\320\222\320\272\320\273\321\216\321\207\320\270\321\202\321\214 \320\263\320\265\320\275\320\265\321\200\320\260\321\202\320\276\321\200", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "\320\237\320\265\321\200\320\270\320\276\320\264 (\320\274\321\201)", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "% \320\276\321\202\320\277\321\200\320\260\320\262\320\272\320\270", nullptr));
        connectButton->setText(QCoreApplication::translate("Widget", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
