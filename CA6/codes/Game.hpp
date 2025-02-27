#pragma once
#include <iostream>
#include <string>
using namespace std;
class Game
{
public:
    Game(string fTeamName_, string sTeamName_, int fTeamGoals_, int sTeamGoals, int week_);
    void matchesResultLeague(int week);

private:
    string fTeamName;
    string sTeamName;
    int fTeamGoals;
    int sTeamGoals;
    int week;
};