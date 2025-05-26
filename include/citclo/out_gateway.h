#include "citclo/order_data.h"
#include "citclo/message_bus.h"
#include <string>
#include <memory>

class IOutGateway
{
private:
protected:
    std::unordered_map<int, std::string> parseFIX(const std::string& fixMessage);
    std::shared_ptr<MessageBus<OrderData>> ackBus;
public:
    IOutGateway(std::shared_ptr<MessageBus<OrderData>> ackBus) : ackBus{ackBus} {};
    virtual void onNewAck(std::string ack) = 0;
    virtual void onNewOrderRequest(OrderData& orderReq) = 0;
    virtual void submitOrder(OrderData order) = 0;
};


class NYSEOutGateway: public IOutGateway
{
public:
    NYSEOutGateway(std::shared_ptr<MessageBus<OrderData>> ackBus): IOutGateway{ackBus} {}; 
    void onNewAck(std::string ack) override;
    void onNewOrderRequest(OrderData& orderReq) override;
    void submitOrder(OrderData order) override;
};