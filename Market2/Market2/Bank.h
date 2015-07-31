#pragma once

#ifndef BANK_H
#define BANK_H

#include <string>
#include <vector>
#include <mutex>
#include <condition_variable> 
#include "Global_variables.h"
#include "Global.h"

class Bank {


public:

	struct producer_account{
		int id;
		float credits;
		bool bankrupt;
	};

	static std::vector<producer_account> producers_accounts;

	struct retailer_account{
		int id;
		float credits;
		bool bankrupt;
	};

	static std::vector<retailer_account> retailers_accounts;

	struct consumer_account{
		int id;
		float credits;
		bool bankrupt;
	};

	static std::vector<consumer_account> consumers_accounts;

	Bank();
	Bank(int);
	~Bank();
	static bool can_produce(int, float, std::string);
	static bool can_buy(int, int, float, std::string source, std::string buy_from);
	static void getMarketStatus();
	static void init();
	static void update_account(int id, float cost, std::string source);
	static void refresh_prosumer_account(int prosumer_id, const int price, int producer_id, std::string buy_from);
	static void refresh_consumer_account(int consumer_id, int producer_id, const float price, std::string buy_from);

	int add_new_account(int id, std::string source);

	std::mutex m;


	std::mutex consumer_mtx_1;
	std::mutex consumer_mtx_2;

};

#endif
