#pragma once

#ifndef ENERGY_H
#define ENERGY_H

#include <vector>
#include <string>
#include "Global_variables.h"
//#include "Global.h"

#define TIME_PER_PRODUCATION 2000
#define ENERGY_TRANSPORTATION_COST 1
#define MAX_ENERGY_PRODUCATION 50

class Energy{

private:
	int producer_id;
	float ammount;
	float price;
	bool availability;
	int day;				//Hmera pou tha einai diathesimi
	int hourFrom;			//Wra enarksis pou tha einai diathesimi
	int hourUntil;			//Wra termatismou pou tha einai diathesimi

public:
	
	/*struct energy_node{
		int energy_ammount;
		int energy_price;
	};*/
	/*struct central_buffer_profile{
		int producer_id;
		std::string source;
		bool expired;
		energy_node ammount_price;
		time_date time_produced;
	};*/

	//static std::vector<central_buffer_profile> central_buffer;
	//static central_buffer_profile central_buffer_array[constants::NUMBER_OF_PRODUCERS];				// a array of size 50
	//static central_buffer_profile central_buffer_array_2[NUMBER_OF_PROSUMERS];						// a array of size 10

	Energy::Energy();
	Energy::Energy(int producer_id, float ammount, float price, bool availability);
	Energy::Energy(int producer_id, float ammount, float price, bool availability, int day, int hourFrom, int hourUntil);
	Energy::~Energy();

	int getProducerId();
	void setProducerId(int producer_id);

	float getAmmount();
	void setAmount(float ammount);

	float getPrice();
	void setPrice(float price);

	bool getAvailability();
	void setAvailability(bool availability);

	int getDay();
	void setDay(int day);

	int getHourFrom();
	void setHourFrom(int hourFrom);

	int getHourUntil();
	void setHourUntil(int hourUntil);

	//int getMinute();
	//void setMinute(int minute);

	void printEnergy();

	bool operator<(Energy e1) { return getPrice() < e1.getPrice(); }	//synartisi gia taxinomisi me vasi tin timi

	static void add_energy(int id, int ammount, int price,bool availability);
	static void remove_energy(int id, int energy_ammount);
	static void getCentralBufferStatus();

};

#endif