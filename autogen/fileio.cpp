#include "fileio.h"
#include <fstream>
#include <stdexcept>

string FileIO::read()
{
    // open file
    ifstream ifs(m_fileName);
    if(!ifs)
    {
        throw(runtime_error{"failed to open file: read(): FileIO"});
    }

    string buffer = "";
    while(!ifs.eof()){
        char ch;
        ifs.get(ch);
        m_data += ch;
    }

    return data();
}

void FileIO::write(string data)
{
    // open file
    ofstream ofs(m_fileName);
    if(!ofs)
    {
        throw(runtime_error{"failed to open file: write(): FileIO"});
    }

    // write data
    ofs << data;
}

