#pragma once
#include "RealPlayer.hpp"
class Striker : public RealPlayer
{
public:
    string getPos() { return "Forward"; }
    Striker(string name, int price);
    void calPlayerScoreR2(int ga, int week);

private:
};

