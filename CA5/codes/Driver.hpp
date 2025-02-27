#ifndef __Driver_H__
#define __Driver_H__

#include "mission.hpp"
#include <vector>
#include <algorithm>
// bool mypred(Mission *first, Mission *second);
class Driver
{
private:
    int driverId;
    std::vector<Mission *> missions;

public:
    Driver(int);
    int getId() { return driverId; }
    void assignMission(Mission *m);
    bool isDriversMissionsEmpty();
    void completeDriverMissions(int sTime, int eTime, int distance);
    void printCompletedMissions();
    std::vector<Mission *> &getMission() { return missions; }
    void printAllMissionInfo();
};
#endif