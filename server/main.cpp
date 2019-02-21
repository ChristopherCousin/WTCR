#include <QtCore/QCoreApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    TestServer *server = new TestServer(3344);
    QObject::connect(server, &TestServer::closed, &app, &QCoreApplication::quit);

    return app.exec();
}
