#include <Eigen/Dense>
#include "citclo/linear_regression_strategy.h"

void CitClo::LinearRegressionStrategy::onNewData(const CitClo::TickerData& ticker)
{
    auto priceHistory = dataStore->getRecentPrice(1000);
    if (priceHistory.size() < 500) return;
    
    size_t N = priceHistory.size();
    Eigen::VectorXd y(N);
    Eigen::MatrixXd X(N, 2);

    for (size_t i = 0; i < N; ++i) {
        y[i] = priceHistory[i];
        X(i, 0) = 1.0;
        X(i, 1) = static_cast<double>(i);
    }
    
    Eigen::VectorXd beta = (X.transpose() * X).ldlt().solve(X.transpose() * y);

    double intercept = beta[0];
    double slope = beta[1];

    double predictedPrice = intercept + slope * (N);
    
    if (ticker.price <= 0.98 * predictedPrice)
    {
        CitClo::OrderData order {ticker.price, ticker.size};
        signalBus->publish(order);
    }
}