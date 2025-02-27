#include "RealTeam.hpp"
int RealTeam::numOfCleensheet()
{
    int count = 0;
    for (auto cleensheet : cleansheets)
    {
        if (cleensheet)
        {
            count++;
        }
    }
    return count;
}
void RealTeam::addCleanSheet(int week)
{
    cleansheets[week - 1] = true;
}
void RealTeam::printTeamInfo()
{
    cout << name << ": "
         << "score: " << score << " | "
         << "GF: " << gf << " | "
         << "GA: " << ga << endl;
}
void RealTeam::printPlayersInfo(bool rankSorting, string positon, int weekNum)
{
    cout << "list of players:\n";
    int count = 1;
    if (rankSorting == false && positon == "")
    {
        sort(this->players.begin(), this->players.end(), cmpNames);
        for (auto p : players)
        {
            printPlayerInfo(this, p, weekNum, count);
        }
    }
    else if (rankSorting == false && positon != "")
    {
        sort(this->players.begin(), this->players.end(), cmpNames);
        if (positon == "gk")
        {
            for (auto p : players)
            {
                if (p->getPos() == "GoalKeeper")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "df")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Defender")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "md")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Midfielder")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "fw")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Forward")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
    }

    else if (rankSorting == true && positon == "")
    {
        sort(players.begin(), players.end(), cmpScore(weekNum));
        for (auto p : players)
        {
            // 1. name: <name> | role: <role> | score: <score>
            printPlayerInfo(this, p, weekNum, count);
        }
    }
    else if (rankSorting == true && positon != "")
    {
        sort(players.begin(), players.end(), cmpScore(weekNum));
        if (positon == "gk")
        {
            for (auto p : players)
            {
                if (p->getPos() == "GoalKeeper")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "df")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Defender")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "md")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Midfielder")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "fw")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Forward")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
    }
    else
    {
        cerr << err.Bad_Request;
    }
}

void RealTeam::updateGAandGF(int gf, int ga)
{
    this->ga += ga;
    this->gf += gf;
}
RealTeam::RealTeam(string name_, vector<RealPlayer *> players_)
{
    name = name_;
    players = players_;
    ga = 0;
    gf = 0;
    score = 0;
    cleansheets = vector<bool>(NUM_OF_WEEKS, false);
}
