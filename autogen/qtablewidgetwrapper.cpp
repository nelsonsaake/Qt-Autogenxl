#include "qtablewidgetwrapper.h"

#include <QHeaderView>

QTableWidgetWrapper::QTableWidgetWrapper(QTableWidget *table)
    : table(table)
{
    resizeTableRows();
}

void QTableWidgetWrapper::resizeTableRows()
{
    if (table==nullptr) return;

    const int rowHeight = 43;
    const int colWidth = 200;

    for(int i=0; i<table->rowCount(); i++){
        table->setRowHeight(i,rowHeight);
    }

    for(int i=0; i<table->columnCount(); i++){
        table->setColumnWidth(i, colWidth);
    }

    table->setMinimumWidth(colWidth*table->columnCount() + 10);
}

void QTableWidgetWrapper::addEntries(vector<double> entries)
{
    vector<QString> str;
    for(double d: entries){
        str.push_back(QString::number(d));
    }
    addEntries(str);
}

void QTableWidgetWrapper::addEntries(vector<QString> entries)
{
    if(table->columnCount()<entries.size()){
       table->setColumnCount(entries.size());
    }

    int row = table->rowCount();
    row ++;
    table->setRowCount(row);
    for(int i=0; i<entries.size(); i++){
        QTableWidgetItem *item = new QTableWidgetItem(entries[i]);
        table->setItem(row-1,i,item);
    }
}




