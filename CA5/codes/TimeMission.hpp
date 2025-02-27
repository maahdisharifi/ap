#ifndef __TimeMission_H__
#define __TimeMission_H__

#include "mission.hpp"

class TimeMission : public Mission
{
public:
    TimeMission(int, int, int, int, int);
    bool isDuplicate(int id);
    void completeMissionTasks(int sTime, int eTime, int distance);

private:
    int missionDuration;
};

#endif