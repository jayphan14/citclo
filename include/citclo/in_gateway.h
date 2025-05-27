#pragma once

#include <vector>
#include <memory>
#include <string>
#include "citclo/ticker_data.h"
#include "citclo/message_bus.h"

namespace CitClo {

class InGateway
{
private:
    TickerData parseData(std::string& data);
    std::shared_ptr<MessageBus<TickerData>> dataBus{};
public:
    InGateway(std::shared_ptr<MessageBus<TickerData>>);
    void onNewData(std::string data);
};

} // namespace CitClo