#include "citclo/out_gateway.h"
#include <sstream>
#include <cstdlib>
#include <ctime>

std::unordered_map<int, std::string> CitClo::IOutGateway::parseFIX(const std::string& fixMessage) {
    std::unordered_map<int, std::string> fields;
    std::stringstream ss(fixMessage);
    std::string token;

    while (std::getline(ss, token, '|')) {
        size_t pos = token.find('=');
        if (pos == std::string::npos) continue;

        int tag = std::stoi(token.substr(0, pos));
        std::string value = token.substr(pos + 1);

        fields[tag] = value;
    }

    return fields;
}

void CitClo::NYSEOutGateway::onNewAck(std::string ack)
{
    auto parsed = parseFIX(ack);

    if (parsed[150] == "2" || parsed[150] == "1") // Order filled
    {
        std::string symbol =  parsed[55];
        double price = std::stod(parsed[31]);
        double volume = std::stod(parsed[32]);
        ackBus->publish(CitClo::OrderData{price, volume});
    }
}

void CitClo::NYSEOutGateway::submitOrder(CitClo::OrderData order)
{
    std::ostringstream fix;

        fix << "8=FIX.4.2|"                // fix version
            << "35=D|"                     // message type = new order single
            << "11=jay123|"                // my own order id
            << "55=AAPL|"                  // symbol place holder
            << "54=1|"                     // Buy order
            << "38=" << order.volume << "|" // OrderQty
            << "44=" << order.price << "|"  // Price
            << "40=2|";                    // OrdType = limit

    // std::cout << "Submitting FIX Order: " << fix.str() << std::endl;
    // randomized fill or no filled or partially filled
    getResponse(order); 
}

void CitClo::NYSEOutGateway::onNewOrderRequest(CitClo::OrderData& orderReq)
{
    submitOrder(orderReq);
}

void CitClo::NYSEOutGateway::getResponse(OrderData order)
{
    std::srand(std::time(nullptr));
    int fillType = std::rand() % 3;

    int lastQty = 0;
    std::string ordStatus;
    std::string execType;


    switch (fillType) {
        case 0:
            // No fill
            return;
        case 1:
            // Partial fill
            lastQty = order.volume / 2;
            ordStatus = "1"; // Partially filled
            execType = "1";  // Partial fill
            break;
        case 2:
            // Full fill
            lastQty = order.volume;
            ordStatus = "2"; // Filled
            execType = "2";  // Fill
            break;
    }

    std::ostringstream response;
    response << "8=FIX.4.2|"
               << "35=8|"                // Execution Report
               << "150=" << execType << "|"   // ExecType
               << "39=" << ordStatus << "|"   // OrdStatus
               << "17=exec123|"          // ExecID
               << "11=jay123|"           // ClOrdID
               << "55=AAPL|"             // Symbol
               << "54=1|"                // Side = Buy
               << "38=" << order.volume << "|" // OrderQty
               << "32=" << lastQty << "|"      // LastQty
               << "31=" << order.price << "|"  // LastPx
               << "14=" << lastQty << "|"      // CumQty
               << "151=" << (order.volume - lastQty) << "|" // LeavesQty
               << "6=" << order.price << "|";   // AvgPx
    
    this->onNewAck(response.str());
}