#include "stdafx.h"
#pragma warning(disable : 4996)

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable> 

#include <algorithm>

#include <chrono>
#include <ctime>
#include <vector>
#include <random>
#include <iomanip>

#include "Bank.h"
#include "Consumer.h"

#include "Global_Objects.h"
#include "Global_variables.h"

using namespace std;


// Default Constructor
Consumer::Consumer(){


	/* Generate the type of consumer

	1 --> Light
	2 --> Microwave
	3 --> Regifrator

	*/

	std::random_device rd;
	std::mt19937 gen(rd());
	std:uniform_int_distribution<> dis(1, 3);

	type = dis(gen);
	credits = 300;
	id = consumers_counter;
	consumers_counter++;

	/*for (int i = 0; i < constants::NUMBER_OF_PRODUCERS; i++){
		energy_messages[i].producer_id = NULL;
		energy_messages[i].available = false;
		energy_messages[i].price = NULL;
		energy_messages[i].quantity = float(99.99);
		//energy_messages[i].time_received.hour = NULL;
		//energy_messages[i].time_received.minute = NULL;
		//energy_messages[i].time_received.second = NULL;
	}*/

}

// Constructor
Consumer::Consumer(int credits, int type){

	this->credits = credits;
	this->type = type;
	id = consumers_counter;
	consumers_counter++;

	/*for (int i = 0; i < constants::NUMBER_OF_PRODUCERS; i++){
		energy_messages[i].producer_id = NULL;
		energy_messages[i].available = false;
		energy_messages[i].price = NULL;
		energy_messages[i].quantity = NULL;
		//energy_messages[i].time_received.hour = NULL;
		//energy_messages[i].time_received.minute = NULL;
		//energy_messages[i].time_received.second = NULL;

	}*/

}

Consumer::~Consumer(){

	//consumer_thread.join();
}

void Consumer::startThread(){

	consumer_thread = std::thread(&Consumer::startConsumer, this);				// create thread and start agent!
	consumer_thread.join();
}

void Consumer::startConsumer(){

	vector<int> prices;
	vector<int> ammounts;
	vector<int> producerIds;
	//int a = timeMinut - 1;
	//while (1){

		if (credits > 0){		// can consume 
			//cout << id << endl;
			//if (true){
			if (needEnergy()){
				// Buy energy from a producer

				int min_energy_price = 999;
				int producer_id = 0;
				
				float energy_ammount = get_energy_ammount();
				int needEnergyFromTime;
				int needEnergyUntilTime;
				int needEnergyDay = timeYear;
				//if (nowOrLater()){
					//later
					needEnergyFromTime = getNeedEnergyFromTime(timeMinute);
					needEnergyUntilTime = getNeedEnergyUntilTime(needEnergyFromTime);
				//}
				//else{
					//now
					//needEnergyFromTime = -1;
					//needEnergyUntilTime = -1;
				//}

				//Periptwsi pou i energeia ksepernaei tin imera meta tis 12 to vrady
				if ((needEnergyFromTime > 1440) && (needEnergyUntilTime > 1440)){
					needEnergyDay++;
					needEnergyFromTime = needEnergyFromTime - 1440;
					needEnergyUntilTime = needEnergyUntilTime - 1440;
				}
				else if ((needEnergyUntilTime > 1440) && (needEnergyFromTime < 1440)){
					needEnergyUntilTime = needEnergyUntilTime - 1440;
				}

				float energy_price = getEnergyPrice(energy_ammount);

				std::string by_from; //producer or prosumer
				
				//cout << monades_energeias.at(1).getAmmount() << endl;
				
				std::sort(monades_energeias.begin(), monades_energeias.end());	//taxinomisi me vasi tin timi opws oristike stin energy.h

				int index = 0;
				
				//if (needEnergyFromTime > -1){
					cout << endl;
					cout << "------------------------------------\n";
					cout << "Consumer with id: " << id << " wants " << energy_ammount << " ammount of energy" << " tin imera: "<< needEnergyDay << " kai apo wra: " << needEnergyFromTime / 60 << ":" << std::setw(2)
						<< std::setfill('0') << needEnergyFromTime % 60 << " mexri tin wra: " << needEnergyUntilTime / 60 << ":" << std::setw(2)
						<< std::setfill('0') << needEnergyUntilTime % 60 << endl;
					cout << "------------------------------------\n";
				//}
				/*else{
					cout << endl;
					cout << "------------------------------------\n";
					cout << "Consumer with id: " << id << " wants " << energy_ammount << " ammount of energy" << " now " << endl;
					cout << "------------------------------------\n";
				}*/

				for each (Energy E in monades_energeias)
				{
					//cout << "------------------------------------\n";					
					cout << "Producer id: " << E.getProducerId() << endl;					
					cout << "Energy ammount: " << E.getAmmount() << endl;
					cout << "Timi: " << E.getPrice() << endl;
					cout << "Availability: " << E.getAvailability() << endl;
					if (E.getAvailability()){
						if (E.getHourFrom() > -1){
							cout << "H energeia einai diathesimi tin imera: "<< E.getDay() << " kai wra: " << E.getHourFrom() / 60 << ":" << std::setw(2)
								<< std::setfill('0') << E.getHourFrom() % 60 << " mexri tin wra: " << E.getHourUntil() / 60 << ":" << std::setw(2)
								<< std::setfill('0') << E.getHourUntil() % 60 << endl;
						}
						else
							cout << "H energeia einai diathesimi twra"<< endl;
					}
					cout << "------------------------------------\n";
				}
				cout << "**********************************\n";
				
					
					bool found = false;
					int kk = 0;
					for (int i = 0; i < monades_energeias.size(); i++)
					{
						//I energeia DEN einai diathesimi twra
						//if ((monades_energeias[i].getHourFrom() > -1) && (needEnergyFromTime >-1)){
							if ((monades_energeias[i].getAvailability()) && (monades_energeias[i].getAmmount() >= energy_ammount) && (monades_energeias[i].getHourFrom() <= needEnergyFromTime)
								&& (monades_energeias[i].getHourUntil() >= needEnergyUntilTime)){
								//buy energy, first check if you can
								if (can_buy(id, monades_energeias[i].getProducerId(), monades_energeias[i].getPrice(), "consumer", "producer")){
									//buy energy							
									refresh_consumer_account(id, monades_energeias[i].getProducerId(), monades_energeias[i].getPrice(), "producer");
									cout << "agorastike i energeia " << kk;
									monades_energeias[i].setAvailability(false);
									//cout << E.getAvailability();
									monades_energeias.erase(monades_energeias.begin() + kk);
									found = true;
								}
							}
						if (found)
							break;
						kk++;
						//}
						//I energeia einai diathesimi twra
						/*else if ((monades_energeias[i].getHourFrom() == -1) && (needEnergyFromTime == -1)){
							if ((monades_energeias[i].getAvailability()) && (monades_energeias[i].getAmmount() >= energy_ammount)){
								//buy energy, first check if you can
								if (can_buy(id, monades_energeias[i].getProducerId(), monades_energeias[i].getPrice(), "consumer", "producer")){
									//buy energy							
									refresh_consumer_account(id, monades_energeias[i].getProducerId(), monades_energeias[i].getPrice(), "producer");
									cout << "agorastike i energeia " << kk;
									monades_energeias[i].setAvailability(false);
									//cout << E.getAvailability();
									monades_energeias.erase(monades_energeias.begin() + kk);
									found = true;
								}
							}
							if (found)
								break;
							kk++;
						}*/
					}
					cout << endl;
				/*for each (Energy E in monades_energeias)
				{	
					int ii = 0;
					int kk = 0;
					if ((E.getAvailability()) && (E.getAmmount() >= energy_ammount)){
						//buy energy, first check if you can
						if (can_buy(id, E.getProducerId(), E.getPrice(), "consumer", "producer")){
							//buy energy							
							refresh_consumer_account(id, E.getProducerId(), E.getPrice(), "producer");
							//cout << "koukou ";
							monades_energeias[ii].setAvailability(false);
							//E.setAvailability(false);
							//cout << E.getAvailability();
							//monades_energeias.erase(monades_energeias.begin() + kk);
							found = true;
						}
					}
					if (found)
						break;
					kk++;
					ii++;
				}*/

				/*cout << "\n\nMinimum element in Vector prices is: "
					<< *(std::min_element(prices.begin(), prices.end()));*/

				/*for (int i = 0; i < constants::NUMBER_OF_PRODUCERS; i++){

					if (energy_messages[i].available == true && energy_messages[i].price <= energy_price && energy_messages[i].quantity >= energy_ammount){
						energy_messages[i].available = false;
						break;
					}
				}*/

				//if (credits >= min_energy_price){	// Can but energy
				//if (can_buy(id, producer_id, min_energy_price, "consumer", "producer")){

					//credits = credits - min_energy_price;
					//remove_energy_from_buffer(producer_id, energy_ammount);	// Remove this ammount of energy from the central buffer

					//m.unlock();

					// Refresh bank account
					//consumer_mtx_1.lock();
					//refresh_consumer_account(id, producer_id, min_energy_price, "producer");
					//consumer_mtx_1.unlock();
				//}

			}
			else{
				return;
				//break;		// WAIT UNTIL TO NEED ENERGY
			}

		}
		else{
			return;
			cout << "BREAK" << endl;
			//break;
		}
		//a++;
	//}
	//consumer_mtx_2.lock();
	//all_consumers--;
	//producers_accounts[id].bankrupt = true;
	//consumer_thread.join();

	//consumer_mtx_2.unlock();
}

int Consumer::get_energy_ammount(){

	std::random_device rd;
	std::mt19937 gen(rd());
	std:uniform_int_distribution<> dis(1, 5);

	return (dis(gen));

}
bool Consumer::needEnergy(){

	// Define a random integer generator
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 1);

	int action = dis(gen);
	//cout << action << endl;

	if (action == 1)
		return true;
	else
		return false;
}

// Returns energy price
float Consumer::getEnergyPrice(int energy_ammount){

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

void Consumer::consumedEnergy(){
	credits--;
	//energy_consumed++;
}

// Returns the id of the consumer
int Consumer::getId(){
	return id;
}

// Returns the credits of the consumer
int Consumer::getCredits(){
	return credits;
}

void Consumer::printCredits(){
	cout << getCredits();
}

float Consumer::getEnergyConsumed(){
	return energy_consumed;

}

int Consumer::getNeedEnergyFromTime(int timeMnt){

	std::random_device rd;
	std::mt19937 gen(rd());
	std:uniform_int_distribution<> dis(timeMnt, timeMnt + 1440);

	return dis(gen);
}

int Consumer::getNeedEnergyUntilTime(int needEnergyFromTime){

	std::random_device rd;
	std::mt19937 gen(rd());
	std:uniform_int_distribution<> dis(needEnergyFromTime, needEnergyFromTime + 30);

	return dis(gen);
}

bool Consumer::nowOrLater(){

	// Define a random integer generator
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, 1);

	int action = dis(gen);
	//cout << action << endl;

	if (action == 1)
		return true;
	else
		return false;
}