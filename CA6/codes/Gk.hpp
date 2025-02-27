#pragma once
#include "RealPlayer.hpp"
class GoalKeeper : public RealPlayer
{
public:
    GoalKeeper(string name, int price);
    string getPos() { return "GoalKeeper"; }
    void calPlayerScoreR2(int ga, int week);

private:
};
