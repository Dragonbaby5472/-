#include <iostream>
#include <string>
using namespace std;
bool land[7][7] = {false};
int solution[7] = { 0 };
int store[40][7] = { 0 };
int counts = 0;
int inputR;
int inputC;
string input;
bool repeated(int[], int[]);

int checkInput(string &str) {//check if input string is a integer and return that number
	for (char const &c : str) {
		if (!((int)c <= 54 && (int)c >= 48)) {
			printf("Input error, please enter again.\n");
			cin >> str;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return checkInput(str);
		}
	}
	return stoi(str);
}
bool check(int row,int column) {
	if (row == 0)
		return true;
	for (int i = row - 1; i >= 0; i--) {
		if (land[i][column])
			return false;
		if ((column - (row - i)) >= 0) {
			if (land[i][column - (row - i)]) {
				return false;
			}
		}
		if ((column + (row - i)) < 7) {
			if (land[i][column + (row - i)])
				return false;
		}
	}
	return true;
}
void compute(int row) {
	for (int i = 0; i < 7; i++) {
		if (check(row, i)) {
			if (row == 6) {
				solution[row] = i;
				for (int i = 0; i < counts; i++) {
					if (repeated(solution, store[i]))
						goto RETURN;
				}
				for (int i = 0; i < 7; i++) {
					cout << solution[i];
					store[counts][i] = solution[i];
				}
				cout << endl;
				counts++;
				
			RETURN:
				return;
			}
			land[row][i] = true;
			solution[row] = i;
			compute(row + 1);
			land[row][i] = false;
		}
	}
}
void computeAnswer(int row) {
	for (int i = 0; i < 7; i++) {
		if (check(row, i)) {
			if (row == 6) {
				solution[row] = i;
				land[row][i] = true;
				if (land[inputC][inputR]) {
					for (int i = 0; i < 7; i++) {
						cout << solution[i];
					}
					cout << endl;
				}
				land[row][i] = false;
				return;
			}
			land[row][i] = true;
			solution[row] = i;
			computeAnswer(row + 1);
			land[row][i] = false;
		}
	}
}
/**/
bool repeated(int check[], int ans[]) {
	int test[7] = { 0 };
	for (int i = 0; i < 7; i++) {
		if (check[6 - ans[i]] != i) //rotate -90
			test[0] ++;
		if (check[ans[i]] != (6 - i))//rotate 90
			test[1] ++;
		if ((check[i] + ans[6 - i]) != 6)//rotate 180
			test[2] ++;
		if (check[i] != ans[6-i])//symmetry
			test[3] ++;
		if (check[6 - ans[i]] != (6 - i))//rotate 90 and symmetry
			test[4] ++;
		if (check[ans[i]] != i) //rotate -90 and symmetry
			test[5] ++;
		if ((check[i] + ans[i]) != 6)//rotate 180 and symmetry
			test[6] ++;
	}
	for (int i = 0; i < 7; i++) {
		if (test[i] == 0)
			return true;
	}
	return false;
}

int main() {
	printf("Please enter (x,y) that the first dwarf stands.\n");
	printf("x >> ");
	cin >> input;
	inputR = checkInput(input);
	printf("y >> ");
	cin >> input;
	inputC = checkInput(input);
	computeAnswer(0);
	printf("Enter \"1\" to show all posibilities\n");
	printf("or enter \"0\" to exit.\n");
AGAIN:
	printf(">> ");
	cin >> input;
	if (checkInput(input) == 1) {
		compute(0);
		printf("There are %d solutions without symmetry operations!", counts);
		return 1;
	}
	else if (checkInput(input) == 0) {
		return 0;
	}
	else {
		printf("Input error! Please enter again\n");
		goto AGAIN;
	}
}
