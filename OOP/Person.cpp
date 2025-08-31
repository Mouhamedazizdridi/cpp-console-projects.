
#include <iostream>
using namespace std;

class clsPerson {
private:
	int _ID;
	string _FirstName, _LastName,_FullName, _Email, _Phone;

	string GetFullName() {
		return _FirstName + " " + _LastName;
	}
public:
	clsPerson(int ID, string FirstName, string LastName, string Email, string Phone) {
		_ID = ID;
		_FirstName = FirstName;
		_LastName = LastName;
		_FullName = GetFullName();
		_Email = Email;
		_Phone = Phone;
	}
	//Set Functions
	void SetFirstName(string FirstName) {
		_FirstName = FirstName;
	}
	void SetLastName(string LastName) {
		_LastName = LastName;
	}
	void SetEmail(string Email) {
		_Email = Email;
	}
	void SetPhone(string Phone) {
		_Phone = Phone;
	}

	//Get Functions
	int ID() {
		return _ID;
	}
	string FirstName() {
		return _FirstName;
	}
	string LastName() {
		return _LastName;
	}
	string FullName() {
		return _FullName;
	}
	string Email() {
		return _Email;
	}
	string Phone() {
		return _Phone;
	}
	 
	void Print() {
		cout << "Info :\n\n";
		cout << "_______________________\n";
		cout << "ID        :" << _ID << endl;
		cout << "First Name:" << _FirstName << endl;
		cout << "Last Name :" << _LastName << endl;
		cout << "Full Name :" << _FullName << endl;
		cout << "Email     :" << _Email << endl;
		cout << "Phone     :" << _Phone << endl;
		cout << "_______________________\n\n";
	}
	void SendEmail(string Subject, string Body) {
		cout << "\nThe Following Message is sent successfuly to Email " << _Email << endl;
		cout << "Subject : " << Subject << endl;
		cout << "Body    : " << Body << endl;
	}
	void SendSMS(string Subject) {
		cout << "\nSMS sent successfuly to Phone : " << _Phone << endl;
		cout << Subject << endl;
	}
};

int main()
{
	
	clsPerson Person1 (77,"Mouhamed Aziz","Dridi","My@gmail.fr","77889955");
	Person1.Print();

	Person1.SendEmail("Hi", "Are u fine ?");
	Person1.SendSMS("Are u Fine My Bro ?");
}