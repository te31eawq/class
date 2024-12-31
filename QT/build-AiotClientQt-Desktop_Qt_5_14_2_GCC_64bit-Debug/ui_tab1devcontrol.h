/********************************************************************************
** Form generated from reading UI file 'tab1devcontrol.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TAB1DEVCONTROL_H
#define UI_TAB1DEVCONTROL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDial>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tab1DevControl
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pPBtimerStart;
    QComboBox *pCBtimerValue;
    QPushButton *pPBQuit;
    QHBoxLayout *horizontalLayout_2;
    QDial *pDialLed;
    QLCDNumber *lcdNumber;
    QHBoxLayout *horizontalLayout_3;
    QProgressBar *pProgressBarLed;

    void setupUi(QWidget *Tab1DevControl)
    {
        if (Tab1DevControl->objectName().isEmpty())
            Tab1DevControl->setObjectName(QString::fromUtf8("Tab1DevControl"));
        Tab1DevControl->resize(800, 430);
        verticalLayout = new QVBoxLayout(Tab1DevControl);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pPBtimerStart = new QPushButton(Tab1DevControl);
        pPBtimerStart->setObjectName(QString::fromUtf8("pPBtimerStart"));
        pPBtimerStart->setCheckable(true);

        horizontalLayout->addWidget(pPBtimerStart);

        pCBtimerValue = new QComboBox(Tab1DevControl);
        pCBtimerValue->addItem(QString());
        pCBtimerValue->addItem(QString());
        pCBtimerValue->addItem(QString());
        pCBtimerValue->addItem(QString());
        pCBtimerValue->addItem(QString());
        pCBtimerValue->setObjectName(QString::fromUtf8("pCBtimerValue"));

        horizontalLayout->addWidget(pCBtimerValue);

        pPBQuit = new QPushButton(Tab1DevControl);
        pPBQuit->setObjectName(QString::fromUtf8("pPBQuit"));

        horizontalLayout->addWidget(pPBQuit);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 3);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pDialLed = new QDial(Tab1DevControl);
        pDialLed->setObjectName(QString::fromUtf8("pDialLed"));
        pDialLed->setMaximum(255);
        pDialLed->setTracking(true);
        pDialLed->setInvertedAppearance(false);
        pDialLed->setInvertedControls(false);
        pDialLed->setWrapping(true);
        pDialLed->setNotchesVisible(true);

        horizontalLayout_2->addWidget(pDialLed);

        lcdNumber = new QLCDNumber(Tab1DevControl);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setDigitCount(2);
        lcdNumber->setMode(QLCDNumber::Hex);
        lcdNumber->setSegmentStyle(QLCDNumber::Filled);

        horizontalLayout_2->addWidget(lcdNumber);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pProgressBarLed = new QProgressBar(Tab1DevControl);
        pProgressBarLed->setObjectName(QString::fromUtf8("pProgressBarLed"));
        pProgressBarLed->setMaximum(255);
        pProgressBarLed->setValue(0);

        horizontalLayout_3->addWidget(pProgressBarLed);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 3);
        verticalLayout->setStretch(2, 1);

        retranslateUi(Tab1DevControl);
        QObject::connect(pDialLed, SIGNAL(valueChanged(int)), lcdNumber, SLOT(display(int)));
        QObject::connect(pDialLed, SIGNAL(valueChanged(int)), pProgressBarLed, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(Tab1DevControl);
    } // setupUi

    void retranslateUi(QWidget *Tab1DevControl)
    {
        Tab1DevControl->setWindowTitle(QCoreApplication::translate("Tab1DevControl", "Form", nullptr));
        pPBtimerStart->setText(QCoreApplication::translate("Tab1DevControl", "TimerStart", nullptr));
        pCBtimerValue->setItemText(0, QCoreApplication::translate("Tab1DevControl", "50", nullptr));
        pCBtimerValue->setItemText(1, QCoreApplication::translate("Tab1DevControl", "100", nullptr));
        pCBtimerValue->setItemText(2, QCoreApplication::translate("Tab1DevControl", "200", nullptr));
        pCBtimerValue->setItemText(3, QCoreApplication::translate("Tab1DevControl", "500", nullptr));
        pCBtimerValue->setItemText(4, QCoreApplication::translate("Tab1DevControl", "1000", nullptr));

        pPBQuit->setText(QCoreApplication::translate("Tab1DevControl", "Quit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Tab1DevControl: public Ui_Tab1DevControl {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TAB1DEVCONTROL_H
