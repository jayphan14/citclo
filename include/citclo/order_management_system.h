#pragma once

// Order Management System
#include "citclo/message_bus.h"
#include "citclo/order_data.h"
#include <deque>
#include <vector>
#include <memory>

namespace CitClo {

class OMS
{
private:
    std::shared_ptr<MessageBus<OrderData>> orderBus;
    // std::deque<OrderData> sentOrders {};
    // std::deque<OrderData> filledOrders {};
    std::vector<OrderData> currentPositions{};
public:
    OMS(std::shared_ptr<MessageBus<OrderData>> orderBus);
    void onNewSignal(OrderData& order);
    void onNewOrderFilled(OrderData& order);
    

    // Positions API
    std::vector<OrderData> getCurrentPositions();
    OrderData getCheapestPosition();
};

} // namespace CitClo