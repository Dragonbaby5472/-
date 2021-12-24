#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include <map>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <limits>
using namespace std;
double min_supp, min_conf;
struct Item
{
	string nameOfItem;//name of the item
	unordered_set<int> numOfData;// number of the data that the item has appear
};
map<string, Item> inputData;//map for all input data <name of the item, Item>
int dataNumber = 0;//number of data
map<string, Item> leftData;//map for data that support rate is bigger than min_sup

double checkInput(string &str) {//check if input string is a integer and return that number
	for (char const &c : str) {
		if (!((int)c <= 57 && (int)c >= 48 || (int)c == 46)) {
			printf("Input error, please enter again.\n");
			cin >> str;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return checkInput(str);
		}
	}
	return stod(str);
}
/* method for split the string and store it to the map*/
void splitString(const string splitStr) {
	stringstream ss;
	string tempStr;
	Item it;
	unordered_set<int> tempSet;
	ss << splitStr;
	dataNumber++;
	while (getline(ss, tempStr, ',')) {
		if (!inputData.count(tempStr)) {
			tempSet.insert(dataNumber);
			it = { tempStr,tempSet };
			inputData.insert(pair<string, Item>(tempStr, it));
		}
		else {
			inputData[tempStr].numOfData.insert(dataNumber);
		}
	}
	return;
}
/*method for inputfile to input data*/
void fileInclude(ifstream &fileIn) {
	
	string dataStr;
	for (int i = 1; fileIn >> dataStr; i++) {
		if ((i % 2) != 0) {
		}
		else {
			splitString(dataStr);
		}
	}
}
/*function to compute support rate*/
double supportRate(unordered_set<string> data_one, unordered_set<string> data_two) {
	bool bool_round = true;
	int supRate = 0;
	for (int i = 1; i <= dataNumber; i++) {
		for (const auto &s : data_one) {
			if (!inputData[s].numOfData.count(i)) {
				bool_round = false;
				goto NEXTROUND;
			}
		}
		for (const auto &t : data_two) {
			if (!inputData[t].numOfData.count(i)) {
				bool_round = false;
				goto NEXTROUND;
			}
		}
	NEXTROUND:
		if (bool_round)
			supRate++;
		bool_round = true;
	}
	return (double)supRate / (double)dataNumber;
}
/*function to compute confident rate of data_from => data_to*/
double confidentRate(unordered_set<string> data_from, unordered_set<string> data_to) {
	bool bool_from, bool_to;
	int conDemo = 0, conNumb = 0;
	for (int i = 1; i <= dataNumber; i++) {
		bool_from = true;
		bool_to = true;
		for (const auto &s : data_from) {
			if (!inputData[s].numOfData.count(i)) {
				bool_from = false;
				break;
			}
		}
		for (const auto &s : data_to) {
			if (!inputData[s].numOfData.count(i)) {
				bool_to = false;
				break;
			}
		}
		if (bool_from && bool_to) {
			conNumb++;
			conDemo++;
		}
		else if (bool_from && !bool_to) {
			conDemo++;
		}
	}
	return (double)conNumb / (double)conDemo;
}
bool findSet(vector<unordered_set<string>> vc, unordered_set<string> k) {
	vector<unordered_set<string>>::iterator it = find(vc.begin(), vc.end(), k);
	if (it != vc.end())
		return true;
	else
		return false;
}
bool findPair(vector<pair<unordered_set<string>, unordered_set<string>>> vc, pair<unordered_set<string>, unordered_set<string>> k) {
	vector<pair<unordered_set<string>, unordered_set<string>>>::iterator it = find(vc.begin(), vc.end(), k);
	if (it != vc.end())
		return true;
	else
		return false;
}
int main() {
	ifstream fileIn("Dataset.txt", ios::in);
	if (!fileIn) {
		cerr << "File \"Dataset.txt\" cound not be opened." << endl;
		exit(1);
	}
	ofstream fileOut("Dataset_Output.txt", ios::out);
	if (!fileOut) {
		cerr << "File \"Dataset_Output.txt\" cound not be opened." << endl;
		exit(2);
	}
	fileInclude(fileIn);
	bool cinin = true;
	string checkStr;
	while (cinin) {
		printf("Please enter the \"min support\".\n");
		cin >> checkStr;
		min_supp = checkInput(checkStr);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		printf("Please enter the \"min confidence\".\n");
		cin >> checkStr;
		min_conf = checkInput(checkStr);
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (min_supp <= 0 || min_supp > 1 || min_conf <= 0 || min_conf > 1) {
			printf("Input range Error!\n");
			cinin = true;
		}
		else {
			cinin = false;
		}
	}
	/*count every item's sup_rate and leave that is bigger than min_sup*/
	for (const auto &s : inputData) {
		double sup = (double)s.second.numOfData.size() / (double)dataNumber;
		if (sup >= min_supp) {
			leftData.insert(s);
		}
	}
	/*map to store result of rules
	  <NO., [0:from, 1:to][from_data or to_data]>*/
	vector<vector<unordered_set<string>>> outputData;
	vector<unordered_set<string>> tempVector;
	unordered_set<string> tempSet_sup;
	unordered_set<string> data_A, data_B;
	vector<unordered_set<string>> passed_set;

	/*count ONE-TO-ONE situation*/
	for (const auto &s : leftData) {
		data_A.insert(s.first);
		for (const auto &t : leftData) {
			if (s.first == t.first){ //to avoid repeat
				break;
			}
			data_B.insert(t.first);
			if (supportRate(data_A, data_B) >= min_supp) {  //s => t
				tempSet_sup = data_A;
				for (const auto &u : data_B) {
					tempSet_sup.insert(u);
				}
				if (!findSet(passed_set, tempSet_sup)) {
					passed_set.push_back(tempSet_sup);
				}
				tempSet_sup.clear();
				if (confidentRate(data_A, data_B) >= min_conf) {
					tempVector.push_back(data_A);
					tempVector.push_back(data_B);
					outputData.push_back(tempVector);
					tempVector.clear();
				}
				if (confidentRate(data_B, data_A) >= min_conf) { //t => s
					tempVector.push_back(data_B);
					tempVector.push_back(data_A);
					outputData.push_back(tempVector);
					tempVector.clear();
				}
			}
			data_B.clear();
		}
		data_A.clear();
	}
	bool continueOrNot = true; //to decided continue or not
	/*size_back: number of data now*/
	/*size_from: number of data before*/
	int size_back = passed_set.size(), size_front = 0, size_temp;
	vector<unordered_set<string>> tempSet_from;
	vector<unordered_set<string>> tempSet_to;
	vector<unordered_set<string>> tempSet_set;
	unordered_map<int, vector<pair<unordered_set<string>, unordered_set<string>>>> mapOfSetPair;
	while (continueOrNot) {
		//bool checkRepeated1 = false;//to check if data_A will repeat next times
		//bool checkRepeated2 = false;//to check if data_B will repeat next times
		/*ONE-TO-N*/
		for (int i = size_back - 1; i >= size_front; i--) {
			/*insert data into unorder_set*/
			data_A = passed_set[i];
			/*check if data_A is used*/
			for (const auto &t : leftData) {
				/*Check if item that will be put in data_B is repeated in the set data_a*/
				if (data_A.count(t.first)) {
					goto NEXT_A;
				}
				data_B.insert(t.first);
				if (mapOfSetPair.count(data_A.size() + data_B.size())) {
					if (findPair(mapOfSetPair.at(data_A.size() + data_B.size()), pair<unordered_set<string>, unordered_set<string>>(data_A, data_B))) {
						goto NEXT_A;
					}
					if (findPair(mapOfSetPair.at(data_A.size() + data_B.size()), pair<unordered_set<string>, unordered_set<string>>(data_B, data_A))) {
						goto NEXT_A;
					}
				}
				if (supportRate(data_A, data_B) >= min_supp) {
					tempSet_sup = data_A;
					for (const auto &u : data_B) {
						tempSet_sup.insert(u);
					}
					if (!findSet(passed_set, tempSet_sup)) {
						passed_set.push_back(tempSet_sup);
					}
					tempSet_sup.clear();
					if (confidentRate(data_A, data_B) >= min_conf) {
						tempVector.push_back(data_A);
						tempVector.push_back(data_B);
						outputData.push_back(tempVector);
						tempVector.clear();
						if (mapOfSetPair.count(data_A.size() + data_B.size())) {
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_A, data_B));
						}
						else {
							mapOfSetPair.insert({ data_A.size() + data_B.size() ,vector < pair<unordered_set<string>, unordered_set<string>>>() });
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_A, data_B));
						}
					}
					if (confidentRate(data_B, data_A) >= min_conf) {
						tempVector.push_back(data_B);
						tempVector.push_back(data_A);
						outputData.push_back(tempVector);
						tempVector.clear();
						if (mapOfSetPair.count(data_A.size() + data_B.size())) {
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_B, data_A));
						}
						else {
							mapOfSetPair.insert({ data_A.size() + data_B.size() ,vector < pair<unordered_set<string>, unordered_set<string>>>() });
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_B, data_A));
						}
					}
				}
			NEXT_A:
				data_B.clear();
			}
			data_A.clear();
		}
		tempSet_from.clear();
		/*N-TO-N*/
		//checkRepeated1 = false;
		for (int i = size_back - 1; i >= size_front; i--) {
			data_A = passed_set[i];
			for (int s = size_front - 1; s >= 0; s--) {
				for (const auto &dataSet : passed_set[s]) {
					if (data_A.count(dataSet)) 
						goto NEXT_C;
					data_B.insert(dataSet);
				}
				if (mapOfSetPair.count(data_A.size() + data_B.size())) {
					if (findPair(mapOfSetPair.at(data_A.size() + data_B.size()), pair<unordered_set<string>, unordered_set<string>>(data_A, data_B))) {
						goto NEXT_C;
					}
					if (findPair(mapOfSetPair.at(data_A.size() + data_B.size()), pair<unordered_set<string>, unordered_set<string>>(data_B, data_A))) {
						goto NEXT_C;
					}
				}
				if (supportRate(data_A, data_B) >= min_supp) {
					tempSet_sup = data_A;
					for (const auto &u : data_B) {
						tempSet_sup.insert(u);
					}
					if (!findSet(passed_set, tempSet_sup)) {
						passed_set.push_back(tempSet_sup);
					}
					tempSet_sup.clear();
					if (confidentRate(data_A, data_B) >= min_conf) {
						tempVector.push_back(data_A);
						tempVector.push_back(data_B);
						outputData.push_back(tempVector);
						tempVector.clear();
						if (mapOfSetPair.count(data_A.size() + data_B.size())) {
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_A, data_B));
						}
						else {
							mapOfSetPair.insert({ data_A.size() + data_B.size() ,vector < pair<unordered_set<string>, unordered_set<string>>>() });
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_A, data_B));
						}
					}
					if (confidentRate(data_B, data_A) >= min_conf) {
						tempVector.push_back(data_B);
						tempVector.push_back(data_A);
						outputData.push_back(tempVector);
						tempVector.clear();
						if (mapOfSetPair.count(data_A.size() + data_B.size())) {
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_B, data_A));
						}
						else {
							mapOfSetPair.insert({ data_A.size() + data_B.size() ,vector < pair<unordered_set<string>, unordered_set<string>>>() });
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_B, data_A));
						}
					}
				}
			NEXT_C:
				data_B.clear();
			}
			tempSet_to.clear();
			data_A.clear();
		}
		tempSet_from.clear();
		for (int i = size_back - 1; i >= size_front; i--) {
			data_A = passed_set[i];
			for (int j = size_back - 1; j >= i; j--) {
				for (const auto &dataSet : passed_set[j]) {
					if (data_A.count(dataSet)) {
						goto NEXT_E;
					}
					data_B.insert(dataSet);
				}
				if (mapOfSetPair.count(data_A.size() + data_B.size())) {
					if (findPair(mapOfSetPair.at(data_A.size() + data_B.size()), pair<unordered_set<string>, unordered_set<string>>(data_A, data_B))) {
						goto NEXT_E;
					}
					if (findPair(mapOfSetPair.at(data_A.size() + data_B.size()), pair<unordered_set<string>, unordered_set<string>>(data_B, data_A))) {
						goto NEXT_E;
					}
				}
				if (supportRate(data_A, data_B) >= min_supp) {
					tempSet_sup = data_A;
					for (const auto &u : data_B) {
						tempSet_sup.insert(u);
					}
					if (!findSet(passed_set, tempSet_sup)) {
						passed_set.push_back(tempSet_sup);
					}
					tempSet_sup.clear();
					if (confidentRate(data_A, data_B) >= min_conf) {
						tempVector.push_back(data_A);
						tempVector.push_back(data_B);
						outputData.push_back(tempVector);
						tempVector.clear();
						if (mapOfSetPair.count(data_A.size() + data_B.size())) {
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_A, data_B));
						}
						else {
							mapOfSetPair.insert({ data_A.size() + data_B.size() ,vector < pair<unordered_set<string>, unordered_set<string>>>() });
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_A, data_B));
						}
					}
					if (confidentRate(data_B, data_A) >= min_conf) {
						tempVector.push_back(data_B);
						tempVector.push_back(data_A);
						outputData.push_back(tempVector);
						tempVector.clear();
						if (mapOfSetPair.count(data_A.size() + data_B.size())) {
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_B, data_A));
						}
						else {
							mapOfSetPair.insert({ data_A.size() + data_B.size() ,vector < pair<unordered_set<string>, unordered_set<string>>>() });
							mapOfSetPair.at(data_A.size() + data_B.size()).push_back(pair<unordered_set<string>, unordered_set<string>>(data_B, data_A));
						}
					}
				}
			NEXT_E:
				data_B.clear();
				
			}
			tempSet_to.clear();
			data_A.clear();
		}
		tempSet_from.clear();
		size_front = size_back;
		size_back = passed_set.size();
		if (size_front == size_back)
			continueOrNot = false;
	}
	/*output result to file*/
	int times = 0;
	fileOut << outputData.size() << "\n";
	for (int i = 0; i < outputData.size(); i++) {
		times = 0;
		for (const auto &dataSet : outputData[i][0]) {
			fileOut << dataSet;
			times++;
			if(times < outputData[i][0].size())
				fileOut << ", ";
		}
		times = 0;
		fileOut << " => ";
		for (const auto &dataSet : outputData[i][1]) {
			fileOut << dataSet;
			times++;
			if (times < outputData[i][1].size())
				fileOut << ", ";
		}
		fileOut << "\n";
	}
	fileIn.close();
	fileOut.close();
	return 0;
}
