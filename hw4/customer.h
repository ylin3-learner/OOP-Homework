#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include <unordered_map>
using namespace std;

class Customer {
private:
    string name;
    string address;
    string phone;

public:
    // Constructor with validation
    Customer(const string& name, const string& address, const string& phone);

    // Setters with input validation
    void setName(const string& name);
    void setAddress(const string& address);
    void setPhone(const string& phone);

    // Getters
    string getName() const;
    string getAddress() const;
    string getPhone() const;
    
    // Static storage for customers
    static unordered_map<string, Customer> customers;
    
    // Static methods to manage customers
    static void addCustomer(const Customer& customer);
    static Customer* getCustomer(const string& name);
};

#endif // CUSTOMER_H
