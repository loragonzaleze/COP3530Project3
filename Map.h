#pragma once
#include <iostream>
#include <map>
#include <cmath>

using namespace std;

//Map Implementation
class Map
{
private:
	//private variable which does not need to be accessed by the user
	map<float, int> hMap;
public:
	//public functions that perform the required tasks
	void LoadDataSet(float pricePoint);
	int FindQuantityDemanded(float pricePoint);
	int PrintMarketStatus(float m, float c, float pricePoint);
	void FindEquilibriumPricePoint(float m, float c, float& equilibriumPrice, int& equilibriumQuantity);
};