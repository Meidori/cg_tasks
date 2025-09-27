#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    
    QQmlApplicationEngine engine;
    
    const QUrl url(u"qml/main.qml"_qs);
    engine.load(url);
    
    return app.exec();
}
