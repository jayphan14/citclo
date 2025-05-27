#pragma once

#include <chrono>
#include <iomanip>
#include <iostream>

namespace CitClo {

struct TickerData {
    std::chrono::system_clock::time_point timestamp;
    double price;
    double bid;
    double ask;
    double size;
};

inline std::ostream& operator<<(std::ostream& os, const TickerData& td) {
    std::time_t time = std::chrono::system_clock::to_time_t(td.timestamp);
    os << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S")
       << " Price: " << td.price
       << " Bid: " << td.bid
       << " Ask: " << td.ask
       << " Size: " << td.size;
    return os;
}

} // namespace CitClo