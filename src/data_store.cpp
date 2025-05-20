#include "citclo/data_store.h"

void DataStore::onNewData(TickerData& ticker)
{
    if (data.size() > 0 && data.back().price == ticker.price)
    {
        data.back().size += ticker.size;
    }
    else
    {
        data.push_back(ticker);
    }


    if (data.size() > cap)
    {
        data.pop_front();
    }
};


std::vector<double>  DataStore::getRecentPrice(int numTicker)
{
    std::vector<double> prices{};

    for (int i = 1; i <= numTicker; i++)
    {
        if (data.size() - i < 0) break;
        prices.push_back(data[data.size() - i].price);
    }

    return prices;
}