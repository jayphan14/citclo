#pragma once

#include <iostream>

struct OrderData
{
    double price = 0;
    double volume;
};

inline std::ostream& operator<<(std::ostream& os, const OrderData& od) {
    os << "Order "
       << " Price: " << od.price
       << " Size: " << od.volume;
    return os;
}