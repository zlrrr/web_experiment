#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_HttpDownloader.h"

class HttpDownloader : public QMainWindow
{
	Q_OBJECT

public:
	HttpDownloader(QWidget *parent = Q_NULLPTR);

private:
	Ui::HttpDownloaderClass ui;

private slots:
	void tool_button_clicked();
};
