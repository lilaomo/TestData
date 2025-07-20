#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "ImportData.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    ImportDataController ctrl;
    //1
    ctrl.setData(123, &ImportData::outReso, "4k");
    //2
    ctrl.setOutReso(123, "4k");
    //3
    ctrl.set(123, ImportData{123});


    auto ptr = ctrl.get(123);
    if (ptr) {
        qDebug() << ptr->outReso;
    }

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("CMakeQml", "Main");

    return app.exec();
}
