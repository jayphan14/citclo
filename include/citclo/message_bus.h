// Unbuffered Message Bus

#pragma once
#include <vector>
#include "citclo/order_data.h"

namespace CitClo {

template <typename T>
class MessageBus
{
private:
    std::vector<std::function<void(T& )>> subscribers{};
public:
    void subscribe( std::function<void(T& )> sub)
    {
        subscribers.push_back(sub);
    };

    void publish(T message)
    {
        for (auto& sub : subscribers)
        {
            sub(message);
        }
    };
};

} // namespace CitClo

