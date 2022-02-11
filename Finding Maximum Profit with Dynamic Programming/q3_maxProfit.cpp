/****************
* Merve CANDAN  *
* 150160041     *
****************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <set>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

pair<int, set<int>> MaxProfit(int numOfCrystals, vector<int> profits, vector<int> entryCosts)
{
	int count = 0;
	size_t length = profits.size();
	int **arr = new int *[profits.size()+1];

	for(size_t i = 0; i < length +1; i++){
		count++;
		arr[i] = new int[numOfCrystals+1];
		arr[i][0] = 0;
	}

	for(int i = 0; i <= numOfCrystals; i++){
		arr[0][i] = 0;
	}
	
	for(size_t i = 1; i < length +1; i++){
		for(int j = 1; j < numOfCrystals +1; j++){
			if(j < entryCosts[i-1]){
				arr[i][j] = arr[i-1][j];
			}
			else{
				arr[i][j] = max(profits[i-1] + arr[i-1][j-entryCosts[i-1]], arr[i-1][j]);	
			}
		}
	}

	set<int> path;

	int temp_crystal = numOfCrystals;
	int num = count - 1;
	int maxim = arr[num][temp_crystal];

	while(temp_crystal > 0 && num > 0){
		if(arr[num][temp_crystal] != arr[num-1][temp_crystal]){
			path.insert(num);
			temp_crystal = temp_crystal - entryCosts[num-1];
		}
		num--;
	}

	/****************************************************************/
	/********* YOU NEED TO USE HERE AS BASE OF YOUR METHOD! *********/
	/* YOU CAN USE HELPER METHODS BUT main() WILL CALL THIS METHOD! */
	/****************************************************************/

	cout << "Dynaming Programming Table" << endl;
	for (int i = 0; (unsigned)i <= profits.size(); i++) {
		for (int j = 0; j <= numOfCrystals; j++) {
			cout << std::right << std::setw(3) << arr[i][j];
		}
		cout << endl;
	}

	return pair<int, set<int>>(maxim, path);
}

int main() {
	int numOfCrystals;
	vector<int> profits;
	vector<int> entryCosts;
	
	string inputFilename;
	cout << "Enter the name of the input file: ";
	cin >> inputFilename;

	ifstream input(inputFilename);

	if (!input.is_open()) {
		cerr << "File named \"" << inputFilename << "\" could not open!" << endl;
		return EXIT_FAILURE;
	}

	string line;
	if (getline(input, line)) {
		numOfCrystals = stoi(line);
	}
	while (getline(input, line, ' ')) {
		profits.push_back(stoi(line));
		getline(input, line);
		entryCosts.push_back(stoi(line));
	}

	pair<int, set<int>> result = MaxProfit(numOfCrystals, profits, entryCosts);

	cout << "Max profit is " << result.first << "." << endl;
	cout << "Cities visited:";
	for (int cityNumber : result.second) {
		cout << " " << cityNumber;
	}
	cout << endl;
}

