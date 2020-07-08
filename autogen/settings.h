#ifndef SETTINGS_H
#define SETTINGS_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include <vector>

using namespace std;

//

struct VehiclePropts{
    QString name;
    int number;
    double min0;
    double max0;
    double step;

    QJsonObject toJson(){
        return QJsonObject{
            {"name", name},
            {"number", number},
            {"min0", min0},
            {"max0", max0},
            {"step", step}
        };
    }
};

//

VehiclePropts defaultFuelCapacity();

VehiclePropts defaultTyrePressure();

VehiclePropts defaultCoolantLevel();

VehiclePropts defaultOperatingTemp();

//

struct VehiclesPropts{
    int startRow;
    int endRow;

    QJsonObject toJson(){
        return QJsonObject{
            {"startRow", startRow},
            {"endRow", endRow}
        };
    }
};

//

VehiclesPropts defaultForVehicles();

//

class Settings
{
public:
    Settings();
    ~Settings(){saveToFile();}

    QJsonDocument defaults();
    bool isSettingsValid();
    bool saveToFile();
    bool loadFromFile();

    QString xlFile();
    vector<VehiclePropts> vehiclePropts();
    VehiclesPropts vehiclesPropts();

    void newSettings(QString xl, vector<VehiclePropts> vvp, VehiclesPropts vp);

private:
    QJsonDocument settings;
    QString settingsFileName;
};

#endif // SETTINGS_H
