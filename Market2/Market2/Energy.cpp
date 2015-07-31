#include "stdafx.h"

#include <iostream>
#include <vector>

#include "Energy.h"





using std::vector;
using namespace std;

/*std::vector<Buffer::central_buffer_profile> Buffer::central_buffer;
std::vector<int> Buffer::test;*/


Energy::Energy(){
}

Energy::Energy(int producer_id, float ammount, float price, bool availability){
	this->producer_id = producer_id;
	this->ammount = ammount;
	this->price = price;
	this->availability = availability;
}

Energy::Energy(int producer_id, float ammount, float price, bool availability, int day, int hourFrom, int hourUntil){
	this->producer_id = producer_id;
	this->ammount = ammount;
	this->price = price;
	this->availability = availability;
	this->day = day;
	this->hourFrom = hourFrom;
	this->hourUntil = hourUntil;
}

int Energy::getProducerId(){
	return producer_id;
}
void Energy::setProducerId(int producer_id){
	this->producer_id = producer_id;
}
float Energy::getAmmount(){
	return ammount;
}
void Energy::setAmount(float ammount){
	this->ammount = ammount;
}
float Energy::getPrice(){
	return price;
}
void Energy::setPrice(float price){
	this->price = price;
}
bool Energy::getAvailability(){
	return availability;
}
void Energy::setAvailability(bool availability){
	this->availability = availability;
}

int Energy::getDay(){
	return day;
}

void Energy::setDay(int day){
	this->day = day;
}

int Energy::getHourFrom(){
	return hourFrom;
}

void Energy::setHourFrom(int hourFrom){
	this->hourFrom = hourFrom;
}

int Energy::getHourUntil(){
	return hourUntil;
}

void Energy::setHourUntil(int hourUntil){
	this->hourUntil = hourUntil;
}

/*int Energy::getMinute(){
	return minute;
}

void Energy::setMinute(int minute){
	this->minute = minute;
}*/

void Energy::printEnergy(){
	
	cout << "Producer_id: " << getProducerId() << "\n"; 
	cout << "Posotita: " << getAmmount() << "\n";
	cout << "Timi: " << getPrice() << "\n";
	cout << "Diathesimotita: " << getAvailability() << "\n";
}

/*
int Buffer::add_energy_to_buffer(int id,int energy_ammount, float energy_price, int hour, int min, int sec){

global_counter++;

// WE CHAVE MULTIPLE NODES OF THE SAME PRODUCER SINCE THIS FUNCTIONS IT BEEN CALLED CONTINUESLY
Buffer::central_buffer_profile *n = new Buffer::central_buffer_profile;

n->producer_id = id;
n->ammount_price.energy_ammount = energy_ammount;
n->ammount_price.energy_price = energy_price;
n->time_produced.hour = hour;
n->time_produced.minute = min;
n->time_produced.second = sec;

Buffer::central_buffer.push_back(*n);				// add to central buffer


return 1;
}*/
/*
void Buffer::remove_energy_from_buffer(int prosumer_id, int producer_id){

if (Buffer::central_buffer_array.size() != 0) {
cout << " AFTer REMOVE FROM ENERGY:  " << Buffer::central_buffer_array[producer_id].produce_id << endl;
Buffer::central_buffer.erase(Buffer::central_buffer_array.begin() + producer_id);			//remove the energy
cout << " INSIDE REMOVE FROM ENERGY:  " << Buffer::central_buffer[producer_id].producer_id << endl;
}

}*/
/*
// A friend function for access from another class
void Buffer::getCentralBufferStatus(){

//cout << "getCentralBufferStatus" << endl;
//cout << Buffer::central_buffer.size() << endl;
//cout << "outside add_energy" << Buffer::test.size() << endl;
for (int i = 0; i < Buffer::central_buffer.size(); i++){

cout << Buffer::central_buffer[i].producer_id << "has:  " << Buffer::central_buffer[i].ammount_price.energy_ammount << endl;
}
for (int j = 0; j < Buffer::test.size(); j++){

cout << Buffer::test[j] << endl;
}
}
*/


Energy::~Energy(){

}
