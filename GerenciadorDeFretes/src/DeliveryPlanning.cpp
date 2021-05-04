#include "DeliveryPlanning.hpp"
#include <algorithm>


int compatible(std::vector<Delivery *> deliveries, int index){

    for(int j=index - 1; j>=0; j--){
        if(deliveries[j]->getEndTime() < deliveries[index]->getStartTime())
            return j;
    }

    return -1;
}


bool comp(Delivery* a, Delivery *b){
    return a->getEndTime() < b->getEndTime();
}

std::vector<std::pair<Driver *, Delivery *>> DeliveryPlanning::SolveDeliveryPlanning(std::vector<Driver *> drivers, std::vector<Delivery *> deliveries)
{
    std::vector<std::pair<Driver *, Delivery *>> answer;

    std::vector<int> compatibleTasks(deliveries.size());

    for(int i = 0; i < (int)compatibleTasks.size(); ++i)
        compatibleTasks[i] = compatible(deliveries, i);

    std::sort(deliveries.begin(), deliveries.end(), comp);

    for(Driver * driver: drivers){


        std::vector<double> lookupTable(deliveries.size() + 1, 0);

        for(int pos = 1; pos < (int)deliveries.size(); ++pos){

            auto getItem = deliveries[pos-1]->getProfit() + lookupTable[compatibleTasks[pos-1]];
            auto lastItem = lookupTable[pos-1];

            if(getItem  > lastItem){
                lookupTable[pos] = getItem;
                answer.push_back(std::make_pair(driver, deliveries[pos]));

                // make a negative profit, that will make the algorithm ignore 
                // the weight next interation
                deliveries[pos]->setProfit(-1*deliveries[pos]->getProfit());
            }else{
                lookupTable[pos] = lastItem;
            }
        }

    }

    return answer;
}
