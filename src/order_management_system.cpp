#include "citclo/order_management_system.h"
#include <numeric>

void CitClo::OMS::onNewSignal(CitClo::OrderData& order)
{
    double totalVolume = std::accumulate(
        sentOrders.begin(), sentOrders.end(), 0.0,
        [](double sum, const CitClo::OrderData& o) {
            return sum + o.volume;
        }
    );
    
    totalVolume += order.volume;

    if (abs(totalVolume) < 1000)
    {
        orderBus->publish(order);
    }
};

std::vector<CitClo::OrderData> CitClo::OMS::getCurrentPositions()
{
    return currentPositions;
}

CitClo::OMS::OMS(std::shared_ptr<CitClo::MessageBus<CitClo::OrderData>> orderBus) : orderBus{orderBus} {};