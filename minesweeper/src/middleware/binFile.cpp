/*!

\author         Oliver Blaser

\date           28.12.2020

\copyright      GNU GPLv3 - Copyright (c) 2020 Oliver Blaser

*/

#include "binFile.h"

#include <fstream>
#include <vector>

using namespace std;

middleware::binFile::binFile(const std::string& file)
{
    fileName = file;
}

middleware::binFile::~binFile()
{
}

std::string middleware::binFile::getFileName() const
{
    return fileName;
}

size_t middleware::binFile::read(uint8_t* data, size_t dataLen) const
{
    size_t nBytesRead = 0;

    try
    {
        ifstream file;

        file.open(fileName, ios::binary | ios::in );

        if (file.is_open())
        {
            file.seekg(0, ios::end);
            nBytesRead = file.tellg();
            file.seekg(0, ios::beg);

            if (dataLen < nBytesRead) nBytesRead = dataLen;

            file.read((char*)data, nBytesRead);

            file.close();
        }
        else
        {
            nBytesRead = 0;
        }
    }
    catch (...)
    {
        nBytesRead = 0;
    }

    return nBytesRead;
}

int middleware::binFile::write(const uint8_t* data, size_t writeNBytes) const
{
    int result = 1;

    try
    {
        ofstream file;

        file.open(fileName, ios::binary | ios::out);

        if (file.is_open())
        {
            file.write((char*)data, writeNBytes);

            file.close();
            result = 0;
        }
        else
        {
            result = 2;
        }
    }
    catch (...)
    {
        result = 3;
    }

    return result;
}
