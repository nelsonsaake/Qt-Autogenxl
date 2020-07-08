#include "settings.h"
#include "fileio.h"
#include "QDebug"

Settings::Settings()
    : settingsFileName("settings.json")
{
    bool isLoaded = false;
    try {
        isLoaded = loadFromFile();
    } catch (runtime_error &e) {
        qDebug() << e.what() << "\n";
    } catch(...){}

    if(!isLoaded){
        qDebug() << "Error loading file.\n";
        qDebug() << "Using defaults.\n";
        settings = defaults();
        return;
    }
}

//

QJsonDocument Settings::defaults()
{
    QJsonArray vehiclePropts{
        defaultFuelCapacity().toJson(),
                defaultTyrePressure().toJson(),
                defaultCoolantLevel().toJson(),
                defaultOperatingTemp().toJson()
    };

    return QJsonDocument{
        QJsonObject {
            {"xlFile", "sheet 11.xlsx"},
            {"vehiclePropts", vehiclePropts},
            {"vehiclesPropts", defaultForVehicles().toJson()}
        }
    };
}

bool Settings::isSettingsValid()
{
    return !settings.isNull();
}

bool Settings::saveToFile()
{
    FileIO settingsFile(settingsFileName.toStdString());

    string data = settings.toJson(QJsonDocument::Indented).toStdString();

    settingsFile.write(data);

    return true;
}

bool Settings::loadFromFile()
{
    FileIO settingsFile(settingsFileName.toStdString());
    QString data = settingsFile.read().c_str();

    QByteArray json = data.toLocal8Bit();
    if(json.isEmpty()){
        qDebug("Error: empty settings file.");
        return false;
    }

    settings = QJsonDocument::fromJson(json);
    if(settings.isEmpty() || !settings.isObject()){
        settings = defaults();
    }

    return true;
}

//

QString Settings::xlFile()
{
    QJsonObject obj = settings.object();
    if(obj.isEmpty()) {
        qDebug() << "Error: json object empty. \n";
        return "";
    }

    return obj.value("xlFile").toString();
}

vector<VehiclePropts> Settings::vehiclePropts()
{
    QJsonObject obj = settings.object();
    QJsonArray array = obj.value("vehiclePropts").toArray();

    vector<VehiclePropts> res;
    for(int i=0; i<array.size(); i++){

        VehiclePropts v;
        QJsonObject obj = array[i].toObject();
        v.name = obj.value("name").toString();
        v.number = obj.value("number").toInt();
        v.max0 = obj.value("max0").toDouble();
        v.min0 = obj.value("min0").toDouble();
        v.step = obj.value("step").toInt();

        res.push_back(v);
    }

    return res;
}

VehiclesPropts Settings::vehiclesPropts()
{
     QJsonObject obj = settings.object();
     obj = obj.value("vehiclesPropts").toObject();

     VehiclesPropts v;
     v.startRow = obj.value("startRow").toInt();
     v.endRow = obj.value("endRow").toInt();

     return v;
}

void Settings::newSettings(QString xl, vector<VehiclePropts> vvp, VehiclesPropts vp)
{
    QJsonArray vehiclePropts;
    for(VehiclePropts vp: vvp){
        vehiclePropts.append(vp.toJson());
    }

    settings = QJsonDocument{
        QJsonObject {
            {"xlFile", xl},
            {"vehiclePropts", vehiclePropts},
            {"vehiclesPropts", vp.toJson()}
        }
    };

    saveToFile();
}

//

VehiclePropts defaultFuelCapacity() {
    VehiclePropts v;
    v.number = 5;
    v.name = "FUEL CAPACITY (L)";
    v.min0 = 795;
    v.max0 = 4992;
    v.step = -1;
    return v;
}

VehiclePropts defaultTyrePressure() {
    VehiclePropts v;
    v.number = 7;
    v.name = "TYRE INFLATION PRESSURE (PSI)";
    v.min0 = 100;
    v.max0 = 105;
    v.step = -1;
    return v;
}

VehiclePropts defaultCoolantLevel() {
    VehiclePropts v;
    v.number = 8;
    v.name = "COOLANT LEVEL (L)";
    v.min0 = 146;
    v.max0 = 1160;
    v.step = -1;
    return v;
}

VehiclePropts defaultOperatingTemp() {
    VehiclePropts v;
    v.number = 10;
    v.name = "NORMINAL OPERATING TEMP. (F)";
    v.min0 = 86;
    v.max0 = 89;
    v.step = 1;
    return v;
}

//

VehiclesPropts defaultForVehicles()
{
    VehiclesPropts v;
    v.startRow = 6;
    v.endRow = 18;
    return v;
}
