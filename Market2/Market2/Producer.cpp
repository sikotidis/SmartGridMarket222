#include "stdafx.h"
#pragma warning(disable : 4996)

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable> 

#include <chrono>
#include <ctime>
#include <vector>
#include <random>

#include "Bank.h"
#include "Producer.h"

#include "Global_Objects.h"
#include "Global.h"


using std::vector;
using namespace std;
vector<Energy> monades_energeias;

// Default constructor
Producer::Producer(){

	/* Generate the type of producer

	1 --> Wind turbine
	2 --> Diesel engine
	3 --> Coal generator

	*/

	std::random_device rd;
	std::mt19937 gen(rd());
	std:uniform_int_distribution<> dis(1, 3);

	type = dis(gen);
	credits = 1000;
	id = producers_prosumers_counter;
	producers_prosumers_counter++;

}
// Constructor with argunmnets
Producer::Producer(int credits, int type){

	this->credits = credits;
	this->type = type;
	id = producers_prosumers_counter;
	producers_prosumers_counter++;

}


Producer::~Producer(){
	//producer_thread.join();
}

// Start the producer's thread
void Producer::startThread(){

	//thread producer_thread(&Producer::startProducer, this);
	//producer_thread = std::thread(&Producer::startProducer, this);				// create thread and start agent!
	//producer_thread.join();
}

void Producer::startProducer(int timeMinut, int timeYear){

	
	int a = timeMinut - 1;
	while (a < timeMinut){								

		if (credits <= 0)
			break;

		float energy_ammount = getEnergyAmmount();
		float energy_price = getEnergyPrice();
		float energy_total_cost = getEnergyTotalCost(energy_ammount);
		int dayAvailable = timeYear;
		int timeAvailableFrom;
		int timeAvailableUntil;
		//if (nowOrLater()){
				//dayAvailable = getDayAvailable(timeYear);
				timeAvailableFrom = getTimeAvailableFrom(timeMinut);
				timeAvailableUntil = getTimeAvailableUntil(timeAvailableFrom);			
		//}
		//else{
			//dayAvailable = -1;
			//timeAvailableFrom = -1;
			//timeAvailableUntil = -1;
		//}

		if ((timeAvailableFrom > 1440) && (timeAvailableUntil > 1440)){
			dayAvailable++;
			timeAvailableFrom = timeAvailableFrom - 1440;
			timeAvailableUntil = timeAvailableUntil - 1440;
		}
		else if ((timeAvailableUntil > 1440) && (timeAvailableFrom < 1440)){
			timeAvailableUntil = timeAvailableUntil - 1440;
		}
		

		if (Bank::can_produce(id, energy_total_cost, "producer")){		// call bank to check if producer can produce energy at the given energy cost
			
			monades_energeias.push_back(Energy(id, energy_ammount, energy_total_cost, true, dayAvailable, timeAvailableFrom, timeAvailableUntil));

			Bank::update_account(id, energy_total_cost, "producer");
		}
		else{
			// can't produce....
			break;
		}
		a++;
	}
	//all_producers--;				// decrease the counter of producers who are still alive
}

// Send energy to the consumer
void Producer::send_energy(int consumer_id, int producer_id){

	float energy_ammount = consumers[consumer_id].energy_messages[producer_id].quantity;
	// Send energy_ammount to the consumer with id "consumer_id"

	// Update the credits of the consumer
	Bank::update_account(consumer_id, consumers[consumer_id].energy_messages[producer_id].price, "consumer");
}

// Returns the number of units that the producer is willing/afford to produce
float Producer::getEnergyAmmount(){

	string period_of_day = Producer::period_of_day();

	switch (type){
	case(1) :
		if (period_of_day == "morning")   // wind turbinne
			return 1;
		else if (period_of_day == "afternoon")
			return 1.5;
		else if (period_of_day == "evening")
			return 0.5;
		else if (period_of_day == "night")
			return 2;
	case(2) :							// diesel engines
		return 5;
	case(3) :							// coal generatros
		return 10;
	}
	return 10;
}

// Returns the energy price taking into account the time of the day
float Producer::getEnergyPrice(){

	string period_of_day = Producer::period_of_day();

	switch (type){
	case(1) :							// wind turbinne
		if (period_of_day == "morning")  // 
			return float(0.552);
		else if (period_of_day == "afternoon")
			return float(0.555);
		else if (period_of_day == "evening")
			return float(0.485);
		else
			return float(0.452);
	case(2) :		// diesel engines
		if (period_of_day == "morning")
			return float(0.755);
		else if (period_of_day == "afternoon")
			return float(0.755);
		else if (period_of_day == "evening")
			return float(0.600);
		else
			return 0.678;
	case(3) :							// coal generatros
		if (period_of_day == "morning")
			return float(0.555);
		else if (period_of_day == "afternoon")
			return float(0.555);
		else if (period_of_day == "evening")
			return float(0.48);
		else
			return float(0.40);
	default:
		return float(0.40);
	}


}

// Returns the period of day of the current transaction
string Producer::period_of_day(){

	/* Generate the time of the day

	1 --> Morning
	2 --> Afternoon
	3 --> Evening

	*/

	/*

	1   - 360 --> night
	361 - 720 --> morning
	721 - 1080 --> afternoon
	1081 - 1440 --> evening

	*/

	//std::random_device rd;
	//std::mt19937 gen(rd());
	//std:uniform_int_distribution<> dis(1, 3);

	//int period_time = dis(gen);

	int period_time = timeMinute;

	if (period_time = 1 && period_time <= 360)
		return "night";
	else if (period_time = 361 && period_time <= 720)
		return "morning";
	else if (period_time = 721 && period_time <= 1080)
		return "afternoon";
	else if (period_time = 1081 && period_time <= 1440)
		return "evening";

}

// Returns the energy total cost
float Producer::getEnergyTotalCost(int energy_ammount){

	switch (type){
	case(1) :							// wind turbinne
		return float(energy_ammount*0.452);
	case(2) :							// diesel engines
		return float(energy_ammount*0.678);
	case(3) :							// coal generatros
		return float(energy_ammount*0.40);
	default:
		return float(energy_ammount*0.40);
	}
}

// Returns producer's id
int Producer::getId(){
	return id;
}

int Producer::getType(){
	return type;
}

// Returns producer's credits
int Producer::getCredits(){
	return credits;
}

//void Producer::printCredits(){
//	cout << getCredits();
//}

// Returns producer's total produced energy
float Producer::getProducedEnergy(){

	float total_energy = 0;
	for (int i = 0; i < producer_buffer.size(); i++){
		total_energy = total_energy + producer_buffer[id].ammount_price.energy_ammount;
	}
	return total_energy;
}

int Producer::getDayAvailable(int timeYear){

	std::random_device rd;
	std::mt19937 gen(rd());
	std:uniform_int_distribution<> dis(timeYear, 365);

	return dis(gen);
}

int Producer::getTimeAvailableFrom(int timeMinut){

	std::random_device rd;
	std::mt19937 gen(rd());
	std:uniform_int_distribution<> dis(timeMinut, timeMinut + 1440);

	return dis(gen);
}

int Producer::getTimeAvailableUntil(int timeAvailableFrom){

	std::random_device rd;
	std::mt19937 gen(rd());
	std:uniform_int_distribution<> dis(timeAvailableFrom, timeAvailableFrom + 30);

	return dis(gen);
}

bool Producer::nowOrLater(){

	// Define a random integer generator
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 1);

	int action = dis(gen);

	if (action == 1)
		return true;
	else
		return false;
}

