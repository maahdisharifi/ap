#pragma once
#include "RealPlayer.hpp"
#include "RealTeam.hpp"
#include "Gk.hpp"
#include "Md.hpp"
#include "St.hpp"
#include "Df.hpp"
#include "FFPlayer.hpp"
#include "Game.hpp"
#include <iostream>
#include <vector>
#include <string>
#include "err.hpp"
#include "Admin.hpp"
#include <fstream>
#include <algorithm>
#include <iomanip>
using namespace std;
const vector<string> PUT_COMMANDS = {};
const vector<string> DELETE_COMMANDS = {};
const vector<string> GET_COMMANDS = {"squad", "matches_result_league", "users_ranking", "league_standings", "players", "team_of_the_week"};
const vector<string> POST_COMMANDS = {"pass_week", "open_transfer_window", "close_transfer_window", "buy_player",
                                      "sell_player", "logout", "register_admin", "login", "signup"};
struct cmp
{
    cmp(int weekNum) { this->weekNum = weekNum; }
    bool operator()(RealPlayer *first, RealPlayer *second)
    {
        return first->getScore(weekNum) > second->getScore(weekNum);
    }
    int weekNum;
};
struct cmpScore
{
    int weekNum;
    cmpScore(int weekNum) { this->weekNum = weekNum; }
    bool operator()(RealPlayer *first, RealPlayer *second)
    {
        // logic uses paramA in some way...
        return first->calculateSeasonScore(weekNum) > second->calculateSeasonScore(weekNum);
    }
};
class RealTeam;
class RealPlayer;
class Defender;
class Forward;
class Midfielder;
class GolaKeeper;
void printPlayerInfo(RealTeam *team, RealPlayer *p, int weekNum, int &count);
bool cmpNames(RealPlayer *first, RealPlayer *second);
bool allEqualToZero(std::vector<double> const &v, int weekNum);
double calcSum(vector<double> const &v, int weekNum);
int numOfPlayedGames(vector<double> const &v, int weekNum);
string findPlayerName(const vector<string> &words);
vector<string> splitInput(string input, char delim);
vector<RealPlayer *> createPlayers(vector<RealPlayer *> &realPlayers, const vector<string> &gks, const vector<string> &dfs,
                                   const vector<string> &mds, const vector<string> &sts);

void readLeagueData(vector<RealPlayer *> &realPlayers, vector<RealTeam *> &realTeams);
RealTeam *findTeam(const vector<RealTeam *> &realTeams, string name);
void updateGAandGf(const vector<string> &twoTeams, const vector<string> &gameResult, vector<RealTeam *> &realTeams);
RealPlayer *findPlayer(const vector<RealPlayer *> &realPlayers, string name);
void updateInjuries(const vector<string> &injuries, int week, vector<RealPlayer *> &realPlayers);
void updateYCards(const vector<string> &yCards, vector<RealPlayer *> &realPlayers);
void updateRCards(int curWeek, const vector<string> &rCards, vector<RealPlayer *> &realPlayers);
void updateScores(vector<string> &scores, vector<RealPlayer *> &realPlayers, int week);
void substring(string line, vector<string> &words, vector<string> &twoTeams, vector<string> &gameResult,
               vector<string> &injuries, vector<string> &yCards, vector<string> &rCards, vector<string> &goalWithAssist, vector<string> &team1, vector<string> &team2);
void updateTeamsScores(const vector<string> &twoTeams, const vector<string> &gameResult, vector<RealTeam *> &realTeams);
void readWeeksData(int curWeek, vector<RealTeam *> &realTeams, vector<RealPlayer *> &realPlayers, vector<Game *> &games);
void passWeek(int &curWeek, Admin &ad);
void showTheTeam(const vector<string> &words, const vector<RealTeam *> &realTeams, int weekNum);
void sortRealTeams(vector<RealTeam *> &realTeams);
void leagueStandings(vector<RealTeam *> &realTeams);
void findTheBestTeam(int weekNum, vector<RealPlayer *> &realPlayers);
void matchesResultLeague(const vector<string> &words, int curWeek, const vector<Game *> &games);
void signup(vector<string> words, vector<FFPlayer *> &ffPlayers);
FFPlayer *find_ffplayer_by_name(string name, vector<FFPlayer *> ffPlayers);
bool login(vector<string> words, vector<FFPlayer *> &ffPlayers, string &CurrUsersUsername);
void logout(string CurrUsersUsername, const vector<FFPlayer *> &ffPlayers, Admin &ad, int &numOfUsersLoggedIn);
void buyPlayer(int curWeek, vector<RealPlayer *> &realPlayers, vector<string> words, string CurrUsersUsername, vector<FFPlayer *> &ffPlayers);
void updateSuspension(vector<RealPlayer *> &realPlayers, int week);
void sellPlayer(vector<RealPlayer *> realPlayers, const vector<string> &words, string currentUserName, vector<FFPlayer *> &ffPlayers);
void updateNumOfSoldPlayers(vector<FFPlayer *> &ffPlayers);
void show_squad(vector<string> words, const vector<FFPlayer *> &ffPlayers, string CurrUsersUserName, int weekNum);
bool mypred(FFPlayer *first, FFPlayer *second);
void user_rankings(vector<FFPlayer *> ffPlayers, int currWeek);
void updateTeamScores(vector<FFPlayer *> &ffPlayers, int currWeek);
void updateFfpAvailableWeeks(vector<FFPlayer *> &ffPlayers, int weekNum);
bool input_is_valid(vector<string> words, int curWeek);
void handleUserInput(int &numOfUsersLoggedIn, int &curWeek, Admin &ad, string input, vector<RealPlayer *> &realPlayers,
                     vector<RealTeam *> &realTeams, vector<Game *> &games, vector<FFPlayer *> &ffPlayers);
float A(float x);
void draw(int week, vector<string> players1, vector<string> players2, vector<RealPlayer *> &RealPlayers);
void win(int week, vector<string> players1, vector<RealPlayer *> &RealPlayers);
void lose(int week, vector<string> players1, vector<RealPlayer *> &RealPlayers);
void updatePlayerScoreR1(int week, vector<RealPlayer *> &RealPlayers, const vector<string> &Team1Players, const vector<string> &Team2Players, const vector<string> &gameResult);
void updateGoalsAssist(int week, vector<string> goalAndAssist, vector<RealPlayer *> &realPlayers);
void updatePlayerScoreR2(int week, vector<string> gameResult, vector<string> team1, vector<string> team2, vector<RealPlayer *> &realPlayers);
void updatePlayerScoreR3_lb(vector<RealPlayer *> &realPlayers, vector<string> team1, vector<string> team2, int week);
void updatePlayerScoreR3_rb(vector<RealPlayer *> &realPlayers, vector<string> team1, vector<string> team2, int week);
void updatePlayerScoreR3_cbs(vector<RealPlayer *> &realPlayers, vector<string> team1, vector<string> team2, int week);
void updatePlayerScoreR3_cms(vector<RealPlayer *> &realPlayers, vector<string> team1, vector<string> team2, int week);
void updatePlayerScoreR3(int week, vector<string> team1, vector<string> team2, vector<RealPlayer *> &realPlayers);
void updatePlayerScoreR4(int week, vector<string> team1, vector<string> team2, vector<RealPlayer *> &realPlayers);
void updateCleensheet(int week, vector<RealTeam *> &realTeams, const vector<string> &twoTeams, const vector<string> &result);
void setCaptain(string curUserName, const vector<string> &words, vector<FFPlayer *> &ffplayers);
void show_budget(string currUsersUsername, vector<FFPlayer *> ffPlayers);
