#include "citclo/order_management_system.h"
#include <numeric>

void OMS::onNewSignal(OrderData order)
{
    double totalVolume = std::accumulate(
        sentOrders.begin(), sentOrders.end(), 0.0,
        [](double sum, const OrderData& o) {
            return sum + o.volume;
        }
    );
    
    totalVolume += order.volume;

    if (abs(totalVolume) < 1000)
    {
        orderBus->publish(order);
    }
};

std::vector<OrderData> OMS::getCurrentPositions()
{
    return currentPositions;
}