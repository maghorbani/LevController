#include "MainWindow.h"
#include <QApplication>


#include <spdlog/spdlog.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    spdlog::set_level(spdlog::level::trace);
//    spdlog::set_pattern("[%5i] %v");
    spdlog::debug("Started");
    MainWindow w;
    w.show();

    return a.exec();
}
