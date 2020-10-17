#include<stdio.h>
#include<iostream>
#include<string>
#include<fstream>

using namespace std;

struct AccDetails 
{
	string AccNumber;
	string AccHolderName;
	string pin;
	float AccBalance = 0;
};

void DisplayText()
{
	cout << "\n\t\t\t BANQUE ROYALE";
	cout << "\n\t\t\t--------------";
	cout << "\n\t\tGuichet Automatique Bancaire";
	cout << "\n\t\t-----------------------------";
}

void displayMenu() 
{
	cout << "\n \t1 - Deposit \n";
	cout << "\t2 - Withdrawal \n";
	cout << "\t3 - Consult \n";
}

short FetchChoice() 
{
	short choice;
	do {
		cout << "\nEnter your choice(1-3): ";
		cin >> choice;

		if (choice < 0 || choice > 3)
		{
			cout << "Incorrect Option entered. Please try again!";
		}
	} while (choice < 0 || choice > 3);
	return choice;
}

bool VerifyUserDetails(AccDetails custAccount) 
{
	bool VerifyAccDetails = false;
	if (!custAccount.AccNumber.empty() &&
		!custAccount.AccHolderName.empty() &&
		!custAccount.pin.empty())
		VerifyAccDetails = true;
	return VerifyAccDetails;
}

short AccRecords(AccDetails custAccounts[], char UserRecords[]) 
{
	bool isVerifySuccess = true;
	fstream myFile;
	string line;
	myFile.open(UserRecords, ios::in);
	short counter = 0, initCounter = 0, nbRecords = 0;
	AccDetails custAccout;
	while (!myFile.eof()) 
	{
		if (initCounter != counter) {
			isVerifySuccess = false;
			break;
		}
		counter++;
		getline(myFile, line);

		switch (initCounter) {
		case 0:
			custAccout.AccNumber = line;
			initCounter++;
			break;
		case 1:
			custAccout.AccHolderName = line;
			initCounter++;
			break;
		case 2:
			custAccout.pin = line;
			initCounter++;
			break;
		case 3:
			custAccout.AccBalance = stof(line);
			initCounter++;
			break;
		}

		if (initCounter % 4 == 0 && VerifyUserDetails(custAccout)) 
		{
			custAccounts[(counter / 4) - 1] = custAccout;
			custAccout.AccNumber = "";
			custAccout.AccHolderName = "";
			custAccout.pin = "";
			custAccout.AccBalance = 0;
			initCounter = 0;
		}
	}
	myFile.close();
	return counter / 4;
}

AccDetails VerifyClient(char UserRecords[], AccDetails custAccounts[], short nbRecords) 
{
	string AccNumber, pin, line;
	bool ValidAccNum = false, ValidPIN = false;
	AccDetails clientAcc;
	do {
		cout << "\n Enter your Account Number : ";
		getline(cin, AccNumber);
		for (short i = 0; i < nbRecords; i++) {
			if (custAccounts[i].AccNumber == AccNumber) {
				ValidAccNum = true;
				cout << "\n\t Welcome " << custAccounts[i].AccHolderName;
				do {
					cout << "\nEnter your pin : ";
					getline(cin, pin);
					if (pin == custAccounts[i].pin) {
						ValidPIN = true;
						clientAcc = custAccounts[i];
						break;
					}
				} while (!ValidPIN);
			}
		}
	} while (!ValidAccNum);
	return clientAcc;
}

void displayAccountInfo(AccDetails custAccount) 
{
	cout << "\n ACCOUNT INFORMATION";
	cout << "\n\tAccount Number : " << custAccount.AccNumber;
	cout << "\n\tClient : " << custAccount.AccHolderName;
	cout << "\n\tPIN : " << custAccount.pin;
	cout << "\n\tBalance $ : " << custAccount.AccBalance;
}

void loadAccount(AccDetails custAccounts[], char UserRecords[], short nbAccounts) 
{
	fstream myFile;
	string line;
	myFile.open(UserRecords, ios::out);
	for (short i = 0; i < nbAccounts; i++) {
		myFile << custAccounts[i].AccNumber << endl;
		myFile << custAccounts[i].AccHolderName << endl;
		myFile << custAccounts[i].pin << endl;
		myFile << custAccounts[i].AccBalance;
	}
	myFile.close();
}

void updateAcc(AccDetails custAccounts[], short nbAcc, AccDetails custAcc) 
{
	for (short i = 0; i < nbAcc; i++) {
		if (custAccounts[i].AccNumber == custAcc.AccNumber) 
		{
			custAccounts[i].AccBalance = custAcc.AccBalance;
		}
	}
}

AccDetails DepositMoney(AccDetails custAcc) 
{
	float depositamt;
	do {
		cout << " Enter an amount to deposit($2-$20,000) : ";
		cin >> depositamt;

		if (depositamt < 2 || depositamt > 20000)
		{
			cout << "\n Entered amount exceeds the account balance. Please try again!";
		}
	} while ((depositamt > 20000) || (depositamt < 2));
	custAcc.AccBalance += depositamt;
	return custAcc;
}

AccDetails withdraw(AccDetails custAcc) 
{
	int WithdrawAmt;
	do {
		cout << "\nPlease enter the amount you want to withdraw: $";
		cin >> WithdrawAmt;
		if (WithdrawAmt > custAcc.AccBalance)
		{
			cout << "\nError! The amount entered exceeds the amount present in the account. Please try again!";
		}

		else if (WithdrawAmt > 500)
		{
			cout << "\nError! The amount entered exceeds the maximum limit of $500. Please try again!";
		}

		else if (WithdrawAmt < 20)
		{
			cout << "\n Error! The amount entered must be greater than $20. Please try again!";
		}
		else if ((WithdrawAmt % 20) != 0)
		{
			cout << "\n Error! The amount entered must be multiples of 20. Please try again!";
		}
	} while (WithdrawAmt > custAcc.AccBalance || WithdrawAmt > 500 || WithdrawAmt < 20 || WithdrawAmt % 20 != 0);

	custAcc.AccBalance -= WithdrawAmt;
	return custAcc;
}