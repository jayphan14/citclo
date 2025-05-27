#pragma once

#include <iostream>

namespace CitClo {

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

} // namespace CitClo