//============================================================================
// Name        : project.cpp
// Author      : Pratik Bonde
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
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
bool sortFlag = false;
int t_compare = 0;
int total_commands = 0;
int no_swaps = 0;
int arrLength = 0;
int num_of_years;
annual_stats* mydata;
void start() {
	cout << name << "********" << endl;

}
vector<string> split(const string& s) {
	vector<string> ret;
	typedef string::size_type string_size;
	string_size i = 0;

	// invariant: we have processed characters [original value of i, i)
	while (i != s.size()) {
		// ignore leading blanks
		// invariant: characters in range [original i, current i) are all spaces
		while (i != s.size() && isspace(s[i]))
			++i;

		// find end of next word
		string_size j = i;
		// invariant: none of the characters in range [original j, current j)is a space
		while (j != s.size() && !isspace(s[j]))
			j++;

		// if we found some nonwhitespace characters
		if (i != j) {
			// copy from s starting at i and taking j - i chars
			ret.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return ret;
}
void readFile() {
	globalArr.clear();
	arrLength = 0;

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
					cout << num_of_years << endl;

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
			//	cout << globalArr[i] << endl;
		}
	}
	//cout << globalArr.size();

	myfile.close();
}

void insertData() {
	int count = 0;
	for (int i = 0; i < num_of_years; i++) {
		mydata[i].year = atoi(globalArr[count++].c_str());

		for (int j = 0; j < 32; j++) {
			vector<string> v;
			stringstream ss(globalArr[count++]);
			string token;
			while (getline(ss, token, '\t')) {
				v.push_back(token);

			}
			strcpy(mydata[i].teams[j].team_name, v[0].c_str());
			mydata[i].teams[j].games = atoi(v[1].c_str());
			mydata[i].teams[j].pts_per_game = atof(v[2].c_str());
			mydata[i].teams[j].total_points = atoi(v[3].c_str());
			mydata[i].teams[j].scrimmage_plays = atoi(v[4].c_str());
			mydata[i].teams[j].yds_per_game = atof(v[5].c_str());
			mydata[i].teams[j].yds_per_play = atof(v[6].c_str());
			mydata[i].teams[j].first_per_game = atof(v[7].c_str());
			mydata[i].teams[j].third_md = atoi(v[8].c_str());
			mydata[i].teams[j].third_att = atoi(v[9].c_str());
			mydata[i].teams[j].third_pct = atoi(v[10].c_str());
			mydata[i].teams[j].fourth_md = atoi(v[11].c_str());
			mydata[i].teams[j].fourth_att = atoi(v[12].c_str());
			mydata[i].teams[j].fourth_pct = atoi(v[13].c_str());
			mydata[i].teams[j].penalties = atoi(v[14].c_str());
			mydata[i].teams[j].pen_yds = atoi(v[15].c_str());
			strcpy(mydata[i].teams[j].top_per_game, v[16].c_str());
			mydata[i].teams[j].fum = atoi(v[17].c_str());
			mydata[i].teams[j].lost = atoi(v[18].c_str());
			mydata[i].teams[j].to = atoi(v[19].c_str());

			//cout<<mydata[i].teams[j].games<<endl;

		}

	}
	total_commands = atoi(globalArr[count++].c_str());
//cout<<total_commands<<endl;
for(int i=0;i<total_commands;i++){
	commands.push_back(globalArr[count].c_str());
	 vector<string> v = split(globalArr[count++].c_str());

	 if(strcmp(v[0].c_str(),"bsort")==0){


	 }

	 //cout<<commands[i]<<endl;

	 /*
	      for (vector<string>::size_type i = 0; i != v.size(); ++i){
	      cout << v[i] << endl;
	      }*/
}

}

void end() {
	cout << "End of processing fitness data for: " + name << endl;
	name.clear();
	globalArr.clear();
	sortFlag = false;
	arrLength = 0;
}

void exitFunc() {
	cout << "Program terminating" << endl;
	exit(0);
}

int main() {
	string line;
	getline(cin, line);

	name = line;
	readFile();
	mydata = new annual_stats[num_of_years];
	insertData();

	return 0;
}

template <class X> void bubble(X *items,int count,struct annual_stats myarray[])
{
  X t;
 // mydata->field;
  for(int a=1; a<count; a++)
    for(int b=count-1; b>=a; b--)
      if(items[b-1] > items[b]) {
        t = items[b-1];
        items[b-1] = items[b];
        items[b] = t;
      }
}
