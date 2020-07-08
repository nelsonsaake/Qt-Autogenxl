#ifndef QTABLEWIDGETADJUSTER_H
#define QTABLEWIDGETADJUSTER_H

#include <QTableWidget>
#include <vector>

using namespace std;

class QTableWidgetWrapper
{
public:
    QTableWidgetWrapper(QTableWidget *table);

    void resizeTableRows();

    void addEntries(vector<double> entries);

    void addEntries(vector<QString> entries);

private:
    QTableWidget *table;
};

#endif // QTABLEWIDGETADJUSTER_H
