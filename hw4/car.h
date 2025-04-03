#ifndef CAR_H
#define CAR_H

#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Car {
	private:
		string make;
		string model;
		int year;
		static double defaultLaborCharges;
		static double defaultPartsCharges;
		static vector<Car> cars; // Store all cars
	
	public:
		Car(const string &make, const string &model, int year);
		
		// Setters
		void setMake(const string &m);
		void setModel(const string &m);
		void setYear(int y);
		
		// Getters
		string getMake() const;
		string getModel() const;
		int getYear() const;
		
		// Static methods to manage default charges
		static void setDefaultLaborCharges(double charge);
		static void setDefaultPartsCharges(double charge);
		static double getDefaultLaborCharges();
		static double getDefaultPartsCharges();
		
		static void addCar(const Car& car);
		static vector<Car> getAllCars();
};

#endif