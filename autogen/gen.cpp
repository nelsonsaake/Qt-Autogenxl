#include "gen.h"
#include "settings.h"
#include "globals.h"

//
bool *m_stopGen = new bool;

//
string str(int i)
{
    ostringstream oss;
    oss << i;
    return oss.str();
}

double genRandomNumber(int min, int max)
{
    qsrand(qrand());
    return qrand() % ((max + 1) - min) + min;
}

//

QString defaultFile {"sheet 11.xlsx"};

//

double readCell(int i, int j)
{
    Settings s;
    Document xlsxR(s.xlFile()); //?
    if (xlsxR.load())
    {
        int row = i; int col = j;
        Cell *cell = xlsxR.cellAt(row, col);
        if (cell != NULL)
        {
            QVariant var = cell->readValue();
            return var.toDouble();
        }
        else error("Error Cell(" + str(row) + ", " + str(col) + ") is NULL");
    }
    else error("Error loading file.");

    return -1;
}

void writeCell(int i, int j, double val)
{
    Settings s;
    Document xlsxR(s.xlFile());
    xlsxR.write(i,j,val);
    xlsxR.save();
}

void setCellData(int i, int j, double min, double max)
{
    double val = genRandomNumber(min,max);
    writeCell(i,j,val);
}

//

vector<double> getCol(int j, int from, int to)
{
    vector<double> col;

    for(int i=from; i<=to; i++){
        double val{readCell(i,j)};
        col.push_back(val);
    }

    return col;
}

void writeCol(int j, int from, int to, vector<double> col)
{
    for(int i=from, vali=0; i<=to&&vali<col.size(); i++, vali++){
        double val=col[vali];
        writeCell(i,j,val);
    }
}

void setCol(int j, int from, int to, double min, double max)
{
    for(int i=from; i<=to; i++){
        setCellData(i,j,min,max);
    }
}

//

void increment(vector<double> &col, double incre_val)
{
    for(double &val : col) val += incre_val;
}

//

void changeVehiclePropts()
{
    Settings settings;
    const int from = settings.vehiclesPropts().startRow;
    const int to = settings.vehiclesPropts().endRow;

    for(VehiclePropts vp : settings.vehiclePropts()){
        const int j = vp.number;

        vector<double> col = getCol(j,from,to);
        increment(col, vp.step);
        writeCol(j,from,to,col);
    }
}

void change()
{
    changeVehiclePropts();
}

//

void setupVehiclePropts()
{
    Settings settings;
    const int from = settings.vehiclesPropts().startRow;
    const int to = settings.vehiclesPropts().endRow;

    for(VehiclePropts vp : settings.vehiclePropts()){
        const int j = vp.number;
        const double min = vp.min0;
        const double max = vp.max0;

        setCol(j,from,to,min,max);
    }
}

void setup()
{
    setupVehiclePropts();
}

//

void dosomething()
{
    setup();

    *m_stopGen = false;
    while(!(*m_stopGen)){
        change();

        const int sec = 1000;
        const int min = sec * 60;

        Sleep(uint(min));
    }
}

