#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;
void ShowATMMainMenue();
void Login();

const string FileName = "ClientsFile.txt";
enum enQuickWithdrawMenueOptions { e20=1,e50=2,e100=3,e200=4,e400=5,e600=6,e800=7,e1000=8,eExit=9 };
enum enATMMainMenueOptions { eQuickWithdraw=1,eNormalWithdraw=2,eDeposit=3,echeckBalance=4,eLogout=5};
struct sClientInfo {
    string AccountNumber;
    string PinCode;
    string Name;
    string PhoneNumber;
    double AccountBalance;
    bool ToDelete = false;
};
sClientInfo CurrentClient;
void BackToMainMenue() {
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowATMMainMenue();
}
double ReadAmountToDeposit() {
    double Amount;
    cout << "Enter Amount to Deposit : "; cin >> Amount;
    return Amount;
}
vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;

    short pos = 0;
    string sWord;


    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos);
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length());
    }

    if (S1 != "")
    {
        vString.push_back(S1);
    }

    return vString;
}
sClientInfo ConvertLineToRecord(string line) {
    vector<string> v = SplitString(line, "#//#");
    sClientInfo client;
    client.AccountNumber = v[0];
    client.PinCode = v[1];
    client.Name = v[2];
    client.PhoneNumber = v[3];
    client.AccountBalance = stod(v[4]);
    return client;
}
void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowATMMainMenue();
}

vector<sClientInfo> LoadClientsDataFromFile(string FileName) {
    vector<sClientInfo> vClients;
    fstream myFile;
    myFile.open(FileName, ios::in); //read mode
    if (myFile.is_open()) {
        string line;
        sClientInfo clients;
        while (getline(myFile, line)) {
            clients = ConvertLineToRecord(line);
            vClients.push_back(clients);
        }
    }
    myFile.close();
    return vClients;
}
bool FindClientByAccNumberAndPin(string AccountNumber, string PinCode, sClientInfo& Client) {
    vector<sClientInfo> vClients = LoadClientsDataFromFile(FileName);
    for (sClientInfo& c : vClients) {
        if (c.AccountNumber == AccountNumber && c.PinCode == PinCode) { 
            Client = c;
            return true;
        }
    }
    return false;
}
bool LoadClientInfo(string AccountNumber,string PinCode) {
    if (FindClientByAccNumberAndPin(AccountNumber, PinCode, CurrentClient)) return true;
    return false;
}
int ReadATMMainMenueOption() {
    int Option;
    cout << "Choose what do you want to do ? [1 to 5] : "; cin >> Option;
    return Option;
}int ReadQuickWithdrawMenueOption() {
    int Option;
    cout << "Choose what to Withdraw ? [1 to 9] : "; cin >> Option;
    return Option;
}
string CreateLine(sClientInfo client, string seperator = "#//#") {
    string ch = "";
    ch += client.AccountNumber + seperator;
    ch += client.PinCode + seperator;
    ch += client.Name + seperator;
    ch += client.PhoneNumber + seperator;
    ch += to_string(client.AccountBalance);
    return ch;
}
string ConvertRecordToLine(sClientInfo client) {
    string ch = CreateLine(client, "#//#");
    return ch;
}
bool SaveToVector(vector<sClientInfo>& vClients, sClientInfo client, string AccNumber) {
    for (sClientInfo& c : vClients) {
        if (c.AccountNumber == AccNumber) {
            c = client;
        }
    }
    return true;
}
bool SaveDataToFile(string FileName, vector<sClientInfo>& vClients) {
    fstream MyFile;
    string line;
    MyFile.open(FileName, ios::out);
    if (MyFile.is_open()) {
        for (sClientInfo& c : vClients) {
            if (c.ToDelete == false) {
                line = ConvertRecordToLine(c);
                MyFile << line << endl;
            }
        }
        return true;
    }
    return false;
}
void DepositAmount(string AccNumber, vector<sClientInfo> vClients) {
    
    char answer;
    double Amount = ReadAmountToDeposit();
    cout << "\nAre you sure to deposit ? y/n? "; cin >> answer;
    if (answer == 'y' || answer == 'Y') {
        CurrentClient.AccountBalance += Amount;
        SaveToVector(vClients, CurrentClient, AccNumber);
        SaveDataToFile(FileName, vClients);
        cout << "deposit succesfuly\n";
        vClients = LoadClientsDataFromFile(FileName);
    }
    
        
        
    
}
bool Withdraw(int Amount) {
    vector<sClientInfo> vClients = LoadClientsDataFromFile(FileName);
    
    if (Amount > CurrentClient.AccountBalance) {
        cout << "Cannot do this withdraw\n";
        return false;
    }
    else {
        char answer;
        cout << "\nAre you sure to Withdraw ? y/n? "; cin >> answer;
        if (answer == 'y' || answer == 'Y') {
            CurrentClient.AccountBalance -= Amount;
            SaveToVector(vClients, CurrentClient, CurrentClient.AccountNumber);
            SaveDataToFile(FileName, vClients);
            cout << "Withdraw succesfuly, Your Balance is : " << CurrentClient.AccountBalance << endl;
            vClients = LoadClientsDataFromFile(FileName);
        }
        return true;
    }
}
void PerfromQuickWithdrawMenueOption(enQuickWithdrawMenueOptions choice) {
    switch (choice) {
    case e20:
        Withdraw(20);
        BackToMainMenue();
        break;
    case e50:
        Withdraw(50);
        BackToMainMenue();
        break;
    case e100:
        Withdraw(100);
        BackToMainMenue();
        break;
    case e200:
        Withdraw(200);
        BackToMainMenue();
        break;
    case e400:
        Withdraw(400);
        BackToMainMenue();
        break;
    case e600:
        Withdraw(600);
        BackToMainMenue();
        break;
    case e800:
        Withdraw(800);
        BackToMainMenue();
        break;
    case e1000:
        Withdraw(1000);
        BackToMainMenue();
        break;
    case eExit:
        ShowATMMainMenue();
    }
}
void ShowQuickWithdrawMenue() {
    system("cls");

    cout << "===========================================\n";
    cout << "\t\tQuick Withdraw Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";

    cout << "Your Balance is " << CurrentClient.AccountBalance << endl;

    PerfromQuickWithdrawMenueOption((enQuickWithdrawMenueOptions)ReadQuickWithdrawMenueOption());

}
void QuickWithdraw() {

    ShowQuickWithdrawMenue();

}
void NormalWithdraw() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\Normal Withdraw Screen\n";
    cout << "===========================================\n";
    bool IsMultipleOfFive = false;
    int amount;
    do 
    {
        cout << "Enter an Amount multiple of 5's : "; cin >> amount;
        if (amount % 5 == 0) IsMultipleOfFive = true;
    } while (!IsMultipleOfFive);
    Withdraw(amount);
}
void Deposit() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\Deposit Screen\n";
    cout << "===========================================\n";
    vector<sClientInfo> vClients = LoadClientsDataFromFile(FileName);
    DepositAmount(CurrentClient.AccountNumber, vClients);
}
void CheckBalance() {
    system("cls");
    cout << "===========================================\n";
    cout << "\t\Deposit Screen\n";
    cout << "===========================================\n\n";
    cout << "Your Balance is : " << CurrentClient.AccountBalance << endl;
}
void PerfromATMMainMenueOption(enATMMainMenueOptions choice) {
    switch (choice) {

    case eQuickWithdraw:
        system("cls");
        QuickWithdraw();
        break;

    case eNormalWithdraw:
        system("cls");
        NormalWithdraw();
        GoBackToMainMenue();
        break;

    case eDeposit:
        system("cls");
        Deposit();
        GoBackToMainMenue();
        break;

    case echeckBalance:
        system("cls");
        CheckBalance();
        GoBackToMainMenue();
        break;

    case eLogout:
        Login();
    }
}
void ShowATMMainMenue() {

    system("cls");

    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";


    PerfromATMMainMenueOption((enATMMainMenueOptions)ReadATMMainMenueOption());
}
void Login()
{
    bool LoginFaild = false;

    string AccountNumber, Pin;
    do
    {
        system("cls");

        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";

        if (LoginFaild)
        {
            cout << "Invlaid AccountNumber/Pin!\n";
        }

        cout << "Enter Account Number ? ";
        cin >> AccountNumber;

        cout << "Enter Pin? ";
        cin >> Pin;

        LoginFaild = !LoadClientInfo(AccountNumber, Pin);

    } while (LoginFaild);

    ShowATMMainMenue();

}

int main()
{
   
	Login();

	system("pause");
	return 0;
}

