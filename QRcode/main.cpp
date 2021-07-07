#include "QRcode.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	QRcodeTest w;
    w.show();
    return a.exec();
}
