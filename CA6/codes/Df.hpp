#pragma once
#include "RealPlayer.hpp"
class Defender : public RealPlayer
{
public:
    string getPos() { return "Defender"; }
    Defender(string name, int price);
    void calPlayerScoreR2(int ga, int week);

private:
};

