#pragma once

#include "Product.h"
#include "Constant.h"

class Order {
private:
	Product build;
	// Four main attributes
	int orderID;
	int PCID;
	int quantity;
	float profitRate;

	// Calculated values
	float PCCost;
	float unitProfit;
	float totalProfit;

	// Discount Values
	float unitProfitWithDiscount;
	float totalProfitWithDiscount;
	float discountDifference;

public:
	Order(int oID, int pID, int quan, float PR) {
		orderID = oID;
		PCID = pID;
		quantity = quan;
		profitRate = PR;
		PCCost = 0;
		unitProfit = 0;
		totalProfit = 0;
		unitProfitWithDiscount = 0;
		totalProfitWithDiscount = 0;
		discountDifference = 0;
	}
	void buildPC();
	int getOrderID();
	int getpcID();
	int getQty();
	float PR();
	float UP();
	float TP();
	float TPWD();
	float DD();
	bool getComponent(int id);
	int getCycle();
	int getCPU();
	float penaltyRate();
	bool operator<(const Order& right) const;
	bool operator>(const Order& right) const;
};

void Order::buildPC() {
	// Order receives pcID from Schedule and takes that number
	// to the Product class to build the PC
	build.buildPC(PCID);
	// Tells the Product class to return the value of all components + cycles
	PCCost = build.getPrice();
	// Calculate net profit
	unitProfit = PCCost * (profitRate / 100);
	// Calculate net profit times the amount of PC's to be produced
	totalProfit = unitProfit * quantity;

	// This section of the function calculates the discounted values
	unitProfitWithDiscount = build.discountedPC() * (profitRate / 100);
	totalProfitWithDiscount = unitProfitWithDiscount * quantity;
	discountDifference = totalProfit - totalProfitWithDiscount;
}

int Order::getOrderID() {
	return orderID;
}

int Order::getpcID() {
	return PCID;
}

int Order::getQty() {
	return quantity;
}

float Order::PR() {
	return profitRate;
}

float Order::UP() {
	return unitProfit;
}

float Order::TP() {
	return totalProfit;
}

float Order::TPWD() {
	return totalProfitWithDiscount;
}

float Order::DD() {
	return discountDifference;
}

bool Order::getComponent(int id) {
	// Asks the Product class if a specific component is present in the 
	// object of Product
	if (build.getComponent(id))
		return true;
	else
		return false;
}

int Order::getCycle() {
	return compCycles[PCID];
}

float Order::penaltyRate() {
	totalProfit -= totalProfit * CANCELLATIONPENALTY;
	return totalProfit;
}

int Order::getCPU() {
	return build.getCPU();
}

// Greater than operator, used for sorting the Order vectors by highest profit
bool Order::operator>(const Order& right) const {
	return (totalProfit > right.totalProfit);
}

// Less then operator, used for sorting the Order vectors by the OrderID
bool Order::operator<(const Order& right) const {
	return (orderID < right.orderID);
}

