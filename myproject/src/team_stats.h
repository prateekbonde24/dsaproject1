/*
 * team_stats.h
 *
 *  Created on: Feb 4, 2016
 *      Author: pratik
 */

#ifndef TEAM_STATS_H_
#define TEAM_STATS_H_

#define NO_TEAMS      32 // Number of NFL teams
#define TEAM_NAME_LEN 25 // Maximum team name string length
#define TOP_LEN        6 // Maximum time of possession string length

struct team_stats {
	char team_name[ TEAM_NAME_LEN]; // Name of NFL team
	int games; // Number of games played in the season
	float pts_per_game; // Points per game
	int total_points; // Total points
	int scrimmage_plays; // Scrimmage plays
	float yds_per_game; // Yards per game
	float yds_per_play; // Yards per play
	float first_per_game; // First downs per game
	int third_md; // Third down conversions
	int third_att; // Third down attempts
	int third_pct; // Third down percentage
	int fourth_md; // Fourth down conversions
	int fourth_att; // Fourth down attempts
	int fourth_pct; // Fourth down percentage
	int penalties; // Number of penalties
	int pen_yds; // Penalty yards
	char top_per_game[ TOP_LEN]; // Time of possession per game
	int fum; // Number of fumbles
	int lost; // Fumbles lost
	int to; // Turnover ratio
};

struct annual_stats {
	int year;
	struct team_stats teams[ NO_TEAMS];
};



#endif /* TEAM_STATS_H_ */

