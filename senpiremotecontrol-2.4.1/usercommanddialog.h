
#ifndef USERCOMMANDDIALOG_H
#define USERCOMMANDDIALOG_H

#include <QDialog>
#include <QDesktopServices>
#include <QFileDialog>

namespace Ui {
class UserCommandDialog;
}

class UserCommandDialog : public QDialog
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString command READ command WRITE setCommand)
    Q_PROPERTY(QString parameters READ parameters WRITE setParameters)
    
public:
    explicit UserCommandDialog(QWidget *parent = 0);
    ~UserCommandDialog();
    
    QString name() const
    {
        return m_name;
    }

    QString command() const
    {
        return m_command;
    }

    QString parameters() const
    {
        return m_parameters;
    }

public slots:
    void setName(QString arg);
    void setCommand(QString arg);
    void setParameters(QString arg);

private slots:
    void on_nameEdit_editingFinished();

    void on_commandEdit_editingFinished();

    void on_parameterEdit_editingFinished();

    void on_browseCommandButton_clicked();

private:
    Ui::UserCommandDialog *ui;
    QString m_name;
    QString m_command;
    QString m_parameters;
};

#endif // USERCOMMANDDIALOG_H
