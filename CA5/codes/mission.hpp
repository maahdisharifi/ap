#ifndef __MISSION_H__
#define __MISSION_H__

class Mission
{
public:
    Mission(int, int, int, int);
    int getSortKey() { return startTime; }
    bool isDuplicate(int id);
    int getMissionId() { return missionId; }
    bool isCompleted() { return completed; }
    virtual void completeMissionTasks(int sTime, int eTime, int distance) = 0;
    void printCompletedMission();
    bool getIsShown() { return isShown; }
    void showed();
    void printAllInfo();

protected:
    int et;
    int missionId;
    int startTime;
    int endTime;
    int reward;
    bool completed;
    bool isShown;
};

#endif