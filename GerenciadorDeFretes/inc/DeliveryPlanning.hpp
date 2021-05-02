#ifndef _DELIVERY_PLANNING_HPP_
#define _DELIVERY_PLANNING_HPP_

#include "Delivery.hpp"
#include "Driver.hpp"
#include "Time.hpp"

#include <vector>
#include <utility>

namespace DeliveryPlanning
{
    std::vector<std::pair<Driver *, Delivery *>> SolveDeliveryPlanning(std::vector<Driver *> drivers, std::vector<Delivery *> deliveries);
}

#endif