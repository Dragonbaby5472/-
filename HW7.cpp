#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
using namespace std;
int column = 0;
int row = 0;
int choose = 0;
int **matrix;
string check;
int max[5];
/*
max[0] = max value
max[1] = initial column
max[2] = last column
max[3] = initial row
max[4] = last row
*/
int sum = 0;
int checkInputPositive(string &str) {	//check if input string is a positive integer and return that number
	for (char const &c : str) {
		if (!((int) c <= 57 && (int) c >= 48)) {
			printf("Input error, please enter again.\n");
			cin >> str;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return checkInputPositive(str);
		}	
	}
	return stoi(str);
}
int checkInput(string &str) {//check if input string is a integer and return that number
	for (char const &c : str) {
		if (!((int)c <= 57 && (int)c >= 48 || (int)c == 45)) {
			printf("Input error, please enter again.\n");
			cin >> str;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return checkInput(str);
		}
	}
	return stoi(str);
}
void autoInput() {	//input automatically
	srand((unsigned)time(NULL));
	for (int i = 0; i < column; i++) {
		for (int j = 0; j < row; j++) {
			matrix[i][j] = rand() % 199 - 99;
		}
	}
	return;
}
void artificialInput() {	//control user input for matrix
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < column; j++) {
			cout << "Input number for column " << j + 1 << " row " << i + 1 << "(only integer available)" << endl;
			cin >> check;
			matrix[j][i] = checkInput(check);
		}
	}
}
void showMatrix(int columeInit, int rowInit, int columnEnd, int rowEnd) {	//show matrix or sub-matrix
	for (int i = rowInit - 1; i < rowEnd; i++) {
		for (int j = columeInit - 1; j < columnEnd; j++) {
			cout << setw(5) << matrix[j][i] << " ";
		}
		cout << "\n" << endl;
	}
}
int main() {
	printf("Please Enter numbers of columns\n");
	cin >> check;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	column = checkInputPositive(check);
	printf("Please Enter numbers of rows\n");
	cin >> check;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	row = checkInputPositive(check);
	matrix = new int*[column];
	for (int i = 0; i < column; i++) {
		matrix[i] = new int[row];
	}
	printf("Please enter \"1\" to enter numbers by yourself,\n");
	printf("or enter \"2\" to enter numbers automatically\n");
CHOOSE:
	cin >> check;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	choose = checkInputPositive(check);
	if (choose == 1) {
		artificialInput();
	}
	else if(choose == 2)
	{
		autoInput();
	} 
	else{
		printf("Input Error, please enter again.\n");
		goto CHOOSE;
	}
	showMatrix(1, 1, column, row);
	for (int i = 1; i <= column; i++) {	//take i column
		for (int j = 1; j <= row; j++) {	//take j row
			for (int k = 0; k <= column - i; k++) {	//initial column
				for (int l = 0; l <= row - j; l++) {	//initial row
					sum = 0;
					for (int m = 0; m < i; m++) {	//sum
						for (int n = 0; n < j; n++) {
							sum += matrix[k + m][l + n];
						}
					}
					if (sum > max[0]) {
						max[0] = sum;
						max[1] = k + 1;
						max[2] = k + i;
						max[3] = l + 1;
						max[4] = l + j;
					}
				}
			}
		}
	}
	cout << "The maximum sum is " << max[0] << endl;
	cout << "Sub-matrix:\n";
	showMatrix(max[1], max[3], max[2], max[4]);
	for (int i = 0; i < column; i++)
		delete[] matrix[i];
	delete matrix;
 }