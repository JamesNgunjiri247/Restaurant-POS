#include <iostream>
#include <map>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;

// Struct to store product information
struct Product {
    string name;
    double price;
    int quantity;

    Product() : name(""), price(0.0), quantity(0) {}
    Product(string n, double p, int q) : name(n), price(p), quantity(q) {}
};

// Supermarket class
class Supermarket {
private:
    map<string, Product> inventory;
    bool loggedIn;
    int loginAttempts;

public:
    Supermarket() : loggedIn(false), loginAttempts(0) {}

    // Add product to inventory
    void addProduct(string name, double price, int quantity) {
        Product product(name, price, quantity);
        inventory[name] = product;
    }

    // Remove product from inventory
    void removeProduct(string name) {
        inventory.erase(name);
    }

    // Update product quantity in inventory
    void updateQuantity(string name, int quantity) {
        if (inventory.find(name) != inventory.end()) {
            inventory[name].quantity = quantity;
        }
    }

    // Login functionality
    void login() {
        string username, password;
        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        // Simple check for login credentials
        if (username == "kathambi" && password == "Gitau") {
            loggedIn = true;
            cout << "Login successful!" << endl;
        } else {
            cout << "Invalid credentials. Login failed." << endl;
            loginAttempts++;
            if (loginAttempts >= 3) {
                cout << "Maximum login attempts reached. Please create a new account." << endl;
                createAccount();
            } else {
                cout << "Please try again." << endl;
                login();
            }
        }
    }

    // Create a new account
    void createAccount() {
        string newUsername, newPassword;
        cout << "Enter new username: ";
        cin >> newUsername;
        cout << "Enter new password: ";
        cin >> newPassword;

        cout << "Account created successfully! Please log in with your new credentials." << endl;
        loggedIn = false;
        loginAttempts = 0;
        login();
    }

    // Make a sale
    void makeSale() {
        if (!loggedIn) {
            cout << "Please login first." << endl;
            return;
        }
        vector<pair<string, int>> cart;  // Product name and quantity pairs
        string productName;
        int productQuantity;

        cout << "Enter customer name: ";
        string customerName;
        cin.ignore();
        getline(cin, customerName);

        cout << "Enter customer phone number: ";
        string phoneNumber;
        cin >> phoneNumber;

        cout << "Enter customer address: ";
        string customerAddress;
        cin.ignore();
        getline(cin, customerAddress);

        cout << "Enter 'done' when finished adding products to the cart." << endl;
        while (true) {
            cout << "Enter product name:";
            cin >> productName;
            if (productName == "done")
                break;

            cout << "Enter product quantity:";
            cin >> productQuantity;

            // Check if product is available in inventory and quantity is sufficient
            if (inventory.find(productName) != inventory.end()) {
                if (productQuantity <= inventory[productName].quantity) {
                    cart.push_back(make_pair(productName, productQuantity));
                    inventory[productName].quantity -= productQuantity;
                    cout << "Product added to cart." << endl;
                } else {
                    cout << "Insufficient quantity available for that product." << endl;
                }
            } else {
                cout << "Product not found in inventory." << endl;
            }
        }

        // Print receipt
        double totalPrice = 0.0;
        cout << "\n------------------------" << endl;
        cout << "      CUSTOMER RECEIPT" << endl;
        cout << "------------------------" << endl;
        cout << "Customer Name: " << customerName << endl;
        cout << "Phone Number: " << phoneNumber << endl;
        cout << "Customer Address: " << customerAddress << endl;
        cout << "------------------------" << endl;
        cout << "Product      Quantity    Price" << endl;
        cout << "------------------------" << endl;
        for (const auto& item : cart) {
            const string& name = item.first;
            int quantity = item.second;
            double price = inventory[name].price * quantity;
            cout << setw(12) << left << name << setw(10) << quantity << setw(10) << price << endl;
            totalPrice += price;
        }
        cout << "------------------------" << endl;
        cout << "Total Price: " << totalPrice << endl;
        cout << "------------------------" << endl;

        // After printing the receipt, prompt for payment method
        promptPaymentMethod(totalPrice);
    }

    // Prompt user for payment method
    void promptPaymentMethod(double totalPrice) {
        cout << "Payment Methods:" << endl;
        cout << "1. Cash" << endl;
        cout << "2. Credit Card" << endl;
        cout << "3. Mobile Payment" << endl;
        cout << "Enter your payment method choice (1/2/3): ";
        int paymentChoice;
        cin >> paymentChoice;

        switch (paymentChoice) {
            case 1: {
                cout << "You have chosen Cash payment." << endl;
                cout << "Enter the amount in cash: ";
                double cashPayment;
                cin >> cashPayment;
                if (cashPayment >= totalPrice) {
                    double balance = cashPayment - totalPrice;
                    cout << "Payment successful. Balance: " << balance << " $" << endl;
                } else {
                    cout << "Insufficient cash payment. Please provide enough amount." << endl;
                    promptPaymentMethod(totalPrice); // Ask for payment method again
                }
                break;
            }
            case 2: {
                cout << "You have chosen Credit Card payment." << endl;
                cout << "Enter your credit card number: ";
                string creditCardNumber;
                cin.ignore();
                getline(cin, creditCardNumber);
                // Add code for credit card payment processing
                cout << "Payment successful." << endl;
                break;
            }
            case 3: {
                cout << "You have chosen Mobile Payment." << endl;
                cout << "Enter your mobile number: ";
                string mobileNumber;
                cin.ignore();
                getline(cin, mobileNumber);
                // Add code for mobile payment processing
                cout << "Payment successful." << endl;
                break;
            }
            default:
                cout << "Invalid payment method choice. Please try again." << endl;
                promptPaymentMethod(totalPrice); // Ask for payment method again
                break;
        }
    }

    // Run the POS system
    void run() {
        if (!loggedIn) {
            cout << "Please login first." << endl;
            return;
        }

        cout << "Bei poa Supermarket POS System" << endl;

        while (true) {
            int choice;
            cout << "\n1. Add product to inventory" << endl;
            cout << "2. Remove product from inventory" << endl;
            cout << "3. Update product quantity" << endl;
            cout << "4. Make a sale" << endl;
            cout << "5. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            string name;
            double price;
            int quantity;

            switch (choice) {
                case 1:
                    cout << "Enter product name: ";
                    cin >> name;
                    cout << "Enter product price: ";
                    cin >> price;
                    cout << "Enter product quantity: ";
                    cin >> quantity;
                    addProduct(name, price, quantity);
                    cout << "Product added to inventory." << endl;
                    break;
                case 2:
                    cout << "Enter product name: ";
                    cin >> name;
                    removeProduct(name);
                    cout << "Product removed from inventory." << endl;
                    break;
                case 3:
                    cout << "Enter product name: ";
                    cin >> name;
                    cout << "Enter new product quantity: ";
                    cin >> quantity;
                    updateQuantity(name, quantity);
                    cout << "Product quantity updated." << endl;
                    break;
                case 4:
                    makeSale();
                    break;
                case 5:
                    cout << "Exiting..." << endl;
                    return;
                default:
                    cout << "Invalid choice. Try again." << endl;
                    break;
            }
        }
    }
};

int main() {
    Supermarket supermarket;
    supermarket.login();
    supermarket.run();
    return 0;
}
