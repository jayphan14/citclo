#pragma once

// Order Management System
#include "citclo/message_bus.h"
#include "citclo/order_data.h"
#include <deque>
#include <vector>
#include <memory>

class OMS
{
private:
    std::shared_ptr<MessageBus<OrderData>> orderBus;
    std::deque<OrderData> sentOrders {};
    std::deque<OrderData> filledOrders {};
    std::vector<OrderData> currentPositions;
public:
    OMS(std::shared_ptr<MessageBus<OrderData>> orderBus) : orderBus{orderBus} {};
    void onNewSignal(OrderData order);
    // void onNewAck(Ack ) 
    std::vector<OrderData> getCurrentPositions();
};