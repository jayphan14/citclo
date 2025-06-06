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

    auto dataBus = std::make_shared<CitClo::MessageBus<CitClo::TickerData>>();

    CitClo::InGateway inGateway(dataBus);
    
    auto inGatewayCallback =  [&inGateway](std::string data) {inGateway.onNewData(data); }; 

    CitClo::DataSource dataSource{std::move(file), inGatewayCallback};

    auto signalBus = std::make_shared<CitClo::MessageBus<CitClo::OrderData>>();


    auto dataStore = std::make_shared<CitClo::DataStore>(10000);



    auto orderBus = std::make_shared<CitClo::MessageBus<CitClo::OrderData>>();
    auto oms = std::make_shared<CitClo::OMS>(orderBus);

    CitClo::LinearRegressionStrategy linRegStrat(signalBus, dataStore, oms);

    auto linRegStratCallback =  [&linRegStrat](CitClo::TickerData& data) {linRegStrat.onNewData(data); }; 
    auto dataStoreCallback =  [&dataStore](CitClo::TickerData& data) {dataStore->onNewData(data); };
    dataBus->subscribe(linRegStratCallback);
    dataBus->subscribe(dataStoreCallback);


    
    auto omsCallback = [&oms](CitClo::OrderData& order) {oms->onNewSignal(order); }; 
    auto omsNewOrderFilledCallback = [&oms](CitClo::OrderData& order) {oms->onNewOrderFilled(order); }; 
    
    signalBus->subscribe(omsCallback);

    auto ackBus = std::make_shared<CitClo::MessageBus<CitClo::OrderData>>();
    ackBus->subscribe(omsNewOrderFilledCallback);

    auto NYSEgw = CitClo::NYSEOutGateway(ackBus);
    auto NYSEgwCallback = [&NYSEgw](CitClo::OrderData& order) {NYSEgw.onNewOrderRequest(order); }; 
    
    orderBus->subscribe(NYSEgwCallback);

    constexpr int NUM_DATAPOINTS = 10000;
    
    for (int i = 0; i < NUM_DATAPOINTS; ++i)
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