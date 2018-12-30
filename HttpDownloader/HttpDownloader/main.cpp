#include "HttpDownloader.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HttpDownloader w;
	w.show();
	return a.exec();
}
