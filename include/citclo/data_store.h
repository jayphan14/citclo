#pragma once 

#include <vector>
#include <iostream>

#include "citclo/ticker_data.h"

namespace CitClo {

class DataStore
{
private:
    size_t cap;
    std::deque<TickerData> data;
public:
    DataStore(size_t cap): cap{cap} {};
    void onNewData(TickerData& ticker);
    std::vector<double> getRecentPrice(int numTicker);
};

} // namespace CitClo