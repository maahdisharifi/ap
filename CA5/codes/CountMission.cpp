#include "CountMission.hpp"
#include "invalidArg.hpp"
CountMission::CountMission(int count, int missionId_, int startTime_, int endTime_, int reward_)
    : Mission(missionId_, startTime_, endTime_, reward_)
{
    if (count < 0)
    {
        throw invalidArg();
    }
    this->count = count;
}
void CountMission::completeMissionTasks(int sTime, int eTime, int distance)
{
    if (this->startTime<sTime &&this->endTime> eTime&&completed==false)
    {
        count--;
        if (count <= 0)
        {
            et=eTime;
            completed = true;
        }
    }
}