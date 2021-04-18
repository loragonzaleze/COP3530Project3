#include "Map.h"

//Function to load an element into the data structure
//Adds a new key if it is an unique value and sets the corresponding qty to 1
//If it is a duplicate value, it increments the corresponding quantity for the price point
void Map::LoadDataSet(float pricePoint)
{
    hMap[pricePoint]++;
}


//Function to find the Quantity demanded for a particular price point by traversing through the elements
int Map::FindQuantityDemanded(float pricePoint)
{
    int quantity = 0;
    for (auto itr = hMap.begin(); itr != hMap.end(); itr++)
    {
        if (itr->first >= pricePoint)
        {
            quantity = quantity + itr->second;
        }
    }
    return quantity;
}


//Function to find the Market Status with the given constraints
int Map::PrintMarketStatus(float m, float c, float pricePoint)
{
    int qtyDemanded = FindQuantityDemanded(pricePoint);
    int qtySupplied = floor((pricePoint - c) / m);
    int status = qtySupplied - qtyDemanded;
    return status;
}


//Function to find the Equilibrium Price and Equilibrium Quantity by traversing through the elements in a descending order
void Map::FindEquilibriumPricePoint(float m, float c, float& equilibriumPrice, int& equilibriumQuantity)
{
    int qd = 0;
    bool check = true;
    auto itr = hMap.end();
    --itr;
    while (check)
    {
        qd = qd + itr->second;
        int qs = floor((itr->first - c) / m);
        if (qd >= qs)
        {
            equilibriumPrice = itr->first;
            break;
        }
        if (itr == hMap.begin())
        {
            check = false;
        }
        --itr;
    }
    equilibriumQuantity = floor((equilibriumPrice - c) / m);
}