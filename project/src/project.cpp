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

void bubble(struct team_stats myarray[], string field, int count);
bool comparefield(string field, team_stats t1, team_stats t2);
template<class comp> int greaterthan(comp item1, comp item2);
bool ifequal(int greater, team_stats t1, team_stats t2);
void printfunction(team_stats t[], string field, string order, int len);
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
	//string filename = "2015-game-stats.txt";
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
	for (int i = 0; i < total_commands; i++) {
		commands.push_back(globalArr[count].c_str());
		vector<string> v = split(globalArr[count++].c_str());

		if (v[0].compare("bsort") == 0) {
			int year_exists = 0;
			if (v[1].compare("range") != 0) {
				int given_year = atoi(v[1].c_str());
				cout<<v[1].c_str()<<endl<<given_year<<endl;
				int year_index;

				for (int i = 0; i < num_of_years; i++) {

					if (mydata[i].year == given_year) {
						year_exists = 1;
						year_index = i;

					}
				}
				if (year_exists == 1) {
					string field;
					string order;
					field = v[2].c_str();
					order = v[3].c_str();
					int count=sizeof(mydata[year_index].teams)/sizeof(mydata[year_index].teams[0]);
					//cout<<count <<endl;
					bubble(mydata[year_index].teams, field,count);
				    printfunction(mydata[year_index].teams, field, order,count);

				} else {
					cout << "Error: No such year." << endl;
				}
			}

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
	delete mydata;
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
	end();
	return 0;
}

void bubble(struct team_stats myarray[], string field, int count) {

	team_stats t;

	//cout<<"Size of my array  "<<a<<endl;
	for (int a = 1; a < count; a++) {
		for (int b = 0; b <= count - 1; b++) {
			if (comparefield(field, myarray[b], myarray[b + 1])) {
				t = myarray[b];
				myarray[b] = myarray[b+1];
				myarray[b+1] = t;
			}
		}
	}

}

bool comparefield(string field, team_stats t1, team_stats t2) {

	int greater = 0;
	bool result = false;
	if ("team_name" == field) {

				if(strcmp(t1.team_name, t2.team_name)>0){
					greater=2;
				}
				else if(strcmp(t1.team_name,t2.team_name)==0)
				{
					greater=0;
				}

	}

	else if ("games" == field) {
		greater = greaterthan(t1.games, t2.games);

	}

	else if ("pts_per_game" == field) {
		greater = greaterthan(t1.pts_per_game, t2.pts_per_game);

	} else if ("total_points" == field) {
		greater = greaterthan(t1.total_points, t2.total_points);

	} else if ("scrimmage_plays" == field) {
		greater = greaterthan(t1.scrimmage_plays, t2.scrimmage_plays);

	} else if ("yds_per_game" == field) {
		greater = greaterthan(t1.yds_per_game, t2.yds_per_game);

	} else if ("yds_per_play" == field) {
		greater = greaterthan(t1.yds_per_play, t2.yds_per_play);

	} else if ("first_per_game" == field) {
		greater = greaterthan(t1.first_per_game, t2.first_per_game);

	} else if ("third_md" == field) {
		greater = greaterthan(t1.third_md, t2.third_md);

	} else if ("third_att" == field) {
		greater = greaterthan(t1.third_att, t2.third_att);

	} else if ("third_pct" == field) {
		greater = greaterthan(t1.third_pct, t2.third_pct);

	} else if ("fourth_md" == field) {
		greater = greaterthan(t1.fourth_md, t2.fourth_md);

	} else if ("fourth_att" == field) {
		greater = greaterthan(t1.fourth_att, t2.fourth_att);

	} else if ("fourth_pct" == field) {
		greater = greaterthan(t1.fourth_pct, t2.fourth_pct);

	} else if ("penalties" == field) {
		greater = greaterthan(t1.penalties, t2.penalties);

	} else if ("pen_yds" == field) {
		greater = greaterthan(t1.pen_yds, t2.pen_yds);

	} else if ("top_per_game" == field) {
		if(strcmp(t1.top_per_game, t2.top_per_game)>0){
							greater=2;
						}
						else if(strcmp(t1.top_per_game,t2.top_per_game)==0)
						{
							greater=1;
						}

	} else if ("fum" == field) {
		greater = greaterthan(t1.fum, t2.fum);

	} else if ("lost" == field) {
		greater = greaterthan(t1.lost, t2.lost);

	} else if ("to" == field) {
		greater = greaterthan(t1.to, t2.to);

	} else {
		cout << "Error: No such field." << endl;
	}

	result = ifequal(greater, t1, t2);

	return result;

}

bool ifequal(int greater, team_stats t1, team_stats t2) {
	bool result = false;
	if (greater == 2) {
		result = true;
	} else if (greater == 1) {
		if (t1.team_name > t2.team_name) {
			result = true;
		}
	}

	else {
		result = false;
	}
	return result;
}

template<class comp> int greaterthan(comp item1, comp item2) {

	if (item1 > item2) {
		return 2;
	} else if (item1 == item2) {
		return 1;
	} else {
		return 0;
	}

}

void printfunction(team_stats t[], string field, string order, int len) {
	//int len = static_cast<int>(sizeof(t)/sizeof(t[0]));

	if ("team_name" == field) {
		cout << "Team Name" << endl;
		if (order.compare("incr") == 0) {

			for (int i = 0; i < len; i++) {
				cout << t[i].team_name << endl;

			}
		} else if (order.compare("decr") == 0) {
			for (int i = len - 1; i >= 0; i--) {
				cout << t[i].team_name << endl;

			}
		}

	}

	else if ("games" == field) {
		cout << "Team Name \t" << field << endl;
		if (order.compare("incr") == 0) {

			for (int i = 0; i < len; i++) {
				cout << t[i].team_name << '\t' << t[i].games << endl;

			}
		} else if (order.compare("decr") == 0) {
			for (int i = len - 1; i >= 0; i--) {
				cout << t[i].team_name << '\t' << t[i].games << endl;

			}
		}

	}

	else if ("pts_per_game" == field) {
		cout << "Team Name \t" << field << endl;
		if (order.compare("incr") == 0) {

			for (int i = 0; i < len; i++) {
				cout << t[i].team_name << '\t' << t[i].pts_per_game << endl;

			}
		} else if (order.compare("decr") == 0) {
			for (int i = len - 1; i >= 0; i--) {
				cout << t[i].team_name << '\t' << t[i].pts_per_game << endl;

			}
		}

	} else if ("total_points" == field) {
		cout << "Team Name \t" << field << endl;
		if (order.compare("incr") == 0) {

			for (int i = 0; i < len; i++) {
				cout << t[i].team_name << '\t' << t[i].total_points << endl;

			}
		} else if (order.compare("decr") == 0) {
			for (int i = len - 1; i >= 0; i--) {
				cout << t[i].team_name << '\t' << t[i].total_points << endl;

			}
		}

	} else if ("scrimmage_plays" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].scrimmage_plays << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].scrimmage_plays << endl;

					}
				}

	} else if ("yds_per_game" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].yds_per_game << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].yds_per_game << endl;

					}
				}

	} else if ("yds_per_play" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].yds_per_play << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].yds_per_play << endl;

					}
				}

	} else if ("first_per_game" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].first_per_game << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].first_per_game << endl;

					}
				}

	} else if ("third_md" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].third_md << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].third_md << endl;

					}
				}

	} else if ("third_att" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].third_att << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].third_att << endl;

					}
				}

	} else if ("third_pct" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].third_pct << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].third_pct << endl;

					}
				}

	} else if ("fourth_md" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].fourth_md << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].fourth_md << endl;

					}
				}

	} else if ("fourth_att" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].fourth_att << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].fourth_att << endl;

					}
				}

	} else if ("fourth_pct" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].fourth_pct << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].fourth_pct << endl;

					}
				}

	} else if ("penalties" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].penalties << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].penalties << endl;

					}
				}

	} else if ("pen_yds" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].pen_yds << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].pen_yds << endl;

					}
				}

	} else if ("top_per_game" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].top_per_game << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].top_per_game << endl;

					}
				}

	} else if ("fum" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].fum << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].fum << endl;

					}
				}

	} else if ("lost" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].lost << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].lost << endl;

					}
				}

	} else if ("to" == field) {
		cout << "Team Name \t" << field << endl;
				if (order.compare("incr") == 0) {

					for (int i = 0; i < len; i++) {
						cout << t[i].team_name << '\t' << t[i].to << endl;

					}
				} else if (order.compare("decr") == 0) {
					for (int i = len - 1; i >= 0; i--) {
						cout << t[i].team_name << '\t' << t[i].to << endl;

					}
				}

	} else {
		cout << "Error: No such field." << endl;
	}

}
