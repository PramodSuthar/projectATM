#include "Options.h"

int main() 
{
	char choice;
	char custRecords[] = "CustomerDetails.txt";
	AccDetails clientAcc, custAccounts[200];

	short numRecords = AccRecords(custAccounts, custRecords);
		clientAcc = VerifyClient(custRecords, custAccounts, numRecords);
		displayMenu();
		choice = FetchChoice();
		if (choice == 1)
		{
			clientAcc = DepositMoney(clientAcc);
			updateAcc(custAccounts, numRecords, clientAcc);
			loadAccount(custAccounts, custRecords, numRecords);
			AccRecords(custAccounts, custRecords);
			displayAccountInfo(clientAcc);
		}
		else if (choice == 2)
		{
			clientAcc = withdraw(clientAcc);
			updateAcc(custAccounts, numRecords, clientAcc);
			loadAccount(custAccounts, custRecords, numRecords);
			AccRecords(custAccounts, custRecords);
			displayAccountInfo(clientAcc);
		}
		else 
		{ 
		displayAccountInfo(clientAcc); 
		system("pause");
		}
		
		return 0;
}