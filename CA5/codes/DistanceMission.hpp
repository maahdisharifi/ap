#ifndef __DistanceMission_H__
#define __DistanceMission_H__
#include "mission.hpp"
class DistanceMission : public Mission
{
public:
DistanceMission(int,int,int,int,int);
void completeMissionTasks(int sTime,int eTime,int distance);
private:
    int distance;
};

#endif