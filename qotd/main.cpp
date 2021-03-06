#include <QGuiApplication>
#include <QQuickView>
#include <QQmlContext>
#include <cudpfetcher.h>
#include <ctcpfetcher.h>

// From https://en.wikipedia.org/wiki/QOTD

/*QString s_Servers [] = {
    "djxmmx.net",
    "alpha.mike-r.com",
    "home.kyleterry.com"
};*/


#define QOTD_PORT 17
#define QOTD_MAX_LEN 512

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQuickView mainView;
    //mainView.rootContext()->setContextProperty("UdpSocket", new CUdpFetcher(&app, QOTD_UDP_PORT, QOTD_UDP_MAX_LEN));
    mainView.rootContext()->setContextProperty("TcpSocket", new CTcpFetcher(&app, "djxmmx.net", QOTD_PORT, QOTD_MAX_LEN));
    mainView.setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    mainView.show();

    return app.exec();
}
