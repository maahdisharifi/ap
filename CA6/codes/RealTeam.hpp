#pragma once
#include <string>
#include <vector>
#include "RealPlayer.hpp"
#include "funcs.hpp"
#include <iostream>
using namespace std;
class RealPlayer;
class RealTeam
{
public:
    RealTeam(string name, vector<RealPlayer *> players);
    void updateGAandGF(int gf, int ga);
    string getName() { return name; };
    void win() { score += 3; }
    void draw() { score++; }
    friend void sortRealTeams(vector<RealTeam *> &realTeams);
    void printPlayersInfo(bool rankSorting, string positon, int weekNum);
    void printTeamInfo();
    void addCleanSheet(int week);
    int numOfCleensheet();

private:
    string name;
    vector<RealPlayer *> players;
    int ga;
    int gf;
    int score;
    vector<bool> cleansheets;
};
