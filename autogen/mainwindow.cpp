#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "gen.h"
#include "matrix.h"
#include "qtablewidgetwrapper.h"

#include <QTableWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    xl=nullptr;
    vpw=nullptr;
    isGenAlive = false;

    addVehicleProptsWidgets();
    addVehiclesProptsWidget();
    addXlFileWidget();
}

//

const int sec = 1000;
const int minute = sec * 60;

//

MainWindow::~MainWindow()
{
    delete ui;
    stopGen();
}

void MainWindow::addVehicleProptsWidgets(VehiclePropts v)
{
    QToolBox *toolBox = this->ui->toolBox;

    VehicleProptsWidget *vehicleProptsWidget = new VehicleProptsWidget;
    vehicleProptsWidget->set(v);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(vehicleProptsWidget);
    layout->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    QWidget *w = new QWidget(this);
    w->setLayout(layout);

    vvpw.push_back(vehicleProptsWidget);

    int index = toolBox->count();
    index = toolBox->insertItem(index,w,v.name);

    connect(vehicleProptsWidget, SIGNAL(updated()), this, SLOT(updateSettings()));
}

void MainWindow::addVehicleProptsWidgets()
{
    for(VehicleProptsWidget *vpw: vvpw) vpw->deleteLater();
    vvpw.clear();

    vector<VehiclePropts> vps = settings.vehiclePropts();
    for(VehiclePropts vp: vps) addVehicleProptsWidgets(vp);
}

void MainWindow::addVehiclesProptsWidget()
{
    VehiclesProptsWidget *vehiclesProptsWidget = new VehiclesProptsWidget;
    vehiclesProptsWidget->set(settings.vehiclesPropts());

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(vehiclesProptsWidget);
    layout->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    QWidget *w = new QWidget(this);
    w->setLayout(layout);

    if(vpw!=nullptr)vpw->deleteLater();
    vpw = vehiclesProptsWidget;

    ui->dataRowLayout->addWidget(w);

    connect(vehiclesProptsWidget, SIGNAL(updated()), this, SLOT(updateSettings()));
}

void MainWindow::addXlFileWidget()
{
    XlFileWidget *xlFileWidget = new XlFileWidget;
    xlFileWidget->set(settings.xlFile());

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(xlFileWidget);
    layout->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    QWidget *w = new QWidget(this);
    w->setLayout(layout);

    if(xl!=nullptr) xl->deleteLater();
    xl=xlFileWidget;

    ui->fileNameLayout->addWidget(w);
    ui->fileNameLayout->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

    connect(xlFileWidget, SIGNAL(updated()), this, SLOT(updateSettings()));
}

//

void MainWindow::startGen()
{
    if(isGenAlive) return;

    QEventLoop qel;
    bool isFinished = false;

    std::thread t(
         [&isFinished, &qel, this]{

            setup();
            this->updateStream();

            *m_stopGen = false;
            this->isGenAlive = true;

            while(!(*m_stopGen)){
                Sleep(uint(sec*10));
                change();
                this->updateStream();
            }

            this->isGenAlive = false;

            qel.quit();
            isFinished = true;
        }
    );

    if(!isFinished) qel.exec();
    t.join();
}

void MainWindow::stopGen()
{
    *m_stopGen = true;
}

void MainWindow::updateStream()
{
   Settings settings;
   const int from = settings.vehiclesPropts().startRow;
   const int to = settings.vehiclesPropts().endRow;

   Matrix mat;
   vector<QString> labels;

   for(VehiclePropts vp : settings.vehiclePropts()){
       const int j = vp.number;
       labels.push_back(vp.name);
       vector<double> col = getCol(j,from,to);

       if(mat.rowCount()<col.size()) mat.setRowCount(col.size());
       mat.appendCol(col);
   }

   QTableWidgetWrapper *tableWrapper = new QTableWidgetWrapper(ui->streamTable);
   tableWrapper->addEntries(labels);
   for(vector<double> entries: mat){
       tableWrapper->addEntries(entries);
   }
}

//

void MainWindow::updateSettings()
{
    vector<VehiclePropts> vvp;
    for(VehicleProptsWidget *vpw: vvpw) vvp.push_back(vpw->get());

    VehiclesPropts vp{vpw->get()};

    settings.newSettings(xl->get(),vvp, vp);
}

