#include "St.hpp"
void Striker::calPlayerScoreR2(int ga, int week)
{
    if (goals[week - 1] == 0)
    {
        playerScore[week - 1]--;
    }
    playerScore[week - 1] += 3 * goals[week - 1] + assists[week - 1];
    playerScore[week - 1] -= 3 * ownGoals[week - 1];
}
Striker::Striker(string name, int price) : RealPlayer(name, price)
{
}
