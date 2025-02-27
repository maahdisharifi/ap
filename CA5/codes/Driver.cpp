#include "Driver.hpp"
#include <iostream>
Driver::Driver(int id)
{
    driverId = id;
}
void Driver::assignMission(Mission *m)
{
    for (int i = 0; i < missions.size(); i++)
    {
        if (m->getMissionId() == missions[i]->getMissionId())
        {
            std::cout << "DUPLICATE_DRIVER_MISSION\n";
            return;
        }
    }
    std::cout << "OK\n";
    missions.push_back(m);
}
bool Driver::isDriversMissionsEmpty()
{
    if (missions.empty())
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Driver::printCompletedMissions()
{
    Mission *last;

    for (auto m : missions)
    {
        if (((m->isCompleted()) == true) && ((m->getIsShown()) == false))
        {
            last = m;
        }
    }
    std::cout << "completed missions for driver " << driverId << ":\n";
    for (int i = 0; i < missions.size(); i++)
    {
        if (((missions[i]->isCompleted()) == true) && ((missions[i]->getIsShown()) == false))
        {
            missions[i]->printCompletedMission();
            missions[i]->showed();
            if (missions[i] != last)
            {
                std::cout << "\n";
            }
        }
    }
}
void Driver::completeDriverMissions(int sTime, int eTime, int distance)
{
    for (auto m : missions)
    {
        m->completeMissionTasks(sTime, eTime, distance);
    }

    this->printCompletedMissions();
}
void Driver::printAllMissionInfo()
{
    std::cout << "missions status for driver " << driverId << ":\n";
    for (auto m : missions)
    {
        m->printAllInfo();
        if (m != missions.back())
        {
            std::cout << "\n";
        }
    }
}