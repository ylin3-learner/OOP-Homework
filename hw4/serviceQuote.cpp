#include "serviceQuote.h"
#include <stdexcept>

#include <chrono> // dates and times
#include <iomanip> // formatting input and output (like setting the date format)
#include <sstream> // format data as strings, especially for handling dates
#include <functional>
#include <iostream>

// Initialize static storage for service quotes
unordered_map<string, vector<ServiceQuote>> ServiceQuote::quotesByCustomer;
unordered_map<string, vector<ServiceQuote>> ServiceQuote::quotesByDate;  

// Helper function to get the current date as a string
inline string getCurrentDate() {
	auto now = chrono::system_clock::now();
	auto time = chrono::system_clock::to_time_t(now);  // converts the now time to a time_t (a representation of the current time).

	stringstream ss;
	// localtime() converts the time_t to a struct tm, which allows us to manipulate or format the date.
	ss << put_time(localtime(&time), "%Y-%m-%d"); // Format as YYYY-mm-dd
	return ss.str();
}

vector<ServiceQuote> getQuote(const string& str, unordered_map<string, vector<ServiceQuote>>& object) {
	auto it = object.find(str);
	if(it != object.end()) {
		return it->second;  // Found the key, return vector<ServiceQuote>
	}
	return {}; // Return an empty vector if not found
}

inline void removeQuoteFromMap(
    unordered_map<string, vector<ServiceQuote>> &quoteMap,
    const string &key,
    function<bool(const ServiceQuote &)> matchCondition
) {
	auto it = quoteMap.find(key);
	if (it == quoteMap.end()) return;  // Key not found

	vector<ServiceQuote> &quotes = it->second;

	// Erase matching elements
	for (auto iter = quotes.begin(); iter != quotes.end(); ) {
		if (matchCondition(*iter)) {
			iter = quotes.erase(iter);
		} else {
			++iter;
		}
	}

	// If empty, remove key from the map
	if (quotes.empty()) {
		quoteMap.erase(key);
	}
}

ServiceQuote::ServiceQuote(const string& customerName, double partsCharges, double laborCharges) {
	this->customerName = customerName;
	this->date = getCurrentDate(); // Set the current date automatically
	this->setLaborCharges(laborCharges);
	this->setPartsCharges(partsCharges);
}

void ServiceQuote::setLaborCharges(double c) {
	if (c < 0) {
		throw invalid_argument("Labor Charges cannot be negative.");
	}
	this->laborCharges = c;
}

void ServiceQuote::setPartsCharges(double c) {
	if (c < 0) {
		throw invalid_argument("Parts Charges cannot be negative.");
	}
	this->partsCharges = c;
}

double ServiceQuote::getPartsCharges() const {
	return this->partsCharges;
}

double ServiceQuote::getLaborCharges() const {
	return this->laborCharges;
}

void ServiceQuote::addQuote(const ServiceQuote& quote) {
    // Add to quotesByCustomer
    auto& customerQuotes = quotesByCustomer[quote.getCustomerName()];
    customerQuotes.push_back(quote);

    // Add to quotesByDate
    auto& dateQuotes = quotesByDate[quote.getDate()];
    dateQuotes.push_back(quote);
}

void ServiceQuote::deleteQuote(const string& name, const string& date) {
    if (quotesByCustomer.empty() || quotesByDate.empty()) {
        cout << "No quotes available.\n";
        return;
    }

    // Check if the quote exists before trying to delete
    if (quotesByCustomer.find(name) == quotesByCustomer.end() ||
        quotesByDate.find(date) == quotesByDate.end()) {
        cout << "Error: No quote found for " << name << " on " << date << ".\n";
        return;
    }

    cout << "Deleting quote for " << name << " on " << date << "...\n";

    // Remove the quote from both maps
    removeQuoteFromMap(quotesByCustomer, name, [&](const ServiceQuote &q) {
        return q.getDate() == date;
    });

    removeQuoteFromMap(quotesByDate, date, [&](const ServiceQuote &q) {
        return q.getCustomerName() == name;
    });

    cout << "Quote deleted successfully.\n";
}


vector<ServiceQuote> ServiceQuote::getQuotesByCustomer(const string& name) {
	return getQuote(name, ServiceQuote::quotesByCustomer);
}

vector<ServiceQuote> getQuotesByDate(const string& date) {
	return getQuote(date, ServiceQuote::quotesByDate);
}

vector<ServiceQuote> ServiceQuote::getAllQuotes() {  
    vector<ServiceQuote> allQuotes; // Vector to hold all quotes  

    // Iterate through customer quotes using iterators  
    for (auto it = quotesByCustomer.begin(); it != quotesByCustomer.end(); ++it) {  
        const vector<ServiceQuote>& quotes = it->second; // Access the vector of quotes for each customer  
        allQuotes.insert(allQuotes.end(), quotes.begin(), quotes.end()); // Add each customer’s quotes to the allQuotes vector  
    }  

    return allQuotes; // Return the vector containing all the quotes  
}  

double ServiceQuote::getSalesTax() const {
	const double taxRate = 0.07;
	return (this->getLaborCharges() + this->getPartsCharges()) * taxRate;
}

double ServiceQuote::getTotalCharges() const {
	return (this->laborCharges + this->partsCharges + this->getSalesTax());
}

string ServiceQuote::getCustomerName() const {  
    return customerName;   
}  

string ServiceQuote::getDate() const {  
    return date; 
}  