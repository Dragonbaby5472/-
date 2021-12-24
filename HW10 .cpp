#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <set>
#include <utility>
#include <iomanip>

using namespace std;
string  sequence_1, sequence_2;
vector<vector<int>> location;
vector<vector<pair<int, int>>> samePoint;
int maxLength;
set<string> all_LCS;
void findLocation(string str1, string str2) {
	for (int i = 0; i < str1.length(); i++) {
		for (int j = 0; j < str2.length(); j++) {
			if (str1[i] == str2[j]) {
				if (i == 0 || j == 0)
					location[i][j] = 1;
				else
					location[i][j] = location[i - 1][j - 1] + 1;
				samePoint[location[i][j]].push_back(pair<int, int>(i, j));
			}
			else {
				if (!i && !j)
					location[i][j] = 0;
				else if (i && !j)
					location[i][j] = location[i - 1][j];
				else if (!i && j)
					location[i][j] = location[i][j - 1];
				else
					location[i][j] = max(location[i - 1][j], location[i][j - 1]);
			}
		}
	}
}

void findLCS(int k, string one_lcs, pair<int, int> point) {
	if (k == maxLength) {
		all_LCS.insert(one_lcs);
		return;
	}
	for (auto s : samePoint[k + 1]) {
		if (point.first < s.first && point.second < s.second) {
			one_lcs.push_back(sequence_1[s.first]);
			findLCS(k + 1, one_lcs, s);
			one_lcs.pop_back();
		}
	}
}

int main() {
	string fileName;
	printf("Please enter the filename:\n");
	cin >> fileName;
	ifstream file_in(fileName);
	if (!file_in) {
		cerr << "file \"" << fileName << "\" could not open." << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	ofstream file_out("result_E24106288.txt");
	if (!file_out) {
		cerr << "file \"result_E24106288.txt\" could not open." << endl;
		system("pause");
		exit(EXIT_FAILURE);
	}
	file_in >> sequence_1;
	file_in >> sequence_2;
	location = vector<vector<int>>(sequence_1.length(), vector<int>(sequence_2.length(), 0));
	samePoint = vector<vector<pair<int, int>>>(max(sequence_1.length(), sequence_2.length()) - 1);
	findLocation(sequence_1, sequence_2);
	maxLength = location[sequence_1.length() - 1][sequence_2.length() - 1];
	if (maxLength != 0) {
		findLCS(0, "", pair<int,int>(-1,-1));
	}
	file_out << maxLength << endl;
	file_out << all_LCS.size() << endl;
	for (auto lcs : all_LCS)
		file_out << lcs << endl;
	file_in.close();
	file_out.close();
	return EXIT_SUCCESS;
}