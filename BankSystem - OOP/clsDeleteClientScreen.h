#pragma once
#include"clsBankClient.h"
#include"clsInputValidate.h"

#include"clsScreen.h"

class clsDeleteClientScreen:protected clsScreen
{
private:
    static void _Print(clsBankClient Client) {
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
public :
	static void ShowDeleteClientScreen()
{
        if (!CheckAccessRights(clsUser::enPermissions::pDeleteClient)) return;
    string AccountNumber = "";

    cout << "\nPlease Enter Account Number: ";
    AccountNumber = clsInputValidate::ReadString();
    while (!clsBankClient::IsClientExist(AccountNumber))
    {
        cout << "\nAccount number is not found, choose another one: ";
        AccountNumber = clsInputValidate::ReadString();
    }

    clsBankClient Client1 = clsBankClient::Find(AccountNumber);
    _Print(Client1);

    cout << "\nAre you sure you want to delete this client y/n? ";

    char Answer = 'n';
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {


        if (Client1.Delete())
        {
            cout << "\nClient Deleted Successfully :-)\n";

            _Print(Client1);
        }
        else
        {
            cout << "\nError Client Was not Deleted\n";
        }
    }
}

};

