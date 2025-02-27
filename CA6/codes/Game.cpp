#include "Game.hpp"
Game::Game(string fTeamName_, string sTeamName_, int fTeamGoals_, int sTeamGoals_, int week_)
{
    fTeamName = fTeamName_;
    sTeamName = sTeamName_;
    fTeamGoals = fTeamGoals_;
    sTeamGoals = sTeamGoals_;
    week = week_;
}
void Game::matchesResultLeague(int week)
{
    if (this->week == week)
        cout << fTeamName << ' ' << fTeamGoals << " | " << sTeamName << ' ' << sTeamGoals << endl;
}