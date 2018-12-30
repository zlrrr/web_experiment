#include "DownLoader.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DownLoader w;
	w.show();
	return a.exec();
}
