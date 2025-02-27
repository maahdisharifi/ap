#include "mission.hpp"
#include "CountMission.hpp"
#include "Driver.hpp"
#include "TimeMission.hpp"
#include <iostream>
#include <string>
#include "DistanceMission.hpp"
#include "duplicationId.hpp"
#include "invalidArg.hpp"
using namespace std;

const string ADD_TIME_MISSION = "add_time_mission";
vector<string> splitInputByComma(string input)
{

    string word = "";
    vector<string> result;
    for (auto x : input)
    {
        if (x == ' ')
        {
            result.push_back(word);
            word = "";
        }
        else
        {
            word += x;
        }
    }
    result.push_back(word);

    return result;
}
void checkDup(vector<Mission *> &missions, int id);
Mission *findMission(int id, vector<Mission *> &missions)
{
    for (auto m : missions)
    {
        if (m->getMissionId() == id)
        {
            return m;
        }
    }
    cout << "MISSION_NOT_FOUND\n";
    return nullptr;
}
Driver *findDriver(int id, vector<Driver *> &drivers)
{
    // find driver if it dosent exit create one
    for (auto d : drivers)
    {
        if (id == d->getId())
        {
            return d;
        }
    }
    Driver *d = new Driver(id);
    drivers.push_back(d);
    return d;
}
Driver *findDri(int id, vector<Driver *> &drivers)
{
    for (auto d : drivers)
    {
        if (id == d->getId())
        {
            return d;
        }
    }
}
bool mypred(Mission *first, Mission *second)
{
    return first->getSortKey() < second->getSortKey();
}
bool checkEmptyVar(vector<string> splitedWords)
{
    for (int i = 0; i < splitedWords.size(); i++)
    {
        if (splitedWords[i] == "")
        {
            return true;
        }
    }
    return false;
}
void addCountMission(const vector<string> &splitedWords, vector<Mission *> &missions)
{
    try
    {
        int missionId = stoi(splitedWords[1]), startTime = stoi(splitedWords[2]), endTime = stoi(splitedWords[3]),
            count = stoi(splitedWords[4]), reward = stoi(splitedWords[5]);
        checkDup(missions, missionId);
        CountMission *cm = new CountMission(count, missionId, startTime, endTime, reward);
        missions.push_back(cm);
        cout << "OK\n";
    }
    catch (duplicationId &er)
    {
        er.what();
    }
    catch (invalidArg &er)
    {
        er.what();
    }
}
void addTimeMission(const vector<string> &splitedWords, vector<Mission *> &missions)
{
    try
    {
        int missionId = stoi(splitedWords[1]), startTime = stoi(splitedWords[2]), endTime = stoi(splitedWords[3]), missionDu = stoi(splitedWords[4]), reward = stoi(splitedWords[5]);
        checkDup(missions, missionId);
        TimeMission *tm = new TimeMission(missionDu, missionId, startTime, endTime, reward);
        missions.push_back(tm);
        cout << "OK\n";
    }
    catch (duplicationId &er)
    {
        er.what();
    }
    catch (invalidArg &er)
    {
        er.what();
    }
}
void addDistanceMission(const vector<string> &splitedWords, vector<Mission *> &missions)
{
    try
    {
        int missionId = stoi(splitedWords[1]), startTime = stoi(splitedWords[2]), endTime = stoi(splitedWords[3]),
            distance = stoi(splitedWords[4]), reward = stoi(splitedWords[5]);
        checkDup(missions, missionId);
        DistanceMission *dm = new DistanceMission(distance, missionId, startTime, endTime, reward);
        missions.push_back(dm);
        cout << "OK\n";
    }
    catch (duplicationId &er)
    {
        er.what();
    }
    catch (invalidArg &er)
    {
        er.what();
    }
}
void handleUserInput(string line, vector<Mission *> &missions, vector<Driver *> &drivers)
{
    vector<string> splitedWords = splitInputByComma(line);
    if (checkEmptyVar(splitedWords) == true)
    {
        cout << "INVALID_ARGUMENTS\n";
        return;
    }
    if (splitedWords[0] == ADD_TIME_MISSION)
    {
        addTimeMission(splitedWords, missions);
    }
    else if (splitedWords[0] == "add_distance_mission")
    {
        addDistanceMission(splitedWords, missions);
    }
    else if (splitedWords[0] == "add_count_mission")
    {
        addCountMission(splitedWords, missions);
    }
    else if (splitedWords[0] == "assign_mission")
    {
        int missionId = stoi(splitedWords[1]), driverId = stoi(splitedWords[2]);
        Mission *m = findMission(missionId, missions);
        if (m == nullptr)
        {
            return;
        }
        Driver *d = findDriver(driverId, drivers);
        d->assignMission(m);
    }
    else if (splitedWords[0] == "record_ride")
    {
        int sTime = stoi(splitedWords[1]), eTime = stoi(splitedWords[2]), driverId = stoi(splitedWords[3]),
            distance = stoi(splitedWords[4]);
        Driver *d = findDriver(driverId, drivers);

        if (d == nullptr || (d->isDriversMissionsEmpty()) == true)
        {
            return;
        }
        if (sTime > eTime)
        {
            cout << "INVALID_ARGUMENTS\n";
            return;
        }
        vector<Mission *> &Dmissions = d->getMission();
        sort(Dmissions.begin(), Dmissions.end(), mypred);
        d->completeDriverMissions(sTime, eTime, distance);
    }
    else if (splitedWords[0] == "show_missions_status")
    {
        int driverId = stoi(splitedWords[1]);
        Driver *d = findDri(driverId, drivers);
        if (d->isDriversMissionsEmpty() == true)
        {
            cout << "DRIVER_MISSION_NOT_FOUND\n";
        }
        vector<Mission *> &Dmissions = d->getMission();
        sort(Dmissions.begin(), Dmissions.end(), mypred);
        d->printAllMissionInfo();
    }
}
void checkDup(vector<Mission *> &missions, int id)
{
    for (auto m : missions)
    {
        if (m->isDuplicate(id))
        {
            throw duplicationId();
        }
    }
}
int main()
{
    vector<Mission *> missions;
    vector<Driver *> drivers;
    string line;
    while (getline(cin, line))
    {
        handleUserInput(line, missions, drivers);
    }
    return 0;
}