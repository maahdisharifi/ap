#include <iostream>
#include <vector>
#include <string>
#include "funcs.hpp"
#include "Game.hpp"
#include "RealPlayer.hpp"
#include "RealTeam.hpp"
#include "FFPlayer.hpp"
#include "St.hpp"
#include "Md.hpp"
#include "Df.hpp"
#include "Gk.hpp"
#include "err.hpp"
using namespace std;
int main()
{
    Admin ad;
    int curWeek = 0;
    vector<RealPlayer *> realPlayers;
    vector<RealTeam *> realTeams;
    vector<Game *> games;
    vector<FFPlayer *> ffPlayers;
    readLeagueData(realPlayers, realTeams);
    string input;
    int numOfUsersLoggedIn = 0;
    while (getline(cin, input))
    {
        handleUserInput(numOfUsersLoggedIn, curWeek, ad, input, realPlayers, realTeams, games, ffPlayers);
    }
    return 0;
}