#include "RealPlayer.hpp"
#include <cmath>
float A(float x)
{
    if (x == 0 || x == 0.0)
    {
        return 0.0;
    }
    return (float)10 / ((float)1 + exp(((float)-1 * x) / (float)6));
}
double RealPlayer::calTotalScore(int weekNum, vector<bool> availableWeeks, string captainName)
{
    double score_sum = 0;
    for (int i = 0; i < NUM_OF_WEEKS; i++)
    {
        if (availableWeeks[i])
        {
            if (this->name == captainName)
            {
                score_sum = score_sum + A(2 * playerScore[i]);
            }
            else
            {
                score_sum = score_sum + (playerScore[i]);
            }
        }
    }
    return score_sum;
}
bool RealPlayer::isAvailable(int curWeek)
{
    for (int i = 2; i < 5; i++)
    {
        if (curWeek >= 4 && isinjuredThisWeek[curWeek - i]) // check last 3 weeks
        {
            return false;
        }
    }

    if (curWeek >= 2 && rCards[curWeek - 2] == true) // check if player had redcard last week
    {
        return false;
    }
    if (yCards >= 3)
    {
        return false;
    }
    return true;
}
double RealPlayer::calculateSeasonScore(int weekNum)
{
    if (allEqualToZero(playerScore, weekNum))
    {
        return 0.0;
    }
    return calcSum(playerScore, weekNum) / numOfPlayedGames(playerScore, weekNum);
}
void RealPlayer::updateScores(int week, double score)
{
    playerScore[week - 1] = score; // update with current weeks score
}
void RealPlayer::updateInjury(int weekNum)
{
    isinjuredThisWeek[weekNum - 1] = true; // update with current weeks injuries
}
RealPlayer::RealPlayer(string name_, int price)
{
    goals = vector<int>(NUM_OF_WEEKS, 0);
    ownGoals = vector<int>(NUM_OF_WEEKS, 0);
    assists = vector<int>(NUM_OF_WEEKS, 0);
    name = name_;
    yCards = 0;
    availableForThisWeek = true;
    isinjuredThisWeek = vector<bool>(NUM_OF_WEEKS, false);
    playerScore = vector<double>(NUM_OF_WEEKS, 0.0);
    rCards = vector<bool>(NUM_OF_WEEKS, false);
    this->price = price;
}
void RealPlayer::updateSuspension(bool suspend)
{
    if (suspend)
    {
        availableForThisWeek = false;
        yCards = 0;
    }
    else
    {
        availableForThisWeek = true;
    }
}
int RealPlayer::getAllGoals()
{
    int sum = 0;
    for (int i = 0; i < goals.size(); i++)
    {
        sum += goals[i];
    }
    return sum;
}
int RealPlayer::getAllAssists()
{
    int sum = 0;
    for (int i = 0; i < assists.size(); i++)
    {
        sum += assists[i];
    }
    return sum;
}