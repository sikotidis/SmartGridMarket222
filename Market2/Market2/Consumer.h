#pragma once

#ifndef CONSUMER_H
#define CONSUMER_H

#include <thread>
#include "Energy.h"
#include "Bank.h"

class Consumer : public Bank {

private:

public:

	std::thread consumer_thread;
	int id;											// Prosumer id
	int type;
	int credits;
	float energy_consumed;

	int energy_bought;

	void startConsumer();

	int Consumer::get_energy_ammount();
	struct time_date{
		int hour, minute, second;
	};
	struct energy_node{
		int energy_ammount;
		int energy_price;
	};
	struct consumer_energy_profile{
		int id;
		energy_node ammount_price;
		time_date time_produced;

	};
	std::vector<consumer_energy_profile> consumer_buffer;				// AMOUNT, PRICE, TIME

	struct message{
		int producer_id;
		bool available;
		float price;
		float quantity;
		time_date time_received;
	};

	message energy_messages[constants::NUMBER_OF_PRODUCERS];		// A array of structs

	static int consumers_counter;
	Consumer();										// Default Constructor
	Consumer(int credits, int type);							// Constructor
	~Consumer();									// Destructor
	int getId();

	void startThread();
	void consumedEnergy();
	int getCredits();
	void printCredits();
	void setEnergyPrice();
	bool needEnergy();
	float getEnergyPrice(int energy_ammount);
	float getEnergyConsumed();
	friend void broker_agent(Consumer &broker);		// broker_agent function can use methods of Consume class

	int getNeedEnergyFromTime(int timeMnt);
	int getNeedEnergyUntilTime(int needEnergyFromTime);
	bool nowOrLater();

};


#endif