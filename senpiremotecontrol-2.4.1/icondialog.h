#ifndef ICONDIALOG_H
#define ICONDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QFileDialog>
#include <QDesktopServices>
#include <QPixmap>

namespace Ui {
class IconDialog;
}

class IconDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QIcon icon READ icon)
    Q_PROPERTY(QString fileName READ fileName)
    Q_PROPERTY(QString settingsDir READ settingsDir WRITE setSettingsDir)
    Q_PROPERTY(bool removeIcon READ removeIcon NOTIFY removeIconChanged)
    
public:
    explicit IconDialog(QWidget *parent = 0);
    ~IconDialog();
    
    QIcon icon() const
    {
        return m_icon;
    }

    QString fileName() const
    {
        return m_fileName;
    }

    QString settingsDir() const
    {
        return m_settingsDir;
    }

    bool removeIcon() const
    {
        return m_removeIcon;
    }

public slots:
    void setSettingsDir(QString arg)
    {
        m_settingsDir = arg;
    }

signals:
    void removeIconChanged(bool arg);

private slots:

    void removeButtonClicked();
    void on_buttonBox_accepted();
    void on_buttonBox_helpRequested();

private:
    Ui::IconDialog *ui;
    QIcon m_icon;
    QString m_fileName;
    QString m_settingsDir;
    bool m_removeIcon;
};

#endif // ICONDIALOG_H
