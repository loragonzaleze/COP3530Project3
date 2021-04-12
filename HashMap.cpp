#include "HashMap.h"

void HashMap::LoadDataSet(float pricePoint)
{
	hMap[pricePoint]++;
}


int HashMap::FindQuantityDemanded(float pricePoint)
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


int HashMap::PrintMarketStatus(float m, float c, float pricePoint)
{
    int qtyDemanded = FindQuantityDemanded(pricePoint);
    int qtySupplied = floor((pricePoint - c) / m);
    int status = qtySupplied - qtyDemanded;
    return status;
}


void HashMap::FindEquilibriumPricePoint(float m, float c, float& equilibriumPrice, int& equilibriumQuantity)
{
    int qd = 0;
    bool check = true;
    auto itr = hMap.end();
    --itr;
    while(check)
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