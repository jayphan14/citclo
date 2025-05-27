#pragma once

#include "citclo/signal_generator.h"
#include "citclo/message_bus.h"
#include "citclo/data_store.h"

namespace CitClo {

class LinearRegressionStrategy: public SignalGenerator
{
private:
public:
    LinearRegressionStrategy(std::shared_ptr<MessageBus<OrderData>> signalBus, std::shared_ptr<DataStore> dataStore): SignalGenerator(signalBus, dataStore) {};
    virtual void onNewData(const TickerData& ticker) override;
};

} // namespace CitClo