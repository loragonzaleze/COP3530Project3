#ifndef HASHMAP_H
#define HASHMAP_H

#pragma once
#include <iostream>
#include <map>
#include <cmath>

using namespace std;

class HashMap
{
private:
    map<float, int> hMap;
public:
    void LoadDataSet(float pricePoint);
    int FindQuantityDemanded(float pricePoint);
    int PrintMarketStatus(float m, float c, float pricePoint);
    void FindEquilibriumPricePoint(float m, float c, float& equilibriumPrice, int& equilibriumQuantity);
};



#endif // HASHMAP_H
