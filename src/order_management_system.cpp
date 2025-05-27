#include "citclo/order_management_system.h"
#include <numeric>
#include <algorithm>


void CitClo::OMS::onNewSignal(CitClo::OrderData& order)
{
    double totalVolume = std::accumulate(
        currentPositions.begin(), currentPositions.end(), 0.0,
        [](double sum, const CitClo::OrderData& o) {
            return sum + o.volume;
        }
    );
    
    totalVolume += order.volume;

    if (abs(totalVolume) < 1000000)
    {
        orderBus->publish(order);
    }
    else
    {
        std::cout << "Cant send order because risk limit" << std::endl;
    }
};

void CitClo::OMS::onNewOrderFilled(OrderData& order)
{
    currentPositions.push_back(order);
    double balance = 0;
    int count = 0;
    double vol = 0;
    std::cout << "Current Position: " << std::endl;
    for (auto& order: currentPositions)
    {
        vol += order.volume;
        balance -= (order.price * order.volume);
        count ++;
        if (count < 4)
            std::cout << order << std::endl;
    }
    std::cout << "..." << std::endl;

    std::cout << "Balance: $" << std::fixed << balance << std::endl;
    std::cout << "Total stock held: " << vol << std::endl;
    std::cout << "-------------------- " << std::endl;
    
};

std::vector<CitClo::OrderData> CitClo::OMS::getCurrentPositions()
{
    return currentPositions;
}

CitClo::OrderData CitClo::OMS::getCheapestPosition()
{   
    auto comp = [](const OrderData& pos1,const OrderData& pos2){
        return pos1.price < pos2.price;
    };
    
    return *std::ranges::min_element(this->currentPositions, comp);
}

CitClo::OMS::OMS(std::shared_ptr<CitClo::MessageBus<CitClo::OrderData>> orderBus) : orderBus{orderBus} {};