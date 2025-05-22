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
    std::deque<OrderData> sent {};
    std::deque<OrderData> filled {};
public:
    void onNewOrder(OrderData order);
    
    std::vector<OrderData> getOutstandingOrder();
};