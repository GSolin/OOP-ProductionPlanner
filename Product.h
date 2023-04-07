#pragma once

#include <vector>
using namespace std;
#include "Constant.h"
#include "Component.h"

class Product {
private:
	int PC_ID;
	int cycles;
	int value;
	int discValue;
	Component parts;
public:
	void buildPC (int ID) {
		PC_ID = ID;
		parts.components(PC_ID);
		cycles = compCycles[ID];
	}
	int getPrice();
	bool getComponent(int id);
	int discountedPC();
	int getCPU();
};

// returns the value of the PC
int Product::getPrice() {
	value = 0;
	value = parts.totalCost();
	value += (cycles * CYCLEPRICE);
	return value;
}

// calculates cost of PC with discounted cpu
int Product::discountedPC() {
	discValue = 0;
	discValue = parts.discCost();
	discValue += (cycles * CYCLEPRICE);
	return discValue;
}

// Checks if specific component is present in Product object
bool Product::getComponent(int id) {
	
	if (parts.comp(id))
		return true;
	else
		return false;
}

int Product::getCPU() {
	return parts.getCPU();
}