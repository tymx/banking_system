#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <stdio.h>
#include <time.h>

using namespace std;

struct account
{
    string firstName;
    string lastName;
    int accountId;
    long long int phoneNumber;
    string accountType;
    string month;
    string day;
    string year;
    int amount;
};

string ACCOUNTFILENAME = "accounts.txt";

int welcomeScreen(int counter);
void devScreen();
void mainMenu(vector<account>& acc);
void selectMenu(int opt, vector<account>& acc);
void getAccounts(vector<account>& acc);
void openAccount(vector<account>& acc);
void saveAccounts(vector<account>& acc);
void despositAmount(vector<account>& acc);
void withdrawAmount();
void displayAccounts(vector<account>& acc);
void displayTransactions();
void checkStrings(string str);

int main()
{

    vector<account> accounts;

    int option;
    int i = 0;

    ifstream existFile(ACCOUNTFILENAME.c_str());
    if(existFile)
    {
        getAccounts(accounts);
    }

    do
    {
        option = welcomeScreen(i);
        if(option == 1 && i == 0)
        {
            devScreen();
        }
        if((option == 2 && i == 0) || (option == 1 && i != 0))
        {
            mainMenu(accounts);
            option = 99;
        }
        i++;
    }while(option != 99);

    return 0;
}

int welcomeScreen(int counter)
{
    int opt;

    if(counter == 0)
    {
        cout << "Welcome to _____ Banking System" << endl;
        cout << "1. View the Developers and Guide" << endl;
        cout << "2. View the Main Menu" << endl;
    }
    else
    {
        cout << "Select an option: " << endl;
        cout << "1: View Main Menu" << endl;
        cout << "99: Exit Program" << endl;
    }


    cin >> opt;

    return opt;
}

void devScreen()
{
    system("cls");
    cout << "Developers:" << endl << endl;
    cout << "Angel Castro" << endl;
    cout << "Taylor Martinez" << endl << endl;

    cout << "Guide:" << endl;

    return;
}

void mainMenu(vector<account>& acc)
{
    int option;

    system("cls");
    cout << "Main Menu: " << endl << endl;

    cout << "1: Open an Account" << endl;
    cout << "2: Deposit Amount in Account" << endl;
    cout << "3: Withdraw Amount from Account" << endl;
    cout << "4: Display All Accounts" << endl;
    cout << "5: Display Transaction Information" << endl;
    cout << "6: Delete an Account" << endl;
    cout << "7: Take out a Loan" << endl;
    cout << "8: Search for Accounts" << endl;
    cout << "9: Transfer Money to Another Account" << endl;
    cout << "10: View the Developers and Guide" << endl;

    cout << endl;

    cout << "Select an option: " << endl;
    cin >> option;

    selectMenu(option, acc);

    return;
}

void selectMenu(int opt, vector<account>& acc)
{

    if(opt == 1)
    {
        openAccount(acc);
        saveAccounts(acc);
    }
    /*
    if (opt == 2)
    {
        depositAmount();
    }
    if(opt == 3)
    {
        withdrawAmount();
    }*/
    if(opt == 4)
    {
        displayAccounts(acc);
    }/*
    if(opt == 5)
    {
        displayTransactions();
    }*/

    return;
}

void getAccounts(vector<account>& acc)
{
    ifstream inFile;
    account tmp;
    char ch;

    inFile.open(ACCOUNTFILENAME.c_str());

    while(!inFile.eof())
    {
        inFile >> tmp.accountId;
        inFile >> tmp.accountType;
        inFile >> tmp.firstName;
        inFile >> tmp.lastName;
        inFile >> tmp.phoneNumber;
        inFile >> tmp.amount;
        inFile >> tmp.month;
        inFile >> tmp.day;
        inFile >> tmp.year;
        inFile.ignore(1000,'\n');
        inFile.ignore(1000,'\n');

        acc.push_back(tmp);
    }

    inFile.close();

    return;
}
//Function by Taylor Martinez. The function opens a new account. User must input data into string or numeric fields.
void openAccount(vector<account>& acc)
{
    account tmp;
    string str;
    bool check = false;
    int counter = 0;
    long long int num;
    int numID = 0;

    system("cls");

    //First Name
    cout << endl << "Enter first name: " << endl;
    cin >> tmp.firstName;

    checkStrings(tmp.firstName);

    //Last Name
    cout << "Enter last name: " << endl;
    cin >> tmp.lastName;

    checkStrings(tmp.lastName);

    //Phone Number
    cout << "Enter phone number: " << endl;
    cin >> tmp.phoneNumber;

    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "You cannot enter a character in this field. Enter numbers only" << endl;
        cout << "Please enter information in field again" << endl;
        cin >> tmp.phoneNumber;
        cin.ignore(1000,'\n');
    }

    while(!check)
    {

        num = tmp.phoneNumber;

        while(num != 0)
        {
            num /= 10;
            counter++;
        }

        if(counter != 10)
        {
            cout << "The number entered does not contain 10 digits" << endl;
            cout << "Please enter a correct phone number" << endl;
            cin >> tmp.phoneNumber;
        }
        else
        {
            check = true;
        }

        counter = 0;

    }

    //Account ID

    tmp.accountId = acc.size() + 1;

    cout << "Account ID: " << setfill('0') << setw(10) << tmp.accountId << endl;

    //Account Type
    cout << "Please choose the number of the type of account you want: " << endl;
    cout << "1: Checking" << endl;
    cout << "2: Saving" << endl;
    cin >> num;

    if(num == 1)
    {
        tmp.accountType = "Checking";
    }
    if(num == 2)
    {
        tmp.accountType = "Saving";
    }

    //Date
    time_t now;
    struct tm * today;

    time(&now);
    today = localtime(&now);

    str = asctime(today);

    tmp.month = str.substr(4,3);
    tmp.day = str.substr(8,2);
    tmp.year = str.substr(20,4);

    //Amount
    cout << "Please input your initial desposit: " << endl;
    cin >> tmp.amount;

    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "You cannot enter a character in this field. Enter numbers only" << endl;
        cout << "Please enter information in field again" << endl;
        cin >> tmp.amount;
        cin.ignore(1000,'\n');
    }

    acc.push_back(tmp);

    saveAccounts(acc);

    cout << endl << "Account has been made" << endl;

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;


    if(num == 0)
    {
        mainMenu(acc);
    }

    return;

}

void saveAccounts(vector<account>& acc)
{
    ofstream outFile;

    account tmp;

    outFile.open(ACCOUNTFILENAME.c_str());

    for(int i = 0; i < acc.size(); ++i)
    {
        outFile << acc.at(i).accountId << " "
        << acc.at(i).accountType << " "
        << acc.at(i).firstName << " "
        << acc.at(i).lastName << " "
        << acc.at(i).phoneNumber << " "
        << acc.at(i).amount << " "
        << acc.at(i).month << " "
        << acc.at(i).day << " "
        << acc.at(i).year << endl;
    }

    outFile.close();

    return;
}

void despositAmount(vector<account>& acc)
{
    system("cls");

}
void withdrawAmount(vector<account>& acc)
{

}

void displayAccounts(vector<account>& acc)
{
    int num;

    system("cls");
    cout << endl;
    cout << "************************************************************************************************************************" << endl;
    cout << "                                                    Accounts                                                      " << endl;
    cout << "************************************************************************************************************************" << endl;
    cout << endl;

    for(int i = 0; i < acc.size(); ++i)
    {
        cout << acc.at(i).accountId << " "
        << acc.at(i).accountType << " "
        << acc.at(i).firstName << " "
        << acc.at(i).lastName << " "
        << acc.at(i).phoneNumber << " "
        << acc.at(i).amount << " "
        << acc.at(i).month << " " << acc.at(i).day << " " <<  acc.at(i).year << endl;
    }

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;


    if(num == 0)
    {
        mainMenu(acc);
    }
}

//Function by Taylor Martinez. Checks to see if a string has any numbers within
void checkStrings(string str)
{
    bool check = false;
    string checkstr;

    checkstr = str;

    while (!check)
    {
        for(unsigned int i = 0; i < checkstr.length(); ++i)
        {
            if(isdigit(checkstr.at(i)))
            {
                cout << "You cannot enter a number in this field. Enter characters only" << endl;
                cout << "Please enter information in field again" << endl;
                cin >> checkstr;
            }
            else
            {
                check = true;
                str = checkstr;
            }
        }
    }

    return;
}
