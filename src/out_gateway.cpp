// #include "citclo/message_bus.h"
// #include <string>
// #include <memory>

// class IOutGateway
// {
// private:
//     std::shared_ptr<MessageBus<OrderData>> ackBus;
// public:
//     IOutGateway(std::shared_ptr<MessageBus<OrderData>> ackBus) : ackBus{ackBus} {};
//     virtual void onNewAck(std::string ack) = 0;
//     virtual void submitOrder(OrderData order) = 0;
// };


// class NYSEOutGateway: public IOutGateway
// {
//     NYSEOutGateway(std::shared_ptr<MessageBus<OrderData>> ackBus): IOutGateway{ackBus} {}; 
//     void onNewAck(std::string ack) override;
//     void submitOrder(OrderData order) override;
// };

#include "citclo/out_gateway.h"
#include <sstream>

std::unordered_map<int, std::string> IOutGateway::parseFIX(const std::string& fixMessage) {
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

void NYSEOutGateway::onNewAck(std::string ack)
{
    auto parsed = parseFIX(ack);

    if (parsed[150] == "2") // Order filled
    {
        std::string symbol =  parsed[55];
        double price = std::stod(parsed[31]);
        double volume = std::stod(parsed[32]);
        ackBus->publish(OrderData{price, volume});
    }
}

void submitOrder(OrderData order)
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

    std::cout << "Submitting FIX Order: " << fix.str() << std::endl;
}