
#include <QCursor>
#include <QApplication>
#include <QMap>
#include <QPair>

#include <ApplicationServices/ApplicationServices.h>
#include <Carbon/Carbon.h>

#include "mac/qcore_mac_p.h"
#include "qglobalfakekey_p.h"

QMap<int,QPair<int,Qt::KeyboardModifiers> > qt_key_to_mac_keycode_make()
{
    QMap<int,QPair<int,Qt::KeyboardModifiers> > m;

    static UInt32 deadKeyState = 0L;
    const UCKeyboardLayout *keyLayout = 0;

#if defined(Q_OS_MAC32)
    KeyboardLayoutRef keyLayoutRef = 0;
    KLGetCurrentKeyboardLayout(&keyLayoutRef);
    OSStatus err;
    if (keyLayoutRef != 0) {
        err = KLGetKeyboardLayoutProperty(keyLayoutRef, kKLuchrData,
                                  (reinterpret_cast<const void **>(&keyLayout)));
        if (err != noErr) {
            qWarning("Qt::internal::unable to get keyboardlayout %ld %s:%d",
                     long(err), __FILE__, __LINE__);
        }
    }
#else
    QCFType<TISInputSourceRef> inputSource = TISCopyCurrentKeyboardInputSource();
    Q_ASSERT(inputSource != 0);
    CFDataRef data = static_cast<CFDataRef>(TISGetInputSourceProperty(inputSource,
                                             kTISPropertyUnicodeKeyLayoutData));
    keyLayout = data ? reinterpret_cast<const UCKeyboardLayout *>(CFDataGetBytePtr(data)) : 0;
#endif

    if (keyLayout) {
        UniChar string[4];
        UniCharCount actualLength;

        for (UInt32 keyCode = 0; keyCode < 128; ++keyCode) {
            if (noErr == UCKeyTranslate(keyLayout, keyCode, kUCKeyActionDisplay, 0, LMGetKbdType(),
                              kUCKeyTranslateNoDeadKeysMask, &deadKeyState, 4, &actualLength, string))
                m.insert(int(string[0]), qMakePair(int(keyCode), Qt::KeyboardModifiers(Qt::NoModifier)));
            if (noErr == UCKeyTranslate(keyLayout, keyCode, kUCKeyActionDisplay, ((shiftKey >> 8) & 0xff), LMGetKbdType(),
                              kUCKeyTranslateNoDeadKeysMask, &deadKeyState, 4, &actualLength, string))
                m.insert(int(string[0]), qMakePair(int(keyCode), Qt::KeyboardModifiers(Qt::ShiftModifier)));
        }
    }
#ifdef Q_OS_MAC32
    else {
        const void *keyboard_layout;
        KeyboardLayoutRef keyLayoutRef = 0;
        KLGetCurrentKeyboardLayout(&keyLayoutRef);
        err = KLGetKeyboardLayoutProperty(keyLayoutRef, kKLKCHRData,
                                  reinterpret_cast<const void **>(&keyboard_layout));

        for (UInt32 keyCode = 0; keyCode < 128; ++keyCode) {
            int translatedChar = KeyTranslate(keyboard_layout, keyCode, &deadKeyState);
            if (translatedChar >= Qt::Key_Space && translatedChar <= Qt::Key_AsciiTilde) {
                m.insert(translatedChar, qMakePair(int(keyCode), Qt::KeyboardModifiers(Qt::NoModifier)));
            }
            translatedChar = KeyTranslate(keyboard_layout, keyCode | shiftKey, &deadKeyState);
            if (translatedChar >= Qt::Key_Space && translatedChar <= Qt::Key_AsciiTilde) {
                m.insert(translatedChar, qMakePair(int(keyCode), Qt::KeyboardModifiers(Qt::ShiftModifier)));
            }

        }
    }
#endif

    m.insert( Qt::Key_Escape,      qMakePair(53, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Tab,         qMakePair(48, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Backspace,   qMakePair(51, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Return,      qMakePair(36, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Enter,       qMakePair(76, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Insert,      qMakePair(114, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Delete,      qMakePair(117, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Print,       qMakePair(105, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Space,       qMakePair(49, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_PageUp,      qMakePair(116, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_PageDown,    qMakePair(121, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_End,         qMakePair(119, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Home,        qMakePair(115, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Left,        qMakePair(123, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Up,          qMakePair(126, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Right,       qMakePair(124, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Down,        qMakePair(125, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_CapsLock,    qMakePair(57, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_NumLock,     qMakePair(71, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F1,          qMakePair(122, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F2,          qMakePair(120, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F3,          qMakePair(99, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F4,          qMakePair(118, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F5,          qMakePair(96, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F6,          qMakePair(97, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F7,          qMakePair(98, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F8,          qMakePair(100, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F9,          qMakePair(101, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F10,         qMakePair(109, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F11,         qMakePair(103, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F12,         qMakePair(111, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F13,         qMakePair(105, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F14,         qMakePair(107, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_F15,         qMakePair(113, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Menu,        qMakePair(110, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Help,        qMakePair(114, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_division,    qMakePair(75, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_multiply,    qMakePair(67, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Minus,       qMakePair(78, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Plus,        qMakePair(69, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Period,      qMakePair(65, Qt::KeyboardModifiers(Qt::NoModifier)) );

    // Modifiers
    m.insert( Qt::ShiftModifier,   qMakePair(56, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Shift,       qMakePair(56, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::ControlModifier, qMakePair(55, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Control,     qMakePair(55, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::AltModifier,     qMakePair(58, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Alt,         qMakePair(58, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::MetaModifier,    qMakePair(59, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_Meta,        qMakePair(55, Qt::KeyboardModifiers(Qt::NoModifier)) );
    m.insert( Qt::Key_CapsLock,    qMakePair(57, Qt::KeyboardModifiers(Qt::NoModifier)) );

    return m;
}

QMap<int,uint> qt_button_to_mac_button_down_make()
{
    QMap<int,uint> m;

    m.insert( Qt::LeftButton,  kCGEventLeftMouseDown );
    m.insert( Qt::MidButton,   kCGEventOtherMouseDown );
    m.insert( Qt::RightButton, kCGEventRightMouseDown );
    return m;
}

QMap<int,uint> qt_button_to_mac_button_up_make()
{
    QMap<int,uint> m;

    m.insert( Qt::LeftButton,  kCGEventLeftMouseUp );
    m.insert( Qt::MidButton,   kCGEventOtherMouseUp );
    m.insert( Qt::RightButton, kCGEventRightMouseUp );
    return m;
}

QMap<int,uint> qt_button_to_mac_button_drag_make()
{
    QMap<int,uint> m;

    m.insert( Qt::LeftButton,  kCGEventLeftMouseDragged );
    m.insert( Qt::MidButton,   kCGEventOtherMouseDragged );
    m.insert( Qt::RightButton, kCGEventRightMouseDragged );
    return m;
}

QMap<int,uint> qt_button_to_mac_button_make()
{
    QMap<int,uint> m;

    m.insert( Qt::LeftButton,  kCGMouseButtonLeft );
    m.insert( Qt::MidButton,   kCGMouseButtonCenter );
    m.insert( Qt::RightButton, kCGMouseButtonRight );
    return m;
}

class QGlobalFakeKeyPrivate
{
public:
    QGlobalFakeKeyPrivate();
    QGlobalFakeKey* q;

    void keyEvent(Qt::Key, bool);
    void mouseEvent(QPoint const&, Qt::MouseButton button, bool down);

    void ensureModifiers(Qt::KeyboardModifiers);
    Qt::KeyboardModifiers currentModifiers() const;

    QMap<int,QPair<int,Qt::KeyboardModifiers> > const keyMap;
    QMap<int,uint> const buttonMap;
    QMap<int,uint> const buttonDownMap;
    QMap<int,uint> const buttonUpMap;
    QMap<int,uint> const buttonDragMap;

    QPoint              currentPos;
    Qt::MouseButtons    currentButtons;
};

QGlobalFakeKeyPrivate::QGlobalFakeKeyPrivate()
    :   keyMap(qt_key_to_mac_keycode_make()),
        buttonMap(qt_button_to_mac_button_make()),
        buttonDownMap(qt_button_to_mac_button_down_make()),
        buttonUpMap(qt_button_to_mac_button_up_make()),
        buttonDragMap(qt_button_to_mac_button_drag_make()),
        currentPos(),
        currentButtons(0)
{
    //Following line is workaround for a bug in Tiger...
    CFRelease(CGEventCreate(NULL));
}

QGlobalFakeKey::QGlobalFakeKey(QObject* parent)
    : QObject(parent),
      d(new QGlobalFakeKeyPrivate)
{
    d->q = this;
}

QGlobalFakeKey::~QGlobalFakeKey()
{
    /*
        Restore all keyboard modifiers to off.
        If we don't do this, the current modifiers stay activated
        even when this application is closed.
        Note that there is no guarantee this code actually gets run.
    */
    //d->ensureModifiers(0);
    /*if (d->currentButtons) {
        d->mouseEvent(d->currentPos, 0);
    }*/

    d->q = 0;
    delete d;
    d = 0;
}

/*
    Returns the Qt keyboard modifiers which are currently pressed.
*/
Qt::KeyboardModifiers QGlobalFakeKeyPrivate::currentModifiers() const
{
    quint32 modifiers = GetCurrentKeyModifiers();

    int state = 0;
    state |= (modifiers & shiftKey ? Qt::ShiftModifier : Qt::NoModifier);
    state |= (modifiers & controlKey ? Qt::ControlModifier : Qt::NoModifier);
    state |= (modifiers & optionKey ? Qt::AltModifier : Qt::NoModifier);
    state |= (modifiers & cmdKey ? Qt::MetaModifier : Qt::NoModifier);

    return Qt::KeyboardModifier(state);
}

void QGlobalFakeKeyPrivate::ensureModifiers(Qt::KeyboardModifiers desiredMod)
{
    Qt::KeyboardModifiers currentMod = currentModifiers();

    // For each modifier..
    for (unsigned i = 0; i < sizeof(q->AllModifiers)/sizeof(Qt::KeyboardModifier); ++i) {
        Qt::KeyboardModifier thisMod = q->AllModifiers[i];
        // If the modifier is currently disabled but we want it enabled, or vice-versa...
        if ((desiredMod & thisMod) && !(currentMod & thisMod)) {
            // press to enable
            keyEvent(q->modifierToKey(thisMod), true);
        } else if (!(desiredMod & thisMod) && (currentMod & thisMod)) {
            // release to disable
            keyEvent(q->modifierToKey(thisMod), false);
        }
    }

    if (currentMod != desiredMod) {
        currentMod = desiredMod;
        for (int i = 0;
                i < 1000 && QApplication::keyboardModifiers() & Qt::KeypadModifier != desiredMod & Qt::KeypadModifier;
                i += 50, QGlobalFakeKey::wait(50))
        {}

#ifdef QT_DEBUG
        if (QApplication::keyboardModifiers() & Qt::KeypadModifier != desiredMod & Qt::KeypadModifier)
            qWarning() << "QGlobalFakeKey: couldn't set all modifiers to desired state! "
                "Current state:" << (void*)(int)QApplication::keyboardModifiers() <<
                "Desired:"       << (void*)(int)desiredMod;
#endif
    }

}

void QGlobalFakeKeyPrivate::keyEvent(Qt::Key key, bool is_press)
{
    int sym = 0;
    Qt::KeyboardModifiers modifiers = Qt::KeyboardModifiers(Qt::NoModifier);
    do {
        QMap<int,QPair<int,Qt::KeyboardModifiers> >::const_iterator found = keyMap.find(key);
        if (found != keyMap.end()) {
            sym = (*found).first;
            if (key < Qt::Key_A || key > Qt::Key_Z)
                modifiers = (*found).second;
            break;
        }

#ifdef QT_DEBUG
        qWarning() << "QGlobalFakeKey: don't know how to translate Qt key"
                   << (void*)key << "into Mac keycode";
#endif
        return;

    } while(0);

    if (modifiers) {
        ensureModifiers(modifiers);
    }

    // TODO: CGPostKeyboardEvent is deprecated in Snow Leopard, however the alternative (using CGEventPost)
    //      does not work as reliably (at least on Tiger/PPC). Further investigation required.
    //CGPostKeyboardEvent(0, (CGKeyCode)sym, is_press);

//#if 0
    CGEventRef event = CGEventCreateKeyboardEvent(NULL, (CGKeyCode)sym, is_press);
    CGEventPost(kCGHIDEventTap, event);
    CFRelease(event);
//#endif

}

void QGlobalFakeKey::sendKey(Qt::Key key, bool down)
{
    d->keyEvent(key, down);

    QGlobalFakeKey::wait(1);
}

void QGlobalFakeKey::sendKeyModifiers(Qt::KeyboardModifiers modifiers, bool down)
{
    if (down)
        d->ensureModifiers(modifiers);
    else
        d->ensureModifiers(0);

    QGlobalFakeKey::wait(1);
}

void QGlobalFakeKeyPrivate::mouseEvent(QPoint const& pos, Qt::MouseButton button, bool down)
{
    CGEventSourceRef source = NULL;
    CGEventType mouseType;
    CGPoint mouseCursorPosition;
    CGMouseButton mouseButton;

    mouseCursorPosition.x = (float)(pos.x());
    mouseCursorPosition.y = (float)(pos.y());

    if (button == Qt::LeftButton)
    {
        mouseButton = kCGMouseButtonLeft;
        if (down)
            mouseType = kCGEventLeftMouseDown;
        else
            mouseType = kCGEventLeftMouseUp;
    }
#if QT_VERSION <= 0x047000
    else if (button == Qt::MidButton)
#else
    else if (button == Qt::MiddleButton)
#endif
    {
        mouseButton = kCGMouseButtonCenter;
        if (down)
            mouseType = kCGEventOtherMouseDown;
        else
            mouseType = kCGEventOtherMouseUp;
    }
    else if (button == Qt::RightButton)
    {
        mouseButton = kCGMouseButtonRight;
        if (down)
            mouseType = kCGEventRightMouseDown;
        else
            mouseType = kCGEventRightMouseUp;
    }

    CGEventRef event = CGEventCreateMouseEvent(source, mouseType, mouseCursorPosition, mouseButton);
    CGEventSetType(event,mouseType);
    CGEventPost(kCGHIDEventTap, event);
    CFRelease(event);

    // Depreaced code
    // CGPostMouseEvent(p, true, 3, Qt::LeftButton & state, Qt::RightButton & state, Qt::MidButton & state);


    //currentButtons = state;
}

void QGlobalFakeKey::sendButton(Qt::MouseButton button, bool down)
{
    QPoint pos = QCursor::pos();
    d->mouseEvent(pos, button, down);

    QGlobalFakeKey::wait(1);
}

void QGlobalFakeKey::sendScroll(int direction, int delta, double acceleration)
{
    if (direction != 1)     //negative scrolls
        acceleration *= -1;

    CGEventSourceRef source = NULL;
    CGScrollEventUnit units = kCGScrollEventUnitLine;
    CGWheelCount wheelCount = 1;
    int32_t wheel1          = (int32_t)(delta*acceleration);

    CGEventRef event = CGEventCreateScrollWheelEvent(source, units, wheelCount, wheel1);
    CGEventSetType(event, units);
    CGEventPost(kCGHIDEventTap, event);
    CFRelease(event);

    QGlobalFakeKey::wait(1);
}
