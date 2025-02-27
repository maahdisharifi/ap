#include "Gk.hpp"
GoalKeeper::GoalKeeper(string name, int price) : RealPlayer(name, price)
{
}
void GoalKeeper::calPlayerScoreR2(int ga, int week)
{
    if (ga == 0)
    {
        this->playerScore[week - 1] += 5;
    }
    else
    {
        playerScore[week - 1] -= ga;
    }
    playerScore[week - 1] += 3;
}