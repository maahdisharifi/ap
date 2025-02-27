#include "Df.hpp"
Defender::Defender(string name, int price) : RealPlayer(name, price)
{
}
void Defender::calPlayerScoreR2(int ga, int week)
{
    if (ga == 0)
    {
        playerScore[week - 1] += 2;
    }

    playerScore[week - 1] += 4 * goals[week - 1];

    playerScore[week - 1] += 3 * assists[week - 1];

    playerScore[week - 1] -= 3 * ownGoals[week - 1];
    playerScore[week - 1] += 1;
}