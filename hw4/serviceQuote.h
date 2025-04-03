#ifndef SERVICEQUOTE_H
#define SERVICEQUOTE_H

#include <string>
#include <unordered_map> // store key-value pairs (like a dictionary in Python)
#include <vector> // store lists of items

using namespace std;

class ServiceQuote {
	private:
		double partsCharges;
		double laborCharges;
		string customerName;
		string date; // Date when service was done
	
	public:
		ServiceQuote(const string& customerName, double partsCharges, double laborCharges);
		
		// Setters
		void setPartsCharges(double c);
		void setLaborCharges(double c);
		
		// Getters
		double getPartsCharges() const;
		double getLaborCharges() const;
		double getSalesTax() const;
		double getTotalCharges() const;
		string getCustomerName() const;
		string getDate() const;
		
		// Storage for service quotes
		static unordered_map<string, vector<ServiceQuote>> quotesByCustomer;
		static unordered_map<string, vector<ServiceQuote>> quotesByDate;
		
		// Static methods to manage servie quotes
		static void addQuote(const ServiceQuote& quote);
		static vector<ServiceQuote> getQuotesByCustomer(const string& name);
		static vector<ServiceQuote> getQuotesByDate(const string& date);
		static void deleteQuote(const string &customerName, const string& date);
		
		static vector<ServiceQuote> getAllQuotes();  
};

#endif