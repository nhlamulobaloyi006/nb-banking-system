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

// ================= MAIN =================
int main()
{
    cout << "NB SMART BANKING SYSTEMS" << endl;
    cout << "Program started" << endl;
    return 0;
}
