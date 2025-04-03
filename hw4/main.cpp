#include <iostream>
#include <stdexcept>
#include "customer.h"
#include "car.h"
#include "serviceQuote.h"

using namespace std;

void displayMenu() {
    cout << "\n\n                MENU\n\n";
    cout << "1) Add a customer\n";
    cout << "2) Add a car\n";
    cout << "3) Create a service quote\n";
    cout << "4) Display all customers\n";
    cout << "5) Display all cars\n";
    cout << "6) Display all service quotes\n";
    cout << "7) Delete a service quote\n";
    cout << "8) Exit the program\n\n";
    cout << "Enter your choice: ";
}

void createServiceQuote() {
    string customerName;
    double partsCharges, laborCharges;

    cout << "Enter customer name: ";
    cin >> customerName;
    cout << "Enter parts charges: ";
    cin >> partsCharges;
    cout << "Enter labor charges: ";
    cin >> laborCharges;

    try {
        ServiceQuote quote(customerName, partsCharges, laborCharges);
        ServiceQuote::addQuote(quote);
        cout << "Service quote created successfully.\n";
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void displayServiceQuotes() {  
    // Get all quotes as a vector  
    vector<ServiceQuote> quotes = ServiceQuote::getAllQuotes();  
    
    if (quotes.empty()) {
    	cout << "No quotes available.\n";
        return;
	}

    // Iterate over each quote in the vector  
    for (const ServiceQuote& quote : quotes) {  
        cout << "Customer: " << quote.getCustomerName()  
             << " Date: " << quote.getDate()  
             << " Parts: " << quote.getPartsCharges()  
             << " Labor: " << quote.getLaborCharges()  
             << " Total: " << quote.getTotalCharges() << endl;  
    }  
}  

void deleteServiceQuote() {
    string customerName, date;
    cout << "Enter customer name: ";
    cin >> customerName;
    cout << "Enter date (YYYY-MM-DD): ";
    cin >> date;

    ServiceQuote::deleteQuote(customerName, date);
}

void addCustomer() {
    string name, address, phone;

    cout << "Enter customer name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter customer address: ";
    getline(cin, address);
    cout << "Enter customer phone (10-digit number): ";
    cin >> phone;

    try {
        Customer newCustomer(name, address, phone);
        Customer::addCustomer(newCustomer);
        cout << "Customer added successfully.\n";
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
}

void addCar() {
    string make, model;
    int year;

    cout << "Enter car make: ";
    cin.ignore();
    getline(cin, make);
    cout << "Enter car model: ";
    getline(cin, model);
    cout << "Enter car year: ";
    cin >> year;

    try {
        Car newCar(make, model, year);
        Car::addCar(newCar); // This ensures the car is saved!
        cout << "Car added successfully.\n";
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }
}


void displayAllCustomers() {
    if (Customer::customers.empty()) {  // Check if there are no customers
        cout << "No customers available.\n";
        return;
    }

    cout << "Customer List:\n";
    for (const auto& customerPair : Customer::customers) {
        const Customer& customer = customerPair.second;
        cout << "Name: " << customer.getName()
             << ", Address: " << customer.getAddress()
             << ", Phone: " << customer.getPhone() << endl;
    }
}


void displayAllCars() {
    vector<Car> cars = Car::getAllCars();  // Fetch all stored cars

    cout << "Total cars stored: " << cars.size() << endl; // Debugging output

    if (cars.empty()) {
        cout << "No cars available.\n";
        return;
    }

    cout << "Car List:\n";
    for (const Car& car : cars) {
        cout << "Make: " << car.getMake()
             << ", Model: " << car.getModel()
             << ", Year: " << car.getYear() << endl;
    }
}



int main() {
    int choice;
    do {
        displayMenu();
        cin >> choice;
        switch (choice) {
            case 1:
                addCustomer();
                break;
            case 2:
                addCar();
                break;
            case 3:
                createServiceQuote();
                break;
            case 4:
                displayAllCustomers();
                break;
            case 5:
                displayAllCars();
                break;
            case 6:
                displayServiceQuotes();
                break;
            case 7:
                deleteServiceQuote();
                break;
            case 8:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
    return 0;
}
