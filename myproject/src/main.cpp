/*
 * main.cpp
 *
 *  Created on: Feb 4, 2016
 *      Author: pratik
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include <ctime>
#include <vector>
#include <math.h>
#include <omp.h>

#include"team_stats.h"
using namespace std;
string name;
vector<string> globalArr;
vector<string> commands;
int num_of_years;
annual_stats* mydata;
int main() {
	string line;
	getline(cin, line);

	name = line;
	string filename = name + ".txt";
	ifstream myfile(filename.c_str());
	if (myfile.is_open()) {
		int c = 0;
		string line;
		vector<string> arr;
		while (getline(myfile, line)) {
			if (!line.empty()) {
				if (c == 0) {
					stringstream ss(line);
					ss >> num_of_years;
					mydata = new annual_stats[num_of_years];

				}

				if (c != 0) {
					if (!line.empty()) {
						arr.push_back(line);

					}
				}

			}

			c++;
		}
		for (size_t i = 0; i < arr.size(); i++) {
			globalArr.push_back(arr[i].c_str());

		}
		arr.clear();
	}
	myfile.close();

}

