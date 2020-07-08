#ifndef VEHICLESPROPTWIDGET_H
#define VEHICLESPROPTWIDGET_H

#include <QWidget>
#include "settings.h"

namespace Ui {
class VehiclesProptWidget;
}

class VehiclesProptsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VehiclesProptsWidget(QWidget *parent = nullptr);
    ~VehiclesProptsWidget();


    void set(VehiclesPropts v);
    VehiclesPropts get();

    void loadDataToUi();
    void saveUiData();

private slots:
    void on_save_clicked();

signals:
    void updated();

private:
    Ui::VehiclesProptWidget *ui;
    VehiclesPropts data;
};

#endif // VEHICLESPROPTWIDGET_H
