#include <iostream>
using namespace std;
int main() {
	float inputNumber;
	cout << "Please enter an integer from 0 to 5.\n";
	do {
		cout << ">>>";
		cin >> inputNumber;
		if (inputNumber == 0) {
			cout << "------------------------------------------\n";
			cout << "|  Name:       Leo Tsai                  |\n";
			cout << "|  Student id: E24106288                 |\n";
			cout << "|  Cellphone:  0912345678                |\n";
			cout << "|  Hobby:      Writing HW                |\n";
			cout << "|  Email:      E24106288@gs.ncku.edu.tw  |\n";
			cout << "------------------------------------------\n";
		}
		else if (inputNumber == 1 || inputNumber == 2 || inputNumber == 3 || 
			     inputNumber == 4 || inputNumber == 5) {
			for (int i = 1; i <= inputNumber; i++) {
				cout << "*";
			}
		}
		else {
			cout << "Please enter an integer from 0 to 5.\n";
		}
	} while (inputNumber != 0 && inputNumber != 1 && inputNumber != 2 &&
		     inputNumber != 3 && inputNumber != 4 && inputNumber != 5);
	return 0;
}