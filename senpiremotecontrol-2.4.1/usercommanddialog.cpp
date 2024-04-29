
#include "usercommanddialog.h"
#include "ui_usercommanddialog.h"

UserCommandDialog::UserCommandDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserCommandDialog)
{
    ui->setupUi(this);
    ui->nameEdit->setFocus();
}

UserCommandDialog::~UserCommandDialog()
{
    delete ui;
}

void UserCommandDialog::setName(QString arg)
{
    m_name = arg;
    ui->nameEdit->setText(arg);
    ui->nameEdit->selectAll();
}

void UserCommandDialog::setCommand(QString arg)
{
    m_command = arg;
    //ui->commandEdit->setText(arg);
}

void UserCommandDialog::setParameters(QString arg)
{
    m_parameters = arg;
    //ui->parameterEdit->setText(arg);
}

void UserCommandDialog::on_nameEdit_editingFinished()
{
    m_name = ui->nameEdit->text();
}

void UserCommandDialog::on_commandEdit_editingFinished()
{
    //m_command = ui->commandEdit->text();
}

void UserCommandDialog::on_parameterEdit_editingFinished()
{
    //m_parameters = ui->parameterEdit->text();
}

void UserCommandDialog::on_browseCommandButton_clicked()
{
QString homePath;
#if (QT_VERSION < 0x050000)
    homePath = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
#else
    homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
#endif
    QString fileName = QFileDialog::getOpenFileName( this,
                                                     tr("Open file"),
                                                     homePath,
                                                     tr("All Files (*)"));
    if (!fileName.isNull()) {
        //ui->commandEdit->setText(fileName);
    }
}
