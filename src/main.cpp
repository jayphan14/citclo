#include "citclo/data_source.h"
#include "citclo/in_gateway.h"
#include "citclo/message_bus.h"
#include "citclo/signal_generator.h"
#include "citclo/data_store.h"
#include "citclo/ticker_data.h"
#include "citclo/order_data.h"
#include "citclo/linear_regression_strategy.h"
#include "citclo/order_management_system.h"
#include "citclo/out_gateway.h"

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

    auto signalBus = std::make_shared<MessageBus<OrderData>>();


    auto dataStore = std::make_shared<DataStore>(10000);

    LinearRegressionStrategy linRegStrat(signalBus, dataStore);

    auto linRegStratCallback =  [&linRegStrat](TickerData& data) {linRegStrat.onNewData(data); }; 
    auto dataStoreCallback =  [&dataStore](TickerData& data) {dataStore->onNewData(data); };

    dataBus->subscribe(linRegStratCallback);
    dataBus->subscribe(dataStoreCallback);

    auto orderBus = std::make_shared<MessageBus<OrderData>>();
    auto oms = OMS(orderBus);
    
    auto omsCallback = [&oms](OrderData& order) {oms.onNewSignal(order); }; 
    
    signalBus->subscribe(omsCallback);

    auto ackBus = std::make_shared<MessageBus<OrderData>>();

    auto NYSEgw = NYSEOutGateway(ackBus);

    auto NYSEgwCallback = [&NYSEgw](OrderData& order) {NYSEgw.onNewOrderRequest(order); }; 
    
    orderBus->subscribe(NYSEgwCallback);

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