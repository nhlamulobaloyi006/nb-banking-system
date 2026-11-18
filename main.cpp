// NB SMART BANKING SYSTEMS
// Gauteng City College - Introduction to Programming NQF 4
// A command line banking system written in C++
// Features: login, check balance, deposit, withdraw, send cash, sign out, exit

#include <iostream>   // for cin and cout
#include <string>     // for using strings
#include <ctime>      // for the date and time on receipts

using namespace std;

// ================= USER DETAILS (stored in arrays) =================
// Position 0 in every array belongs to the same person,
// position 1 belongs to the second person, and so on.
string usernames[4] = {"Nhlamulo", "Ocean", "Liyema", "Martin"};
string surnames[4] = {"Baloyi", "Chirwa", "Goloza", "Chuine"};
string pins[4] = {"0625", "0514", "0524", "0824"};
int account_numbers[4] = {20154545, 20456942, 20649863, 20348548};
double balances[4] = {0, 10, 25, 30};

// ================= LOGGED IN USER DETAILS =================
string name, surname;   // name and surname of the person who logged in
int account_num;        // account number of the person who logged in
int getIndex = -1;      // position of the logged in user in the arrays
bool isUser = false;    // true when the login was successful

// menu option that the user chooses
int option;

// ================= LOGIN FUNCTIONS =================

// Checks that the username and pin were filled in correctly.
// Returns true if they are fine, false if not.
bool validateAuthInput(string username, string pin)
{
    if (username.length() == 0 || pin.length() != 4)
    {
        cout << "Username cannot be empty and the pin must be 4 digits" << endl;
        return false;
    }
    return true;
}

// Asks for the username and pin and keeps asking until they are correct
void authentication()
{
    string username, pin;

    isUser = false;   // reset, so a new login always starts fresh

    cout << "============================" << endl;
    cout << " NB SMART BANKING SYSTEMS" << endl;
    cout << "============================" << endl;

    // keep asking until the login is successful
    while (isUser == false)
    {
        cout << "        LOGIN" << endl << endl;
        cout << "Username: " << endl;
        cin >> username;
        cout << "Pin: " << endl;
        cin >> pin;

        // if the input is not valid, ask again
        if (validateAuthInput(username, pin) == false)
        {
            continue;   // jump back to the top of the loop
        }

        // loop through all the users to find a matching username and pin
        for (int i = 0; i < 4; i++)
        {
            if (usernames[i] == username && pins[i] == pin)
            {
                getIndex = i;                    // remember who logged in
                isUser = true;
                name = usernames[i];
                surname = surnames[i];
                account_num = account_numbers[i];
            }
        }

        if (isUser == false)
        {
            cout << "username or pin is invalid" << endl;
            cout << "============================" << endl;
        }
        else
        {
            cout << "Access granted" << endl;
        }
    }
}

// ================= MAIN =================
int main()
{
    authentication();   // the user must log in first
    return 0;
}