#include<iostream>
#include<fstream>
#include<sstream>
//#include<windows.h>
#include <unistd.h>

using namespace std;

class Bill {
private:
    string Item;
    int Rate, Quantity;
public:
    Bill() : Item(""), Rate(0), Quantity(0) {}

    void setItem(string item) { Item = item; }
    void setRate(int rate) { Rate = rate; }
    void setQuant(int quant) { Quantity = quant; }

    string getItem() { return Item; }
    int getRate() { return Rate; }
    int getQuant() { return Quantity; }
};

void addItem(Bill b) {
    bool close = false;
    while (!close) {
        int choice;
        cout << "\t \t1. Add Item" << endl;
        cout << "\t \t2. Close" << endl;
        cout << "\t Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            system("clear");
            string item;
            int rate, quant;

            cout << "\tEnter Item Name: ";
            cin >> item;
            b.setItem(item);

            cout << "\tEnter Rate of the Item: ";
            cin >> rate;
            b.setRate(rate);

            cout << "\tEnter Quantity of the item: ";
            cin >> quant;
            b.setQuant(quant);

            ofstream out("/mnt/d/alfa.txt", ios::app);
            if (!out) {
                cout << "\tError opening file!" << endl;
            } else {
                out << b.getItem() << ":" << b.getRate() << ":" << b.getQuant() << endl;
            }
            out.close();
            cout << "\tItem added successfully" << endl;
            sleep(3);
        } else if (choice == 2) {
            system("clear");
            close = true;
            cout << "\tBack to main menu!" << endl;
            sleep(3);
        }
    }
}

void printBill() {
    system("clear");
    int count = 0;
    bool close = false;

    while (!close) {
        system("clear");
        int choice;
        cout << "\t1. Add Bill" << endl;
        cout << "\t2. Close" << endl;
        cout << "\tEnter choice: ";
        cin >> choice;

        if (choice == 1) {
            string item;
            int quant;
            cout << "\tEnter Item: ";
            cin >> item;
            cout << "\tEnter Quantity: ";
            cin >> quant;

            ifstream in("/mnt/d/alfa.txt");
            ofstream out("/mnt/d/alfa_temp.txt");

            string line;
            bool found = false;

            while (getline(in, line)) {
                stringstream ss(line);
                string itemName;
                int itemRate, itemQuant;

                getline(ss, itemName, ':');
                ss >> itemRate;
                ss.ignore(); // skip ':'
                ss >> itemQuant;

                if (item == itemName) {
                    found = true;
                    if (quant <= itemQuant) {
                        int amount = itemRate * quant;
                        cout << "\tItem | Rate | Quantity | Amount" << endl;
                        cout << "\t" << itemName << "\t" << itemRate << "\t" << quant << "\t" << amount << endl;

                        int newQuant = itemQuant - quant;
                        out << itemName << ":" << itemRate << ":" << newQuant << endl;
                        count += amount;
                    } else {
                        cout << "\tSorry, not enough stock for " << item << "!" << endl;
                        out << line << endl; // keep original
                    }
                } else {
                    out << line << endl;
                }
            }

            if (!found) {
                cout << "\tItem Not Available!" << endl;
            }

            in.close();
            out.close();
            remove("/mnt/d/alfa.txt");
            rename("/mnt/d/alfa_temp.txt", "/mnt/d/alfa.txt");

        } else if (choice == 2) {
            close = true;
            cout << "\tCounting total bill..." << endl;
        }
        sleep(3);
    }

    system("clear");
    cout << "\n\n\tTotal Bill------------------------: " << count << endl << endl;
    cout << "\tThanks for shopping!" << endl;
    sleep(5);
}

int main() {
    Bill b;
    bool exit = false;
    while (!exit) {
        system("clear");
        int val;
        cout << "\t Welcome to the Bill Management System" << endl;
        cout << "\t***************************************" << endl;
        cout << "\t \t1. Add Item" << endl;
        cout << "\t \t2. View Bill" << endl;
        cout << "\t \t3. Exit" << endl;
        cout << "\t \tEnter your choice: ";
        cin >> val;

        if (val == 1) {
            system("clear");
            addItem(b);
            sleep(3);
        } else if (val == 2) {
            printBill();
        } else if (val == 3) {
            system("clear");
            exit = true;
            cout << "\tGood Luck!!" << endl;
            sleep(3);
        }
    }
    return 0;
}
