#include <QApplication>
#include <QtSingleApplication>
#include "senpicontrolserver.h"

int main(int argc, char *argv[])
{
    QtSingleApplication instance(argc, argv);
    if (instance.sendMessage("hello"))
    {
        qWarning("SenPiControl-Server is already running");
        return 0;
    }

    SenPiControlServer w;
    QApplication::setQuitOnLastWindowClosed(false);

    instance.setActivationWindow(&w);

    QObject::connect(&instance, SIGNAL(messageReceived(const QString&)),
                     &w, SLOT(applicationStarted(QString)));

    return instance.exec();
}
