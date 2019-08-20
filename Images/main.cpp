#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*MainWindow w;
    w.show();*/
    OpenGlWidget openGl;
    openGl.setTitle("Images");
	
    // rozmiar okna
    openGl.resize(640,400);
    openGl.show();

    return a.exec();
}
