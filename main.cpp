#include "ncnndlg.h"
#include <QApplication>
#include <stdio.h>
#undef stderr

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NCNNDlg w;
    w.show();

    return a.exec();
}
