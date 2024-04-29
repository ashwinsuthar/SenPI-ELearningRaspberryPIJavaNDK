#include "icondialog.h"
#include "ui_icondialog.h"

IconDialog::IconDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IconDialog)
{
    ui->setupUi(this);

    m_removeIcon = false;

    QPushButton *button = new QPushButton(tr("Browse..."), this);
    QPushButton *button2 = new QPushButton(tr("Remove"), this);
    ui->buttonBox->addButton(button, QDialogButtonBox::HelpRole);
    ui->buttonBox->addButton(button2, QDialogButtonBox::DestructiveRole);
    connect(button2, SIGNAL(clicked()),
            this, SLOT(removeButtonClicked()));
}

IconDialog::~IconDialog()
{
    delete ui;
}

void IconDialog::removeButtonClicked()
{
    m_removeIcon = true;
    emit removeIconChanged(true);
    this->reject();
}

void IconDialog::on_buttonBox_accepted()
{
    QString fileName = QString("%1/%2.png").arg(m_settingsDir).arg(ui->listWidget->currentRow());
    m_icon = ui->listWidget->currentItem()->icon();
    m_icon.pixmap(64).save(fileName);
    m_fileName = fileName;
}

void IconDialog::on_buttonBox_helpRequested()
{
    QString homePath;
#if (QT_VERSION < 0x050000)
    homePath = QDesktopServices::storageLocation(QDesktopServices::HomeLocation);
#else
    homePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
#endif
    QString fileName = QFileDialog::getOpenFileName( this,
                                                     tr("Open icon"),
                                                     homePath,
                                                     tr("Images (*.png *.xpm *.jpg *.bmp)"));
    if (!fileName.isNull()) {
        m_icon = QIcon(fileName);
        m_fileName = fileName;
        this->accept();
    }
}
