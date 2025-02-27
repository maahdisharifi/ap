#pragma once
#include "RealPlayer.hpp"
class Midfielder : public RealPlayer
{
public:
    string getPos() { return "Midfielder"; }
    Midfielder(string name, int price);
    void calPlayerScoreR2(int ga, int week);

private:
};
