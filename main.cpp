/*I hold a copy of this assignment that I can produce if the original is lost or damaged.
  I hereby certify that no part of this assignment has been copied from any other student’s work or
  from any other source except where due acknowledgement is made in the assignment.No part
  of this assignment has been written / produced for me by another person except where such
  collaboration has been authorised by the subject lecturer concerned. */
// IDE: Microsoft Visual Studio 2019
#include "Constant.h"
#include "SmartSchedule.h"
#include "Component.h"
#include "BundleGenerator.h"


int main() {
	// Creates a text file with a list of 120-180 random orders
	BundleGenerator list;
	list.generateOrders();

	// Start the main object
	SmartSchedule openDay;

	// Reads the order file
	openDay.takeOrders();

	// Outputs PC and component production to seperate txt files
	openDay.outputPCProduction();
	openDay.countComponent();

	// Seperates orders-to-keep from orders-to-cancel
	openDay.keepOrders();

	// Outputs data into a txt file
	openDay.outputOrders();

	//Outputs data to console
	openDay.consoleOut();
}