#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "RealPlayer.hpp"
#include "Gk.hpp"
#include "St.hpp"
#include "Df.hpp"
#include "Md.hpp"
class FFPlayer
{
public:
    FFPlayer(string TeamName_, string passWord_);
    bool checkNameDup(string name_);
    void updateFfpAvailableWeeks(int weekNum);
    bool checkPassword(string pass);
    string getTeamName() { return TeamName; }
    void loginUser() { loginStatus = true; }
    void logoutUser() { loginStatus = false; }
    bool getLoginStatus() { return loginStatus; }
    bool addPlayer(RealPlayer *rpp);
    bool isCompleted();
    int getNumOfSoldPlayers() { return numOfSoldPlayers; }
    bool sellPlayer(string playerName, bool isCompleted, vector<RealPlayer *> realPlayers);
    void resetNumOFSoldPlayers() { numOfSoldPlayers = 0; }
    void print_squad();
    double calcTeamTotalScore(int weekNum, vector<bool> availableWeeks);
    int getTotalTeamScore() { return points; }
    vector<bool> getAvailableWeeks() { return availableWeeks; }
    void setCaptain(string playerName);
    void show_team_budget() { cout << this->budget << endl; }
    int get_budget() { return budget; }
    void set_new_budget(int new_budget) { budget = new_budget; }
    int totalCost() { return (gk->get_price() + df1->get_price() + df2->get_price() + md->get_price() + st->get_price()); }

private:
    string TeamName;
    string passWord;
    bool loginStatus;
    double points;
    int numOfSoldPlayers;
    RealPlayer *gk;
    RealPlayer *df1;
    RealPlayer *df2;
    RealPlayer *md;
    RealPlayer *st;
    vector<bool> availableWeeks;
    string captainName;
    int budget;
};