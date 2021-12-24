#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
int disk = 0;
int *towerA;	//to store data of disks in tower.
int *towerB;	//data in tower can help me to check input 
int *towerC;	//and show the tower in picture.
void moveByComputer(char towerA, char towerB, char towerC, int disk) { //to show the answer.
	if (disk == 1)
		cout << "Move disk " << disk << " from " << towerA << " to " << towerC << endl;
	else {
		moveByComputer(towerA, towerC, towerB, disk - 1);
		cout << "Move disk " << disk << " from " << towerA << " to " << towerC << endl;
		moveByComputer(towerB, towerA, towerC, disk - 1);
	}
}
/*By read data in towers, we can form a tower by output numbers of [].*/
void showTower() {	
	cout << "Tower A:" << endl;
	cout << endl;
	for (int i = 1; i <= disk; i++) {	//To make a tower by numbers of [].
		if(towerA[i - 1] > 0)
		cout << setw((disk) * 2 - (towerA[i - 1] - 1) * 2);
		for (int j = 1; j <= (2 * towerA[i - 1] - 1); j++) {
			cout << "[]";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Tower B:" << endl;
	cout << endl;
	for (int i = 1; i <= disk; i++) {
		if (towerB[i - 1] > 0)
		cout << setw((disk) * 2 - (towerB[i - 1] - 1) * 2);
		for (int j = 1; j <= (2 * towerB[i - 1] - 1); j++) {
			cout << "[]";
		}
		cout << endl;
	}
	cout << endl;
	cout << "Tower C:" << endl;
	cout << endl;
	for (int i = 1; i <= disk; i++) {
		if (towerC[i - 1] > 0)
		cout << setw((disk) * 2 - (towerC[i - 1] - 1) * 2);
		for (int j = 1; j <= (2 * towerC[i - 1] - 1); j++) {
			cout << "[]";
		}
		cout << endl;
	}
}
/*Method to control player playing this game.*/
void moveByPlayer() {
	towerA = new int[disk];	//Decide how many data to store.
	towerB = new int[disk];
	towerC = new int[disk];
	string inputA, inputB;	//to store input string.
	int temp;
	/*initialize the tower array*/
	for (int i = 1; i <= disk; i++) {
		towerA[i - 1] = i;
	}
	for (int i = 1; i <= disk; i++) {
		towerB[i - 1] = 0;
	}
	for (int i = 1; i <= disk; i++) {
		towerC[i - 1] = 0;
	}
	do {	//loop for player to do.
		showTower();
	INPUTA:
		cout << "Which tower's disk do you want to move?\n";
		cout << "Enter A, B or C." << endl;
		cin >> inputA;
		if (inputA != "A" && inputA != "B" && inputA != "C") {	//Check input
			printf("Input error! Please enter again:\n");
			goto INPUTA;
		}
	INPUTB:
		cout << "which tower  do you want to put?\n";
		cout << "Enter A, B or C." << endl;
		cin >> inputB;
		if (inputB != "A" && inputB != "B" && inputB != "C" ) {	//Check input
			printf("Input error! Please enter again:\n");
			goto INPUTB;
		}
		if (inputB == inputA) {
			printf("Input error! Please enter again:\n");
			goto INPUTB;
		}
		if (inputA == "A") {
			if (inputB == "B" && towerA[0] >= towerB[0] && towerB[0] != 0) {
				printf("Input error! Please enter again:\n");
				goto INPUTA;
			}
			else if (inputB == "C" && towerA[0] >= towerC[0] && towerC[0] != 0) {
				printf("Input error! Please enter again:\n");
				goto INPUTA;
			}
		}
		else if (inputA == "B") {
			if (inputB == "A" && towerB[0] >= towerA[0] && towerA[0] != 0) {
				printf("Input error! Please enter again:\n");
				goto INPUTA;
			}
			else if (inputB == "C" && towerB[0] >= towerC[0] && towerC[0] != 0) {
				printf("Input error! Please enter again:\n");
				goto INPUTA;
			}
		}if (inputA == "C") {
			if (inputB == "B" && towerC[0] >= towerB[0] && towerB[0] != 0) {
				printf("Input error! Please enter again:\n");
				goto INPUTA;
			}
			else if (inputB == "A" && towerC[0] >= towerA[0] && towerA[0] != 0) {
				printf("Input error! Please enter again:\n");
				goto INPUTA;
			}
		}
		/*Start to change data to what player want.*/
		if (inputA == "A") {
			temp = towerA[0];
			for (int i = 0; i < disk - 1; i++) {
				towerA[i] = towerA[i + 1];
			}
			towerA[disk-1] = 0;
		}
		else if (inputA == "B") {
			temp = towerB[0];
			for (int i = 0; i < disk - 1; i++) {
				towerB[i] = towerB[i + 1];
			}
			towerB[disk-1] = 0;
		}
		else if (inputA == "C") {
			temp = towerC[0];
			for (int i = 0; i < disk - 1; i++) {
				towerC[i] = towerC[i + 1];
			}
			towerC[disk-1] = 0;
		}
		if (inputB == "A") {
			for (int i = 2; i <= disk; i++) {
				towerA[disk - i + 1] = towerA[disk - i];
			}
			towerA[0] = temp;
		}
		else if (inputB == "B") {
			for (int i = 2; i <= disk; i++) {
				towerB[disk - i + 1] = towerB[disk - i];
			}
			towerB[0] = temp;
		}
		else if (inputB == "C") {
			for (int i = 2; i <= disk; i++) {
				towerC[disk - i + 1] = towerC[disk - i];
			}
			towerC[0] = temp;
		}
		else {
			printf("Input error! Please enter again:(\n");
			goto INPUTA;
		}
		cout << "Move disk " << temp << " from tower " << inputA << " to " << inputB << endl;
	} while (towerC[disk - 1] != disk);
	showTower();
	cout << "WIN!!";
	delete[] towerC;	//delete array
	delete[] towerB;
	delete[] towerA;
} 
 /*Check input*/
bool checkinput(string str, int &i) {
	for (char &c : str) {
		if (isdigit(c) == 0) {
			printf("Input error! Please enter again:\n");
			return false;
		}
	}
	i = stoi(str);
	return true;
}
int main() {
	cout << "Please enter number of disks:" << endl;
	string diskstr;
	do {
		cin >> diskstr;
	} while (checkinput(diskstr, disk) == false);
CHOOSE:
	cout << "Enter \"play\" if you want to play by yourself,\n";
	cout << "or enter \"answer\" to show the step." << endl;
	string choose;
	cin >> choose;
	if (choose == "answer") {
		moveByComputer('A', 'B', 'C', disk);
	}
	else if (choose == "play") {
		moveByPlayer();
	}
	else {
		cout << "Input error! Please enter again : " << endl;
		goto CHOOSE;
	}
	return 0;
}