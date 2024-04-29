#include "qglobalfakekey_p.h"

/*QGlobalFakeKey::QGlobalFakeKey(QObject *parent) :
    QObject(parent)
{
}*/

Qt::KeyboardModifier const QGlobalFakeKey::AllModifiers[] =
{Qt::ShiftModifier, Qt::ControlModifier, Qt::AltModifier, Qt::MetaModifier, Qt::KeypadModifier};

void QGlobalFakeKey::wait(const int ms)
{
    QTime time;
    time.start();
    while (time.elapsed() < ms)
        ;
}

Qt::Key QGlobalFakeKey::modifierToKey(Qt::KeyboardModifier mod)
{
    switch (mod) {
        case Qt::ShiftModifier:
            return Qt::Key_Shift;
        case Qt::ControlModifier:
            return Qt::Key_Control;
        case Qt::AltModifier:
            return Qt::Key_Alt;
        case Qt::MetaModifier:
            return Qt::Key_Meta;
        case Qt::KeypadModifier:
            return Qt::Key_NumLock;
        default:
            break;
    }
    return Qt::Key(0);
}
