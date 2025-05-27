#pragma once

#include <fstream>
#include <string>
#include <sstream>
#include <functional>

namespace CitClo {

struct DataSource
{
    std::ifstream dataStream;
    std::function<void(std::string)> cb;

    void source(); // source takes in a call back functions
};

} // namespace CitClo