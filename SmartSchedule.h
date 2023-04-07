#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include "Order.h"



class SmartSchedule {
private:
	// number members
	int orderID, pcID, quan, profRate, orderCount, cycleCount;
	int compCount[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	int cpuCount[4] = { 0, 0, 0, 0 };
	float totalProfit;
	float totalPenalty;
	float totalDiscount;
	// vector members
	vector<Order> bundle;
	vector<Order> keptOrders;
	vector<Order> canceledOrders;
public:
	SmartSchedule() {
		orderID = 0;
		pcID = 0;
		quan = 0;
		profRate = 0;
		orderCount = 0;
		cycleCount = 0;
		totalProfit = 0;
		totalPenalty = 0;
		totalDiscount = 0;
	}
	void takeOrders();
	void outputOrders();
	void consoleOut();
	void outputPCProduction();
	void countComponent();
	void keepOrders();
};


void SmartSchedule::takeOrders() {
	ifstream orderFile;

	orderFile.open("orderbundle.txt");
	if (orderFile.fail()) {
		cout << "Fuck";
		exit(1);
	}

	// Reads every line of the text file and takes each lines' data to create
	// an object of Order for that specific order
	while (!orderFile.eof()) {
		char deliminator;
		orderID = 0;	pcID = 0;	quan = 0; profRate = 0;
		orderFile.get(deliminator); // "["
		orderFile >> orderID;
		orderFile.get(deliminator); // ","
		orderFile >> pcID;
		orderFile.get(deliminator); // ","
		orderFile >> quan;
		orderFile.get(deliminator); // ","
		orderFile >> profRate;
		orderFile.get(deliminator); // "]"
		orderFile.get(deliminator); // "\n"

		// Create instance of Order and input data
		Order calculate(orderID, pcID, quan, profRate);
		calculate.buildPC();
		// Store object in a vector to be used later
		bundle.push_back(calculate);
		// Increment total order count
		orderCount++;
		
	}
	orderFile.close();

	// Output all orders read to the console
	cout << "Begin order scheduling\n";
	cout << "Total orders: " << orderCount << endl
		 << setw(9) << "OrderId"  << " "
		 << setw(9) << "pcId"  << " "
		 << setw(8) << "qty" << " "
		 << setw(15) << "profitRate" << " "
		 << setw(16) << "totalProfit" << endl;

	// Go through the vector bundle and display data from every object
	// In order: OrderId, pcId, qty, profitRate, totalProfit
	for (int i = 0; i < bundle.size(); i++) {
		cout.precision(0);
		cout << std::right
			 << setw(9) << bundle[i].getOrderID() << " "
			 << setw(9) << bundle[i].getpcID() << " "
			 << setw(8) << bundle[i].getQty() << " "
			 << setw(13) << "%" << bundle[i].PR() << " ";
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << setw(16) << bundle[i].TP() << endl;
	}
	// SmartSchedule - Sorts objects from highest profit to lowest profit
	sort(bundle.begin(), bundle.end(), greater<Order>());
}

void SmartSchedule::keepOrders() {
	// Now that bundle is organised from highest profit to lowest profit, the program can
	// splits the bundle vector into two seperate vectors:
	//	1. keptOrders - all orders that can be carried out are put into here
	//	2. canceledOrders - all orders that go beyond the cycle limit are put here
	for (int i = 0; i < bundle.size(); i++) {
		if ((cycleCount + bundle[i].getCycle()) < CYCLES) {
			keptOrders.push_back(bundle[i]);
			cycleCount += bundle[i].getCycle();
		}
		else
			canceledOrders.push_back(bundle[i]);
	}
}

void SmartSchedule::outputOrders() {
	// Outputs all recorded orders, keptOrders, and canceledOrders into schedule.txt
	ofstream orderOutput;
	orderOutput.open("schedule.txt");
	if (orderOutput.fail()) {
		cout << "Output file opening failed.\n";
		exit(1);
	}

	orderOutput << "\nThe orders to be produced: " << keptOrders.size() << endl
		        << setw(9) << "OrderId" << " "
				<< setw(9) << "pcId" << " "
				<< setw(8) << "qty" << " "
				<< setw(15) << "profitRate" << " "
				<< setw(16) << "totalProfit"
				<< setw(15) << "discount" << endl;

	// Re-sorts the Order objects arranging them by orderID
	sort(keptOrders.begin(), keptOrders.end());

	cout.setf(ios::fixed);
	cout.precision(2);
	for (int i = 0; i < keptOrders.size(); i++) {
		orderOutput.precision(0);
		orderOutput << std::right
					<< setw(9) << keptOrders[i].getOrderID() << " "
					<< setw(9) << keptOrders[i].getpcID() << " "
					<< setw(8) << keptOrders[i].getQty() << " "
					<< setw(13) << "%" << keptOrders[i].PR() << " ";
		orderOutput.setf(ios::fixed);
		orderOutput.precision(2);
		// If the CPU was produced over 500 times then the discounted savings will
		// be displayed and applied to the total profit, otherwise it prints 0.00
		if (cpuCount[keptOrders[i].getCPU()] > 500) {
			orderOutput << setw(16) << keptOrders[i].TP() << " "
						<< setw(14) << keptOrders[i].DD() << endl;
			totalProfit += keptOrders[i].TP() + keptOrders[i].DD();
			totalDiscount += keptOrders[i].DD();
		}
		else {
			orderOutput << setw(16) << keptOrders[i].TP() << " "
						<< setw(14) << 0.00 << endl;
			totalProfit += keptOrders[i].TP();
		}
	}
	orderOutput << setw(6) << "Total amount of Cycles: " << cycleCount << endl;

	orderOutput << "\nThe orders to be cancelled: " << canceledOrders.size() << endl;
	if (canceledOrders.size() > 0) {
		orderOutput << setw(9) << "OrderId" << " "
					<< setw(9) << "pcId" << " "
					<< setw(8) << "qty" << " "
					<< setw(15) << "penalty" << endl;
	}
				

	// Re-sorts the Order objects arranging them by orderID
	sort(canceledOrders.begin(), canceledOrders.end());
	cout.setf(ios::fixed);
	cout.precision(2);
	for (int i = 0; i < canceledOrders.size(); i++) {
		orderOutput.precision(0);
		orderOutput << std::right
					<< setw(9) << canceledOrders[i].getOrderID() << " "
					<< setw(9) << canceledOrders[i].getpcID() << " "
					<< setw(8) << canceledOrders[i].getQty() << " ";
		orderOutput.setf(ios::fixed);
		orderOutput.precision(2);
		orderOutput << setw(15) << canceledOrders[i].penaltyRate() << endl;
		totalProfit += canceledOrders[i].penaltyRate();
		totalPenalty += canceledOrders[i].penaltyRate();
	}

	// Outputs the total profit, total penaly and total discount
	orderOutput << "\nTotal Profit: $" << totalProfit << " (total penalty = $"
				<< totalPenalty << ", total discount = $" << totalDiscount << ")\n"
				<< "Total Production Cycles: " << cycleCount << endl;

	orderOutput.close();
}

void SmartSchedule::consoleOut() {
	// Same as the above function except now the keptOrders and canceled
	// orders are being printed to the console
	cout << "\nThe orders to be produced: " << keptOrders.size() << endl
	     << setw(9) << "OrderId" << " "
		 << setw(9) << "pcId" << " "
		 << setw(8) << "qty" << " "
		 << setw(15) << "profitRate" << " "
		 << setw(16) << "totalProfit"
		 << setw(15) << "discount" << endl;

	// [keptOrders]
	for (int i = 0; i < keptOrders.size(); i++) {	
		cout.precision(0);
		cout << std::right
			<< setw(9) << keptOrders[i].getOrderID() << " "
			<< setw(9) << keptOrders[i].getpcID() << " "
			<< setw(8) << keptOrders[i].getQty() << " "		
		    << setw(13) << "%" << keptOrders[i].PR() << " ";
		cout.setf(ios::fixed);
		cout.precision(2);
		// If the CPU was produced over 500 times then the discounted savings will
		// be displayed and applied to the total profit, otherwise it prints 0.00
		if (cpuCount[keptOrders[i].getCPU()] > 500) {
			cout << setw(16) << keptOrders[i].TP() << " "
				 << setw(14) << keptOrders[i].DD() << endl;
		}
		else {
			cout << setw(16) << keptOrders[i].TP() << " "
				 << setw(14) << 0.00 << endl;
		}	
	}

	// [cancelledOrder]

	cout << "\nThe orders to be cancelled: " << canceledOrders.size() << endl;
	if (canceledOrders.size() > 0) {
		cout << setw(9) << "OrderId" << " "
			 << setw(9) << "pcId" << " "
			 << setw(8) << "qty" << " "
			 << setw(15) << "penalty" << endl;
	}
	

	for (int i = 0; i < canceledOrders.size(); i++) {
		cout.precision(0);
		cout << std::right
			<< setw(9) << canceledOrders[i].getOrderID() << " "
			<< setw(9) << canceledOrders[i].getpcID() << " "
			<< setw(8) << canceledOrders[i].getQty() << " ";
		cout.setf(ios::fixed);
		cout.precision(2);
		cout << setw(15) << canceledOrders[i].penaltyRate() << endl;
	}

	// Display total profit, total penaly and total discount
	cout << "\nTotal Profit: $" << totalProfit << " (total penalty = $"
		 << totalPenalty << ", total discount = $" << totalDiscount << ")\n";
	cout << "Total Production Cycles: " << cycleCount << endl;

}

void SmartSchedule::outputPCProduction() {
	ofstream pcOutput;
	pcOutput.open("productionPlan.txt");
	if (pcOutput.fail()) {
		cout << "Output file opening failed.\n";
		exit(1);
	}

	// Print PC production to productionPlan.txt
	// Goes through all PC's and adds quantity to count if
	// PC id returns true in the Order object
	pcOutput << " pcID" << setw(5) << " " << "amount\n";
	int count;
	for (int i = 0; i <= 15; i++) {
		count = 0;
		for (int j = 0; j < bundle.size(); j++) {	
			if (i == bundle[j].getpcID()) {
				count += bundle[j].getQty();
			}
		}
		pcOutput << std::right
				 << setw(4) << i << ": " 
				 << std::right << setw(10) << count << endl;
	}
	pcOutput.close();
}

void SmartSchedule::countComponent() {
	ofstream compOutput;
	compOutput.open("componentDemand.txt");
	if (compOutput.fail()) {
		cout << "Output file opening failed.\n";
		exit(1);
	}

	// Prints component count to componentDemand.txt
	compOutput << "compID" << setw(5) << " " 
			   << "amount" << setw(4) << " " << "compName\n";

	// Go through every component and add to count the order quantity if component 
	// is present in the Order object
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < bundle.size(); j++) {
			if (bundle[j].getComponent(i)) {
				compCount[i] += bundle[j].getQty();
				if(i<4)
					cpuCount[i] += bundle[j].getQty();
			}
		}
		compOutput << std::right << setw(5) << i << ":" << setw(4) << " ";
		compOutput << std::right << setw(7) << compCount[i] << setw(4) << " ";
		compOutput << std::right << setw(7) << nameMap[i] << endl;
	}
	compOutput.close();

	// Now that the total components have been counted, print potential CPU demand 
	// to the console
	cout << "\nPotential CPU demand: ";
	for (int i = 0; i < 4; i++)
		cout << compCount[i] << "  ";
	cout << endl;
}