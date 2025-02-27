#include "Md.hpp"
void Midfielder::calPlayerScoreR2(int ga, int week)
{
    if (ga == 0)
    {
        playerScore[week - 1]++;
    }
    playerScore[week - 1] += 3 * goals[week - 1] + 2 * assists[week - 1];
    playerScore[week - 1] -= 3 * ownGoals[week - 1];
}
Midfielder::Midfielder(string name, int price) : RealPlayer(name, price)
{
}