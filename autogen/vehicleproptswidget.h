#ifndef VEHICLEPROPTSWIDGET_H
#define VEHICLEPROPTSWIDGET_H

#include <QWidget>
#include <settings.h>

namespace Ui {
class VehicleProptsWidget;
}

class VehicleProptsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit VehicleProptsWidget(QWidget *parent = nullptr);
    ~VehicleProptsWidget();

    void set(VehiclePropts v);
    VehiclePropts get();

    void loadDataToUi();
    void saveUiData();

private slots:
    void on_save_clicked();

signals:
    void updated();

private:
    Ui::VehicleProptsWidget *ui;
    VehiclePropts data;
};

#endif // VEHICLEPROPTSWIDGET_H
