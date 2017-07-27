//Angel Castro COP 1334
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

using namespace std;

struct account
{
    string firstName;
    string lastName;
    int accountId;
    long long int phoneNumber;
    string accountType;
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

string ACCOUNTFILENAME = "accounts.txt";

int welcomeScreen(int counter);
void devScreen();
void mainMenu(vector<account>& acc, vector<loans>& loan);
void selectMenu(int opt, vector<account>& acc, vector<loans>& loan);
void getAccounts(vector<account>& acc);
void openAccount(vector<account>& acc, vector<loans>& loan);
void saveAccounts(vector<account>& acc);
void despositAmount(vector<account>& acc);
void withdrawAmount();
void displayAccounts(vector<account>& acc, vector<loans>& loan);
void displayTransactions();
void checkStrings(string str);
void eraseAcc(vector<account>& acc, vector<loans>& loan);
void loanProcess(vector<loans>& loan, vector<account>& acc);
void getLoanData(vector<loans>& loan);
void saveLoanData(vector<loans> loan);
int showLoanMenu();
int found(vector<loans> loan, int accNum);
void searchAcc(vector<account> acc, vector<loans> loan);
void transferAcc(vector<account>& acc, vector<loans>& loan);
int foundAcc(vector<account>& acc, int accNum);

int main()
{
    vector<account> accounts;
    vector<loans> loan;

    int option;
    int i = 0;

    //ifstream existFile(ACCOUNTFILENAME.c_str());
   // if(existFile)
   //// {
    //    getAccounts(accounts);
    //}
    getAccounts(accounts);
    getLoanData(loan);

    do
    {
        option = welcomeScreen(i);
        if(option == 1 && i == 0)
        {
            devScreen();
        }
        if((option == 2 && i == 0) || (option == 1 && i != 0))
        {
            mainMenu(accounts, loan);
            option = 99;
        }
        i++;
    }while(option != 99);

    system("cls");
    //Saves data inputted
    saveLoanData(loan);

    return 0;
}

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

void devScreen()
{
    system("cls");

    cout << "Developers:" << endl << endl;
    cout << "Angel Castro" << endl;
    cout << "Taylor Martinez" << endl << endl;

    cout << "Guide:" << endl;

    return;
}

void mainMenu(vector<account>& acc, vector<loans>& loan)
{
    int option;

    system("cls");
    cout << "**********************************************" << endl;
    cout << "                 Main Menu                    " << endl;
    cout << "**********************************************" << endl;
    cout << "Main Menu: " << endl << endl;

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

    selectMenu(option, acc, loan);

    return;
}

void selectMenu(int opt, vector<account>& acc, vector<loans>& loan)
{

    if(opt == 1)
    {
        openAccount(acc, loan);
        saveAccounts(acc);
    }

    if (opt == 2)
    {
        //depositAmount();
    }
    if(opt == 3)
    {
        //withdrawAmount();
    }
    if(opt == 4)
    {
        displayAccounts(acc, loan);

    }
    if(opt == 5)
    {
        //displayTransactions();
    }

    if(opt == 6)
    {
        system("cls");
        eraseAcc(acc, loan);
    }

    if(opt == 7)
    {
        system("cls");
        loanProcess(loan, acc);
    }
    if(opt == 8)
    {
       system("cls");
       searchAcc(acc, loan);
    }
    if(opt == 9)
    {
       system("cls");
       transferAcc(acc, loan);
    }
    if(opt == 0)
        return;

    if(opt > 10 || opt < 1)
        cout << "Please enter a correct option" << endl;


    return;
}

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

        acc.push_back(tmp);
    }

    inFile.close();

    return;
}

void openAccount(vector<account>& acc, vector<loans>& loan)
{
    account tmp;
    string str;
    bool check = false;
    int counter = 1;
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

    /*while(!cin.fail())
    {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "You cannot enter a character in this field. Enter numbers only" << endl;
        cout << "Please enter information in field again" << endl;
        cin.ignore(1000,'\n');
        cin >> tmp.phoneNumber;
        cin.ignore(1000,'\n');
    }*/

    check = false;

    /*while(!check)
    {
        num = tmp.phoneNumber;
        while(num >= 0)
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
        counter = 1;
    }*/

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

    //Amount
    cout << "Please input your initial desposit: " << endl;
    cin >> tmp.amount;

    acc.push_back(tmp);

    cout << endl << "Account has been made" << endl;

    cout << endl;

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;

    if(num == 0)
    {
        mainMenu(acc, loan);
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

void despositAmount(vector<account>& acc)
{
    system("cls");
}

void displayAccounts(vector<account>& acc, vector<loans>& loan)
{

    system("cls");

    int num;

    cout << "************************************************************************************************************************" << endl;
    cout << "                                                    Account Information                                                 " << endl;
    cout << "************************************************************************************************************************" << endl;
    cout << "Account No." << setw(17) << "Account Type" << setw(15) << "Name" << setw(24) << "Phone Number"
         << setw(14) << "Amount" << endl;
    cout << "************************************************************************************************************************" << endl;

    string name;

    for(int i=0; i < acc.size(); i++)
    {
        name = acc.at(i).firstName + " " + acc.at(i).lastName;

        cout << setw(5) << right << acc.at(i).accountId;
        cout << setw(22) << right << acc.at(i).accountType;
        cout << setw(20) << right << name;
        cout << setw(18) << right << acc.at(i).phoneNumber;
        cout << setw(15) << right << acc.at(i).amount << endl;
        cout << endl;
    }


    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;

    if(num == 0)
    {
        mainMenu(acc, loan);
    }

}

//Program by Taylor Martinez. Checks to see if a string has any numbers within
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
void eraseAcc(vector<account>& acc, vector<loans>& loan)
{
    int i;
    int opt;
    int num;


    cout << "Please enter the account number to delete: ";
    cin >> i;

    foundAcc(acc, i);
    if(i == -1)
    {
        cout << "Record was not found" << endl;
        return;
    }

    cout << endl;

    cout << "Would you like to delete the account under " << acc.at(i).firstName << " " << acc.at(i).lastName << endl;

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
        mainMenu(acc, loan);
    }

}

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
void loanProcess(vector<loans>& loan, vector<account>& acc)
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
                cout << "Please enter your last name: ";
                cin >> temp.nameLast;
                cout << "Please enter your social security number: ";
                cin >> temp.social;
                cout << "Please enter the amount of the loan: ";
                cin >> temp.loanAmt;

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
                cin >> temp.nameFirst;
                cout << "Please enter your last name: ";
                cin >> temp.nameLast;
                cout << "Please enter your social security number: ";
                cin >> temp.social;
                cout << "Please enter the amount of the loan: ";
                cin >> temp.loanAmt;

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
                cout << "Please enter your last name: ";
                cin >> temp.nameLast;
                cout << "Please enter your social security number: ";
                cin >> temp.social;
                cout << "Please enter the amount of the loan: ";
                cin >> temp.loanAmt;

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
        mainMenu(acc, loan);
    }

}

//Searches data, only account number completed can use same template for date
void searchAcc(vector<account> acc, vector<loans> loan)
{
    int opt;
    int num;

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
                 << setw(14) << "Amount" << endl;
            cout << "************************************************************************************************************************" << endl;

            string name;

            name = acc.at(val).firstName + " " + acc.at(val).lastName;

            cout << setw(5) << right << acc.at(val).accountId;
            cout << setw(22) << right << acc.at(val).accountType;
            cout << setw(20) << right << name;
            cout << setw(18) << right << acc.at(val).phoneNumber;
            cout << setw(15) << right << acc.at(val).amount << endl;
            cout << endl;
        }
        if(val == -1)
        {
            cout << "\nRecord was not found" << endl;
        }
    }

    if(opt==2)
    {

    }
    if(opt>2 || opt<1)
        cout << "Please enter a valid option" << endl;

    cout << endl;

    cout << "Press 0 if you wish return to the main menu" << endl;
    cin >> num;

    if(num == 0)
    {
        mainMenu(acc, loan);
    }
}

//returns index to display account
int foundAcc(vector<account>& acc, int accNum)
{

        for(int i=0; i < acc.size(); i++)
        {
            if(acc.at(i).accountId == accNum)
                return i;
        }
    return -1;
}

//Transfer loans based on social security entered can be changed to anything else
void transferAcc(vector<account>& acc, vector<loans>& loan)
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
        mainMenu(acc, loan);
    }

}
