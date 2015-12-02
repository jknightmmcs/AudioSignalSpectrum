#include "audiosignalspectrumwindow.h"
#include "inputdatadialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AudioSignalSpectrumWindow w;
    w.showMaximized();
    
    return a.exec();
}
