#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "points.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<Points>("Pts", 1, 0, "Points");
    QQmlApplicationEngine engine;

    const QUrl url(u"qml/main.qml"_qs);
    engine.load(url);
    
    return app.exec();
}
