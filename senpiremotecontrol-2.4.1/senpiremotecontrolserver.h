
#ifndef SENPIREMOTECONTROLSERVER_H
#define SENPIREMOTECONTROLSERVER_H

#define LAST_CHANGE __DATE__ " " __TIME__

//#define PORTABLE

#include <QMainWindow>
#include <QtNetwork>
#include <QSystemTrayIcon>
#include <QAbstractButton>
#include <QFileDialog>
#if (QT_VERSION < 0x050000)
#include <QDesktopServices>
#else
#include <QStandardPaths>
#endif
#include <QLocalSocket>
#include <QtConcurrentRun>
#include <QMessageBox>
#include <QEvent>
#include <QKeyEvent>
#include <QLineEdit>
#include <QToolButton>
#include <QMenu>
#include <QClipboard>
#include <QDesktopWidget>
#include "usercommanddialog.h"
#include "helpdialog.h"
#include "icondialog.h"

#ifdef QT_DEBUG
#include <QDebug>
#endif

//#ifdef Q_OS_LINUX
//#define PLAYERCONTROL
//#endif

#ifdef PLAYERCONTROL
#include "./playwolf/playercontroller.h"
#endif

enum UserCommandType { CommandType, ShortcutType, SequenceType};

struct UserCommand {
    UserCommandType type;
    QString name,
            iconPath,
            command,
            parameters,
            shortcut;
    Qt::Key key;
    Qt::KeyboardModifiers modifiers;
    QStringList commandList;
};

typedef struct {
    QString text;
    Qt::Key key;
    Qt::KeyboardModifiers modifiers;
} ButtonSetting;

typedef struct Version_Struct{
    quint8 major;
    quint8 minor;
    quint8 revision;
    bool operator !=(const struct Version_Struct &b)
    {
        return (this->major != b.major) || (this->minor != b.minor) || (this->revision != b.revision);
    }
    bool operator ==(const struct Version_Struct &b)
    {
        return (this->major == b.major) && (this->minor == b.minor) && (this->revision == b.revision);
    }
    bool operator <(const struct Version_Struct &b)
    {
        return (this->major < b.major) || (this->minor < b.minor) || (this->revision < b.revision);
    }
    bool operator >(const struct Version_Struct &b)
    {
        return (this->major > b.major) || (this->minor > b.minor) || (this->revision > b.revision);
    }
    bool operator <=(const struct Version_Struct &b)
    {
        return (this->major <= b.major) && (this->minor <= b.minor) && (this->revision <= b.revision);
    }
    bool operator >=(const struct Version_Struct &b)
    {
        return (this->major >= b.major) && (this->minor >= b.minor) && (this->revision >= b.revision);
    }
} Version;

namespace Ui {
    class SenPiControlServer;
}

class SenPiControlServer : public QMainWindow {
    Q_OBJECT
    Q_PROPERTY(int networkTimeout READ networkTimeout WRITE setNetworkTimeout NOTIFY networkTimeoutChanged)
    Q_PROPERTY(Version clientVersion READ clientVersion WRITE setClientVersion NOTIFY clientVersionChanged)
    Q_PROPERTY(QString language READ language WRITE setLanguage NOTIFY languageChanged)

public:
    SenPiControlServer(QWidget *parent = 0);
    ~SenPiControlServer();

    int networkTimeout() const
    {
        return m_networkTimeout;
    }

    Version clientVersion() const
    {
        return m_clientVersion;
    }

    QString language() const
    {
        return m_language;
    }

public slots:
    void setNetworkTimeout(int arg)
    {
        if (m_networkTimeout != arg) {
            m_networkTimeout = arg;
            networkTimeoutTimer->setInterval(m_networkTimeout);
            emit networkTimeoutChanged(arg);
        }
    }

    void setClientVersion(Version arg)
    {
        if (m_clientVersion != arg) {
            m_clientVersion = arg;
            emit clientVersionChanged(arg);
        }
    }

    void setLanguage(QString arg)
    {
        if (m_language != arg) {
            m_language = arg;

            if(m_language.contains(QString("de"))) {
                m_language = "de";
                translator1->load("de", ":/i18");
                translator4->load("qt_de", ":/i18");
                qApp->installTranslator(translator1);
                qApp->installTranslator(translator4);
               }
            else if(m_language.contains(QString("ru"))) {
                m_language = "ru";
                translator2->load("ru", ":/i18");
                translator4->load("qt_ru", ":/i18");
                qApp->installTranslator(translator2);
                qApp->installTranslator(translator4);
               }
            else if(m_language.contains(QString("uk"))) {
                m_language = "uk";
                translator3->load("uk", ":/i18");
                translator4->load("qt_uk", ":/i18");
                qApp->installTranslator(translator3);
                qApp->installTranslator(translator4);
               }
            else {                                          // english fall through
                m_language = "en";
                qApp->removeTranslator(translator1);
                qApp->removeTranslator(translator2);
                qApp->removeTranslator(translator3);
                qApp->removeTranslator(translator4);
               }
            initializeTrayIcon();
            emit languageChanged(m_language);
        }
    }

signals:
    void networkTimeoutChanged(int arg);

    void clientVersionChanged(Version arg);

    void languageChanged(QString arg);

protected:
    void changeEvent(QEvent *e);
    void showEvent (QShowEvent * event);
    bool eventFilter(QObject *object, QEvent *event);

private:
    Ui::SenPiControlServer    *ui;
    QTcpSocket                  *tcpSocket;
    QUdpSocket                  *udpSocket;
    QSystemTrayIcon             *trayIcon;
    bool                        trayIconVisible;
    QList<UserCommand>          userCommands;
    QList<UserCommand>          tempUserCommands;
    QStringList                 currentSequence;

    //QByteArray passwordHash;
    QString password;
    QString settingsDir;

    Qt::Key                 currentKey;
    Qt::KeyboardModifiers   currentModifiers;

    QTimer               *delayedReleaseTimer;
    Qt::KeyboardModifiers delayedReleaseModifiers;

    //button configuration
    QList<ButtonSetting>    buttonSettingList;
    QList<ButtonSetting>    tmpButtonSettingList;
    QList<QLineEdit*>       lineEditList;
    QList<QToolButton*>     resetButtonList;
    QSignalMapper           *resetButtonMapper;

    QPointF cursorPos;
    bool    autoStartEnabled;

    //network
    QUrl url;
    QNetworkAccessManager qnam;
    QNetworkReply *reply;
    QFile *updateFile;
    QTimer *networkTimeoutTimer;
    bool networkTimeoutResponseReceived;

    // Translators
    QTranslator *translator1;
    QTranslator *translator2;
    QTranslator *translator3;
    QTranslator *translator4;

    void initializeTrayIcon();

#ifdef PLAYERCONTROL
    PlayerController *playerController;
#endif

#ifdef LIGHTCONTROL
    QLocalSocket *localSocket;
void incomingLight(QByteArray data);
#endif

    //button functions
    QList<ButtonSetting> defaultButtonSettings();
    void initializeButtonConfigurator();
    void syncButtonSettings();
    void storeButtonSettings();

    //some functionss
    void setIcon(QString name);
    void setAutostart(bool enabled);
    Version versionFromString(const QString string);
    int getCommandPerName(QString commandName);
    void runCommand(int index, bool pressed);
    void runCommand(const QString name, bool pressed);

    //incoming network functions
    void incomingKey(QByteArray data);
    void incomingText(QByteArray data);
    void incomingMouse(QByteArray data);
    void incomingAction(QByteArray data);
    void incomingButton(QByteArray data);
    void incomingKeepAlive(QByteArray data);
    void incomingVersion(QByteArray data);

    void incomingConnectionRequest();
    void incomingData();

    //outgoing network functionss
    void sendIcons();
    void sendVersion();
#ifdef PLAYERCONTROL
    void sendAmarokData();
#endif

    void sendKeyAndModifiers(Qt::Key key, Qt::KeyboardModifiers modifiers, bool keyPressed);
    void startSequence(QStringList stringList);

    //setting loading and saving to ini
    void loadSettings();
    void saveSettings();

    //loading and saving settings to GUI
    void savePassword();
    void loadConfig();
    void saveConfig();

    //other network functions
    void initializeNetworkTimeoutTimer();

    int m_networkTimeout;

    Version m_clientVersion;

    QString m_language;

private slots:
    void incomingUdpData();
    void incomingButtonDelayedRelease();
    void deleteConnection();
    void socketConnected();
    void saveTempChanges();
    void refreshIpAddress();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void checkNetworkTimeout();

    void doSequence();

    //button configuration
    void resetButtonSetting(int id);

    //single application
    void applicationStarted(const QString &message);

    //update checking, only enabled in Windows
#if defined(Q_OS_WIN) || defined(Q_OS_MAC)
    void checkForUpdates();
    void updateCheckStarted();
    void updateCheckFinished();
#endif

    void on_browseExecutableButton_clicked();
    void on_deleteUserCommand_clicked();
    void on_iconButton_clicked();
    void on_buttonBox_clicked(QAbstractButton* button);
    void on_userCommandsList_currentRowChanged(int currentRow);
    void on_addUserCommand_clicked();
    void on_actionSettings_triggered();
    void on_revertCursorButton_clicked();
    void on_revertScrollButton_clicked();
    void on_revertPortButton_clicked();
    void on_actionAbout_triggered();
    void on_actionHelp_triggered();
    void on_deleteShortcutButton_clicked();
    void on_typeCombo_currentIndexChanged(int index);
    void on_sequenceAddCommandButton_clicked();
    void on_sequenceTimeoutButton_clicked();
    void on_sequenceRemoveButton_clicked();
    void on_revertModifierTimeout_clicked();
    void on_revertTimeoutButton_clicked();
};

#endif // SENPICONTROLSERVER_H
