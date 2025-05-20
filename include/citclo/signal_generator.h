#include <vector>
#include <iostream>

#include "citclo/ticker_data.h"

class SignalGenerator
{
private:
public:
    void onNewData(TickerData& ticker)
    {
        std::cout << "SignalGenerator received new data: " << ticker << '\n';
    }
};