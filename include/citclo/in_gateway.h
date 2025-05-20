#pragma once

#include <vector>
#include <memory>
#include <string>
#include "citclo/ticker_data.h"

class InGateway
{
private:
    TickerData parseData(std::string& data);
public:
    InGateway();
    void onNewData(std::string data);
};