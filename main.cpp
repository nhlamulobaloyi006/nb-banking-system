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

// ================= HELPER FUNCTIONS =================

// Prints the current date and time (used on the receipts)
void showDate()
{
    time_t now = time(0);   // get the time right now
    cout << ctime(&now);    // ctime already adds a new line at the end
}

// Asks for an amount and returns it.
// Returns -1 if the user typed something that is not a number.
double readAmount()
{
    double amount;
    cin >> amount;

    if (cin.fail())          // the user typed letters instead of a number
    {
        cin.clear();                // clear the error
        cin.ignore(1000, '\n');     // throw away the wrong input
        return -1;
    }
    return amount;
}

// ================= BANKING FUNCTIONS =================

// Option 1: shows the account details and the current balance
void checkBalance(double balance)
{
    cout << "=======================" << endl;
    cout << "Account Details" << endl;
    cout << "=======================" << endl;
    cout << "Account Holder: " << name[0] << " " << surname << endl; // first letter of the name + surname
    cout << "Account number: " << account_num << endl;
    cout << "Balance: R" << balance << endl;
}

// Option 2: adds money to the account
void deposit(double balance)
{
    double depositCash;

    cout << "Enter amount to deposit" << endl;
    cout << "=R";
    depositCash = readAmount();

    // the amount must be more than 0
    if (depositCash <= 0)
    {
        cout << "Invalid amount. The amount must be a number more than 0" << endl;
        return;   // go back to the menu
    }

    balance = balance + depositCash;   // add the money
    balances[getIndex] = balance;      // save the new balance in the array

    // print the receipt
    cout << "=========================================================" << endl;
    cout << " NB SMART BANKING SYSTEMS             Transaction record" << endl << endl;
    cout << "                                CASH DEPOSIT RECEIPT" << endl << endl;
    cout << " TRANSACTION DATE   ";
    showDate();
    cout << " CUSTOMER NAME      " << name[0] << " " << surname << endl << endl;
    cout << " TO ACCOUNT         " << account_num << endl << endl;
    cout << " AMOUNT DEPOSITED    R" << depositCash << endl << endl;
    cout << " ACCOUNT BALANCE     R" << balance << endl;
    cout << "=========================================================" << endl;
}

// Option 3: takes money out of the account
void withdraw(double balance)
{
    double withdrawCash;

    cout << "Enter amount to withdraw" << endl;
    cout << "=R";
    withdrawCash = readAmount();

    // the amount must be more than 0
    if (withdrawCash <= 0)
    {
        cout << "Invalid amount. The amount must be a number more than 0" << endl;
        return;
    }

    // the user cannot withdraw more than the balance
    if (balance < withdrawCash)
    {
        cout << "You have insufficient funds" << endl;
    }
    else
    {
        balance = balance - withdrawCash;   // take the money out
        balances[getIndex] = balance;       // save the new balance in the array

        // convert the account number to text so we can show only the last 4 digits
        string accountText = to_string(account_numbers[getIndex]);

        // print the receipt
        cout << "=========================================================" << endl;
        cout << " NB SMART BANKING SYSTEMS             Transaction record" << endl << endl;
        cout << "                                CASH WITHDRAWAL RECEIPT" << endl << endl;
        cout << " TRANSACTION DATE   ";
        showDate();
        cout << " FROM ACCOUNT        " << "*************" << accountText.substr(4, 4) << endl << endl;
        cout << " AMOUNT WITHDRAWN   R -" << withdrawCash << endl << endl;
        cout << " AVAILABLE FUNDS    R " << balance << endl << endl;
        cout << " ACCOUNT BALANCE    R " << balance << endl;
        cout << "=========================================================" << endl;
    }
}

// Option 4: sends money to another account
void sendCash(double balance)
{
    string benName, benSurname, reference;   // beneficiary = the person receiving the money
    int benAccount;
    int benIndex = -1;                       // -1 means "not found yet"
    double amount;

    cout << "=======================" << endl;
    cout << "    Beneficiaries" << endl;
    cout << "=======================" << endl;

    cout << "Enter beneficiary name" << endl;
    cout << "= ";
    cin >> benName;
    cout << "Enter beneficiary surname" << endl;
    cout << "= ";
    cin >> benSurname;
    cout << "Enter beneficiary account number" << endl;
    cout << "= ";
    cin >> benAccount;

    // the account number must be a number
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid account number, please try again" << endl;
        return;
    }

    cin.ignore(1000, '\n');   // remove the Enter key left over, so getline works
    cout << "Enter beneficiary reference" << endl;
    cout << "= ";
    getline(cin, reference);  // getline allows spaces in the reference

    // loop through all the users to find the beneficiary
    for (int i = 0; i < 4; i++)
    {
        if (account_numbers[i] == benAccount && usernames[i] == benName && surnames[i] == benSurname)
        {
            benIndex = i;   // found the account
        }
    }

    // the account does not exist
    if (benIndex == -1)
    {
        cout << "Account not found. Check the name, surname and account number" << endl;
        return;
    }

    // you cannot send money to yourself
    if (benIndex == getIndex)
    {
        cout << "You cannot send cash to your own account" << endl;
        return;
    }

    cout << "Enter amount" << endl;
    cout << "=R";
    amount = readAmount();

    // the amount must be more than 0
    if (amount <= 0)
    {
        cout << "Invalid amount. The amount must be a number more than 0" << endl;
        return;
    }

    // check that the balance is enough
    if (balance >= amount)
    {
        balances[benIndex] = balances[benIndex] + amount;   // beneficiary receives the money
        balance = balance - amount;                         // we lose the money
        balances[getIndex] = balance;                       // save our new balance

        // print the proof of payment
        cout << "=========================================================" << endl;
        cout << " NB SMART BANKING SYSTEMS             Transaction record" << endl << endl;
        cout << "                                PROOF OF PAYMENT" << endl << endl;
        cout << " BENEFICIARY NAME            " << usernames[benIndex][0] << " " << surnames[benIndex] << endl;
        cout << " BENEFICIARY ACCOUNT NUMBER  " << benAccount << endl;
        cout << " BENEFICIARY REFERENCE       " << reference << endl;
        cout << " AMOUNT SENT                 R " << amount << endl;
        cout << " YOUR NEW BALANCE            R " << balance << endl << endl;
        cout << " TRANSACTION DATE            ";
        showDate();
        cout << "=========================================================" << endl;
    }
    else
    {
        cout << "You have insufficient funds" << endl;
    }
}

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

// ================= MENU =================

// Shows the menu, reads the choice and calls the correct function
void menu()
{
    cout << "=======================" << endl;
    cout << "Welcome back " << name << endl;
    cout << "=======================" << endl;
    cout << "Choose option" << endl;
    cout << "1. Check Balance & Account Details" << endl;
    cout << "2. Deposit Cash" << endl;
    cout << "3. Withdraw Cash" << endl;
    cout << "4. Send Cash" << endl;
    cout << "5. Sign out" << endl;
    cout << "0. Exit" << endl;
    cout << "= ";
    cin >> option;

    // if the user typed letters, set option to -1 so it goes to the default case
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        option = -1;
    }

    // always send the latest balance from the array to the functions
    switch (option)
    {
    case 1:
        checkBalance(balances[getIndex]);
        break;
    case 2:
        deposit(balances[getIndex]);
        break;
    case 3:
        withdraw(balances[getIndex]);
        break;
    case 4:
        sendCash(balances[getIndex]);
        break;
    case 5:
        cout << "You have been signed out" << endl;
        authentication();   // go back to the login screen
        break;
    case 0:
        cout << "Exiting program.." << endl;
        break;
    default:
        cout << "Invalid choice. Please enter a number from 0 to 5" << endl;
        break;
    }
}

// ================= MAIN =================
int main()
{
    authentication();   // the user must log in first

    // show the menu again and again until the user chooses 0 (Exit)
    do
    {
        menu();
    } while (option != 0);

    return 0;
}
