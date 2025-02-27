#ifndef __CountMission_H__
#define __CountMission_H__
#include "mission.hpp"
class CountMission : public Mission
{
public:
   CountMission(int,int,int,int,int);
   void completeMissionTasks(int sTime,int eTime,int distance);
private:
    int count;
};

#endif