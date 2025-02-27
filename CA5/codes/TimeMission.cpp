#include "TimeMission.hpp"
#include "invalidArg.hpp"
TimeMission::TimeMission(int duTime, int missionId_, int startTime_,
                         int endTime_, int reward_)
    : Mission(missionId_, startTime_, endTime_, reward_)
{
    if (duTime < 0)
    {
        throw invalidArg();
    }
    missionDuration = duTime*60;
}
void TimeMission::completeMissionTasks(int sTime, int eTime, int distance)
{
    if ((this->startTime <= sTime) && (this->endTime >= eTime) && (completed == false))
    {
        missionDuration = missionDuration - (eTime - sTime);
        if (missionDuration <= 0)
        {
            et=eTime;
            completed = true;
        }
    }
}