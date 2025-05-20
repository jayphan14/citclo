#include <iostream>
#include "citclo/data_source.h"
#include "citclo/in_gateway.h"

int main()
{
    std::string dataPath = "../data/data.txt";
    std::ifstream file(dataPath);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << dataPath << '\n';
        return 1;
    }

    InGateway inGateway;
    auto inGatewayCallback =  [&inGateway](std::string data) {inGateway.onNewData(data); }; 

    DataSource dataSource{std::move(file), inGatewayCallback};




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