#pragma once
#include <string>
using namespace std;

const int cycleMap[] = { 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7 };

const int compMap[16][4] = { { 0, 4, 6, 8 }, { 0, 4, 6, 9 }, { 0, 4, 7, 8 }, { 0, 4, 7, 9 }, 
							 { 1, 4, 6, 8 }, { 1, 4, 6, 9 }, { 1, 4, 7, 8 }, { 1, 4, 7, 9 }, 
							 { 2, 5, 6, 8 }, { 2, 5, 6, 9 }, { 2, 5, 7, 8 }, { 2, 5, 7, 9 }, 
							 { 3, 5, 6, 8 }, { 3, 5, 6, 9 }, { 3, 5, 7, 8 }, { 3, 5, 7, 9 }};

const int compPrice[] = { 1000, 1500, 1000, 1500, 250, 250, 100, 200, 300, 400 };

const int compCycles[] = { 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7 };

const string nameMap[] = { "Pintel CPU 3 GHz", "Pintel CPU 5 GHz", "IMD CPU 3GHz", "IMD CPU 5GHz", 
						   "Pintel motherboard", "IMD motherboard", 
						   "Memory 8 GB", "Memory 16 GB", "Hard disk 1TB", "Hard disk 2TB" };

const int CPUDiscountPrice[] = { 820, 1230, 820, 1230 };

const int CYCLES = 1000;

const double CPUDISCOUNT = 0.18;

const double CANCELLATIONPENALTY = 0.03;

const int MAXORDERQUANTITY = 30;

const int MINPROFITRATE = 25;

const int MAXPROFITRATE = 75;

const int MINORDERBUNDLE = 120;

const int MAXORDERBUNDLE = 200;

const int CYCLEPRICE = 100;
