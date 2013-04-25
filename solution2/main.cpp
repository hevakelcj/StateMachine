#include <QApplication>
#include "videointerface.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VideoInterface dlg;
    dlg.show();
    return a.exec();
}
