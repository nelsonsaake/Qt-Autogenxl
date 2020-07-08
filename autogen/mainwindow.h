#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include "settings.h"
#include "vehicleproptswidget.h"
#include "vehiclesproptwidget.h"
#include "xlfilewidget.h"
#include "thread"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addVehicleProptsWidgets(VehiclePropts v);
    void addVehicleProptsWidgets();
    void addVehiclesProptsWidget();
    void addXlFileWidget();

    void startGen();
    void stopGen();
    void updateStream();

public slots:
    void updateSettings();

private:
    //
    Ui::MainWindow *ui;

    XlFileWidget *xl;
    vector<VehicleProptsWidget *> vvpw;
    VehiclesProptsWidget *vpw;

    Settings settings;    
    bool isGenAlive;
};

#endif // MAINWINDOW_H
