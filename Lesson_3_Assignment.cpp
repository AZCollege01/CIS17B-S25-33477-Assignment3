// Author: Aaron Zamora
// With Starter code from Assignment Page

// including header files
#include <iostream>
#include <memory>
#include <stdexcept>
using namespace std;

// TODO: Define custom exception classes here
// - NegativeDepositException (for negative deposit attempts)
class NegativeDepositException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Negative deposits are not allowed!";
    }

};

// - NegativeWithdrawalException (for negative withdrawal attempts)
class NegativeWithdrawalException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Negative withdrawals are not allowed!";
    }
};

// - OverdrawException (for withdrawing more than the balance)
class OverdrawException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "You can not overdraw from what is in the account!";
    }
};

// - InvalidAccountOperationException (for transactions on a closed account)
class InvalidAccountOperationException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Account has been closed, no further transactions are allowed!";
    }
};

// - InvalidInputException (for when user inputs characters instead of numbers)
class InvalidInputException : public exception
{
public:
    const char* what() const noexcept override
    {
        return "Invalid input! Please enter a number.";
    }
};

class BankAccount {
private:
    string accountNumber;
    double balance;
    bool isActive;

public:
    // Constructor to initialize account number, balance, and active status
    BankAccount(string accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance), isActive(true) {}

    // Deposit method
    void deposit(double amount) {
        // TODO: Implement exception handling for negative deposits
        if (!isActive) // check if account is closed for transactions
        {
			throw InvalidAccountOperationException();
        }
        if (cin.fail()) // check if user inputs characters instead of numbers
        {
            cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			throw InvalidInputException();
        }
        if (amount < 0)
        {
            throw NegativeDepositException();
        }
        balance += amount;
    }

    // Withdraw method
    void withdraw(double amount) {
        // TODO: Implement exception handling for overdrawing and closed accounts
		if (!isActive) // check if account is closed for transactions
		{
			throw InvalidAccountOperationException();
		}
        if (cin.fail()) // check if user inputs characters instead of numbers
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw InvalidInputException();
        }
        if (amount > balance) // check if withdrawal amount is greater than the current balance
        {
            throw OverdrawException();
        }
        if (amount < 0) // check if user inputs a negative number
        {
			throw NegativeWithdrawalException();
        }
        balance -= amount;
    }

    // Method to get current balance
    double getBalance() const {
		if (!isActive) // check if account is closed for transactions
		{
			throw InvalidAccountOperationException();
		}
        return balance;
    }

    // Method to close the account
    void closeAccount() {
        // TODO: Prevent further transactions when the account is closed
        if (!isActive) // check if the account is already closed by the user
        {
            cout << "Account is already closed." << endl;
			cout << endl; // line spacing for readability
            return;
        }
        isActive = false;
    }

    // Method to check if the account is active
    bool isAccountActive() const {
        return isActive;
    }
};

// start of program
int main() {
    try {
        int _initialBalance; // user input for initial bank balance
        int choice; // user input for menu interface
        double usrBalance; // user input for deposit and withdrawal

        // TODO: Ask the user to enter an initial balance and create a BankAccount object using smart pointers
        // Example: std::cout << "Enter initial balance: ";
        //          std::cin >> initialBalance;
        //          auto account = std::make_unique<BankAccount>("123456", initialBalance);
        //auto account = std::make_unique<BankAccount>("123456", 1000.0); // Example initialization

        //user menu to allow for user input testing

        cout << "Welcome to the Bank Management System" << endl;
        cout << endl;

        // The creation of the Bank Account for the user
        cout << "Please Enter initial balance for the account: ";

        // while loop for user input validation
        while (true)
        {
            cin >> _initialBalance;
            if (!cin) // checking if user inputs characters instead of numbers
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "invalid input. please enter a number." << endl;
                continue;
            }
            else if (_initialBalance < 0) // checking if user inputs a negative balance
            {
                cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid balance. Please don't enter negative numbers." << endl;
                continue;
            }
            else //breaks when input is valid
            {
                cout << endl; // line spacing for readability
                break;
            }
        }

        auto account = make_unique<BankAccount>("123456", _initialBalance);
        cout << "Bank Account Created: #" << "123456" << endl;
        cout << "$ " << _initialBalance << " balance has been added to the account." << endl;
		cout << endl; // line spacing for readability

        // Start of the User Input Demonstration
        // while loop for menu
        while (true) {

            //menu display for user
            cout << "Please enter a number to select." << endl;
            cout << "1. Deposit" << endl;
            cout << "2. Withdrawal" << endl;
            cout << "3. Current Balance" << endl;
            cout << "4. Close Account" << endl;
            cout << "5. Exit Program" << endl;

            cin >> choice; //user input for menu

            if (!cin) //checking if user inputs characters instead of numbers
            {
                cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Input. Please enter 1-5." << endl;
				cout << endl; // line spacing for readability
                continue;
            }

            else if (choice < 1 || choice > 5) //checking the range of user input
            {
                cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Input. Please enter 1-5." << endl;
				cout << endl; // line spacing for readability
                continue;
            }

            //switch statement to handle user input
            switch (choice) {

            case 1: // Deposit
                cout << "Please enter the amount to deposit: ";
                cin >> usrBalance;
                try //checking user input for deposit
                {
                    account->deposit(usrBalance);
                    cout << "Deposited $" << usrBalance << " into the account." << endl;
                }
				catch (const exception& e) //catching exception and using custom exception when caught
				{
                    cout << e.what() << endl;
					cout << endl; // line spacing for readability
				}
                break;

            case 2: // Withdrawal
                cout << "Please enter the amount to withdraw: ";
                cin >> usrBalance;
                try //checking user input for withdrawal
                {
                    account->withdraw(usrBalance);
                    cout << "Withdrew $" << usrBalance << " from the account." << endl;
                }
                catch (const exception& e) //catching exception and using custom exception when caught
                {
                    cout << e.what() << endl;
					cout << endl; // line spacing for readability
                }
                break;

            case 3: // Current Balance
                try
                {
                    cout << "Current Balance: $" << account->getBalance() << endl;
                    cout << endl; // line spacing for readability
                }
                catch (const exception& e) //catching exception when account is closed
                {
                    cout << e.what() << endl;
					cout << endl; // line spacing for readability
                }
                break;

            case 4: // Close Account
                if (account->isAccountActive() == true) //checks if account is active
                {
                    account->closeAccount();
                    cout << "Account Closed." << endl;
					cout << endl; // line spacing for readability
                }
                else
                {
                    account->closeAccount(); // member function displays error message
                }
                break;

            case 5: // Exit Program
                cout << "Exiting Program." << endl;
                break;

            default: //error checking input choice
                cout << "Invalid Input. Please Enter 1-5." << endl;
                break;
            }
            if (choice == 5) { //breaks out of loop if user enters 5
                break;
            }
        }

        // Demonstration section for test cases
        cout << "Demonstrating test cases." << endl;
        cout << endl;

        //test account creation
        cout << "Creating Test Account..." << endl;
        auto accountTest = make_unique<BankAccount>("121233", 100);
        cout << endl;

        // Test case: Deposit
        try
        {
            cout << "Depositing -$1000..." << endl;
            accountTest->deposit(-1000); // should throw custom exception
        }
        catch (const exception& e)
        {
            cout << e.what() << endl;
            cout << "Deposit Exception caught and Demonstrated." << endl;
            cout << endl;
        }

        // Test case: Withdraw
        try {
            cout << "Withdrawing $500..." << endl;
            accountTest->withdraw(500); // should throw custom exception
        }
        catch (const exception& e)
        {
            cout << e.what() << endl;
            cout << "Withdraw Exception caught and Demonstrated." << endl;
            cout << endl;
        }

        // Test case: withdraw with negative amount
        try {
            cout << "Withdrawing -$500..." << endl;
            accountTest->withdraw(-500); // should throw custom exception
        }
        catch (const exception& e)
        {
            cout << e.what() << endl;
            cout << "Negative Withdraw Exception caught and Demonstrated." << endl;
            cout << endl;
        }

        // Test case: Get Balance
        cout << "Current Balance: $" << accountTest->getBalance() << endl;
        cout << endl;

        // Test case: Closed Account
        cout << "Closing the Test acocunt..." << endl;
        accountTest->closeAccount(); // closing the account for demonstration
        cout << endl;

        // Test case: Deposit on Closed Account
        try 
        {
            accountTest->deposit(100); // should throw custom exception
        }
        catch (const exception& e)
        {
            cout << e.what() << endl;
            cout << "Closed Deposit Exception caught and Demonstrated" << endl;
            cout << endl;
        }

        //Test case: Withdraw on Closed Account
        try
        {
            accountTest->withdraw(50); // should throw custom exception
        }
        catch (const exception& e)
        {
            cout << e.what() << endl;
            cout << "Closed Withdraw Exception caught and Demonstrated" << endl;
            cout << endl;
        }

        //Test case: Getting Balance on Closed Account
        try
        {
            accountTest->getBalance(); //should throw custom exception
        }
        catch (const exception& e)
        {
            cout << e.what() << endl;
            cout << "Closed Getting Balance Exception caught and Demonstrated" << endl;
            cout << endl;
        }

        // End of program
        cout << "End of Demonstration." << endl;

    }
    catch (const exception& e) {
        // TODO: Catch and handle exceptions properly
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}