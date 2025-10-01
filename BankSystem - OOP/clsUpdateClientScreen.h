#pragma once
#include"clsScreen.h"
#include"clsInputValidate.h"
#include"clsBankClient.h"
class clsUpdateClientScreen:protected clsScreen
{

private:
	static void _Print(clsBankClient Client)
	{
		cout << "\nClient Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << Client.FirstName;
		cout << "\nLastName    : " << Client.LastName;
		cout << "\nFull Name   : " << Client.FullName();
		cout << "\nEmail       : " << Client.Email;
		cout << "\nPhone       : " << Client.Phone;
		cout << "\nAcc. Number : " << Client.AccountNumber();
		cout << "\nPassword    : " << Client.PinCode;
		cout << "\nBalance     : " << Client.AccountBalance;
		cout << "\n___________________\n";

	}
	static void ReadClientInfo(clsBankClient& Client)
	{
	    cout << "\nEnter FirstName: ";
	    Client.FirstName = clsInputValidate::ReadString();
	
	    cout << "\nEnter LastName: ";
	    Client.LastName = clsInputValidate::ReadString();
	
	    cout << "\nEnter Email: ";
	    Client.Email = clsInputValidate::ReadString();
	
	    cout << "\nEnter Phone: ";
	    Client.Phone = clsInputValidate::ReadString();
	
	    cout << "\nEnter PinCode: ";
	    Client.PinCode = clsInputValidate::ReadString();
	
	    cout << "\nEnter Account Balance: ";
	    Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}
public:
	static void ShowUpdateClientScreen()
	{
		if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients)) return;
	    string AccountNumber = "";
	
	    cout << "\nPlease Enter client Account Number: ";
	    AccountNumber = clsInputValidate::ReadString();
	
	    while (!clsBankClient::IsClientExist(AccountNumber))
	    {
	        cout << "\nAccount number is not found, choose another one: ";
	        AccountNumber = clsInputValidate::ReadString();
	    }
	
	    clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		_Print(Client1);
	
	    cout << "\n\nUpdate Client Info:";
	    cout << "\n____________________\n";
	
	
	    ReadClientInfo(Client1);
	
	    clsBankClient::enSaveResults SaveResult;
	
	    SaveResult = Client1.Save();
	
	    switch (SaveResult)
	    {
	    case  clsBankClient::enSaveResults::svSucceeded:
	    {
	        cout << "\nAccount Updated Successfully :-)\n";
			_Print(Client1);
	        break;
	    }
	    case clsBankClient::enSaveResults::svFaildEmptyObject:
	    {
	        cout << "\nError account was not saved because it's Empty";
	        break;
	
	    }
	
	    }
	}
	

};

