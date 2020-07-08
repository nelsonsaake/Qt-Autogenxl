#ifndef FILEIO_H_INCLUDED
#define FILEIO_H_INCLUDED

#include <iostream>

using namespace std;

//
class FileIO
{
public:
    FileIO(string fileName):m_fileName(fileName) {}

    string data() const
    {
        return m_data;
    }

    void printData() const
    {
        for(const char& ch: m_data)
        {
            cout << ch;
        }
    }

    string read();

    void write(string);

private:
    string m_fileName;      // fileName
    string m_data;
};

#endif
