#pragma once
#include<iomanip>
#include"clsScreen.h"
#include"clsBankClient.h"

class clsClientListScreen:protected clsScreen
{
private:
	void static PrintClientRecordLine(clsBankClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber();
    cout << "| " << setw(35) << left << Client.FullName();
    cout << "| " << setw(10) << left << Client.Phone;
    cout << "| " << setw(17) << left << Client.Email;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(10) << left << Client.AccountBalance;

}
public:
    static void ShowClientsList()
    {
        if (!CheckAccessRights(clsUser::enPermissions::pListClients)) return;
        vector <clsBankClient> vClients = clsBankClient::GetClientsList();
        string Title = "\t Client List Screen";
        string SubTitle = "\t (" + to_string(vClients.size()) + ") Client(s).";
        _DrawScreenHeader(Title, SubTitle);

        

        cout << "\n\t\t\t\t";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(35) << "Client Name";
        cout << "| " << left << setw(10) << "Phone";
        cout << "| " << left << setw(17) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(10) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else

            for (clsBankClient Client : vClients)
            {

                PrintClientRecordLine(Client);
                cout << endl;
            }

        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

    }

};

