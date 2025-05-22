#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include "citclo/ticker_data.h"
#include "citclo/order_data.h"
#include "citclo/data_store.h"
#include "citclo/message_bus.h"

class SignalGenerator
{
protected:
    std::shared_ptr<MessageBus<OrderData>> orderBus;
    std::shared_ptr<DataStore> dataStore;
public:
    SignalGenerator(std::shared_ptr<MessageBus<OrderData>> orderBus, std::shared_ptr<DataStore> dataStore): orderBus {orderBus}, dataStore{dataStore} {}; 
    virtual ~SignalGenerator() = default;
    virtual void onNewData(const TickerData& ticker) = 0;
};