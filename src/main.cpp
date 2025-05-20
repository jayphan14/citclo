#include "citclo/data_source.h"
#include "citclo/in_gateway.h"
#include "citclo/message_bus.h"
#include "citclo/signal_generator.h"
#include "citclo/data_storage.h"

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

    SignalGenerator signalGenerator;
    DataStorage dataStorage;

    auto signalGeneratorCallback =  [&signalGenerator](TickerData data) {signalGenerator.onNewData(data); }; 
    auto dataStorageCallback =  [&dataStorage](TickerData data) {dataStorage.onNewData(data); };

    dataBus->subscribe(signalGeneratorCallback);
    dataBus->subscribe(dataStorageCallback);



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