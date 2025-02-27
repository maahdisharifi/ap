#include "DistanceMission.hpp"
#include "invalidArg.hpp"
DistanceMission::DistanceMission(int distance, int missionId_, int startTime_, int endTime_, int reward_)
    : Mission(missionId_, startTime_, endTime_, reward_)
{
    if (distance < 0)
    {
        throw invalidArg();
    }
    this->distance = distance;
}
void DistanceMission::completeMissionTasks(int sTime, int eTime, int distance)
{
    if ((this->startTime <= sTime) && (this->endTime >= eTime) && (completed == false))
    {
        this->distance = this->distance - distance;
        if (this->distance <= 0)
        {
            et=eTime;
            completed = true;
        }
    }
}