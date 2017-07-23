#include <iostream>
#include <cstdlib>

using namespace std;

int welcomeScreen(int counter);
void devScreen();
void mainMenu();

int main()
{
    int option;
    int i = 0;

    do
    {
        option = welcomeScreen(i);
        if(option == 1 && i == 0)
        {
            devScreen();
        }
        if((option == 2 && i == 0) || (option == 1 && i != 0))
        {
            mainMenu();
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
    //cout << "Press zero when you wish to go back to the Welcome Screen" << endl << endl;
    cout << "Developers:" << endl << endl;
    cout << "Angel Castro" << endl;
    cout << "Taylor Martinez" << endl << endl;

    cout << "Guide:" << endl;

    return;
}

void mainMenu()
{
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

    return;
}
