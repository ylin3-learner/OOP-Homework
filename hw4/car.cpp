#include <ctime> // For getting current year
#include <stdexcept> // For exception handling
#include <vector>
#include "car.h"

// Initialize static members
double Car::defaultLaborCharges = 50.0; // Default labor charge
double Car::defaultPartsCharges = 100.0; // Default parts charge

vector<Car> Car::cars; // Initialize static vector

Car::Car(const string& make, const string& model, int year) {
	setMake(make);
	setModel(model);
	setYear(year);
}

void Car::setMake(const string& make) {
	if (make.empty()) throw invalid_argument("Make cannot be empty.");
	this->make = make;
}

void Car::setModel(const string &model) {
	this->model = model;
}

void Car::setYear(int year) {
	time_t now = time(nullptr); // access current time
	tm *localTime = localtime(&now); // turn into tm structure

	int currentYear = 1900 + localTime->tm_year;

	if (year < 1886 || year > currentYear)
		throw invalid_argument("Year must be between 1886 and " + to_string(currentYear) + ".");
	this->year = year;
}

string Car::getMake() const {
	return this->make;
}

string Car::getModel() const {
	return this->model;
}

int Car::getYear() const {
	return this->year;
}

void Car::setDefaultLaborCharges(double charge) {
	if (charge < 0) throw invalid_argument("Labor charge cannot be negative.");
	defaultLaborCharges = charge;
}

void Car::addCar(const Car& car) {
    cars.push_back(car);
}

vector<Car> Car::getAllCars() {
    return cars;
}

void Car::setDefaultPartsCharges(double charge) {
	if (charge < 0) throw invalid_argument("Parts charge cannot be be negative.");
	defaultPartsCharges = charge;
}

double Car::getDefaultLaborCharges() {
	// defaultLaborCharges and defaultPartsCharges are static, so they belong to the class, not an instance.
	// Remove this->
	return defaultLaborCharges;
}

double Car::getDefaultPartsCharges() {
	return defaultPartsCharges;
}