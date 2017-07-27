//Angel Castro and Taylor Martinez COP 1334
//Final project::Banking System

#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>
#include <string>
#include <cctype>
#include <cstdlib>
#include <iomanip>
#include <ctime>
#include <cmath>
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
struct loans
{
    string nameFirst;
    string nameLast;
    string loanType;
    int social;
    int loanAmt;
    int loanID;
    double loanPrice;
    double loanMonthPay;

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
void mainMenu(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran);
void selectMenu(int opt, vector<account>& acc, vector<loans>& loan, vector<transaction>& tran);
void getAccounts(vector<account>& acc);
void getTransactions(vector<transaction>& tran);
void openAccount(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran);
void saveAccounts(vector<account>& acc);
void depositAmount(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran);
void withdrawAmount(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran);
void displayAccounts(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran);
void displayTransactions(vector<account>& acc, vector<loans>& loan, vector<transaction> tran);
int foundTran(vector<transaction>& tran, int tranNum);
void checkStrings(string str);
void eraseAcc(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran);
void loanProcess(vector<loans>& loan, vector<account>& acc, vector<transaction>& tran);
void getLoanData(vector<loans>& loan);
void saveLoanData(vector<loans> loan);
int showLoanMenu();
int found(vector<loans> loan, int accNum);
void searchAcc(vector<account> acc, vector<loans> loan, vector<transaction> tran );
void saveTransactions(vector<transaction>& tran);
void transferAcc(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran);
int foundAcc(vector<account>& acc, int accNum);
int foundTran(vector<transaction>& tran, int tranNum);
int foundDay(vector<transaction>& tran, string mon, string day, string year);

int main()
{
    vector<account> accounts;
    vector<loans> loan;
    vector<transaction> transactions;

    int option;
    int i = 0;

    getAccounts(accounts);
    getLoanData(loan);
    getTransactions(transactions);

    do
    {
        option = welcomeScreen(i);
        if(option == 1 && i == 0)
        {
            devScreen();
        }
        if((option == 2 && i == 0) || (option == 1 && i != 0))
        {
            mainMenu(accounts, loan, transactions);
            option = 99;
        }
        i++;
    }while(option != 99);

    system("cls");
    //Saves data inputted
    saveLoanData(loan);

    return 0;
}
//Function by Taylor Martinez. Function outputs the welcome menu.
int welcomeScreen(int counter)
{
    int opt;

    if(counter == 0)
    {
        cout << "**********************************************" << endl;
        cout << "        Welcome to MDC Banking System         " << endl;
        cout << "**********************************************" << endl;
        cout << "1. View the Developers and Guide" << endl;
        cout << "2. View the Main Menu" << endl;
    }
    else
    {
        cout << endl;
        cout << "Select an option: " << endl;
        cout << "1: View Main Menu" << endl;
        cout << "99: Exit Program" << endl;
    }


    cin >> opt;

    return opt;
}
//Function by Taylor Martinez. Function outputs the Developers and Guide menu
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
//Function by Taylor Martinez. Function outputs the main menu
void mainMenu(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran)
{
    int option;

    system("cls");
    cout << "**********************************************" << endl;
    cout << "                 Main Menu                    " << endl;
    cout << "**********************************************" << endl;
    cout << endl;

    cout << "1: Open an Account" << endl;
    cout << "2: Deposit Amount in Account" << endl;
    cout << "3: Withdraw Amount from Account" << endl;
    cout << "4: Display All Accounts" << endl;
    cout << "5: Display Transaction Information" << endl;
    cout << "6: Delete an Account" << endl;
    cout << "7: Loan Application and Payments" << endl;
    cout << "8: Search for Accounts" << endl;
    cout << "9: Transfer Money to Another Account" << endl;
    cout << "0: Exit Program" << endl;

    cout << endl;

    cout << "Select an option: " << endl;
    cin >> option;

    selectMenu(option, acc, loan, tran);

    return;
}
//Function by Taylor Martinez. Function allows user to select from main menu.
void selectMenu(int opt, vector<account>& acc, vector<loans>& loan, vector<transaction>& tran)
{

    if(opt == 1)
    {
        openAccount(acc, loan, tran);
        saveAccounts(acc);
    }

    if (opt == 2)
    {
        depositAmount(acc, loan, tran);
        saveAccounts(acc);
        saveTransactions(tran);
    }
    if(opt == 3)
    {
        withdrawAmount(acc, loan, tran);
        saveAccounts(acc);
        saveTransactions(tran);
    }
    if(opt == 4)
    {
        displayAccounts(acc,loan, tran);

    }
    if(opt == 5)
    {
        displayTransactions(acc, loan, tran);
    }

    if(opt == 6)
    {
        system("cls");
        eraseAcc(acc, loan, tran);
    }

    if(opt == 7)
    {
        system("cls");
        loanProcess(loan, acc, tran);
    }
    if(opt == 8)
    {
       system("cls");
       searchAcc(acc, loan, tran);
    }
    if(opt == 9)
    {
       system("cls");
       transferAcc(acc, loan, tran);
    }
    if(opt == 0)
    {
        return;
    }

    if(opt > 10 || opt < 1)
        cout << "Please enter a correct option" << endl;


    return;
}
//Function by Taylor Martinez. Function grabs account info. from account file.
void getAccounts(vector<account>& acc)
{
    ifstream inFile;
    account tmp;
    char ch;

    inFile.open("accounts.txt");

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

        acc.push_back(tmp);
    }

    inFile.close();

    return;
}
//Function by Taylor Martinez. Function grabs the transactions from the transaction file.
void getTransactions(vector<transaction>& tran)
{
    ifstream inFile;
    transaction tmpp;

    inFile.open(TRANFILENAME.c_str());

    while(!inFile.eof())
    {
        inFile >> tmpp.accountID;
        inFile >> tmpp.transactionID;
        inFile >> tmpp.transactionType;
        inFile >> tmpp.firstName;
        inFile >> tmpp.lastName;
        inFile >> tmpp.amount;
        inFile >> tmpp.month;
        inFile >> tmpp.day;
        inFile >> tmpp.year;

        tran.push_back(tmpp);
    }

    inFile.close();

    return;
}
//Function by Taylor Martinez. Function opens an account for user and adds it to the list of accounts
void openAccount(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran)
{
    account tmp;
    string str;
    bool check = false;
    int counter = 0;
    int num;
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
    cout << "Please input your initial deposit: " << endl;
    cin >> tmp.amount;

    while(cin.fail())
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "You cannot enter a character in this field. Enter numbers only" << endl;
        cout << "Please enter information in field again" << endl;
        cin >> tmp.phoneNumber;
        cin.ignore(1000,'\n');
    }

    acc.push_back(tmp);

    cout << endl << "Account has been made" << endl;

    cout << endl;

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;

    if(num == 0)
    {
        mainMenu(acc, loan, tran);
    }

    return;

}
//Function by Taylor Martinez. Function saves account info into file.
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
        << acc.at(i).amount << " "
        << acc.at(i).month << " "
        << acc.at(i).day << " "
        << acc.at(i).year << endl;
    }
    len = acc.size()-1;
        outFile << acc.at(len).accountId << " "
        << acc.at(len).accountType << " "
        << acc.at(len).firstName << " "
        << acc.at(len).lastName << " "
        << acc.at(len).phoneNumber << " "
        << acc.at(len).amount << " "
        << acc.at(len).month << " "
        << acc.at(len).day << " "
        << acc.at(len).year;

    outFile.close();

    return;
}
//Function by Taylor Martinez. Function saves the transactions into its own file.
void saveTransactions(vector<transaction>& tran)
{
    ofstream outFile;
    int len;

    outFile.open(TRANFILENAME.c_str());

    for(int i = 0; i < tran.size()-1; ++i)
    {
        outFile << tran.at(i).accountID << " "
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

    outFile << tran.at(len).accountID << " "
        << tran.at(len).transactionID << " "
        << tran.at(len).transactionType << " "
        << tran.at(len).firstName << " "
        << tran.at(len).lastName << " "
        << tran.at(len).amount << " "
        << tran.at(len).month << " "
        << tran.at(len).day << " "
        << tran.at(len).year << endl;

    outFile.close();

    return;
}
//Function by Taylor Martinez. Function deposits money amount into account amount and adds the transaction into the transaction list
void depositAmount(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran)
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
    tmp.transactionID += 1;

    tran.push_back(tmp);

    saveTransactions(tran);
    saveAccounts(acc);

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;


    if(num == 0)
    {
        mainMenu(acc,loan, tran);
    }

    return;

}
//Function by Taylor Martinez. Function withdraws money amount from account amount and adds the transaction into the transaction list
void withdrawAmount(vector<account>& acc,vector<loans>& loan,  vector<transaction>& tran)
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

    tmp.transactionID++;
    tmp.accountID = acc.at(ID).accountId;

    tmp.transactionType = "Withdraw";

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
    tmp.transactionID += 1;

    tran.push_back(tmp);

    saveTransactions(tran);
    saveAccounts(acc);

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;


    if(num == 0)
    {
        mainMenu(acc, loan, tran);
    }

    return;
}
//Function by Taylor Martinez. Function outputs all accounts on screen.
void displayAccounts(vector<account>& acc, vector<loans>& loan, vector<transaction>&tran)
{

    system("cls");

    int num;

    cout << "************************************************************************************************************************" << endl;
    cout << "                                                    Account Information                                                 " << endl;
    cout << "************************************************************************************************************************" << endl;
    cout << "Account No." << setw(17) << "Account Type" << setw(15) << "Name" << setw(24) << "Phone Number"
         << setw(14) << "Amount" << setw(20) << "Date Created" << endl;
    cout << "************************************************************************************************************************" << endl;

    string name;

    for(int i=0; i < acc.size(); i++)
    {
        name = acc.at(i).firstName + " " + acc.at(i).lastName;

        cout << setw(5) << right << acc.at(i).accountId;
        cout << setw(22) << right << acc.at(i).accountType;
        cout << setw(20) << right << name;
        cout << setw(18) << right << acc.at(i).phoneNumber;
        cout << setw(15) << right << acc.at(i).amount;
        cout << setw(12) << right << acc.at(i).month << " " << acc.at(i).day << " " <<  acc.at(i).year << endl;
    }


    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;

    if(num == 0)
    {
        mainMenu(acc, loan, tran);
    }

}
//Function by Taylor Martinez. Function outputs all transactions on screen.
void displayTransactions(vector<account>& acc, vector<loans>& loan, vector<transaction> tran)
{
    int num;
    int opt;
    int c;
    string mon;
    string day;
    string year;

    system("cls");


    cout << "How do you want the information displayed?" << endl;
    cout << "1: Type Of Transaction" << endl;
    cout << "2: Date" << endl;
    cout << "3: All Transaction" << endl;
    cin >> opt;

    if(opt == 1)
    {
        system("cls");
        cout << "What type of transaction?" << endl;
        cout << "1: Deposit" << endl;
        cout << "2: Withdraw" << endl;
        cin >> c;
        cout << endl;

        if(c==1)
        {
           cout << "************************************************************************************************************************" << endl;
            cout << "                                                    Account Information                                                 " << endl;
            cout << "************************************************************************************************************************" << endl;
            cout << "Account No." << setw(17) << "Transaction ID" << setw(18) << "Transaction Type" << setw(13) << "Name"
                 << setw(23) << "Amount" << setw(22) << "Transaction Date" << endl;
            cout << "************************************************************************************************************************" << endl;

            for(unsigned int i = 0; i < tran.size() ; ++i)
            {
                if(tran.at(i).transactionType == "Deposit")
                {
                    string name;
                    name = tran.at(i).firstName + " " + tran.at(i).lastName;

                    cout << setw(10) << left << tran.at(i).accountID << " "
                    << setw(10) << right <<tran.at(i).transactionID << " "
                    << setw(20) << right << tran.at(i).transactionType << " "
                    << setw(22) << right << name << " "
                    << setw(14) << right << tran.at(i).amount << " "
                    << setw(13) << right << tran.at(i).month << " " << tran.at(i).day << " " <<  tran.at(i).year << endl;
                }

            }
        }
        if(c==2)
        {
            cout << "************************************************************************************************************************" << endl;
            cout << "                                                    Account Information                                                 " << endl;
            cout << "************************************************************************************************************************" << endl;
            cout << "Account No." << setw(17) << "Transaction ID" << setw(18) << "Transaction Type" << setw(13) << "Name"
                 << setw(23) << "Amount" << setw(22) << "Transaction Date" << endl;
            cout << "************************************************************************************************************************" << endl;

            for(unsigned int i = 0; i < tran.size() ; ++i)
            {
                if(tran.at(i).transactionType == "Withdraw")
                {
                    string name;
                    name = tran.at(i).firstName + " " + tran.at(i).lastName;

                    cout << setw(10) << left << tran.at(i).accountID << " "
                    << setw(10) << right <<tran.at(i).transactionID << " "
                    << setw(20) << right << tran.at(i).transactionType << " "
                    << setw(22) << right << name << " "
                    << setw(14) << right << tran.at(i).amount << " "
                    << setw(13) << right << tran.at(i).month << " " << tran.at(i).day << " " <<  tran.at(i).year << endl;
                }

            }
        }
        if(c >= 3 || c <= 0)
        {
            cout << endl;
            cout << "Please enter a correct option" << endl;
        }


    }
    if(opt == 2)
    {
        while(mon.length() != 3 || day.length() != 2 || year.length() != 4)
        {
            cout << "Please enter date(format: Jan 01 2017): ";
            cin >> mon >> day >> year;

            if(mon.length() == 3 && day.length() == 2 && year.length() == 4)
                break;
        }

            cout << "************************************************************************************************************************" << endl;
            cout << "                                                    Account Information                                                 " << endl;
            cout << "************************************************************************************************************************" << endl;
            cout << "Account No." << setw(17) << "Transaction ID" << setw(18) << "Transaction Type" << setw(13) << "Name"
                 << setw(23) << "Amount" << setw(22) << "Transaction Date" << endl;
            cout << "************************************************************************************************************************" << endl;

            for(unsigned int i = 0; i < tran.size() ; ++i)
            {
                if(foundDay(tran, mon, day, year) != -1)
                {
                    string name;
                    name = tran.at(i).firstName + " " + tran.at(i).lastName;

                    cout << setw(10) << left << tran.at(i).accountID << " "
                    << setw(10) << right <<tran.at(i).transactionID << " "
                    << setw(20) << right << tran.at(i).transactionType << " "
                    << setw(22) << right << name << " "
                    << setw(14) << right << tran.at(i).amount << " "
                    << setw(13) << right << tran.at(i).month << " " << tran.at(i).day << " " <<  tran.at(i).year << endl;
                }

            }
            if(foundDay(tran, mon, day, year) == -1)
            {
                cout << "Record was not found" << endl;
            }

    }
    if(opt==3)
    {
        cout << "************************************************************************************************************************" << endl;
        cout << "                                                    Account Information                                                 " << endl;
        cout << "************************************************************************************************************************" << endl;
        cout << "Account No." << setw(17) << "Transaction ID" << setw(18) << "Transaction Type" << setw(13) << "Name"
             << setw(23) << "Amount" << setw(22) << "Transaction Date" << endl;
        cout << "************************************************************************************************************************" << endl;

        for(unsigned int i = 0; i < tran.size(); ++i)
        {
        string name;
        name = tran.at(i).firstName + " " + tran.at(i).lastName;

        cout << setw(10) << left << tran.at(i).accountID << " "
        << setw(10) << right <<tran.at(i).transactionID << " "
        << setw(20) << right << tran.at(i).transactionType << " "
        << setw(22) << right << name << " "
        << setw(14) << right << tran.at(i).amount << " "
        << setw(13) << right << tran.at(i).month << " " << tran.at(i).day << " " <<  tran.at(i).year << endl;
        }
    }
    if(opt > 3 || opt < 1)
    {
        cout << "Please enter a correct option" << endl;
    }



    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;

    if(num == 0)
    {
        mainMenu(acc, loan, tran);
    }
}

//Function by Taylor Martinez. Function checks if a number is inside the string.
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
///Angel
void eraseAcc(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran)
{
    int i;
    int opt;
    int num;


    cout << "Please enter the account number to delete: ";
    cin >> i;

    num = foundAcc(acc, i);
    if(num == -1)
    {
        cout << "Record was not found" << endl;
        return;
    }

    cout << endl;

    cout << "Would you like to delete the account under " << acc.at(num).firstName << " " << acc.at(num).lastName << endl;

    cout << endl;

    cout << "Enter 1: Yes" << endl;
    cout << "Enter 2: No" << endl;
    cin >> opt;

    while(opt != 2)
    {
        if(opt==1)
        {
            acc.erase(acc.begin()+i);
            break;


        }
        if(opt >2 || opt < 1)
        {
            cout << "Please enter a correct option" << endl;
        }
    }

     cout << endl;

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;

    if(num == 0)
    {
        mainMenu(acc, loan, tran);
    }

}
///Angel
int showLoanMenu()
{
    int opt;

    cout << endl;
    cout << "************************************************************************************************************************" << endl;
    cout << "                                                    Loan Menu                                                      " << endl;
    cout << "************************************************************************************************************************" << endl;
    cout << endl;

    cout << "Enter 1: Loan Application" << endl;
    cout << "Enter 2: Loan Payments" << endl;
    cout << "Enter 3: Display Loan Information" << endl;
    cout << "Enter 0: Exit" << endl;
    cin >> opt;

    return opt;

}
///Angel
void getLoanData(vector<loans>& loan)
{
    ifstream myFile;
    loans tmp;

    myFile.open("LoanData.txt");

    while(!myFile.eof())
    {
        myFile >> tmp.nameFirst >> tmp.nameLast
               >> tmp.loanType >> tmp.social
               >> tmp.loanAmt >> tmp.loanID
               >> tmp.loanPrice >> tmp.loanMonthPay;

        loan.push_back(tmp);
    }

    myFile.close();
}
///Angel
void saveLoanData(vector<loans> loan)
{
    ofstream saveFile;




        int len;
        saveFile.open("LoanData.txt");

        for(int i = 0; i < loan.size()-1; i++)
        {
            saveFile << loan.at(i).nameFirst << " " << loan.at(i).nameLast << " "
                     << loan.at(i).loanType << " " << loan.at(i).social << " "
                     << loan.at(i).loanAmt << " " << loan.at(i).loanID << " "
                     << loan.at(i).loanPrice << " " << loan.at(i).loanMonthPay << endl;
        }
        len = loan.size()-1;
        saveFile  << loan.at(len).nameFirst << " " << loan.at(len).nameLast << " "
                     << loan.at(len).loanType << " " << loan.at(len).social << " "
                     << loan.at(len).loanAmt << " " << loan.at(len).loanID << " "
                     << loan.at(len).loanPrice << " " << loan.at(len).loanMonthPay;

        saveFile.close();

}
///Angel
void loanProcess(vector<loans>& loan, vector<account>& acc, vector<transaction>& tran)
{
    int opt;
    int num;
    bool flag = true;

    const double MORTGAGE_RATE = 0.00375;
    const double STUDENT_RATE = 0.00167;
    const double PERSONAL_RATE = 0.00833;



    while(flag)
    {

        opt = showLoanMenu();
        if(opt ==1)
        {
            system("cls");
            int dec;
            loans temp;

            cout << "Loan Type" << endl;
            cout << endl;

            cout << "Enter 1: Mortgage" << endl;
            cout << "Enter 2: Student Loan" << endl;
            cout << "Enter 3: Personal Loan" << endl;
            cin >> dec;

            //Creates loan account and calculate mortgage loan
            if(dec==1)
            {
                temp.loanType = "Mortgage";
                cout << "Please enter your first name: ";
                cin >> temp.nameFirst;
                checkStrings(temp.nameFirst);
                cout << "Please enter your last name: ";
                cin >> temp.nameLast;
                checkStrings(temp.nameLast);
                cout << "Please enter your social security number: ";
                cin >> temp.social;
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "You cannot enter a character in this field. Enter numbers only" << endl;
                    cout << "Please enter information in field again" << endl;
                    cin >> temp.social;
                    cin.ignore(1000,'\n');
                }
                cout << "Please enter the amount of the loan: ";
                cin >> temp.loanAmt;
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "You cannot enter a character in this field. Enter numbers only" << endl;
                    cout << "Please enter information in field again" << endl;
                    cin >> temp.loanAmt;
                    cin.ignore(1000,'\n');
                }


                srand(time(0));

                temp.loanID = rand();

                system("cls");
                cout << "Thanking you for applying for a loan application" <<endl;

                cout << endl;

                cout << "Your loan ID is: " << temp.loanID << endl;

                cout << endl;

                cout << "Mortgage given out at 30 year fixed rate of 4.5%" << endl;

                temp.loanMonthPay = temp.loanAmt * ((MORTGAGE_RATE * pow(1+MORTGAGE_RATE,360)) / (pow(1+MORTGAGE_RATE,360) - 1));

                temp.loanPrice = (temp.loanMonthPay * 360);

                cout << fixed << setprecision(2);
                cout << "Total Cost of Mortgage: " << temp.loanPrice << endl;
                cout << "Monthly Installment: " << temp.loanMonthPay << endl;

                loan.push_back(temp);

            }
            //Creates loan account and calculate student loan
            if(dec==2)
            {
                temp.loanType = "Student";
                cout << "Please enter your first name: ";
                checkStrings(temp.nameFirst);
                cout << "Please enter your last name: ";
                checkStrings(temp.nameLast);
                cout << "Please enter your social security number: ";
                cin >> temp.social;
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "You cannot enter a character in this field. Enter numbers only" << endl;
                    cout << "Please enter information in field again" << endl;
                    cin >> temp.social;
                    cin.ignore(1000,'\n');
                }
                cout << "Please enter the amount of the loan: ";
                cin >> temp.loanAmt;
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "You cannot enter a character in this field. Enter numbers only" << endl;
                    cout << "Please enter information in field again" << endl;
                    cin >> temp.loanAmt;
                    cin.ignore(1000,'\n');
                }


                srand(time(0));

                temp.loanID = rand();

                system("cls");
                cout << "Thanking you for applying for a loan application" <<endl;

                cout << endl;

                cout << "Your loan ID is: " << temp.loanID << endl;

                cout << endl;

                cout << "Student loans are given out at a 10 year fixed rate of 2.0%" << endl;

                temp.loanMonthPay = temp.loanAmt * ((STUDENT_RATE * pow(1+STUDENT_RATE,120)) / (pow(1+STUDENT_RATE,120) - 1));

                temp.loanPrice = (temp.loanMonthPay * 120);

                cout << fixed << setprecision(2);
                cout << "Total Cost of Loan: " << temp.loanPrice << endl;
                cout << "Monthly Installment: " << temp.loanMonthPay << endl;

                loan.push_back(temp);
            }
            //Creates loan account and calculate personal loan
            if(dec==3)
            {
                temp.loanType = "Personal";
                cout << "Please enter your first name: ";
                cin >> temp.nameFirst;
                checkStrings(temp.nameFirst);
                cout << "Please enter your last name: ";
                cin >> temp.nameLast;
                checkStrings(temp.nameLast);
                cout << "Please enter your social security number: ";
                cin >> temp.social;
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "You cannot enter a character in this field. Enter numbers only" << endl;
                    cout << "Please enter information in field again" << endl;
                    cin >> temp.social;
                    cin.ignore(1000,'\n');
                }
                cout << "Please enter the amount of the loan: ";
                cin >> temp.loanAmt;
                while(cin.fail())
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "You cannot enter a character in this field. Enter numbers only" << endl;
                    cout << "Please enter information in field again" << endl;
                    cin >> temp.loanAmt;
                    cin.ignore(1000,'\n');
                }


                srand(time(0));

                temp.loanID = rand();

                system("cls");
                cout << "Thanking you for applying for a loan application" <<endl;

                cout << endl;

                cout << "Your loan ID is: " << temp.loanID << endl;

                cout << endl;

                cout << "Personal loans are given out at a 10 year fixed rate of 10.0%" << endl;

                temp.loanMonthPay = temp.loanAmt * ((PERSONAL_RATE * pow(1+PERSONAL_RATE,120)) / (pow(1+PERSONAL_RATE,120) - 1));

                temp.loanPrice = (temp.loanMonthPay * 120);

                cout << fixed << setprecision(2);
                cout << "Total Cost of Loan: " << temp.loanPrice << endl;
                cout << "Monthly Installment: " << temp.loanMonthPay << endl;

                loan.push_back(temp);

            }
            if(dec>3||dec<1)
                cout << "Please enter a correct option" << endl;
        }
        //Loan payment based on loan id
        if(opt == 2)
        {
            system("cls");

            int id;
            int i;
            double amt;
            bool check = false;

            cout << "Please enter Loan ID: ";
            cin >> id;

            for(i = 0; i < loan.size(); i++)
            {
                if(id == loan.at(i).loanID)
                {
                    check = true;
                    break;
                }

            }
            if(check==false)
            {
                cout << "Loan ID was not found" << endl;
                break;
            }

            cout << endl;

            cout << loan.at(i).nameFirst << " " << loan.at(i).nameLast << "'s " << loan.at(i).loanType << endl;

            cout << "Total loan cost: " << loan.at(i).loanPrice << endl;
            cout << "Monthly Installment: " << loan.at(i).loanMonthPay << endl;

            cout << endl;

            cout << "Please enter your payment amount: ";
            cin >> amt;

            loan.at(i).loanPrice = loan.at(i).loanPrice- amt;

            cout << endl;

            cout << "Current loan cost: " << loan.at(i).loanPrice;

            cout << endl;
            }
        if(opt == 3)
        {
            system("cls");
            int display;

            cout << "How would you like the information displayed?" << endl;
            cout << "Enter 1: Display All Information" << endl;
            cout << "Enter 2: Display by Loan Type" << endl;
            cin  >> display;

            cout << "************************************************************************************************************************" << endl;
            cout << "                                                    Loan Information                                                      " << endl;
            cout << "************************************************************************************************************************" << endl;
            cout << "Name" << setw(25) << "Loan Type" << setw(15) << "Social" << setw(16) << "Loan Amount"
                     << setw(14) << "Loan ID" << setw(20) << "Total Loan Cost" << setw(24) << "Monthly Installment" << setw(10) << endl;
            cout << "************************************************************************************************************************" << endl;
            //Display all loan information
            if(display==1)
            {
                for(int i = 0; i < loan.size(); i++)
                {
                string name;

                name = loan.at(i).nameFirst + " " + loan.at(i).nameLast;

                cout << setw(15) << left << name;
                cout << setw(13) << right << loan.at(i).loanType;
                cout << setw(16) << right << loan.at(i).social;
                cout << setw(14) << right << loan.at(i).loanAmt;
                cout << setw(15) << right << loan.at(i).loanID;
                cout << setw(18) << right << loan.at(i).loanPrice;
                cout << setw(18) << right << loan.at(i).loanMonthPay << endl;
                }
                cout << endl;
            }
            //Display loan information on loan type
            if(display==2)
            {
                int d;
                system("cls");
                cout << "What loan type would you like to see?" << endl;
                cout << endl;
                cout << "Enter 1: Mortgage" << endl;
                cout << "Enter 2: Student Loan" << endl;
                cout << "Enter 3: Personal Loan" << endl;
                cin >> d;

                cout << "************************************************************************************************************************" << endl;
                cout << "                                                    Loan Information                                                      " << endl;
                cout << "************************************************************************************************************************" << endl;
                cout << "Name" << setw(25) << "Loan Type" << setw(15) << "Social" << setw(16) << "Loan Amount"
                     << setw(14) << "Loan ID" << setw(20) << "Total Loan Cost" << setw(24) << "Monthly Installment" << setw(10) << endl;
                cout << "************************************************************************************************************************" << endl;

                if(d==1)
                {
                    for(int i = 0; i < loan.size(); i++)
                    {
                        if(loan.at(i).loanType=="Mortgage")
                        {
                            string name;

                        name = loan.at(i).nameFirst + " " + loan.at(i).nameLast;

                        cout << setw(15) << left << name;
                        cout << setw(13) << right << loan.at(i).loanType;
                        cout << setw(16) << right << loan.at(i).social;
                        cout << setw(14) << right << loan.at(i).loanAmt;
                        cout << setw(15) << right << loan.at(i).loanID;
                        cout << setw(18) << right << loan.at(i).loanPrice;
                        cout << setw(18) << right << loan.at(i).loanMonthPay << endl;
                        }
                    }
                }
                if(d==2)
                {
                    for(int i = 0; i < loan.size(); i++)
                    {
                        if(loan.at(i).loanType=="Student")
                        {
                            string name;

                        name = loan.at(i).nameFirst + " " + loan.at(i).nameLast;

                        cout << setw(15) << left << name;
                        cout << setw(13) << right << loan.at(i).loanType;
                        cout << setw(16) << right << loan.at(i).social;
                        cout << setw(14) << right << loan.at(i).loanAmt;
                        cout << setw(15) << right << loan.at(i).loanID;
                        cout << setw(18) << right << loan.at(i).loanPrice;
                        cout << setw(18) << right << loan.at(i).loanMonthPay << endl;
                        }
                    }
                }
                if(d==3)
                {
                    for(int i = 0; i < loan.size(); i++)
                    {
                        if(loan.at(i).loanType=="Personal")
                        {
                            string name;

                        name = loan.at(i).nameFirst + " " + loan.at(i).nameLast;

                        cout << setw(15) << left << name;
                        cout << setw(13) << right << loan.at(i).loanType;
                        cout << setw(16) << right << loan.at(i).social;
                        cout << setw(14) << right << loan.at(i).loanAmt;
                        cout << setw(15) << right << loan.at(i).loanID;
                        cout << setw(18) << right << loan.at(i).loanPrice;
                        cout << setw(18) << right << loan.at(i).loanMonthPay << endl;
                        }
                    }
                }
                if(d>3||d<0)
                    cout << "Please enter a valid option" << endl;

            }
            if(display>2||display<1)
            {
                cout << "Please enter a valid option" << endl;
            }
        }
        if(opt==0)
            flag = false;

    }
     cout << endl;

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;

    if(num == 0)
    {
        mainMenu(acc, loan, tran);
    }

}

///Angel
void searchAcc(vector<account> acc, vector<loans> loan, vector<transaction> tran)
{
    int opt;
    int num;
    string mon;
    string day;
    string year;


    cout << "How would you like to search for the account information?" << endl;
    cout << "Enter 1: Account Number" << endl;
    cout << "Enter 2: Date" << endl;
    cin >> opt;

    if(opt==1)
    {
        int accNum;
        int val;
        system("cls");
        cout << "Enter the account number: ";
        cin >> accNum;


        val = foundAcc(acc, accNum);


        if( val != -1)
        {
            cout << "************************************************************************************************************************" << endl;
            cout << "                                                    Account Information                                                 " << endl;
            cout << "************************************************************************************************************************" << endl;
            cout << "Account No." << setw(17) << "Account Type" << setw(15) << "Name" << setw(24) << "Phone Number"
                 << setw(14) << "Amount" << setw(20) << "Date Created" << endl;
            cout << "************************************************************************************************************************" << endl;

            string name;

            name = acc.at(val).firstName + " " + acc.at(val).lastName;

            cout << setw(5) << right << acc.at(val).accountId;
            cout << setw(22) << right << acc.at(val).accountType;
            cout << setw(20) << right << name;
            cout << setw(18) << right << acc.at(val).phoneNumber;
            cout << setw(15) << right << acc.at(val).amount;
             cout << setw(12) << right << acc.at(val).month << " " << acc.at(val).day << " " <<  acc.at(val).year << endl;
        }
        if(val == -1)
        {
            cout << "\nRecord was not found" << endl;
        }
    }

    if(opt==2)
    {
        int val;
        while(mon.length() != 3 || day.length() != 2 || year.length() != 4)
        {
            cout << "Please enter date(format: Jan 01 2017): ";
            cin >> mon >> day >> year;

            if(mon.length() == 3 && day.length() == 2 && year.length() == 4)
                break;
        }

            cout << "************************************************************************************************************************" << endl;
            cout << "                                                    Account Information                                                 " << endl;
            cout << "************************************************************************************************************************" << endl;
            cout << "Account No." << setw(17) << "Account Type" << setw(15) << "Name" << setw(24) << "Phone Number"
                 << setw(14) << "Amount" << setw(20) << "Date Created" << endl;
            cout << "************************************************************************************************************************" << endl;

            for(unsigned int i = 0; i < tran.size() ; ++i)
            {
                if(foundDay(tran, mon, day, year) != -1)
                {
                    string name;

                    val = foundDay(tran, mon, day, year);

                    name = acc.at(val).firstName + " " + acc.at(val).lastName;

                    cout << setw(5) << right << acc.at(val).accountId;
                    cout << setw(22) << right << acc.at(val).accountType;
                    cout << setw(20) << right << name;
                    cout << setw(18) << right << acc.at(val).phoneNumber;
                    cout << setw(15) << right << acc.at(val).amount;
                    cout << setw(12) << right << acc.at(val).month << " " << acc.at(val).day << " " <<  acc.at(val).year << endl;
                }

            }
            if(foundDay(tran, mon, day, year) == -1)
            {
                cout << "Record was not found" << endl;
            }
    }
    if(opt>2 || opt<1)
        cout << "Please enter a valid option" << endl;

    cout << endl;

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;

    if(num == 0)
    {
        mainMenu(acc, loan, tran);
    }
}

///Angel
int foundAcc(vector<account>& acc, int accNum)
{

        for(int i=0; i < acc.size(); i++)
        {
            if(acc.at(i).accountId == accNum)
                return i;
        }
    return -1;
}

///Taylor
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

///Angel
int foundDay(vector<transaction>& tran, string mon, string day, string year)
{
    for(int i=0; i < tran.size(); i++)
        {
            if(tran.at(i).month == mon && tran.at(i).day == day && tran.at(i).year == year)
                return i;
        }
    return -1;
}

///Angel
void transferAcc(vector<account>& acc, vector<loans>& loan, vector<transaction>& tran)
{
    int accNo1;
    int accNo2;
    int index1;
    int index2;
    int funds;
    int num;

    cout << "Enter account number of account that is transferring: ";
    cin >> accNo1;

    cout << endl;

    cout << "Enter account number of account receiving the transfer: ";
    cin  >> accNo2;

    system("cls");

    cout << "Account Transferring\n" << endl;
    index1 = foundAcc(acc, accNo1);
    cout << "Name of Account Holder: " << acc.at(index1).firstName << " " << acc.at(index1).lastName << endl;
    cout << "Amount in Account: " << acc.at(index1).amount << endl;

    cout << "Account receiving Transfer\n" << endl;
    index2 = foundAcc(acc, accNo2);
    cout << "Name of Account Holder: " << acc.at(index2).firstName << " " << acc.at(index2).lastName << endl;
    cout << "Amount in Account: " << acc.at(index2).amount << endl;

    cout << endl;

    cout << "Enter amount to be transfer: ";
    cin >> funds;
    if(funds >0 && funds <= acc.at(index1).amount)
    {
        acc.at(index1).amount = acc.at(index1).amount - funds;
        acc.at(index2).amount = acc.at(index2).amount + funds;
        saveAccounts(acc);
    }
    else
        cout << "Please enter a valid amount" << endl;

    system("cls");

    cout << "Amount transferred: " << funds << endl;
    cout << endl;
    cout << "Name of Account Holder: " << acc.at(index1).firstName << " " << acc.at(index1).lastName << endl;
    cout << "Amount in Account: " << acc.at(index1).amount << endl;
    cout << endl;
    cout << "Name of Account Holder: " << acc.at(index2).firstName << " " << acc.at(index2).lastName << endl;
    cout << "Amount in Account: " << acc.at(index2).amount << endl;

    cout << endl;

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;

    if(num == 0)
    {
        mainMenu(acc, loan, tran);
    }

}
