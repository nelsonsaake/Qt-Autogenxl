#include "vehicleproptswidget.h"
#include "ui_vehicleproptswidget.h"
#include "gen.h"

VehicleProptsWidget::VehicleProptsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehicleProptsWidget)
{
    ui->setupUi(this);
}

VehicleProptsWidget::~VehicleProptsWidget()
{
    delete ui;
}

void VehicleProptsWidget::set(VehiclePropts v)
{
    data=v;
    loadDataToUi();
}

VehiclePropts VehicleProptsWidget::get()
{
    return data;
}

void VehicleProptsWidget::loadDataToUi()
{
    ui->name->setText(data.name);
    ui->number->setText(str(data.number).c_str());
    ui->min0->setText(QString::number(data.min0));
    ui->max0->setText(QString::number(data.max0));
    ui->increment->setText(QString::number(data.step));
}

void VehicleProptsWidget::saveUiData()
{
   data.name = ui->name->text();
   data.number = ui->number->text().toInt();
   data.min0 = ui->min0->text().toDouble();
   data.max0 = ui->max0->text().toDouble();
   data.step = ui->increment->text().toDouble();
}

void VehicleProptsWidget::on_save_clicked()
{
    saveUiData();
    emit updated();
}
