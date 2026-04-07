#include "Customer.h"
#include "Store.h"
#include <map>
#include <iostream>
#include <vector>
#include <string>
#include <deque>

using namespace std;

void clearBuffer() {
    cin.clear();
    while (cin.get() != '\n' && !cin.eof());
}

int safeCin() {
    int value = 0;
    while (!(cin >> value)) {
        clearBuffer();
    }
    return value;
}

void printDecimal(double value) {
    long long rounded = (long long)(value * 10.0 + 0.5);
    long long integerPart = rounded / 10;
    int decimalPart = (int)(rounded % 10); 
    cout << integerPart << "." << decimalPart;
}

void printItemLine(const Item& item, int index) {
    cout << left << index << ". ";
    string name = item.getName();
    cout << name;
    for (int i = 0; i < (31 - (int)name.length()); i++) cout << " ";
    cout << "price: ";
    printDecimal(item.getPrice());
    cout << endl;
}

void printCartItems(set<Item>* cart) {
    if (!cart || cart->empty()) {
        cout << "The cart is empty!" << endl;
        return;
    }
    int idx = 0;
    for (set<Item>::iterator it = cart->begin(); it != cart->end(); ++it) {
        printItemLine(*it, idx++);
    }
}

int main() {
    map<string, Customer> abcCustomers;
    Store s1("Shefa Isaschar", "InventorySuperMarket.csv");
    Store s2("MagshIKEA", "InventoryIKEA.csv");
    Store s3("MagshiPharm", "InventoryPharm.csv");

    int choice = 0;
    while (choice != 4) {
        cout << "Welcome to MagshiMart!" << endl;
        cout << "1. To sign as customer and buy items" << endl;
        cout << "2. To update existing customer's items" << endl;
        cout << "3. To print the customer who pays the most" << endl;
        cout << "4. To exit" << endl;
        choice = safeCin();

        if (choice == 1) {
            string name = "";
            cout << "Enter your name: ";
            cin >> name;
            if (abcCustomers.find(name) == abcCustomers.end()) abcCustomers[name] = Customer(name);

            int subChoice = 0;
            while (true) {
                cout << "Welcome!\nSelect one of the options:\n1. To create a new shopping cart\n2. Back to main menu\nYour Choice:" << endl;
                subChoice = safeCin();
                if (subChoice == 1 || subChoice == 2) break;
            }
            if (subChoice == 2) continue;

            string cartName = "";
            cout << "Enter the new shopping cart name: ";
            cin >> cartName;
            abcCustomers[name].createNewShoppingCart(cartName);

            int storeChoice = 0;
            while (true) {
                cout << "Select the store:\n1. Shefa Isaschar\n2. MagshIKEA\n3. MagshiPharm\n4. Back" << endl;
                storeChoice = safeCin();
                if (storeChoice >= 1 && storeChoice <= 4) break;
            }
            if (storeChoice == 4) continue;

            Store* activeStore = (storeChoice == 1) ? &s1 : (storeChoice == 2 ? &s2 : &s3);
            int itemIdx = 0;
            while (true) {
                const deque<Item>& prods = activeStore->getProducts();
                cout << "The items you can buy are: (-1 to exit)" << endl;
                for (int i = 0; i < (int)prods.size(); i++) printItemLine(prods[i], i);
                itemIdx = safeCin();
                if (itemIdx == -1) break;
                if (itemIdx >= 0 && itemIdx < (int)prods.size()) abcCustomers[name].addItem((*activeStore)[itemIdx], cartName);
            }
        }
        else if (choice == 2) {
            string name = "";
            cout << "Enter your name: "; cin >> name;
            if (abcCustomers.find(name) == abcCustomers.end()) {
                cout << "Couldn't find this name!" << endl; continue;
            }

            string selCart = "";
            int cartChoice = 0;
            while (true) {
                vector<string> cartList = abcCustomers[name].getCartNames();

                cout << "Select Shopping Cart: (-1 to exit, 0 to new cart)" << endl;
                for (int i = 0; i < (int)cartList.size(); i++) {
                    cout << (i + 1) << ". " << cartList[i] << endl;
                }

                cartChoice = safeCin();
                if (cartChoice == -1) break;

                if (cartChoice == 0) {
                    cout << "Enter name: "; cin >> selCart;
                    abcCustomers[name].createNewShoppingCart(selCart);
                    continue;
                }
                else if (cartChoice > 0 && cartChoice <= (int)cartList.size()) {
                    selCart = cartList[cartChoice - 1];
                    break;
                }
            }
            if (cartChoice == -1) continue;

            int updateOp = 0;
            while (true) {
                cout << "Selected Cart: " << selCart << endl;
                cout << "1. Add items\n2. Remove items\n3. Back to main menu" << endl;
                updateOp = safeCin();
                if (updateOp >= 1 && updateOp <= 3) break;
            }
            if (updateOp == 3) continue;

            if (updateOp == 1) {
                int stChoice = 0;
                while (true) {
                    cout << "Select Store:\n1. SuperMarket\n2. IKEA\n3. Pharm\n4. to exit" << endl;
                    stChoice = safeCin();
                    if (stChoice >= 1 && stChoice <= 4) break;
                }
                if (stChoice == 4) continue;
                Store* activeStore = (stChoice == 1) ? &s1 : (stChoice == 2 ? &s2 : &s3);
                int itm = 0;
                while (true) {
                    const deque<Item>& prods = activeStore->getProducts();
                    cout << "Items in store: (-1 to exit)" << endl;
                    for (int i = 0; i < (int)prods.size(); i++) printItemLine(prods[i], i);
                    itm = safeCin();
                    if (itm == -1) break;
                    if (itm >= 0 && itm < (int)prods.size()) abcCustomers[name].addItem((*activeStore)[itm], selCart);
                }
            }
            else if (updateOp == 2) {
                int itmToRemove = 0;
                while (true) {
                    set<Item>* currentCartSet = abcCustomers[name].getShoppingCart(selCart);

                    if (!currentCartSet || currentCartSet->empty()) {
                        cout << "The cart is empty!" << endl;
                        break;
                    }

                    cout << "Items in your cart: (-1 to exit)" << endl;
                    printCartItems(currentCartSet);

                    itmToRemove = safeCin();
                    if (itmToRemove == -1) break;

                    if (itmToRemove >= 0 && itmToRemove < (int)currentCartSet->size()) {
                        set<Item>::iterator it = currentCartSet->begin();
                        for (int i = 0; i < itmToRemove; ++i) {
                            ++it;
                        }
                        Item itemToHandle = *it;
                        abcCustomers[name].removeItem(itemToHandle, selCart);
                    }
                }
            }
        }
        else if (choice == 3) {
            if (abcCustomers.empty()) cout << "No customers!" << endl;
            else {
                string win = ""; double topVal = -1.0;
                for (map<string, Customer>::iterator it = abcCustomers.begin(); it != abcCustomers.end(); ++it) {
                    if (it->second.totalSum() >= topVal) { topVal = it->second.totalSum(); win = it->first; }
                }
                cout << "The customer that payed the most is " << win << "who payed ";
                printDecimal(topVal); cout << endl;
            }
        }
    }
    cout << "Thank you for visiting MagshiMart!\nGoodbye!" << endl;
    return 0;
}