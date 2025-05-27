#pragma once

#include <string>

namespace CitClo
{
    struct Ack
    {
        std::string symbol; 
        double quantity;
        double price;
    };
}