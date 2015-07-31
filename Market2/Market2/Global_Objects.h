#pragma once
#include "producer.h"
#include "consumer.h"
#include "Energy.h"
#include <vector>

#ifndef GLOBAL_OBJECTS_H

extern Producer producers[5];	// Storing producers objects
extern Consumer consumers[10];	// Storing consumers objects
extern vector<Energy> monades_energeias;

#endif