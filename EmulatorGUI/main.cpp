#include "EmulatorGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	EmulatorGUI w;
	w.show();
	return a.exec();
}
