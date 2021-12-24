#include <time.h>
#include <iostream>
#include <string>
#include <stdlib.h>
using namespace std;
int numbers[4];	//Numbers for player to guess.
int guessNumbers[4];
int a = 0;	//aAbB
int b = 0;
int times = 0;	//Count how many times do play guess.
int keepgoing = 0;	//To ckeck whether play wants to keep playing.
/*Method to make random number.*/
void randomNumber();
void keepplaying();
void enterNumber();
bool compare();
/*Main*/
int main() {
	randomNumber();
	printf("Please enter four digits number.\nNumbers cannot be 0\n");
	enterNumber();
	while (compare() == false) {
		if (times == 4) {	//Keep player from guessing too many times.
			printf("Guess too many times.\n");
			printf("The answer is ");
			for (int i = 0; i < 4; i++) {
				printf("%d", numbers[i]);
			}
			printf(". ");
			keepplaying();
			exit(0);
			for (int i = 0; i < 4; i++) {
				printf("%d", numbers[i]);
			}
			return 0;
		}
		times += 1;
		printf("%dA%dB, guess again .\n", a, b);
		a = 0;
		b = 0;
		enterNumber();
	}
	cout << "you win!\n";
	keepplaying();
	return 0;
}
/*Make random numbers.*/
void randomNumber() {
	srand((unsigned)time(NULL));	//Seed
	for (int i = 0; i < 4; i++) {
		numbers[i] = rand() % 9 + 1;
		for (int j = 0; j < i; j++) {	//If repeated, give another random number for number[i].
			if (numbers[j] == numbers[i]) {
				i--;
			}
		}
	}
}
/*Ask player whether they want to keep playing.*/
void keepplaying() {
	cout << "Do you want to continue?\nIf so, enter 1. Or enter any number to end the game.\n";
	cin >> keepgoing;
	if (keepgoing == 1) {
		a = 0;	
		b = 0;
		times = 0;
		keepgoing = 0;
		main();
	}
}
/*Use a stupid way to store what player guess into "guessNumber".*/
void enterNumber() {
	string str;
	int p;
	cin >> str;
	for (char &c : str) {
		if (isdigit(c) == 0) {
			printf("Input error!Please enter four digits number:\n");
			enterNumber();
			return;
		}
	}
	p = stoi(str);
	if (p <= 999 || p >= 10000) {
		printf("Input error!Please enter four digits number:\n");
		enterNumber();
		return;
	}
	for (int i = 0; i < 4; i++) {
		guessNumbers[3 - i] = p % 10;
		p /= 10;
	}
	for (int i = 0; i < 4; i++) {
		if (guessNumbers[i] == 0) {
			printf("Input error!Please enter four digits number:\n");
			enterNumber();
			return;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < i; j++) {
			if (guessNumbers[i] == guessNumbers[j]) {
				printf("Input error!Please enter four digits number:\n");
				enterNumber();
				return;
			}
		}
	}
}
/*compare input and answer.*/
bool compare() {	
	for (int i = 0; i < 4; i++) {
		if (guessNumbers[i] == numbers[i])
			a++;
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (guessNumbers[j] == numbers[i])
				b++;
		}
	}
	b -= a;	//b need to deduct condition same as a; 
	if (a == 4)
		return true;
	return false;
}