#include <vector>
#include <iostream>

#include "citclo/ticker_data.h"

class DataStorage
{
private:
    std::vector<TickerData> data;
public:
    void onNewData(TickerData& ticker)
    {
        std::cout << "Data storaged received new data: " << ticker << '\n';
    }
};