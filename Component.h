#pragma once

class Component {
private:
	int CompID;
	string compList[4];
	// compNo - holds the component id's used for the pc
	int compNo[4];
	int cost;
	int price;
public:
	void components(int pcid);
	int getPrice(int i);
	int totalCost();
	int discCost();
	bool comp(int id);
	int getCPU();
};

// Goes through the compMap constant and returns the specific components for
// the object of Product
void Component::components(int pcid = -1) {
	for (int i = 0; i < 4; i++) {
		compNo[i] = compMap[pcid][i];
	}
}

// returns component value
int Component::getPrice(int i) {
	price = 0;
	price = compPrice[i];
	return price;
}

// returns value of all components in pc
int Component::totalCost() {
	price = 0;
	for (int i = 0; i < 4; i++) {
		price += compPrice[compNo[i]];
	}
	return price;
}

int Component::discCost() {
	price = 0;
	int cpuDisc;
	cpuDisc = compPrice[compNo[0]];
	cpuDisc -= cpuDisc * CPUDISCOUNT;
	for (int i = 1; i < 4; i++) {
		price += compPrice[compNo[i]];
	}
	price += cpuDisc;
	return price;
}

// returns true if specific component in pc is present
bool Component::comp(int id) {
	for (int i = 0; i < 4; i++) {
		if (id == compNo[i])
			return true;
	}
	return false;
}

int Component::getCPU() {
	return compNo[0];
}
