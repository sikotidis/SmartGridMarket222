#pragma once

#ifndef GLOBAL_H

#include <mutex>
#include <condition_variable>


using namespace std;

extern int global_counter;
extern int producers_prosumers_counter;
extern int all_producers;
extern int all_retailers;
extern int all_consumers;


extern int timeYear;
extern int endYear; // Simulate 365 days = 1 year
extern int timeMinute;
extern int endTime; // Simulate 1440 minutes = 24 hours
extern int tick; // Each tick = 1 minute
extern int threshold; //Every 15 minutes a new transaction*/

extern std::mutex mtx;
extern std::condition_variable cv;

extern std::condition_variable producers_cv;
extern std::mutex producers_mtx;
extern std::condition_variable consumers_cv;
extern std::mutex consumers_mtx;


extern bool ready;
//extern bool flag;

#endif


