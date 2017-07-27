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

struct transaction
{
    string firstName;
    string lastName;
    int transactionID = 0;
    int accountID;
    string transactionType;
    string month;
    string day;
    string year;
    int amount;

};

string ACCOUNTFILENAME = "accounts.txt";
string TRANFILENAME = "transactions.txt";

int welcomeScreen(int counter);
void devScreen();
void mainMenu(vector<account>& acc, vector<transaction> tran);
void selectMenu(int opt, vector<account>& acc, vector<transaction>& tran);
void getAccounts(vector<account>& acc);
void getTransactions(vector<transaction>& tran);
void openAccount(vector<account>& acc, vector<transaction> tran);
void saveAccounts(vector<account>& acc);
void saveTransactions(vector<transaction> tran);
void depositAmount(vector<account>& acc, vector<transaction>& tran);
void withdrawAmount(vector<account>& acc, vector<transaction>& tran);
void displayAccounts(vector<account> acc, vector<transaction> tran);
void displayTransactions(vector<account>& acc, vector<transaction> tran);
void checkStrings(string str);
int foundAcc(vector<account>& acc, int accNum);
int foundTran(vector<transaction>& tran, int tranNum);

int main()
{

    vector<account> accounts;
    vector<transaction> transactions;

    int option;
    int i = 0;

    getAccounts(accounts);

    do
    {
        option = welcomeScreen(i);
        if(option == 1 && i == 0)
        {
            devScreen();
        }
        if((option == 2 && i == 0) || (option == 1 && i != 0))
        {
            mainMenu(accounts, transactions);
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
        cout << endl << "Select an option: " << endl;
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
    cout << "With this program you will be able to: " << endl;
    cout << "- Make an Account with MDC Banking" << endl;
    cout << "- Make deposits and withdrawals into and from the account" << endl;
    cout << "- Be able to see all accounts and their information" << endl;
    cout << "- Be able to see all transactions that has been done with MDC Banking" << endl;
    cout << "- Be able to take out loans" << endl;
    cout << "- Be able to search for specific accounts in the system" << endl;
    cout << "- Be able to transfer money from one account to another of your choosing" << endl;

    cout << endl << "While using this program: " << endl;
    cout << "- Enter a number when asked for one. Characters won't be allowed in numeric fields" << endl;
    cout << "- Enter a character when asked for one. Numbers won't be allowed in character fields" << endl;

    return;
}

void mainMenu(vector<account>& acc, vector<transaction> tran)
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

    selectMenu(option, acc, tran);

    return;
}

void selectMenu(int opt, vector<account>& acc, vector<transaction>& tran)
{

    if(opt == 1)
    {
        openAccount(acc, tran);
    }

    if (opt == 2)
    {
        depositAmount(acc, tran);
    }
    if(opt == 3)
    {
        withdrawAmount(acc, tran);
    }
    if(opt == 4)
    {
        displayAccounts(acc, tran);
    }
    if(opt == 5)
    {
        displayTransactions(acc,tran);
    }

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
void getTransactions(vector<transaction>& tran)
{
    ifstream myFile;
    transaction tmp;

    myFile.open("transactions.txt");

    while(!myFile.eof())
    {
        myFile >> tmp.accountID;
        myFile >> tmp.transactionID;
        myFile >> tmp.transactionType;
        myFile >> tmp.firstName;
        myFile >> tmp.lastName;
        myFile >> tmp.amount;
        myFile >> tmp.month;
        myFile >> tmp.day;
        myFile >> tmp.year;

        tran.push_back(tmp);
    }

    myFile.close();

    return;
}

//Function by Taylor Martinez. The function opens a new account. User must input data into string or numeric fields.
void openAccount(vector<account>& acc, vector<transaction> tran)
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
        mainMenu(acc, tran);
    }

    return;

}

void saveAccounts(vector<account>& acc)
{

    ofstream outFile;

    account tmp;

    int len;

    outFile.open("accounts.txt");

    for(int i = 0; i < acc.size()-1; ++i)

    {

        outFile << acc.at(i).accountId << " "

        << acc.at(i).accountType << " "

        << acc.at(i).firstName << " "

        << acc.at(i).lastName << " "

        << acc.at(i).phoneNumber << " "

        << acc.at(i).amount << endl;

    }

    len = acc.size()-1;

        outFile << acc.at(len).accountId << " "

        << acc.at(len).accountType << " "

        << acc.at(len).firstName << " "

        << acc.at(len).lastName << " "

        << acc.at(len).phoneNumber << " "

        << acc.at(len).amount;



    outFile.close();



    return;
}

void saveTransactions(vector<transaction> tran)
{
    int len;

    ofstream outiFile;

    outiFile.open(TRANFILENAME.c_str());

    for(int i = 0; i < tran.size()-1; ++i)

    {

        outiFile << tran.at(i).accountID << " "

        << tran.at(i).transactionID << " "

        << tran.at(i).transactionType << " "

        << tran.at(i).firstName << " "

        << tran.at(i).lastName << " "

        << tran.at(i).amount << " "

        << tran.at(i).month << " "

        << tran.at(i).day << " "

        << tran.at(i).year << endl;

    }

    len = tran.size()-1;

        outiFile << tran.at(len).accountID << " "

        << tran.at(len).transactionID << " "

        << tran.at(len).transactionType << " "

        << tran.at(len).firstName << " "

        << tran.at(len).lastName << " "

        << tran.at(len).amount << " "

        << tran.at(len).month << " "

        << tran.at(len).day << " "

        << tran.at(len).year;


    outiFile.close();

    return;
}

void depositAmount(vector<account>& acc, vector<transaction>& tran)
{
    int ID;
    int num;
    int numID;
    int deposit;
    string str;
    transaction tmp;


    system("cls");
    cout << "Enter the ID of the account you wish to deposit money to: " << endl;
    cin >> numID;

    ID = foundAcc(acc, numID);

    cout << "Account Holder's Name: " << acc.at(ID).firstName + " " + acc.at(ID).lastName << endl;
    cout << "Account Balance: " << acc.at(ID).amount << endl;
    cout << endl << "Enter Amount you wish to deposit: " << endl;
    cin >> deposit;

    acc.at(ID).amount += deposit;

    cout << endl << "New Balance: " <<  acc.at(ID).amount << endl;

    tmp.firstName = acc.at(ID).firstName;
    tmp.lastName =acc.at(ID).lastName;

    if(foundTran(tran,numID) != 0)
    {
        tmp.transactionID = foundTran(tran,numID) + 1;
    }
    else
    {
        tmp.transactionID++;
    }

    tmp.accountID = acc.at(ID).accountId;

    tmp.transactionType = "Deposit";

    //Date
    time_t now;
    struct tm * today;

    time(&now);
    today = localtime(&now);

    str = asctime(today);

    tmp.month = str.substr(4,3);
    tmp.day = str.substr(8,2);
    tmp.year = str.substr(20,4);

    tmp.amount = deposit;

    tran.push_back(tmp);

    saveTransactions(tran);
    saveAccounts(acc);

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;


    if(num == 0)
    {
        mainMenu(acc, tran);
    }

    return;

}
void withdrawAmount(vector<account>& acc, vector<transaction>& tran)
{
    int ID;
    int num;
    int numID;
    string str;
    int withdrawal;
    transaction tmp;


    system("cls");
    cout << "Enter the ID of the account you wish to withdraw money from: " << endl;
    cin >> numID;

    ID = foundAcc(acc, numID);

    cout << "Account Holder's Name: " << acc.at(ID).firstName + " " + acc.at(ID).lastName << endl;
    cout << "Account Balance: " << acc.at(ID).amount << endl;
    cout << endl << "Enter Amount you wish to withdraw: " << endl;
    cin >> withdrawal;

    acc.at(ID).amount -= withdrawal;

    cout << endl << "New Balance: " <<  acc.at(ID).amount << endl;

    tmp.firstName = acc.at(ID).firstName;
    tmp.lastName = acc.at(ID).lastName;

    if(foundTran(tran,numID) != 0)
    {
        tmp.transactionID = foundTran(tran,numID) + 1;
    }
    else
    {
        tmp.transactionID++;
    }

    tmp.accountID = acc.at(ID).accountId;

    tmp.transactionType = "Withdrawal";

    //Date
    time_t now;
    struct tm * today;


    time(&now);
    today = localtime(&now);

    str = asctime(today);

    tmp.month = str.substr(4,3);
    tmp.day = str.substr(8,2);
    tmp.year = str.substr(20,4);

    tmp.amount = withdrawal;

    tran.push_back(tmp);

    saveTransactions(tran);
    saveAccounts(acc);

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;


    if(num == 0)
    {
        mainMenu(acc, tran);
    }

    return;
}

void displayAccounts(vector<account> acc, vector<transaction> tran)
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
        mainMenu(acc, tran);
    }
}
void displayTransactions(vector<account>& acc, vector<transaction> tran)
{
    int num;

    getTransactions(tran);

    system("cls");
    for(unsigned int i = 0; i < tran.size(); ++i)
    {
        cout << tran.at(i).accountID << " "
        << tran.at(i).transactionID << " "
        << tran.at(i).transactionType << " "
        << tran.at(i).firstName << " " << tran.at(i).lastName << " "
        << tran.at(i).amount << " "
        << tran.at(i).month << " " << tran.at(i).day << " " <<  tran.at(i).year << endl;
    }

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;

    if(num == 0)
    {
        mainMenu(acc, tran);
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
int foundAcc(vector<account>& acc, int accNum)
{
        for(int i=0; i < acc.size(); i++)

        {

            if(acc.at(i).accountId == accNum)

                return i;

        }

    return -1;

}
int foundTran(vector<transaction>& tran, int tranNum)
{
        int counter = 0;

        for(int i=0; i < tran.size(); i++)
        {
            if(tran.at(i).accountID == tranNum)

                counter++;

        }

    return counter;

}
