#ifndef GEN_H
#define GEN_H

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

#include <vector>
#include <stdexcept>
#include <sstream>

#include <QDebug>
#include <windows.h>

using namespace QXlsx;
using namespace std;

string str(int i);
void dosomething();

void setup();
void change();

vector<double> getCol(int j, int from, int to);

extern bool *m_stopGen;

#endif // GEN_H
