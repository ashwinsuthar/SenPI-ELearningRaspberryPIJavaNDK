
#ifndef _QGLOBALFAKEKEY_P_H
#define _QGLOBALFAKEKEY_P_H

#include <QObject>
#include <QKeySequence>
#include <QTime>
//#include "qglobalfakekey_p.h"
#ifdef QT_DEBUG
#include <QDebug>
#endif

class QGlobalFakeKeyPrivate;

class QGlobalFakeKey : public QObject
{
    Q_OBJECT
public:
    explicit QGlobalFakeKey(QObject *parent = 0);
    virtual ~QGlobalFakeKey();

    void sendKey(Qt::Key key, bool down);
    void sendKeyModifiers(Qt::KeyboardModifiers modifiers, bool down);
    void sendButton(Qt::MouseButton button, bool down);
    void sendScroll(int direction, int delta, double acceleration);

private:
    QGlobalFakeKeyPrivate* d;
    friend class QGlobalFakeKeyPrivate;

    static Qt::Key modifierToKey(Qt::KeyboardModifier mod);
    static Qt::KeyboardModifier const AllModifiers[5];

    static void wait(int const ms);
};

#endif // _QGLOBALFAKEKEY_P_H
