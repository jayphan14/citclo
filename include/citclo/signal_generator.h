#pragma once

#include <vector>
#include <iostream>
#include <memory>
#include "citclo/ticker_data.h"
#include "citclo/order_data.h"
#include "citclo/data_store.h"
#include "citclo/message_bus.h"
#include "citclo/order_management_system.h"

namespace CitClo {

class SignalGenerator
{
protected:
    std::shared_ptr<MessageBus<OrderData>> signalBus;
    std::shared_ptr<DataStore> dataStore;
    std::shared_ptr<OMS> oms;
public:
    SignalGenerator(
        std::shared_ptr<MessageBus<OrderData>> signalBus,
        std::shared_ptr<DataStore> dataStore,
        std::shared_ptr<OMS> oms
    ) : signalBus{signalBus},
        dataStore{dataStore},
        oms{oms} {};
    virtual ~SignalGenerator() = default;
    virtual void onNewData(const TickerData& ticker) = 0;
};

} // namespace CitClo