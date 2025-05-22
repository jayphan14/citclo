#include "citclo/data_source.h"
#include "citclo/in_gateway.h"
#include "citclo/message_bus.h"
#include "citclo/signal_generator.h"
#include "citclo/data_store.h"
#include "citclo/ticker_data.h"
#include "citclo/order_data.h"
#include "citclo/linear_regression_strategy.h"

#include "memory"
#include <iostream>


int main()
{
    std::string dataPath = "../data/data.txt";
    std::ifstream file(dataPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << dataPath << '\n';
        return 1;
    }

    auto dataBus = std::make_shared<MessageBus<TickerData>>();

    InGateway inGateway(dataBus);
    
    auto inGatewayCallback =  [&inGateway](std::string data) {inGateway.onNewData(data); }; 

    DataSource dataSource{std::move(file), inGatewayCallback};

    auto orderBus = std::make_shared<MessageBus<OrderData>>();


    auto dataStore = std::make_shared<DataStore>(10000);

    LinearRegressionStrategy linRegStrat(orderBus, dataStore);

    auto linRegStratCallback =  [&linRegStrat](TickerData& data) {linRegStrat.onNewData(data); }; 
    auto dataStoreCallback =  [&dataStore](TickerData& data) {dataStore->onNewData(data); };

    dataBus->subscribe(linRegStratCallback);
    dataBus->subscribe(dataStoreCallback);

    while(true)
    {
        try
        {
            dataSource.source();
        }
        catch (std::runtime_error& e)
        {
            std::cout << e.what() << '\n';
            return 0;
        }
    }
    return 0;
};