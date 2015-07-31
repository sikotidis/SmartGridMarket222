#pragma once

#ifndef PRODUCER_H
#define PRODUCER_H

#include <thread>
#include "Bank.h"
#include "Energy.h"



class Producer: public Bank{				// Producer inherits from Bank

private:
	std::thread producer_thread;
	int type;
	int id;												// Producer id
	int credits;										// Credits a producer has
	int time;
	float Producer::getEnergyAmmount();
	float Producer::getEnergyPrice();
	float getEnergyTotalCost(int energy_ammount);
	std::string period_of_day();

public:

	void startThread();
	struct time_date{
		int hour, minute, second;
	};
	struct energy_node{
		int energy_ammount;
		int energy_cost;
	};
	struct producer_energy_profile{
		int id;
		bool expired;
		energy_node ammount_price;
		//time_date time_produced;

	};
	static int producers_counter;
	static int producer_counter_list;
	std::vector<producer_energy_profile> producer_buffer;
	void Producer::send_energy(int consumer_id, int producer_id);
	Producer();										// Default Constructor
	Producer(int credits, int type);				// Constructor
	~Producer();									// Destructor
	int getId();

	int getCredits();

	int getType();

	void printCredits();

	void setEnergyProductionCost();

	int getDayAvailable(int timeYear);

	int getTimeAvailableFrom(int timeMinut);

	int getTimeAvailableUntil(int timeAvailableFrom);

	bool nowOrLater();

	float getProducedEnergy();

	void startProducer(int timeMinut, int timeYear);
	//friend void broker_agent(Producer &broker);		// broker_agent function can use methods of Produce class

};


#endif