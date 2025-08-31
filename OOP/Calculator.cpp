
#include <iostream>
using namespace std;

class clsCalculator {
private:
	string _LastOperation="Clear";
	float _LastNumber=0;
	float _Result = 0;
	float _PreviousResult = 0;

	bool _IsZero(float Number) {
		return Number == 0;
	}

public:
	
	void Clear() {
		_LastOperation = "Clear";
		_LastNumber = 0;
		_Result = 0;
	}
	void Add(float Number) {
		_LastOperation = "Adding";
		_PreviousResult = _Result;
		_LastNumber = Number;
		_Result += Number;

		
	}
	void Subtract(float Number) {
		_LastOperation = "Subtracting";
		_PreviousResult = _Result;
		_LastNumber = Number;
		_Result -= Number;

	}
	void Divide(float Number) {
		_LastNumber = Number;
		if (_IsZero(Number)) {
			Number = 1;
		}
		_LastOperation = "Dividing";
		_PreviousResult = _Result;
		
		_Result /= Number;
	}
	void Multiply(float Number) {
		_LastOperation = "Multiplying";
		_PreviousResult = _Result;
		_LastNumber = Number;
		_Result *= Number;
	}
	float GetFinalResult() {
		return _Result;
	}
	void PrintResult() {
		cout << "Result After " << _LastOperation << " " << _LastNumber << " is : " << _Result << endl;
	}
	void CancelLastOperation() {
		_Result = _PreviousResult;
		_LastOperation = "Cancelling Last Operation";
		_LastNumber = 0;
	}
};

int main()
{
	clsCalculator Calculator1;
	Calculator1.Clear();
	Calculator1.Add(10);
	Calculator1.PrintResult();
	Calculator1.Subtract(2);
	Calculator1.PrintResult();
	Calculator1.Divide(3);
	Calculator1.PrintResult();
	Calculator1.Multiply(4);
	Calculator1.PrintResult();
	
	Calculator1.CancelLastOperation();
	Calculator1.PrintResult();

}