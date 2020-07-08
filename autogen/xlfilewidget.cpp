#include "xlfilewidget.h"
#include "ui_xlfilewidget.h"

XlFileWidget::XlFileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::xlFile)
{
    ui->setupUi(this);
}

XlFileWidget::~XlFileWidget()
{
    delete ui;
}

void XlFileWidget::loadDataToUi()
{
    ui->filePath->setText(filePath);
}

void XlFileWidget::saveUiData()
{
    filePath = ui->filePath->text();
}

QString XlFileWidget::get() const
{
    return filePath;
}

void XlFileWidget::set(const QString &value)
{
    filePath = value;
    loadDataToUi();
}

void XlFileWidget::on_save_clicked()
{
    saveUiData();
    emit updated();
}
