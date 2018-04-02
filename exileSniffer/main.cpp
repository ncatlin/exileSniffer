#include "stdafx.h"
#include "exileSniffer.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	exileSniffer w;
	w.show();
	return a.exec();
}
