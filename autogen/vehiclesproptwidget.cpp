#include "vehiclesproptwidget.h"
#include "ui_vehiclesproptwidget.h"
#include "gen.h"

VehiclesProptsWidget::VehiclesProptsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VehiclesProptWidget)
{
    ui->setupUi(this);
}

VehiclesProptsWidget::~VehiclesProptsWidget()
{
    delete ui;
}

void VehiclesProptsWidget::set(VehiclesPropts v)
{
    data=v;
    loadDataToUi();
}

VehiclesPropts VehiclesProptsWidget::get()
{
    return data;
}

void VehiclesProptsWidget::loadDataToUi()
{
    ui->startRow->setText(str(data.startRow).c_str());
    ui->endRow->setText(str(data.endRow).c_str());
}

void VehiclesProptsWidget::saveUiData()
{
    data.startRow = ui->startRow->text().toInt();
    data.endRow = ui->endRow->text().toInt();
}

void VehiclesProptsWidget::on_save_clicked()
{
    saveUiData();
    emit updated();
}
