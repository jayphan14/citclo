#pragma once

#include "citclo/signal_generator.h"
#include "citclo/message_bus.h"
#include "citclo/data_store.h"

class LinearRegressionStrategy: public SignalGenerator
{
private:
public:
    LinearRegressionStrategy(std::shared_ptr<MessageBus<OrderData>> orderBus, std::shared_ptr<DataStore> dataStore): SignalGenerator(orderBus, dataStore) {};
    virtual void onNewData(const TickerData& ticker) override;
};