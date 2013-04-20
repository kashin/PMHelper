#include <QApplication>
#include "src/pmhelperapplication.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    PMHelperApplication helperApplication;
    helperApplication.show();

    return app.exec();
}
