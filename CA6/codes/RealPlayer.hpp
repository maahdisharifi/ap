#pragma once
#include <vector>
#include <string>
#include "funcs.hpp"
using namespace std;
const int NUM_OF_WEEKS = 19;
class RealPlayer
{
public:
    RealPlayer(string name_, int price);
    int getNumOfGoals(int week) { return goals[week - 1]; }
    string getName() { return name; }
    void updateInjury(int weekNum);
    void updateYCards() { yCards++; }
    void updateRCards(int curWeek) { rCards[curWeek - 1] = true; }
    void updateScores(int week, double score);
    double getScore(int weekNum) { return playerScore[weekNum - 1]; }
    virtual string getPos() = 0;
    double calculateSeasonScore(int weekNum);
    bool isAvailable(int curWeek);
    void decreaseScore(int week, int goalSum) { playerScore[week - 1] -= goalSum; }
    void updateSuspension(bool suspend);
    bool isAvailableForThisWeek() { return availableForThisWeek; }
    double calTotalScore(int weekNum, vector<bool> availableWeeks, string captainName);
    void ownGoal(int week) { ownGoals[week - 1]++; }
    void goal(int week) { this->goals[week - 1]++; }
    void assist(int week) { this->assists[week - 1]++; }
    int get_price() { return price; }
    void win(int week) { playerScore[week - 1] += 5; }
    void lose(int week) { playerScore[week - 1]--; }
    void draw(int week) { playerScore[week - 1]++; }
    virtual void calPlayerScoreR2(int ga, int week) = 0;
    void calFunA(int week) { playerScore[week - 1] = A(playerScore[week - 1]); }
    int getAllGoals();
    int getAllAssists();
protected:
    string name;
    vector<double> playerScore;
    int yCards;
    bool availableForThisWeek;
    vector<bool> rCards;
    vector<bool> isinjuredThisWeek;
    vector<int> ownGoals; // owngoal[0]=2
    vector<int> goals;
    vector<int> assists;
    int price;
};
