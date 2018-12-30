#pragma once

#include <QtWidgets/QWidget>
#include "ui_DownLoader.h"

class DownLoader : public QWidget
{
	Q_OBJECT

public:
	DownLoader(QWidget *parent = Q_NULLPTR);

private:
	Ui::DownLoaderClass ui;

private slots:
	DownLoader::tool_bt_clicked();
};
