#include<iostream>
#include<string>
#include<vector>
#include<cctype>
#include<fstream>
#include<iomanip>
using namespace std;
const string FileName = "bank.txt";
enum enMainMenueOptions {
	eShowClientList = 1, eAddClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eExit = 6
};
struct sClientInfo {
	string AccountNumber;
	string PinCode;
	string Name;
	string PhoneNumber;
	double AccountBalance;
	bool ToDelete = false;
};
int ReadMainMenueOption() {
	
	int option;
	cout << "choose what u want to do ? [1 to 6]? "; cin >> option;
	return option;
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
void PrintClientInfo(sClientInfo client) {
	cout << "\nThe following record :\n\n";
	cout << "\nAccount Number :" << client.AccountNumber;
	cout << "\nPin Code       :" << client.PinCode;
	cout << "\nFull Name      :" << client.Name;
	cout << "\nPhone Number   :" << client.PhoneNumber;
	cout << "\nAccount Balance:" << client.AccountBalance;
}
sClientInfo ReadClient() {
	sClientInfo client;
	cout << "Enter Account Number "; getline(cin >> ws, client.AccountNumber);
	cout << "Enter Pin Code ";  getline(cin, client.PinCode);
	cout << "Enter Full Name ";  getline(cin, client.Name);
	cout << "Enter Phone Number ";  getline(cin, client.PhoneNumber);
	cout << "Enter Account Balance "; cin >> client.AccountBalance;
	cout << endl;
	return client;
}
void PrintClientRecord(sClientInfo client) {
	cout << "| " << left << setw(15) << client.AccountNumber;
	cout << "| " << left << setw(10) << client.PinCode;
	cout << "| " << left << setw(20) << client.Name;
	cout << "| " << left << setw(15) << client.PhoneNumber;
	cout << "| " << left << setw(15) << client.AccountBalance;
}
void PrintAllClients(vector<sClientInfo> vClients) {
	cout << "\n\t\t\t\tClient List (" << vClients.size() << ") Client(s).\n";
	cout << "------------------------------------------------------------";
	cout << "-------------------------------------------------\n\n";
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(20) << "Full Name";
	cout << "| " << left << setw(15) << "Phone Number";
	cout << "| " << left << setw(15) << "Accout Balance\n";
	cout << "------------------------------------------------------------";
	cout << "-------------------------------------------------\n\n";
	for (sClientInfo& client : vClients) {
		PrintClientRecord(client);
		cout << endl;
	}
	cout << "------------------------------------------------------------";
	cout << "-------------------------------------------------\n\n";

}
string CeateLine(sClientInfo client, string seperator = "#//#") {
	string ch = "";
	ch += client.AccountNumber + seperator;
	ch += client.PinCode + seperator;
	ch += client.Name + seperator;
	ch += client.PhoneNumber + seperator;
	ch += to_string(client.AccountBalance);
	return ch;
}
string ConvertRecordToLine(sClientInfo client) {
	string ch = CeateLine(client, "#//#");
	return ch;
}
void PutClientInFile(string FileName, string ch) {

	fstream file(FileName, ios::out | ios::app);  // Use append mode
	if (file.is_open()) {
		file << ch << endl;  // write line and newline
		file.close();
	}
}
string ReadAccountNumber() {
	string ch;
	cout << "please enter account number to search : "; cin >> ch;
	return ch;
}
bool FoundClientByAccountNumber(string AccNumber, vector<sClientInfo> vClients, sClientInfo& client) {
	for (sClientInfo& c : vClients) {
		if (c.AccountNumber == AccNumber) {
			client = c;
			return true;
		}
	}
	return false;
}
bool MarkClientToDelete(string AccNumber, vector<sClientInfo>& vClients) {
	for (sClientInfo& c : vClients) {
		if (c.AccountNumber == AccNumber) {
			c.ToDelete = true;
			return true;
		}
	}
	return false;
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
bool DeleteClientByAccountNumber(string AccNumber, vector<sClientInfo>& vClients) {
	sClientInfo client;
	char answer;
	if (FoundClientByAccountNumber(AccNumber, vClients, client)) {
		PrintClientInfo(client);
		cout << "\ndo u want to delete this client ? y/n? "; cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			MarkClientToDelete(AccNumber, vClients);
			SaveDataToFile(FileName, vClients);
			cout << "\ndeleted succesfuly\n";
			vClients = LoadClientsDataFromFile(FileName);
		}
		return true;
	}
	else {
		cout << "\nclient with acc number " << AccNumber << " not found!\n";
		return false;
	}
}
sClientInfo ReadClientInfo(string AccNumber) {
	sClientInfo client;
	client.AccountNumber = AccNumber;
	cout << "Enter Pin Code ";  getline(cin >> ws, client.PinCode);
	cout << "Enter Full Name ";  getline(cin, client.Name);
	cout << "Enter Phone Number ";  getline(cin, client.PhoneNumber);
	cout << "Enter Account Balance "; cin >> client.AccountBalance;
	cout << endl;
	return client;
}
bool SaveToVector(vector<sClientInfo>& vClients, sClientInfo client, string AccNumber) {
	for (sClientInfo& c : vClients) {
		if (c.AccountNumber == AccNumber) {
			c = client;
		}
	}
	return true;
}
bool UpdateClientByAccountNumber(string AccNumber, vector<sClientInfo>& vClients) {
	sClientInfo client;
	char answer;
	if (FoundClientByAccountNumber(AccNumber, vClients, client)) {
		PrintClientInfo(client);
		cout << "\ndo u want to update this client ? y/n? "; cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			client = ReadClientInfo(AccNumber);
			SaveToVector(vClients, client, AccNumber);
			SaveDataToFile(FileName, vClients);
			cout << "update succesfuly\n";
			vClients = LoadClientsDataFromFile(FileName);
		}
		return true;
	}
	else {
		cout << "client with acc number " << AccNumber << " not found!\n";
		return false;
	}
}
bool PrintResultOfSearch(string AccNumber, vector<sClientInfo>& vClients) {
	sClientInfo client;
	char answer;
	if (FoundClientByAccountNumber(AccNumber, vClients, client)) {
		PrintClientInfo(client);
		return true;
	}
	return false;
}


void ShowClientList() {
	vector<sClientInfo> vClients = LoadClientsDataFromFile(FileName);
	PrintAllClients(vClients);
}

void AddClientToList() {
	cout << "_____________________________" << endl;
	cout << "\tAdd client screen" << endl;
	cout << "_____________________________" << endl;
	sClientInfo client = ReadClient();
	string ch = ConvertRecordToLine(client);
	PutClientInFile(FileName,ch);
}

void DeleteClient() {
	cout << "_____________________________" << endl;
	cout << "\tDelete client screen" << endl;
	cout << "_____________________________" << endl;
	string AccNumber = ReadAccountNumber();
	vector<sClientInfo> vClients = LoadClientsDataFromFile(FileName);
	DeleteClientByAccountNumber(AccNumber, vClients);
}

void UpdateClient() {
	cout << "_____________________________" << endl;
	cout << "\tUpdate client screen" << endl;
	cout << "_____________________________" << endl;
	string AccNumber = ReadAccountNumber();
	vector<sClientInfo> vClients = LoadClientsDataFromFile(FileName);
	UpdateClientByAccountNumber(AccNumber, vClients);
}

void FindClient() {
	cout << "_____________________________" << endl;
	cout << "\tFind client screen" << endl;
	cout << "_____________________________" << endl;
	string AccNumber = ReadAccountNumber();
	vector<sClientInfo> vClients = LoadClientsDataFromFile(FileName);
	PrintResultOfSearch(AccNumber,vClients);
}

void ExitProgram() {
	cout << "-------------------------------------------\n\n";
	cout << "\t\tEnd Program\n\n";
	cout << "-------------------------------------------\n\n";
}

void BackToMenue() {
	cout << "\n\nPress any key to go back to Main Menue...";
	system("pause");
	
}

void PerfromMainMenueOption(enMainMenueOptions choice) {
	switch(choice){
	case eShowClientList:
		system("cls");
		ShowClientList();
		BackToMenue();
		break;
	case eAddClient:
		system("cls");
		AddClientToList();
		BackToMenue();
		break;
	case eDeleteClient:
		system("cls");
		DeleteClient();
		BackToMenue();
		break;
	case eUpdateClient:
		system("cls");
		UpdateClient();
		BackToMenue();
		break;
	case eFindClient:
		system("cls");
		FindClient();
		BackToMenue();
		break;
	case eExit:
		system("cls");
		ExitProgram();
		break;
	}
}

void ShowMainMenue() {
	while (true) {
		system("cls");
		cout << "================================================================================\n\n";
		cout << "\t\t\t\tMain Menue Screen\n\n";
		cout << "================================================================================\n\n";
		cout << "\t\t [1] Show Client List\n";
		cout << "\t\t [2] Add Client in List\n";
		cout << "\t\t [3] Delete Client From List\n";
		cout << "\t\t [4] Update Client in List\n";
		cout << "\t\t [5] Find Client in List\n";
		cout << "\t\t [6] Exit\n";
		cout << "=================================================================================\n\n";
		enMainMenueOptions choice = (enMainMenueOptions)ReadMainMenueOption();
		PerfromMainMenueOption(choice);
	}

}

int main() {
	ShowMainMenue();

	system("pause");
	return 0;
}