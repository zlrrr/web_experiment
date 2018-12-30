/********************************************************************************
** Form generated from reading UI file 'DownLoader.ui'
**
** Created by: Qt User Interface Compiler version 5.11.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADER_H
#define UI_DOWNLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DownLoaderClass
{
public:

    void setupUi(QWidget *DownLoaderClass)
    {
        if (DownLoaderClass->objectName().isEmpty())
            DownLoaderClass->setObjectName(QStringLiteral("DownLoaderClass"));
        DownLoaderClass->resize(600, 400);

        retranslateUi(DownLoaderClass);

        QMetaObject::connectSlotsByName(DownLoaderClass);
    } // setupUi

    void retranslateUi(QWidget *DownLoaderClass)
    {
        DownLoaderClass->setWindowTitle(QApplication::translate("DownLoaderClass", "DownLoader", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DownLoaderClass: public Ui_DownLoaderClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADER_H
