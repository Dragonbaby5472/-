#include <iostream>
#include <string>
using namespace std;
//method to check if n is a number.
bool checkNumber(const string& str)
{
	for (char const &c : str) {
		if (isdigit(c) == 0)
			return false;
	}
	return true;
}
//Check input string.
string isNumber(string str) {
	while (checkNumber(str) == false) {
		cout << "Not a number or an integer. Please enter a positive integer or 0.(smaller than 186)\n";
		cout << ">>>";
		cin >> str;
	}
	return str;
}
//check if n is too big.
int isSmall(int a) {
	while (a > 186) {
		string n;
		cout << "It is too big. Please enter a positive integer or 0.(smaller than 186)\n";
		cout << ">>>";
		cin >> n;
		isNumber(n);
		a = stoi(n);
	}
	return a;
}
int main() {
	string n;
	cout << "Please enter a positive integer or 0.(smaller than 186)\n";
	cout << ">>>";
	cin >> n;
	n = isNumber(n);
	int times = stoi(n);
	times = isSmall(times);
	float *fibonacci = new float[times + 1];//Giving an array to store fibonacci numbers.
											//use float because int isn't enough.
	for (int i = 0; i <= times; i++) {
		if (i == 0) {	//Remember to use == not =.
			fibonacci[i] = 0;
		}
		else if (i == 1) {	//Remember to use == not =.
			fibonacci[i] = 1;
		}
		else {
			fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];
		}
	}
	for (int i = 0; i <= times; i++) {	//cout all the fibonacci numbers.
		cout << "F" << i << " = " << fibonacci[i] << "\n";
	}
	return 0;
}