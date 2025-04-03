#include <iostream>
#include <stdexcept>  // For std::invalid_argument
#include <regex>
#include <unordered_map>
#include "customer.h"

using namespace std;

// Initialize static storage for customers
unordered_map<string, Customer> Customer::customers;

// Constructor with input validation
Customer::Customer(const string& name, const string& address, const string& phone) {
	setName(name);
	setAddress(address);
	setPhone(phone);
}

// Setters with input validation
void Customer::setName(const string& name) {
	if (name.empty()) {
		throw invalid_argument("Name cannot be empty.");
		return;
	}
	this->name = name;
}

void Customer::setAddress(const string& address) {
	if (address.empty()) {
		throw invalid_argument("Address cannot be empty.");
		return;
	}
	this->address = address;
}

void Customer::setPhone(const string& phone) {
	regex phonePattern("\\d{10}"); // 10 digits
	if (!regex_match(phone, phonePattern))
		throw invalid_argument("Invalid phone number format.");

	// Check if the phone number already exists
	for (const auto& ptr : customers) {
		if (ptr.second.getPhone() == phone) {
			throw invalid_argument("Phone number already existed.");
			return;
		}
	}

	this->phone = phone;
}

// Getters with const
string Customer::getName() const {
	return name;
}

string Customer::getAddress() const {
	return address;
}

string Customer::getPhone() const {
	return phone;
}

// Static method to add a customer
void Customer::addCustomer(const Customer& customer) {
	// Check for duplicate phone number before inserting
	for (const auto& ptr : customers) {
		if (ptr.second.getPhone() == customer.getPhone()) {
			throw invalid_argument("Phone number: " + ptr.second.getPhone() + " already exists.");
		}
	}

	// Insert customer to the map only if phone number is unique
	customers.emplace(customer.getName(), customer);
}


// Static method to retrieve a customer by name
Customer* Customer::getCustomer(const string& name) {
	auto it = customers.find(name);
	if (it != customers.end()) {
		return &(it->second);
	} else {
		return nullptr;
	}
}