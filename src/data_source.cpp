#include "citclo/data_source.h"

void DataSource::source()
{
    if (!dataStream.is_open()) {
        throw std::runtime_error("File is not opened");
    }

    std::string nextLine;
    if (!getline(dataStream, nextLine))
        throw std::runtime_error("End of File");

    cb(nextLine);
};