/********************************************************************************
** Form generated from reading UI file 'HttpDownloader.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HTTPDOWNLOADER_H
#define UI_HTTPDOWNLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HttpDownloaderClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QComboBox *comboBox;
    QToolButton *toolButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HttpDownloaderClass)
    {
        if (HttpDownloaderClass->objectName().isEmpty())
            HttpDownloaderClass->setObjectName(QStringLiteral("HttpDownloaderClass"));
        HttpDownloaderClass->resize(600, 400);
        centralWidget = new QWidget(HttpDownloaderClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 180, 54, 12));
        comboBox = new QComboBox(centralWidget);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(120, 170, 311, 22));
        toolButton = new QToolButton(centralWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(450, 170, 37, 18));
        HttpDownloaderClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HttpDownloaderClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        HttpDownloaderClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(HttpDownloaderClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        HttpDownloaderClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(HttpDownloaderClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        HttpDownloaderClass->setStatusBar(statusBar);

        retranslateUi(HttpDownloaderClass);
        QObject::connect(toolButton, SIGNAL(clicked()), HttpDownloaderClass, SLOT(tool_buttton_clicked()));

        QMetaObject::connectSlotsByName(HttpDownloaderClass);
    } // setupUi

    void retranslateUi(QMainWindow *HttpDownloaderClass)
    {
        HttpDownloaderClass->setWindowTitle(QApplication::translate("HttpDownloaderClass", "HttpDownloader", nullptr));
        label->setText(QApplication::translate("HttpDownloaderClass", "\344\270\213\350\275\275\345\234\260\345\235\200", nullptr));
        toolButton->setText(QApplication::translate("HttpDownloaderClass", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HttpDownloaderClass: public Ui_HttpDownloaderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HTTPDOWNLOADER_H
