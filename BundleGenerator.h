#pragma once
#include <fstream>
#include <iostream>
#include <iomanip>
#include <time.h>
#include "Constant.h"
using namespace std;

class BundleGenerator {
	int noOfOrders;
	int orderID;
	int pcID;
	int quan;
	float unitProfitRate;
public:
	BundleGenerator() {
		noOfOrders = 0;
		orderID = 100;
		pcID = 0;
		quan = 0;
		unitProfitRate = 0;
	}
	void generateOrders();
};

void BundleGenerator::generateOrders() {
	// srand, so every instance of the program creates a new orderbundle
	srand(time(NULL));
	ofstream fout;
	fout.open("orderbundle.txt");
	if (fout.fail()) {
		cout << "Output file opening failed.\n";
		exit(1);
	}

	// Off-by-one, creates the first order outside of the for loop
	pcID = rand() % 16;
	quan = rand() % (MAXORDERQUANTITY + 1) + 1;
	unitProfitRate = rand() % 51 + MINPROFITRATE;

	fout << "[" << 100 << "," << pcID << "," << quan << "," << unitProfitRate << "]";

	// Generates the total number of orders and the for loops begins
	noOfOrders = rand() % 82 + MINORDERBUNDLE;
	for (int i = 101; i <= (noOfOrders+100); i++) {
		pcID = rand() % 16;
		quan = rand() % (MAXORDERQUANTITY+1) + 1;
		unitProfitRate = rand() % 51 + MINPROFITRATE;

		fout << "\n[" << i << "," << pcID << "," << quan << "," << unitProfitRate << "]";
	}
}