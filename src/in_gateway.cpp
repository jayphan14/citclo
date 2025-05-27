#include "citclo/in_gateway.h"
#include "citclo/ticker_data.h"
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

CitClo::TickerData CitClo::InGateway::parseData(std::string& data)
{
    CitClo::TickerData ticker;
    std::stringstream ss(data);
    std::string date;
    std::string time;

    std::getline(ss, date, ',');
    std::getline(ss, time, ',');

    std::tm tm = {};
    std::istringstream dtss(date + " " + time);
    dtss >> std::get_time(&tm, "%m/%d/%Y %H:%M:%S");
    if (dtss.fail()) {
        throw std::runtime_error("Failed to parse date/time");
    }

    auto time_c = std::mktime(&tm);
    ticker.timestamp = std::chrono::system_clock::from_time_t(time_c);
    
    std::string token;

    std::getline(ss, token, ',');
    ticker.price = std::stod(token);

    std::getline(ss, token, ',');
    ticker.bid = std::stod(token);

    std::getline(ss, token, ',');
    ticker.ask = std::stod(token);

    std::getline(ss, token, ',');
    ticker.size = std::stod(token);

    return ticker;
};

void CitClo::InGateway::onNewData(std::string data)
{
    CitClo::TickerData td = parseData(data);
    dataBus->publish(td);
};

CitClo::InGateway::InGateway(std::shared_ptr<CitClo::MessageBus<CitClo::TickerData>> bus): dataBus{bus} {}; 