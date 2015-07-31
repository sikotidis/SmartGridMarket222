#include "stdafx.h"

#include <iostream>
#include <string>
#include <thread>

#include <mutex>
#include <condition_variable> 

#include <ctime>
#include <vector>

#include "Bank.h"
#include "Producer.h"
#include "Global_Objects.h"


using std::vector;
using namespace std;

std::vector<Bank::producer_account> Bank::producers_accounts;
std::vector<Bank::retailer_account> Bank::retailers_accounts;
std::vector<Bank::consumer_account> Bank::consumers_accounts;


// Default constructor
Bank::Bank(){

}

// Constructor with argument
Bank::Bank(int k){


}

// A method to initialize the Bank
void Bank::init(){

	// initialize the producers accounts
	int last_id;
	for (int i = 0; i < constants::NUMBER_OF_PRODUCERS; i++){

		producer_account *n = new producer_account;
		//n[i] = new producer_account;
		n->id = i;
		n->credits = 10000;
		n->bankrupt = false;
		Bank::producers_accounts.push_back(*n);
		last_id = i;
		//delete n;
	}

	// initialize the retailers accounts
	for (int j = last_id + 1; j < last_id + constants::NUMBER_OF_RETAILERS; j++){		// 0->10
		retailer_account *n = new retailer_account;
		n->id = j;
		n->credits = 100;
		n->bankrupt = false;
		retailers_accounts.push_back(*n);

	}

	// initialize the producers accounts
	for (int i = 0; i < constants::NUMBER_OF_CONSUMERS; i++){
		consumer_account *n = new consumer_account;
		n->id = i;
		n->credits = 10000;
		n->bankrupt = false;
		consumers_accounts.push_back(*n);
		//delete n;
	}

}

// Check if a producer/retailer can produce energy or not
bool Bank::can_produce(int id, float production_cost, std::string source){

	if (source == "producer"){
		if (Bank::producers_accounts[id].credits >= production_cost){
			return true;														// can produce
		}
		else
			return false;
	}
	/*else {		// retailer
	if (Bank::retailers_accounts[id].credits >= production_cost){
	return true;														// can produce
	}
	else
	return false;
	}*/

}

// Check if a consumer/retailer can buy energy or not
bool Bank::can_buy(int id, int producer_id, float production_cost, std::string source, std::string buy_from){

	if (source == "consumer"){
		if (Bank::consumers_accounts[id].credits >= production_cost){
			//Bank::consumers_accounts[id].credits -= production_cost;			// decrease the value of credits
			//refresh_consumer_account(id, producer_id, production_cost, buy_from);
			return true;														// can produce
		}
		else
			return false;

	}
	else{		//retailer
		if (Bank::retailers_accounts[id].credits >= production_cost){
			//Bank::prosumers_accounts[id].credits -= production_cost;			// decrease the value of credits
			refresh_prosumer_account(id, producer_id, production_cost, buy_from);
			return true;														// can produce
		}
		else
			return false;
	}

}

// Get the status of our marketplace
void Bank::getMarketStatus(){

	cout << "------------------------------ PRODUCERS ---------------------------------------" << endl;
	//cout << Bank::producers_accounts.size() << endl;
	int l_id;
	for (int i = 0; i <constants::NUMBER_OF_PRODUCERS; i++){
		cout << "producer with id:" << Bank::producers_accounts[i].id << " | type of producer: "<<  producers[i].getType() << " | credits: " << Bank::producers_accounts[i].credits << endl;
		l_id = i;
	}
	/*cout << "------------------------------------RETAILERS--------------------------------" << endl;
	for (int i = l_id + 1; i <l_id + constants::NUMBER_OF_RETAILERS; i++){
	cout << "prosumer with id:" << Bank::retailers_accounts[i].id << " , has  :" << Bank::retailers_accounts[i].credits << endl;
	}*/
	cout << "--------------------------------- CONSUMERS -----------------------------------" << endl;
	for (int i = 0; i <constants::NUMBER_OF_CONSUMERS; i++){
		cout << "consumer with id:" << Bank::consumers_accounts[i].id << " | credits: " << Bank::consumers_accounts[i].credits << endl;
	}
	cout << "--------------------------------- END -----------------------------------------" << endl;
}

void Bank::update_account(int id, float cost, std::string source){

	if (source == "producer")
		Bank::producers_accounts[id].credits -= cost;
	else if (source == "prosumer")
		Bank::retailers_accounts[id].credits -= cost;
	else if (source == "consumer")
		Bank::consumers_accounts[id].credits -= cost;
}

void Bank::refresh_prosumer_account(int prosumer_id, int producer_id, const int price, std::string buy_from){

	Bank::retailers_accounts[prosumer_id].credits -= price;				// refresh the prosumer account
	if (buy_from == "producer")
		Bank::producers_accounts[producer_id].credits += price;			// refresh the producer's account	
	else
		Bank::retailers_accounts[producer_id].credits += price;			// refresh the prosumer's account

}

void Bank::refresh_consumer_account(int consumer_id, int producer_id, const float price, std::string buy_from){


	Bank::consumers_accounts[consumer_id].credits -= price;				// refresh the consumer account
	if (buy_from == "producer")
		Bank::producers_accounts[producer_id].credits += (price+1);			// refresh the producer's account		
	else
		Bank::retailers_accounts[producer_id].credits += price;			// refresh the prosumer's account


}

int Bank::add_new_account(int id, std::string source){

	if (source == "producer"){
		producer_account *n = new producer_account;
		n->id = 101;		// BUG. LAST ID + 1
		n->credits = 100;
		producers_accounts.push_back(*n);
	}

	else if (source == "retailer"){
		retailer_account *n = new retailer_account;
		n->id = 101;		// BUG. LAST ID + 1
		n->credits = 100;
		retailers_accounts.push_back(*n);
	}

	else if (source == "consumer"){
		consumer_account *n = new consumer_account;
		n->id = 101;		// BUG. LAST ID + 1
		n->credits = 100;
		consumers_accounts.push_back(*n);
	}

	return 1;

}

Bank::~Bank(){
	//delete[] producers_accounts;
}
