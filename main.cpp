#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <ctime>
#include <cmath>


using namespace std;



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

void eraseAcc(vector<loans>& players);
void loanProcess(vector<loans>& loan);
void getLoanData(vector<loans>& loan);
void saveLoanData(vector<loans> loan);
int showLoanMenu();
int showMenu();
int found(vector<loans> loan, int accNum);
void searchLoan(vector<loans> loan);
void transferLoan(vector<loans> loan);

int main()
{
    int opt;
    int index;


    vector<loans> loan;
    bool quit = true;

    getLoanData(loan);

    while(quit)
    {
        //Displaying menu
        opt = showMenu();
        if(opt == 1)
        {
            system("cls");
            eraseAcc(loan);
        }
        if(opt==2)
        {
            system("cls");
            loanProcess(loan);
        }
        if(opt==3)
        {
            system("cls");
            searchLoan(loan);
        }
        if(opt==4)
        {
            system("cls");
            transferLoan(loan);
            cout << endl;
        }
        if(opt == 0)
            quit = false;
        if(opt > 4 || opt < 0)
        {
            system("cls");
            cout << "Please enter a correct option" << endl;
            cout << endl;
        }
    }

    system("cls");
    //Saves data inputted
    saveLoanData(loan);

    return 0;
}
void eraseAcc(vector<loans>& loan)
{
    int i;
    int opt;


    cout << "Please enter index of the account to delete: ";
    cin >> i;

    cout << endl;

    cout << "Would you like to delete the account under " << loan.at(i).nameFirst << " " << loan.at(i).nameLast << endl;

    cout << endl;

    cout << "Enter 1: Yes" << endl;
    cout << "Enter 2: No" << endl;
    cin >> opt;

    while(opt != 2)
    {
        if(opt==1)
        {
            loan.erase(loan.begin()+i);
            break;


        }
        if(opt >2 || opt < 1)
        {
            cout << "Please enter a correct option" << endl;
            cout << "Would you like to delete the account under " << loan.at(i).nameFirst << " " << loan.at(i).nameLast << endl;

            cout << endl;

            cout << "Enter 1: Yes" << endl;
            cout << "Enter 2: No" << endl;
            cin >> opt;
        }
    }

}
int showMenu()
{
    int choice;

    cout << "Menu" << endl;
    cout << "Enter 1: Erase" << endl;
    cout << "Enter 2: Loan" << endl;
    cout << "Enter 3: Search" << endl;
    cout << "Enter 4: Transfer" <<endl;
    cout << "Enter 0: Exit" << endl;
    cin >> choice;

    return choice;
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

    int i;
    int dec;

    cout << "Would you like to save the information? \nEnter 1: Yes \nEnter 2: No" << endl;
    cin >> dec;

    if(dec == 1)
    {
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
        cout << "Data Saved" <<endl;
    }
    else
        cout << "Data Not Saved" << endl;

}
void loanProcess(vector<loans>& loan)
{
    int opt;
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
}

void searchLoan(vector<loans> loan)
{
    int opt;

    cout << "How would you like to search for the account information?" << endl;
    cout << "Enter 1: Account Number" << endl;
    cout << "Enter 2: Date" << endl;
    cin >> opt;

    if(opt==1)
    {
        int accNum;
        system("cls");
        cout << "Enter the account number: ";
        cin >> accNum;


        if(found(loan, accNum) != -1)
        {
            cout << "************************************************************************************************************************" << endl;
            cout << "                                                    Loan Information                                                      " << endl;
            cout << "************************************************************************************************************************" << endl;
            cout << "Name" << setw(25) << "Loan Type" << setw(15) << "Social" << setw(16) << "Loan Amount"
                 << setw(14) << "Loan ID" << setw(20) << "Total Loan Cost" << setw(24) << "Monthly Installment" << setw(10) << endl;
            cout << "************************************************************************************************************************" << endl;

            string name;
            int index = found(loan, accNum);

            name = loan.at(index).nameFirst + " " + loan.at(index).nameLast;

            cout << setw(15) << left << name;
            cout << setw(13) << right << loan.at(index).loanType;
            cout << setw(16) << right << loan.at(index).social;
            cout << setw(14) << right << loan.at(index).loanAmt;
            cout << setw(15) << right << loan.at(index).loanID;
            cout << setw(18) << right << loan.at(index).loanPrice;
            cout << setw(18) << right << loan.at(index).loanMonthPay << endl;
            cout << endl;
        }
        if(found(loan, accNum) == -1)
        {
            cout << "\nRecord was not found" << endl;
        }
    }

    if(opt==2)
    {

    }
    if(opt>2 || opt<1)
        cout << "Please enter a valid option" << endl;

}

int found(vector<loans> loan, int accNum)
{

        for(int i=0; i < loan.size(); i++)
        {
            if(loan.at(i).social == accNum)
                return i;
        }
    return -1;
}

void transferLoan(vector<loans> loan)
{
    int accNo1;
    int accNo2;
    int index1;
    int index2;
    int funds;

    cout << "Enter account number of account that is transferring: ";
    cin >> accNo1;

    cout << endl;

    cout << "Enter account number of account receiving the transfer: ";
    cin  >> accNo2;

    system("cls");

    cout << "Account Transferring\n" << endl;
    index1 = found(loan, accNo1);
    cout << "Name of Account Holder: " << loan.at(index1).nameFirst << " " << loan.at(index1).nameLast << endl;
    cout << "Amount in Account: " << loan.at(index1).loanPrice << endl;

    cout << "Account receiving Transfer\n" << endl;
    index2 = found(loan, accNo2);
    cout << "Name of Account Holder: " << loan.at(index2).nameFirst << " " << loan.at(index2).nameLast << endl;
    cout << "Amount in Account: " << loan.at(index2).loanPrice << endl;

    cout << endl;

    cout << "Enter amount to be transfer: ";
    cin >> funds;
    if(funds >0 && funds <= loan.at(index1).loanPrice)
    {
        loan.at(index1).loanPrice = loan.at(index1).loanPrice-funds;
        loan.at(index2).loanPrice = loan.at(index2).loanPrice + funds;

    }
    else
        cout << "Please enter a valid amount" << endl;

    system("cls");

    cout << "Amount transferred: " << funds << endl;
    cout << endl;
    cout << "Name of Account Holder: " << loan.at(index1).nameFirst << " " << loan.at(index1).nameLast << endl;
    cout << "Amount in Account: " << loan.at(index1).loanPrice << endl;
    cout << endl;
    cout << "Name of Account Holder: " << loan.at(index2).nameFirst << " " << loan.at(index2).nameLast << endl;
    cout << "Amount in Account: " << loan.at(index2).loanPrice << endl;

}
