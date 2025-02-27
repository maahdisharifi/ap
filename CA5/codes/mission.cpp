#include "mission.hpp"
#include <stdexcept>
#include "invalidArg.hpp"
#include <iostream>
using namespace std;
Mission::Mission(int id, int startTime, int endTime, int reward)
{
    if (startTime > endTime || startTime < 0 || endTime < 0 || reward < 0)
    {
        throw invalidArg();
    }
    missionId = id;
    this->startTime = startTime;
    this->endTime = endTime;
    this->reward = reward;
    completed = false;
    isShown = false;
}
void Mission::showed()
{
    isShown = true;
}
bool Mission::isDuplicate(int id)
{
    if (missionId == id)
    {
        return true;
    }
    return false;
}
void Mission::printCompletedMission()
{
    cout << "mission: " << missionId << endl;
    cout << "start timestamp: " << startTime << endl;
    cout << "end timestamp: " << et<< endl;
    cout << "reward: " << reward << endl;
}
void Mission::printAllInfo()
{
    cout << "mission " << missionId << ":" << endl;
    cout << "start timestamp: " << startTime << endl;
    if (completed == true)
    {
        cout << "end timestamp: "
             << et << endl;
        cout << "reward: " << reward << endl;
        cout << "status: completed\n";
    }
    else
    {
        cout << "end timestamp: " << -1 << endl;
        cout << "reward: " << reward << endl;
        cout << "status: ongoing\n";
    }
    
}