#include "stdafx.h"

#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <ctime>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "Producer.h"
#include "Consumer.h"
#include "Bank.h"

#include "Global.h"
#include "Global_Objects.h"

using namespace std;

void start_thread(int type);

// Define some static variables
int Producer::producer_counter_list = 0;
int Consumer::consumers_counter = 0;
int producers_prosumers_counter = 0;
int global_counter = 0;

std::mutex mtx;
std::condition_variable cv;

std::condition_variable producers_cv;
std::mutex producers_mtx;
std::condition_variable consumers_cv;
std::mutex consumers_mtx;

const int NUMBER_OF_CONSUMERS = 10;
const int NUMBER_OF_PRODUCERS = 5;
//const int NUMBER_OF_PROSUMERS = 6;

int all_producers = constants::NUMBER_OF_PRODUCERS;
int all_consumers = constants::NUMBER_OF_CONSUMERS;
//int all_prosumers = constants::NUMBER_OF_RETAILERS;
bool ready = false;
bool no_consumers = true;

Producer producers[NUMBER_OF_PRODUCERS];		// storing all producers
Consumer consumers[NUMBER_OF_CONSUMERS];		// storing all consumers
std::vector<int> cons;

int timeYear = 1;
int endYear = 365; // Simulate 365 days = 1 year
int timeMinute = 0;
int endTime = 1440; // Simulate 1440 minutes = 24 hours
int tick = 1; // Each tick = 1 minute
int threshold = 15; //Every 15 minutes a new transaction

int main(){

	//int a = producers[1].getCredits();
	//cout <<"Credits: "<< a <<endl;
	//producers[2].printCredits();
	


	Bank bank_controller(1);						// create a bank object
	bank_controller.init();
	Bank::getMarketStatus();

	for (int i = 0; i < constants::NUMBER_OF_CONSUMERS; i++){
		cons.push_back(i);
	}
	int gg = 60;
	int vv = 2;
	//while (timeYear <= vv){
		while (timeMinute < gg){
			monades_energeias.erase(monades_energeias.begin(), monades_energeias.end());
			cout << "Hmera: " << timeYear << " kai wra:  " << timeMinute / 60 << ":" << std::setw(2)
				<< std::setfill('0') << timeMinute % 60 << "\n";
			
			for (int i = 0; i < constants::NUMBER_OF_PRODUCERS; i++)
				producers[i].startProducer(timeMinute, timeYear);
		
				std::random_shuffle(cons.begin(), cons.end());
			for each (int i in cons)
				{
					//cout << i << " main" << endl;
					consumers[i].startConsumer();
				}
			
			/*if (timeMinute % 15 == 0){	//threshold every 15 minutes, clean transaction
				//cout << "threshold\n";
				monades_energeias.clear();
			}*/
			timeMinute += tick;
		}
	//timeYear++;;
	//}
	//for each (Energy E in monades_energeias)
	//{
	//	E.printEnergy();
	//}
	// Start producers agents
	//for (int i = 0; i < constants::NUMBER_OF_PRODUCERS; i++)
	//	producers[i].startThread();
	//producers[i].startProducer();
	// Start consumers agents

	bool no_consumers = false;
	ready = true;
	//producers_cv.notify_all();	// Wake up any sleeped producer

	//cout<<consumers[0].energy_messages[0].quantity;

	// Block the main thread until all prodcuers and consumers to be initialized and start producing/consuming
	//while (all_producers > 0 && all_consumers > 0){}

	Bank::getMarketStatus();

	////////////////////////////////////
	cin.clear();
	cin.ignore(255, '\n');
	cin.get();
	return 0;
	///////////////////////////////////
}

void start_thread(int type){

}




