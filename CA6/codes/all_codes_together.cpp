#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
const int NUM_OF_WEEKS = 19;

struct error
{
    string Bad_Request = "Bad Request\n";
    string Permission_Denied = "Permission Denied\n";
    string Not_Found = "Not Found\n";
    string Empty = "Empty\n";
};
const error err;
float A(float x)
{
    if (x == 0 || x == 0.0)
    {
        return 0.0;
    }
    return (float)10 / ((float)1 + exp(((float)-1 * x) / (float)6));
}
string findPlayerName(const vector<string> &words)
{
    string playerName;
    if (words.size() == 5)
    {
        return words[4];
    }
    else
    {
        for (int i = 4; i < words.size(); i++)
        {
            playerName += words[i] + " ";
        }
        playerName.pop_back();
        return playerName;
    }
}

class Admin
{
public:
    Admin();
    bool isLoggedIn() { return loginStatus; }
    bool registerAdmin(string userName, string passWord);
    void logout() { loginStatus = false; }
    void OpenTransferWindow() { transferWindowStatus = true; }
    void CloseTransferWindow() { transferWindowStatus = false; }
    bool GetTransferWindowStatus() { return transferWindowStatus; }

private:
    string username;
    string passwrod;
    bool loginStatus;
    int curWeek;
    bool transferWindowStatus;
};
bool Admin::registerAdmin(string userName, string passWord)
{
    if (this->passwrod == passWord && this->username == userName)
    {
        loginStatus = true;
        cout << "OK\n";
        return true;
    }
    else
    {
        cerr << err.Bad_Request;
        return false;
    }
}
Admin::Admin()
{
    username = "admin";
    transferWindowStatus = false;
    passwrod = "123456";
    loginStatus = false;
    curWeek = 0;
}

class RealPlayer
{
public:
    RealPlayer(string name_, int price);
    int getNumOfGoals(int week) { return goals[week - 1]; }
    string getName() { return name; }
    void updateInjury(int weekNum);
    void updateYCards() { yCards++; }
    void updateRCards(int curWeek) { rCards[curWeek - 1] = true; }
    void updateScores(int week, double score);
    double getScore(int weekNum) { return playerScore[weekNum - 1]; }
    virtual string getPos() = 0;
    double calculateSeasonScore(int weekNum);
    bool isAvailable(int curWeek);
    void decreaseScore(int week, int goalSum) { playerScore[week - 1] -= goalSum; }
    void updateSuspension(bool suspend)
    {
        if (suspend)
        {
            availableForThisWeek = false;
            yCards = 0;
        }
        else
        {
            availableForThisWeek = true;
        }
    }
    bool isAvailableForThisWeek() { return availableForThisWeek; }
    double calTotalScore(int weekNum, vector<bool> availableWeeks, string captainName);
    void ownGoal(int week) { ownGoals[week - 1]++; }
    void goal(int week) { this->goals[week - 1]++; }
    void assist(int week) { this->assists[week - 1]++; }
    int get_price() { return price; }
    void win(int week) { playerScore[week - 1] += 5; }
    void lose(int week) { playerScore[week - 1]--; }
    void draw(int week) { playerScore[week - 1]++; }
    virtual void calPlayerScoreR2(int ga, int week) = 0;
    void calFunA(int week) { playerScore[week - 1] = A(playerScore[week - 1]); }
    int getAllGoals();
    int getAllAssists();

protected:
    string name;
    vector<double> playerScore;
    int yCards;
    bool availableForThisWeek;
    vector<bool> rCards;
    vector<bool> isinjuredThisWeek;
    vector<int> ownGoals; // owngoal[0]=2
    vector<int> goals;
    vector<int> assists;
    int price;
};
int RealPlayer::getAllGoals()
{
    int sum = 0;
    for (int i = 0; i < goals.size(); i++)
    {
        sum += goals[i];
    }
    return sum;
}
int RealPlayer::getAllAssists()
{
    int sum = 0;
    for (int i = 0; i < assists.size(); i++)
    {
        sum += assists[i];
    }
    return sum;
}

RealPlayer *findPlayer(const vector<RealPlayer *> &realPlayers, string name)
{
    for (auto p : realPlayers)
    {
        if (p->getName() == name)
        {
            return p;
        }
    }
    return nullptr;
}
double RealPlayer::calTotalScore(int weekNum, vector<bool> availableWeeks, string captainName)
{
    double score_sum = 0;
    for (int i = 0; i < NUM_OF_WEEKS; i++)
    {
        if (availableWeeks[i])
        {
            if (this->name == captainName)
            {
                score_sum = score_sum + A(2 * playerScore[i]);
            }
            else
            {
                score_sum = score_sum + (playerScore[i]);
            }
        }
    }
    return score_sum;
}
bool RealPlayer::isAvailable(int curWeek)
{
    for (int i = 2; i < 5; i++)
    {
        if (curWeek >= 4 && isinjuredThisWeek[curWeek - i]) // check last 3 weeks
        {
            return false;
        }
    }

    if (curWeek >= 2 && rCards[curWeek - 2] == true) // check if player had redcard last week
    {
        return false;
    }
    if (yCards >= 3)
    {
        return false;
    }
    return true;
}
bool allEqualToZero(std::vector<double> const &v, int weekNum)
{
    for (int i = 0; i < weekNum; i++)
    {
        if (v[i] != 0.0)
        {
            return false;
        }
    }
    return true;
}
double calcSum(vector<double> const &v, int weekNum)
{
    double sum = 0.0;
    for (int i = 0; i < weekNum; i++)
    {
        sum += v[i];
    }
    return sum;
}
int numOfPlayedGames(vector<double> const &v, int weekNum)
{
    int count = 0;
    for (int i = 0; i < weekNum; i++)
    {
        if (v[i] != 0.0)
        {
            count++;
        }
    }
    return count;
}
double RealPlayer::calculateSeasonScore(int weekNum)
{
    if (allEqualToZero(playerScore, weekNum))
    {
        return 0.0;
    }
    return calcSum(playerScore, weekNum) / numOfPlayedGames(playerScore, weekNum);
}
void RealPlayer::updateScores(int week, double score)
{
    playerScore[week - 1] = score; // update with current weeks score
}
void RealPlayer::updateInjury(int weekNum)
{
    isinjuredThisWeek[weekNum - 1] = true; // update with current weeks injuries
}
RealPlayer::RealPlayer(string name_, int price)
{
    goals = vector<int>(NUM_OF_WEEKS, 0);
    ownGoals = vector<int>(NUM_OF_WEEKS, 0);
    assists = vector<int>(NUM_OF_WEEKS, 0);
    name = name_;
    yCards = 0;
    availableForThisWeek = true;
    isinjuredThisWeek = vector<bool>(NUM_OF_WEEKS, false);
    playerScore = vector<double>(NUM_OF_WEEKS, 0.0);
    rCards = vector<bool>(NUM_OF_WEEKS, false);
    this->price = price;
}
struct cmp
{
    cmp(int weekNum) { this->weekNum = weekNum; }
    bool operator()(RealPlayer *first, RealPlayer *second)
    {
        return first->getScore(weekNum) > second->getScore(weekNum);
    }
    int weekNum;
};
class GoalKeeper : public RealPlayer
{
public:
    GoalKeeper(string name, int price);
    string getPos() { return "GoalKeeper"; }
    void calPlayerScoreR2(int ga, int week);

private:
};
////////////////////
GoalKeeper::GoalKeeper(string name, int price) : RealPlayer(name, price)
{
}
void GoalKeeper::calPlayerScoreR2(int ga, int week)
{
    if (ga == 0)
    {
        this->playerScore[week - 1] += 5;
    }
    else
    {
        playerScore[week - 1] -= ga;
    }
    playerScore[week - 1] += 3;
}
class Defender : public RealPlayer
{
public:
    string getPos() { return "Defender"; }
    Defender(string name, int price);
    void calPlayerScoreR2(int ga, int week);

private:
};
void Defender::calPlayerScoreR2(int ga, int week)
{
    if (ga == 0)
    {
        playerScore[week - 1] += 2;
    }

    playerScore[week - 1] += 4 * goals[week - 1];

    playerScore[week - 1] += 3 * assists[week - 1];

    playerScore[week - 1] -= 3 * ownGoals[week - 1];
    playerScore[week - 1] += 1;
}

Defender::Defender(string name, int price) : RealPlayer(name, price)
{
}
class Midfielder : public RealPlayer
{
public:
    string getPos() { return "Midfielder"; }
    Midfielder(string name, int price);
    void calPlayerScoreR2(int ga, int week);

private:
};
void Midfielder::calPlayerScoreR2(int ga, int week)
{
    if (ga == 0)
    {
        playerScore[week - 1]++;
    }
    playerScore[week - 1] += 3 * goals[week - 1] + 2 * assists[week - 1];
    playerScore[week - 1] -= 3 * ownGoals[week - 1];
}
Midfielder::Midfielder(string name, int price) : RealPlayer(name, price)
{
}
class Striker : public RealPlayer
{
public:
    string getPos() { return "Forward"; }
    Striker(string name, int price);
    void calPlayerScoreR2(int ga, int week);

private:
};
void Striker::calPlayerScoreR2(int ga, int week)
{
    if (goals[week - 1] == 0)
    {
        playerScore[week - 1]--;
    }
    playerScore[week - 1] += 3 * goals[week - 1] + assists[week - 1];
    playerScore[week - 1] -= 3 * ownGoals[week - 1];
}
Striker::Striker(string name, int price) : RealPlayer(name, price)
{
}

class FFPlayer
{
public:
    FFPlayer(string TeamName_, string passWord_);
    bool checkNameDup(string name_)
    {
        if (TeamName == name_)
        {
            cout << "Bad Request\n";
            return true;
        }
        return false;
    }
    void updateFfpAvailableWeeks(int weekNum);
    bool checkPassword(string pass)
    {
        if (pass == passWord)
        {
            return true;
        }
        return false;
    }
    string getTeamName() { return TeamName; }
    void loginUser() { loginStatus = true; }
    void logoutUser() { loginStatus = false; }
    bool getLoginStatus() { return loginStatus; }
    bool addPlayer(RealPlayer *rpp);
    bool isCompleted();
    int getNumOfSoldPlayers() { return numOfSoldPlayers; }
    bool sellPlayer(string playerName, bool isCompleted, vector<RealPlayer *> realPlayers);
    void resetNumOFSoldPlayers() { numOfSoldPlayers = 0; }
    void print_squad();
    double calcTeamTotalScore(int weekNum, vector<bool> availableWeeks)
    {

        if (this->isCompleted())
        {
            points = gk->calTotalScore(weekNum, availableWeeks, captainName) + df1->calTotalScore(weekNum, availableWeeks, captainName) +
                     df2->calTotalScore(weekNum, availableWeeks, captainName) + md->calTotalScore(weekNum, availableWeeks, captainName) +
                     st->calTotalScore(weekNum, availableWeeks, captainName);
        }
    }
    int getTotalTeamScore() { return points; }
    vector<bool> getAvailableWeeks() { return availableWeeks; }
    void setCaptain(string playerName);
    void show_team_budget() { cout << this->budget << endl; }
    int get_budget() { return budget; }
    void set_new_budget(int new_budget) { budget = new_budget; }
    int totalCost() { return (gk->get_price() + df1->get_price() + df2->get_price() + md->get_price() + st->get_price()); }

private:
    string TeamName;
    string passWord;
    bool loginStatus;
    double points;
    int numOfSoldPlayers;
    RealPlayer *gk;
    RealPlayer *df1;
    RealPlayer *df2;
    RealPlayer *md;
    RealPlayer *st;
    vector<bool> availableWeeks;
    string captainName;
    int budget;
};
void FFPlayer::setCaptain(string playerName)
{
    if (st->getName() != playerName && gk->getName() != playerName && df1->getName() != playerName && df2->getName() != playerName && md->getName() != playerName)
    {
        cerr << err.Not_Found;
    }
    else
    {
        captainName = playerName;
        cout << "OK\n";
    }
}
void FFPlayer::updateFfpAvailableWeeks(int weekNum)
{
    if (this->isCompleted())
    {
        this->availableWeeks[weekNum - 1] = true;
    }
    else
    {
        this->availableWeeks[weekNum - 1] = false;
    }
}
bool cmpNames(RealPlayer *first, RealPlayer *second)
{
    return (first->getName() < second->getName());
}
void FFPlayer::print_squad()
{

    cout << "fantasy team: " << TeamName << endl;
    if (captainName == gk->getName())
    {
        cout << "Goalkeeper: " << gk->getName() << " (CAPTAIN)" << endl;
    }
    else
    {
        cout << "Goalkeeper: " << gk->getName() << endl;
    }
    if (cmpNames(df1, df2))
    {
        if (df1->getName() == captainName)
        {
            cout << "Defender1: " << df1->getName() << " (CAPTAIN)" << endl;
        }
        else
        {
            cout << "Defender1: " << df1->getName() << endl;
        }
        if (df2->getName() == captainName)
        {
            cout << "Defender2: " << df2->getName() << " (CAPTAIN)" << endl;
        }
        else
        {
            cout << "Defender2: " << df2->getName() << endl;
        }
    }
    else
    {
        if (df2->getName() == captainName)
        {
            cout << "Defender1: " << df2->getName() << " (CAPTAIN)" << endl;
        }
        else
        {
            cout << "Defender1: " << df2->getName() << endl;
        }
        if (df1->getName() == captainName)
        {
            cout << "Defender2: " << df1->getName() << " (CAPTAIN)" << endl;
        }
        else
        {
            cout << "Defender2: " << df1->getName() << endl;
        }
    }
    if (captainName == md->getName())
    {
        cout << "Midfielder: " << md->getName() << " (CAPTAIN)" << endl;
    }
    else
    {
        cout << "Midfielder: " << md->getName() << endl;
    }
    if (captainName == st->getName())
    {
        cout << "Striker: " << st->getName() << " (CAPTAIN)" << endl;
    }
    else
    {
        cout << "Striker: " << st->getName() << endl;
    }
}
bool FFPlayer::sellPlayer(string playerName, bool completed, vector<RealPlayer *> realPlayers)
{
    if ((gk != nullptr) && gk->getName() == playerName)
    {
        RealPlayer *rpp = findPlayer(realPlayers, playerName);
        this->set_new_budget(this->get_budget() + rpp->get_price());
        if (playerName == captainName)
        {
            captainName = "";
        }
        gk = nullptr;
    }
    else if ((df1 != nullptr) && df1->getName() == playerName)
    {
        RealPlayer *rpp = findPlayer(realPlayers, playerName);
        this->set_new_budget(this->get_budget() + rpp->get_price());
        if (playerName == captainName)
        {
            captainName = "";
        }
        df1 = nullptr;
    }
    else if ((df2 != nullptr) && df2->getName() == playerName)
    {
        RealPlayer *rpp = findPlayer(realPlayers, playerName);
        this->set_new_budget(this->get_budget() + rpp->get_price());
        if (playerName == captainName)
        {
            captainName = "";
        }
        df2 = nullptr;
    }
    else if (md->getName() == playerName)
    {
        RealPlayer *rpp = findPlayer(realPlayers, playerName);
        this->set_new_budget(this->get_budget() + rpp->get_price());
        if (playerName == captainName)
        {
            captainName = "";
        }
        md = nullptr;
    }
    else if ((st != nullptr) && st->getName() == playerName)
    {
        RealPlayer *rpp = findPlayer(realPlayers, playerName);
        this->set_new_budget(this->get_budget() + rpp->get_price());
        if (playerName == captainName)
        {
            captainName = "";
        }
        st = nullptr;
    }
    else
    {
        cerr << err.Not_Found;
        return false;
    }
    if (completed)
    {
        numOfSoldPlayers++;
    }
    cout << "OK\n";
    return true;
}
bool FFPlayer::isCompleted()
{
    if (gk == nullptr || df1 == nullptr || df2 == nullptr || md == nullptr || st == nullptr)
    {
        return false;
    }
    return true;
}
bool FFPlayer::addPlayer(RealPlayer *rpp)
{
    if (rpp->getPos() == "GoalKeeper")
    {
        if (gk != nullptr)
        {
            cerr << err.Bad_Request;
            return false;
        }
        else
        {
            gk = rpp;
            return true;
        }
    }
    if (rpp->getPos() == "Midfielder")
    {
        if (md != nullptr)
        {
            cerr << err.Bad_Request;
            return false;
        }
        else
        {
            md = rpp;
            return true;
        }
    }
    if (rpp->getPos() == "Forward")
    {
        if (st != nullptr)
        {
            cerr << err.Bad_Request;
            return false;
        }
        else
        {
            st = rpp;
            return true;
        }
    }
    if (rpp->getPos() == "Defender")
    {
        if (df1 != nullptr && df2 != nullptr)
        {
            cerr << err.Bad_Request;
            return false;
            ;
        }
        if (df1 != nullptr && df2 == nullptr)
        {
            df2 = rpp;
            return true;
        }
        if (df1 == nullptr && df2 != nullptr)
        {
            df1 = rpp;
            return true;
        }
        if (df1 == nullptr && df2 == nullptr)
        {
            df1 = rpp;
            return true;
        }
    }
}
FFPlayer::FFPlayer(string TeamName_, string passWord_)
{
    TeamName = TeamName_;
    passWord = passWord_;
    loginStatus = false;
    points = 0;
    gk = nullptr;
    df1 = nullptr;
    df2 = nullptr;
    md = nullptr;
    st = nullptr;
    numOfSoldPlayers = 0;
    availableWeeks = vector<bool>(NUM_OF_WEEKS, false);
    budget = 2500;
}
class RealTeam
{
public:
    RealTeam(string name, vector<RealPlayer *> players);
    void updateGAandGF(int gf, int ga);
    string getName() { return name; };
    void win() { score += 3; }
    void draw() { score++; }
    friend void sortRealTeams(vector<RealTeam *> &realTeams);
    void printPlayersInfo(bool rankSorting, string positon, int weekNum);
    void printTeamInfo();
    void addCleanSheet(int week);
    int numOfCleensheet();

private:
    string name;
    vector<RealPlayer *> players;
    int ga;
    int gf;
    int score;
    vector<bool> cleansheets;
};
int RealTeam::numOfCleensheet()
{
    int count = 0;
    for (auto cleensheet : cleansheets)
    {
        if (cleensheet)
        {
            count++;
        }
    }
    return count;
}
void RealTeam::addCleanSheet(int week)
{
    cleansheets[week - 1] = true;
}
void RealTeam::printTeamInfo()
{
    cout << name << ": "
         << "score: " << score << " | "
         << "GF: " << gf << " | "
         << "GA: " << ga << endl;
}
struct cmpScore
{
    int weekNum;
    cmpScore(int weekNum) { this->weekNum = weekNum; }
    bool operator()(RealPlayer *first, RealPlayer *second)
    {
        // logic uses paramA in some way...
        return first->calculateSeasonScore(weekNum) > second->calculateSeasonScore(weekNum);
    }
};
void printPlayerInfo(RealTeam *team, RealPlayer *p, int weekNum, int &count)
{
    if (p->getPos() == "GoalKeeper")
    {
        cout << fixed;
        cout << setprecision(1);
        cout << count << ". "
             << "name: " << p->getName() << " | "
             << "role: " << p->getPos() << " | "
             << "score: " << p->calculateSeasonScore(weekNum) << " | "
             << "cost: " << p->get_price() << " | "
             << "clean sheets: " << team->numOfCleensheet() << endl;
    }
    else if (p->getPos() == "Defender")
    {
        cout << fixed;
        cout << setprecision(1);
        cout << count << ". "
             << "name: " << p->getName() << " | "
             << "role: " << p->getPos() << " | "
             << "score: " << p->calculateSeasonScore(weekNum) << " | "
             << "cost: " << p->get_price() << " | "
             << "goals: " << p->getAllGoals() << " | "
             << "assists: " << p->getAllAssists() << " | "
             << "clean sheets: " << team->numOfCleensheet() << endl;
    }
    else if (p->getPos() == "Midfielder")
    {
        cout << fixed;
        cout << setprecision(1);
        cout << count << ". "
             << "name: " << p->getName() << " | "
             << "role: " << p->getPos() << " | "
             << "score: " << p->calculateSeasonScore(weekNum) << " | "
             << "cost: " << p->get_price() << " | "
             << "goals: " << p->getAllGoals() << " | "
             << "assists: " << p->getAllAssists() << " | "
             << "clean sheets: " << team->numOfCleensheet() << endl;
    }
    else if (p->getPos() == "Forward")
    {
        cout << fixed;
        cout << setprecision(1);
        cout << count << ". "
             << "name: " << p->getName() << " | "
             << "role: " << p->getPos() << " | "
             << "score: " << p->calculateSeasonScore(weekNum) << " | "
             << "cost: " << p->get_price() << " | "
             << "goals: " << p->getAllGoals() << " | "
             << "assists: " << p->getAllAssists() << endl;
    }
    count++;
}
void RealTeam::printPlayersInfo(bool rankSorting, string positon, int weekNum)
{
    cout << "list of players:\n";
    int count = 1;
    if (rankSorting == false && positon == "")
    {
        sort(this->players.begin(), this->players.end(), cmpNames);
        for (auto p : players)
        {
            printPlayerInfo(this, p, weekNum, count);
        }
    }
    else if (rankSorting == false && positon != "")
    {
        sort(this->players.begin(), this->players.end(), cmpNames);
        if (positon == "gk")
        {
            for (auto p : players)
            {
                if (p->getPos() == "GoalKeeper")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "df")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Defender")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "md")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Midfielder")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "fw")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Forward")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
    }

    else if (rankSorting == true && positon == "")
    {
        sort(players.begin(), players.end(), cmpScore(weekNum));
        for (auto p : players)
        {
            // 1. name: <name> | role: <role> | score: <score>
            printPlayerInfo(this, p, weekNum, count);
        }
    }
    else if (rankSorting == true && positon != "")
    {
        sort(players.begin(), players.end(), cmpScore(weekNum));
        if (positon == "gk")
        {
            for (auto p : players)
            {
                if (p->getPos() == "GoalKeeper")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "df")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Defender")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "md")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Midfielder")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
        else if (positon == "fw")
        {
            for (auto p : players)
            {
                if (p->getPos() == "Forward")
                {
                    printPlayerInfo(this, p, weekNum, count);
                }
            }
        }
    }
    else
    {
        cerr << err.Bad_Request;
    }
}
bool input_is_valid(vector<string> words, int curWeek)
{
    if ((words[0] != "POST" && words[0] != "GET" && words[0] != "PUT" && words[0] != "DELETE") || words.size() == 1)
    {
        cerr << err.Bad_Request;
        return false;
    }
    if (words[1] == "team_of_the_week")
    {
        if (words[0] != "GET")
        {
            cerr << err.Not_Found;
            return false;
        }
        if ((words.size() != 3 || words.size() != 5) || words[2] != "?" ||
            stoi(words[4]) <= 0 && stoi(words[4]) > 19 && stoi(words[4]) > curWeek)
        {
            cerr << err.Bad_Request;
            return false;
        }
        if (words.size() == 3)
        {
            return true;
        }
        if (words.size() == 5 && (words[3] == "weeknum" || words[3] == "week") && stoi(words[4]) > 0 && stoi(words[4]) <= 19 && stoi(words[4]) <= curWeek)
        {
            return true;
        }
        cerr << err.Bad_Request;
        return false;
    }
    if (words[1] == "players")
    {
        if (words[0] != "GET")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() > 7 || words.size() < 5 || words[2] != "?" || (words[3] != "team" || words[3] != "team_name"))
        {
            cerr << err.Bad_Request;
            return false;
        }
        return true;
    }
    if (words[1] == "league_standings")
    {
        if (words[0] != "GET")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() >= 2)
        {
            cerr << err.Bad_Request;
            return false;
        }
        return true;
    }
    if (words[1] == "user_ranking")
    {
        if (words[0] != "GET")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() >= 2)
        {
            cerr << err.Bad_Request;
            return false;
        }
        return true;
    }
    if (words[1] == "matches_result_league")
    {
        if (words[0] != "GET")
        {
            cerr << err.Not_Found;
            return false;
        }
        if ((words.size() == 3) && words[2] == "?")
        {
            return true;
        }
        if (words.size() == 5 && words[2] == "?" && (words[3] == "week_num" || words[3] == "week") && stoi(words[4]) > 0 && stoi(words[4]) <= 19 && stoi(words[4]) <= curWeek)
        {
            return true;
        }
        cerr << err.Bad_Request;
        return false;
    }
    if (words[1] == "signup")
    {
        if (words[0] != "POST")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() == 7 && words[2] == "?" && words[3] == "team_name" && words[5] == "password")
        {
            return true;
        }
        cerr << err.Bad_Request;
        return false;
    }
    if (words[1] == "login")
    {
        if (words[0] != "POST")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() == 7 && words[2] == "?" && words[3] == "team_name" && words[5] == "password")
        {
            return true;
        }
        cerr << err.Bad_Request;
        return false;
    }
    if (words[1] == "register_admin")
    {
        if (words[0] != "POST")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() == 7 && words[2] == "?" && words[3] == "username" && words[5] == "password")
        {
            return true;
        }
        cerr << err.Bad_Request;
        return false;
    }
    if (words[1] == "logout")
    {
        if (words[0] != "POST")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() != 2)
        {
            cerr << err.Bad_Request;
            return false;
        }
        return true;
    }
    if (words[1] == "sell_player")
    {
        if (words[0] != "POST")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() != 5 || words[2] != "?" || words[3] != "name")
        {
            cerr << err.Bad_Request;
            return false;
        }
        return true;
    }
    if (words[1] == "buy_player")
    {
        if (words[0] != "POST")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() != 5 || words[2] != "?" || words[3] != "name")
        {
            cerr << err.Bad_Request;
            return false;
        }
        return true;
    }
    if (words[1] == "squad")
    {
        if (words[0] != "GET")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() == 3 && words[2] == "?")
        {
            return true;
        }
        if (words[2] == "?" && words.size() == 5 && words[3] == "fantasy_team")
        {
            return true;
        }
        cerr << err.Bad_Request;
        return false;
    }
    if (words[1] == "close_transfer_window")
    {
        if (words[0] != "POST")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() != 2)
        {
            cerr << err.Bad_Request;
            return false;
        }
        return true;
    }
    if (words[1] == "open_transfer_window")
    {
        if (words[0] != "POST")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() != 2)
        {
            cerr << err.Bad_Request;
            return false;
        }
        return true;
    }
    if (words[1] == "pass_week")
    {
        if (words[0] != "POST")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() != 2)
        {
            cerr << err.Bad_Request;
            return false;
        }
        return true;
    }
    if (words[1] == "set_captain")
    {
        if (words[0] != "POST")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() != 5 || words[2] != "?" || words[3] != "name")
        {
            return false;
        }
        return true;
    }
    if (words[1] == "show_budget")
    {
        if (words[0] != "GET")
        {
            cerr << err.Not_Found;
            return false;
        }
        if (words.size() == 2)
        {
            return true;
        }
        return false;
    }

    else
    {
        cerr << err.Not_Found;
        return false;
    }
}
void RealTeam::updateGAandGF(int gf, int ga)
{
    this->ga += ga;
    this->gf += gf;
}
RealTeam::RealTeam(string name_, vector<RealPlayer *> players_)
{
    name = name_;
    players = players_;
    ga = 0;
    gf = 0;
    score = 0;
    cleansheets = vector<bool>(NUM_OF_WEEKS, false);
}
class Game
{
public:
    Game(string fTeamName_, string sTeamName_, int fTeamGoals_, int sTeamGoals, int week_);
    void matchesResultLeague(int week);

private:
    string fTeamName;
    string sTeamName;
    int fTeamGoals;
    int sTeamGoals;
    int week;
};
Game::Game(string fTeamName_, string sTeamName_, int fTeamGoals_, int sTeamGoals_, int week_)
{
    fTeamName = fTeamName_;
    sTeamName = sTeamName_;
    fTeamGoals = fTeamGoals_;
    sTeamGoals = sTeamGoals_;
    week = week_;
}
void Game::matchesResultLeague(int week)
{
    if (this->week == week)
        cout << fTeamName << ' ' << fTeamGoals << " | " << sTeamName << ' ' << sTeamGoals << endl;
}
vector<string> splitInput(string input, char delim)
{
    string word = "";
    vector<string> result;
    for (auto x : input)
    {
        if (x == delim)
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
vector<RealPlayer *> createPlayers(vector<RealPlayer *> &realPlayers, const vector<string> &gks, const vector<string> &dfs,
                                   const vector<string> &mds, const vector<string> &sts)
{
    vector<RealPlayer *> temp;
    for (auto name : gks)
    {
        if (!name.empty() && name[name.size() - 1] == '\r' || name[name.size() - 1] == '$')
            name.erase(name.size() - 1);
        vector<string> nameAndPrice = splitInput(name, ':');
        GoalKeeper *gk = new GoalKeeper(nameAndPrice[0], stoi(nameAndPrice[1]));
        temp.push_back(gk);
        realPlayers.push_back(gk);
    }
    for (auto name : dfs)
    {
        if (!name.empty() && name[name.size() - 1] == '\r' || name[name.size() - 1] == '$')
            name.erase(name.size() - 1);
        vector<string> nameAndPrice = splitInput(name, ':');
        Defender *df = new Defender(nameAndPrice[0], stoi(nameAndPrice[1]));
        temp.push_back(df);
        realPlayers.push_back(df);
    }
    for (auto name : mds)
    {
        if (!name.empty() && name[name.size() - 1] == '\r' || name[name.size() - 1] == '$')
            name.erase(name.size() - 1);
        vector<string> nameAndPrice = splitInput(name, ':');
        Midfielder *md = new Midfielder(nameAndPrice[0], stoi(nameAndPrice[1]));
        temp.push_back(md);
        realPlayers.push_back(md);
    }
    for (auto name : sts)
    {
        if (!name.empty() && name[name.size() - 1] == '\r' || name[name.size() - 1] == '$')
            name.erase(name.size() - 1);
        vector<string> nameAndPrice = splitInput(name, ':');
        Striker *st = new Striker(nameAndPrice[0], stoi(nameAndPrice[1]));
        temp.push_back(st);
        realPlayers.push_back(st);
    }
    return temp;
}

void readLeagueData(vector<RealPlayer *> &realPlayers, vector<RealTeam *> &realTeams)
{
    ifstream pLeagueFile;
    pLeagueFile.open("premier_league.csv", ios::in);
    string line;
    getline(pLeagueFile, line); // read junk line
    while (getline(pLeagueFile, line))
    {
        vector<string> splitedWordsBycomma = splitInput(line, ',');
        string TeamName = splitedWordsBycomma[0];
        vector<string> gks = splitInput(splitedWordsBycomma[1], ';');
        vector<string> dfs = splitInput(splitedWordsBycomma[2], ';');
        vector<string> mds = splitInput(splitedWordsBycomma[3], ';');
        vector<string> fws = splitInput(splitedWordsBycomma[4], ';');
        vector<RealPlayer *> temp = createPlayers(realPlayers, gks, dfs, mds, fws);
        RealTeam *rtp = new RealTeam(TeamName, temp);
        realTeams.push_back(rtp);
    }
}
RealTeam *findTeam(const vector<RealTeam *> &realTeams, string name)
{
    for (auto rtp : realTeams)
    {
        if (name == rtp->getName())
        {
            return rtp;
        }
    }
    return nullptr;
}
void updateGAandGf(const vector<string> &twoTeams, const vector<string> &gameResult, vector<RealTeam *> &realTeams)
{
    RealTeam *t1 = findTeam(realTeams, twoTeams[0]);
    RealTeam *t2 = findTeam(realTeams, twoTeams[1]);
    t1->updateGAandGF(stoi(gameResult[0]), stoi(gameResult[1]));
    t2->updateGAandGF(stoi(gameResult[1]), stoi(gameResult[0]));
}
void updateInjuries(const vector<string> &injuries, int week, vector<RealPlayer *> &realPlayers)
{
    for (auto name : injuries)
    {
        if (name == "")
        {
            continue;
        }
        RealPlayer *rpp = findPlayer(realPlayers, name);
        rpp->updateInjury(week);
    }
}
void updateYCards(const vector<string> &yCards, vector<RealPlayer *> &realPlayers)
{
    for (auto name : yCards)
    {
        if (name == "")
        {
            continue;
        }
        RealPlayer *rpp = findPlayer(realPlayers, name);
        rpp->updateYCards();
    }
}
void updateRCards(int curWeek, const vector<string> &rCards, vector<RealPlayer *> &realPlayers)
{
    for (auto name : rCards)
    {
        if (name == "")
        {
            continue;
        }
        RealPlayer *rpp = findPlayer(realPlayers, name);
        rpp->updateRCards(curWeek);
    }
}
void updateScores(vector<string> &scores, vector<RealPlayer *> &realPlayers, int week)
{
    for (auto wd : scores)
    {
        vector<string> nameAndScore = splitInput(wd, ':');
        RealPlayer *rpp = findPlayer(realPlayers, nameAndScore[0]);
        rpp->updateScores(week, stoi(nameAndScore[1]));
    }
}
void substring(string line, vector<string> &words, vector<string> &twoTeams, vector<string> &gameResult,
               vector<string> &injuries, vector<string> &yCards, vector<string> &rCards, vector<string> &goalWithAssist, vector<string> &team1, vector<string> &team2)
{
    words = splitInput(line, ',');
    twoTeams = splitInput(words[0], ':');
    gameResult = splitInput(words[1], ':');
    injuries = splitInput(words[2], ';');
    yCards = splitInput(words[3], ';');
    rCards = splitInput(words[4], ';');
    goalWithAssist = splitInput(words[5], ';');
    team1 = splitInput(words[1], ';');
    team2 = splitInput(words[6], ';');
}
void draw(int week, vector<string> players1, vector<string> players2, vector<RealPlayer *> &RealPlayers)
{
    for (auto t1player : players1)
    {
        findPlayer(RealPlayers, t1player)->draw(week);
    }
    for (auto t2player : players2)
    {
        findPlayer(RealPlayers, t2player)->draw(week);
    }
}
void win(int week, vector<string> players1, vector<RealPlayer *> &RealPlayers)
{
    for (auto t1player : players1)
    {
        findPlayer(RealPlayers, t1player)->win(week);
    }
}
void lose(int week, vector<string> players1, vector<RealPlayer *> &RealPlayers)
{
    for (auto t1player : players1)
    {
        findPlayer(RealPlayers, t1player)->lose(week);
    }
}
void updatePlayerScoreR1(int week, vector<RealPlayer *> &RealPlayers, const vector<string> &Team1Players, const vector<string> &Team2Players, const vector<string> &gameResult)
{
    if (stoi(gameResult[0]) > stoi(gameResult[1]))
    {
        win(week, Team1Players, RealPlayers);
        lose(week, Team2Players, RealPlayers);
    }
    else if (stoi(gameResult[0]) < stoi(gameResult[1]))
    {
        win(week, Team2Players, RealPlayers);
        lose(week, Team1Players, RealPlayers);
    }
    else if (stoi(gameResult[0]) == stoi(gameResult[1]))
    {
        draw(week, Team1Players, Team2Players, RealPlayers);
    }
}
void updateTeamsScores(const vector<string> &twoTeams, const vector<string> &gameResult, vector<RealTeam *> &realTeams)
{
    RealTeam *ft = findTeam(realTeams, twoTeams[0]);
    RealTeam *st = findTeam(realTeams, twoTeams[1]);
    if (stoi(gameResult[0]) > stoi(gameResult[1]))
    {
        ft->win();

        // ft.
    }
    else if (stoi(gameResult[0]) < stoi(gameResult[1]))
    {
        st->win();
    }
    else if (stoi(gameResult[0]) == stoi(gameResult[1]))
    {
        ft->draw();
        st->draw();
    }
}
void updateGoalsAssist(int week, vector<string> goalAndAssist, vector<RealPlayer *> &realPlayers);
void updatePlayerScoreR2(int week, vector<string> gameResult, vector<string> team1, vector<string> team2, vector<RealPlayer *> &realPlayers)
{
    // team1[0];
    for (auto playerName : team1)
    {
        findPlayer(realPlayers, playerName)->calPlayerScoreR2(stoi(gameResult[0]), week);
        // playerName.calScoreR2
    }
    for (auto playerName : team2)
    {
        findPlayer(realPlayers, playerName)->calPlayerScoreR2(stoi(gameResult[1]), week);
    }
}
void updatePlayerScoreR3_lb(vector<RealPlayer *> &realPlayers, vector<string> team1, vector<string> team2, int week)
{
    RealPlayer *lb = findPlayer(realPlayers, team1[1]);
    RealPlayer *rb = findPlayer(realPlayers, team2[4]);
    RealPlayer *rm = findPlayer(realPlayers, team2[10]);
    lb->decreaseScore(week, rb->getNumOfGoals(week) + rm->getNumOfGoals(week));
    lb = findPlayer(realPlayers, team2[1]);
    rb = findPlayer(realPlayers, team1[4]);
    rm = findPlayer(realPlayers, team1[10]);
    lb->decreaseScore(week, rb->getNumOfGoals(week) + rm->getNumOfGoals(week));
}
void updatePlayerScoreR3_rb(vector<RealPlayer *> &realPlayers, vector<string> team1, vector<string> team2, int week)
{
    RealPlayer *rb = findPlayer(realPlayers, team1[4]);
    RealPlayer *lb = findPlayer(realPlayers, team2[1]);
    RealPlayer *lm = findPlayer(realPlayers, team2[8]);
    rb->decreaseScore(week, lb->getNumOfGoals(week) + lm->getNumOfGoals(week));
    rb = findPlayer(realPlayers, team2[4]);
    lb = findPlayer(realPlayers, team1[1]);
    lm = findPlayer(realPlayers, team1[8]);
    rb->decreaseScore(week, lb->getNumOfGoals(week) + lm->getNumOfGoals(week));
}
void updatePlayerScoreR3_cbs(vector<RealPlayer *> &realPlayers, vector<string> team1, vector<string> team2, int week)
{
    RealPlayer *cb1 = findPlayer(realPlayers, team1[2]);
    RealPlayer *cb2 = findPlayer(realPlayers, team1[3]);
    RealPlayer *st = findPlayer(realPlayers, team1[9]);
    findPlayer(realPlayers, team2[2])->decreaseScore(week, cb1->getNumOfGoals(week) + cb2->getNumOfGoals(week) + st->getNumOfGoals(week));
    findPlayer(realPlayers, team2[3])->decreaseScore(week, cb1->getNumOfGoals(week) + cb2->getNumOfGoals(week) + st->getNumOfGoals(week));
    cb1 = findPlayer(realPlayers, team2[2]);
    cb2 = findPlayer(realPlayers, team2[3]);
    st = findPlayer(realPlayers, team2[9]);
    findPlayer(realPlayers, team1[3])->decreaseScore(week, cb1->getNumOfGoals(week) + cb2->getNumOfGoals(week) + st->getNumOfGoals(week));
    findPlayer(realPlayers, team1[2])->decreaseScore(week, cb1->getNumOfGoals(week) + cb2->getNumOfGoals(week) + st->getNumOfGoals(week));
}
void updatePlayerScoreR3_cms(vector<RealPlayer *> &realPlayers, vector<string> team1, vector<string> team2, int week)
{
    RealPlayer *cm1 = findPlayer(realPlayers, team1[5]);
    RealPlayer *cm2 = findPlayer(realPlayers, team1[6]);
    RealPlayer *cm3 = findPlayer(realPlayers, team1[7]);
    findPlayer(realPlayers, team2[5])->decreaseScore(week, cm1->getNumOfGoals(week) + cm2->getNumOfGoals(week) + cm3->getNumOfGoals(week));
    findPlayer(realPlayers, team2[6])->decreaseScore(week, cm1->getNumOfGoals(week) + cm2->getNumOfGoals(week) + cm3->getNumOfGoals(week));
    findPlayer(realPlayers, team2[7])->decreaseScore(week, cm1->getNumOfGoals(week) + cm2->getNumOfGoals(week) + cm3->getNumOfGoals(week));
    cm1 = findPlayer(realPlayers, team2[5]);
    cm2 = findPlayer(realPlayers, team2[6]);
    cm3 = findPlayer(realPlayers, team2[7]);
    findPlayer(realPlayers, team1[5])->decreaseScore(week, cm1->getNumOfGoals(week) + cm2->getNumOfGoals(week) + cm3->getNumOfGoals(week));
    findPlayer(realPlayers, team1[6])->decreaseScore(week, cm1->getNumOfGoals(week) + cm2->getNumOfGoals(week) + cm3->getNumOfGoals(week));
    findPlayer(realPlayers, team1[7])->decreaseScore(week, cm1->getNumOfGoals(week) + cm2->getNumOfGoals(week) + cm3->getNumOfGoals(week));
}
void updatePlayerScoreR3(int week, vector<string> team1, vector<string> team2, vector<RealPlayer *> &realPlayers)
{
    updatePlayerScoreR3_lb(realPlayers, team1, team2, week);
    updatePlayerScoreR3_rb(realPlayers, team1, team2, week);
    updatePlayerScoreR3_cbs(realPlayers, team1, team2, week);
    updatePlayerScoreR3_cms(realPlayers, team1, team2, week);
}
void updatePlayerScoreR4(int week, vector<string> team1, vector<string> team2, vector<RealPlayer *> &realPlayers)
{
    for (auto name : team1)
    {
        findPlayer(realPlayers, name)->calFunA(week);
    }
    for (auto name : team1)
    {
        findPlayer(realPlayers, name)->calFunA(week);
    }
}
void updateCleensheet(int week, vector<RealTeam *> &realTeams, const vector<string> &twoTeams, const vector<string> &result)
{
    if (stoi(result[0]) == 0)
    {
        findTeam(realTeams, twoTeams[1])->addCleanSheet(week);
    }
    else if (stoi(result[1]) == 0)
    {
        findTeam(realTeams, twoTeams[0])->addCleanSheet(week);
    }
}
void readWeeksData(int curWeek, vector<RealTeam *> &realTeams, vector<RealPlayer *> &realPlayers, vector<Game *> &games)
{
    // for (int week = 1; week <= curWeek; week++)
    //{
    ifstream weeks_statsFile;
    // string fileName = "weeks_stats/week_" + to_string(week) + ".csv";
    string fileName = "weeks_stats/week_" + to_string(curWeek) + ".csv";
    weeks_statsFile.open(fileName);
    string line;
    getline(weeks_statsFile, line);
    while (getline(weeks_statsFile, line))
    {
        // resetplayerscore
        vector<string> words, twoTeams, gameResult, injuries, yCards, rCards, goalWithAssist, team1, team2;
        substring(line, words, twoTeams, gameResult, injuries, yCards, rCards, goalWithAssist, team1, team2);
        updateGAandGf(twoTeams, gameResult, realTeams);
        updateTeamsScores(twoTeams, gameResult, realTeams);
        updateCleensheet(curWeek, realTeams, twoTeams, gameResult);
        //  updateGoalsAssist(week, goalWithAssist, realPlayers);
        updateGoalsAssist(curWeek, goalWithAssist, realPlayers);
        updatePlayerScoreR1(curWeek, realPlayers, team1, team2, gameResult);
        // updatePlayerScoreR2()
        updatePlayerScoreR2(curWeek, gameResult, team1, team2, realPlayers);
        // updatePlayerScoreR3()
        updatePlayerScoreR3(curWeek, team1, team2, realPlayers);
        // updatePlayerScoreR4(curWeek, team1, team2, realPlayers);
        updateInjuries(injuries, curWeek, realPlayers);
        updateYCards(yCards, realPlayers);
        updateRCards(curWeek, rCards, realPlayers);
        // updateScores(scores, realPlayers, week);
        Game *game = new Game(twoTeams[0], twoTeams[1], stoi(gameResult[0]), stoi(gameResult[1]), curWeek);
        games.push_back(game);
    }
    weeks_statsFile.close();
    //  }
}
void passWeek(int &curWeek, Admin &ad)
{
    if (ad.isLoggedIn())
    {
        cout << "OK\n";
        curWeek++;
    }
    else
        cerr << err.Permission_Denied;
}
void showTheTeam(const vector<string> &words, const vector<RealTeam *> &realTeams, int weekNum)
{
    string teamName = words[4];
    RealTeam *rtp = findTeam(realTeams, teamName);
    if (rtp == nullptr)
    {
        cerr << err.Not_Found;
        return;
    }
    if (words.size() == 5)
    {
        rtp->printPlayersInfo(false, "", weekNum);
    }
    else if (words.size() == 7)
    {
        rtp->printPlayersInfo(true, words[5], weekNum);
    }
    else if (words.size() == 6)
    {
        if (words[5] == "rank")
        {
            rtp->printPlayersInfo(true, "", weekNum);
        }
        else
        {
            rtp->printPlayersInfo(false, words[5], weekNum);
        }
    }
}
void sortRealTeams(vector<RealTeam *> &realTeams)
{

    sort(realTeams.begin(), realTeams.end(), [](RealTeam *first, RealTeam *second)
         {
             if (first->score != second->score)
                 return first->score > second->score;

             if (first->score == second->score && (first->gf - first->ga) != (second->gf - second->ga))
                 return (first->gf - first->ga) > (second->gf - second->ga);
             if ((first->score == second->score) && ((first->gf - first->ga) == (second->gf - second->ga)))
                 return first->gf > second->gf;
             else
             {
                 return first->getName() < second->getName();
             } });
}
void leagueStandings(vector<RealTeam *> &realTeams)
{
    sortRealTeams(realTeams);
    cout << "league standings:\n";
    int count = 1;
    for (auto rtp : realTeams)
    {
        cout << count << ". ";
        rtp->printTeamInfo();
        count++;
    }
}
void findTheBestTeam(int weekNum, vector<RealPlayer *> &realPlayers)
{
    sort(realPlayers.begin(), realPlayers.end(), cmp(weekNum));
    for (auto rpp : realPlayers)
    {
        if (rpp->getPos() == "GoalKeeper")
        {
            cout << fixed;
            cout << setprecision(1);
            cout << "GoalKeeper: " << rpp->getName() << " | "
                 << "score: " << rpp->getScore(weekNum) << endl;
            break;
        }
    }
    vector<RealPlayer *> twoDef;
    for (auto rpp : realPlayers)
    {
        if (twoDef.size() == 2)
        {
            break;
        }
        if (rpp->getPos() == "Defender")
        {
            twoDef.push_back(rpp);
        }
    }
    cout << fixed;
    cout << setprecision(1);
    cout << "Defender1: " << twoDef[0]->getName() << " | "
         << "score: " << twoDef[0]->getScore(weekNum) << endl;
    cout << fixed;
    cout << setprecision(1);
    cout << "Defender2: " << twoDef[1]->getName() << " | "
         << "score: " << twoDef[1]->getScore(weekNum) << endl;
    for (auto rpp : realPlayers)
    {
        if (rpp->getPos() == "Midfielder")
        {
            cout << fixed;
            cout << setprecision(1);
            cout << "Midfielder: " << rpp->getName() << " | "
                 << "score: " << rpp->getScore(weekNum) << endl;
            break;
        }
    }
    for (auto rpp : realPlayers)
    {
        if (rpp->getPos() == "Forward")
        {
            cout << fixed;
            cout << setprecision(1);
            cout << "Forward: " << rpp->getName() << " | "
                 << "score: " << rpp->getScore(weekNum) << endl;
            break;
        }
    }
}
void matchesResultLeague(const vector<string> &words, int curWeek, const vector<Game *> &games)
{
    if (words.size() == 3)
    {
        if (curWeek == 0)
        {
            cerr << err.Bad_Request;
            return;
        }
        for (auto game : games)
        {
            game->matchesResultLeague(curWeek);
        }
    }
    else
    {
        if (stoi(words[4]) <= 0 || stoi(words[4]) > curWeek)
        {
            cerr << err.Bad_Request;
            return;
        }
        for (auto game : games)
        {
            game->matchesResultLeague(stoi(words[4]));
        }
    }
}

void signup(vector<string> words, vector<FFPlayer *> &ffPlayers)
{
    for (auto ffp : ffPlayers)
    {
        if (ffp->checkNameDup(words[4]))
        {
            return;
        }
    }
    ffPlayers.push_back(new FFPlayer(words[4], words[6]));
    cout << "OK\n";
}
FFPlayer *find_ffplayer_by_name(string name, vector<FFPlayer *> ffPlayers)
{
    for (int i = 0; i < ffPlayers.size(); i++)
    {
        if (ffPlayers[i]->getTeamName() == name)
        {
            return ffPlayers[i];
        }
    }
    return nullptr;
}
bool login(vector<string> words, vector<FFPlayer *> &ffPlayers, string &CurrUsersUsername)
{
    FFPlayer *player_ptr = find_ffplayer_by_name(words[4], ffPlayers);
    if (player_ptr == NULL)
    {
        cerr << err.Not_Found;
        return false;
    }
    if (player_ptr->checkPassword(words[6]))
    {
        player_ptr->loginUser();
        CurrUsersUsername = words[4];
        cout << "OK\n";
        return true;
    }
    else
    {
        cerr << err.Permission_Denied;
        return false;
    }
}
void logout(string CurrUsersUsername, const vector<FFPlayer *> &ffPlayers, Admin &ad, int &numOfUsersLoggedIn)
{
    FFPlayer *ffp = find_ffplayer_by_name(CurrUsersUsername, ffPlayers);

    if ((ffp != nullptr) && ffp->getLoginStatus() == true)
    {
        ffp->logoutUser();
        cout << "OK\n";
        numOfUsersLoggedIn--;
    }
    else if (ad.isLoggedIn())
    {
        ad.logout();
        cout << "OK\n";
        numOfUsersLoggedIn--;
    }
    else
    {
        cerr << err.Permission_Denied;
    }
}
void buyPlayer(int curWeek, vector<RealPlayer *> &realPlayers, vector<string> words, string CurrUsersUsername, vector<FFPlayer *> &ffPlayers)
{
    FFPlayer *ffp = find_ffplayer_by_name(CurrUsersUsername, ffPlayers);
    string playerName = findPlayerName(words);
    if ((ffp == nullptr) || ffp->getLoginStatus() == false)
    {
        cerr << err.Bad_Request;
        return;
    }

    RealPlayer *rpp = findPlayer(realPlayers, playerName);
    if (rpp == nullptr)
    {
        cerr << err.Not_Found;
        return;
    }
    if (rpp->isAvailableForThisWeek())
    {
        if (ffp->get_budget() >= rpp->get_price())
        {
            ffp->set_new_budget(ffp->get_budget() - rpp->get_price());
            if (ffp->addPlayer(rpp))
                cout << "OK\n";
        }
        else
        {
            cerr << err.Bad_Request;
        }
    }
    else
    {
        cout << "This player is not available for next week\n";
    }
}
void updateSuspension(vector<RealPlayer *> &realPlayers, int week)
{
    for (auto rpp : realPlayers)
    {
        if (rpp->isAvailable(week) == false)
        {
            rpp->updateSuspension(true);
        }
        else
        {
            rpp->updateSuspension(false);
        }
    }
}

void sellPlayer(vector<RealPlayer *> realPlayers, const vector<string> &words, string currentUserName, vector<FFPlayer *> &ffPlayers)
{
    string playerName = findPlayerName(words);
    if (!findPlayer(realPlayers, playerName))
    {
        cerr << err.Not_Found;
        return;
    }
    FFPlayer *ffp = find_ffplayer_by_name(currentUserName, ffPlayers);
    if ((ffp == nullptr) || ffp->getLoginStatus() == false)
    {
        cerr << err.Bad_Request;
        return;
    }

    if (ffp->isCompleted())
    {
        if (ffp->getNumOfSoldPlayers() < 2)
        {
            ffp->sellPlayer(playerName, true, realPlayers);
        }
        else
        {
            cerr << err.Permission_Denied;
        }
    }
    else
    {
        ffp->sellPlayer(playerName, false, realPlayers);
    }
}
void updateNumOfSoldPlayers(vector<FFPlayer *> &ffPlayers)
{
    for (auto ffp : ffPlayers)
    {
        ffp->resetNumOFSoldPlayers();
    }
}
void show_squad(vector<string> words, const vector<FFPlayer *> &ffPlayers, string CurrUsersUserName, int weekNum)
{
    string wanted_team_name;
    FFPlayer *tp;
    if (words.size() == 5)
    {
        wanted_team_name = words[4];
        tp = find_ffplayer_by_name(wanted_team_name, ffPlayers);
        if (tp->getLoginStatus() == false)
        {
            cerr << err.Bad_Request;
            return;
        }
        if (tp != nullptr)
        {
            if (tp->isCompleted())
            {
                tp->print_squad();
                cout << "Total Points: " << tp->getTotalTeamScore() << endl; // needs to cout points
                cout << "Team Cost: " << tp->totalCost() << endl;
            }
            else
                cerr << err.Empty;
        }
        else
        {
            cerr << err.Not_Found;
        }
    }
    else if (words.size() == 3) // 3
    {

        tp = find_ffplayer_by_name(CurrUsersUserName, ffPlayers);
        if (tp->getLoginStatus() == false)
        {
            cerr << err.Bad_Request;
            return;
        }
        tp->print_squad();
        cout << tp->getTotalTeamScore() << endl; // needs to cout this line;
    }
}
bool mypred(FFPlayer *first, FFPlayer *second) // wtf is this int
{
    if (first->getTotalTeamScore() != second->getTotalTeamScore())
    {
        return first->getTotalTeamScore() > second->getTotalTeamScore();
    }
    else
    {
        return first->getTeamName() < second->getTeamName();
    }
}

void user_rankings(vector<FFPlayer *> ffPlayers, int currWeek)
{
    vector<FFPlayer *> ffPlayers_cpy = ffPlayers;
    sort(ffPlayers_cpy.begin(), ffPlayers_cpy.end(), mypred);
    for (int i = 0; i < ffPlayers_cpy.size(); i++)
    {
        cout << i + 1 << ". team_name: " << ffPlayers_cpy[i]->getTeamName() << " | point: " << ffPlayers_cpy[i]->getTotalTeamScore() << endl;
    }
}
void updateTeamScores(vector<FFPlayer *> &ffPlayers, int currWeek)
{
    for (int i = 0; i < ffPlayers.size(); i++)
    {

        ffPlayers[i]->calcTeamTotalScore(currWeek, ffPlayers[i]->getAvailableWeeks());
    }
}
void updateFfpAvailableWeeks(vector<FFPlayer *> &ffPlayers, int weekNum)
{

    for (auto ffp : ffPlayers)
    {
        // ffp.
        ffp->updateFfpAvailableWeeks(weekNum);
    }
}

void setCaptain(string curUserName, const vector<string> &words, vector<FFPlayer *> &ffplayers)
{
    FFPlayer *ffp = find_ffplayer_by_name(curUserName, ffplayers);
    if ((ffp == nullptr) || ffp->getLoginStatus() == false)
    {
        cerr << err.Bad_Request;
        return;
    }
    // ffp.
    ffp->setCaptain(words[4]);
}
void show_budget(string currUsersUsername, vector<FFPlayer *> ffPlayers);
void handleUserInput(int &numOfUsersLoggedIn, int &curWeek, Admin &ad, string input, vector<RealPlayer *> &realPlayers,
                     vector<RealTeam *> &realTeams, vector<Game *> &games, vector<FFPlayer *> &ffPlayers)
{
    static string CurrUsersUsername;
    vector<string> words = splitInput(input, ' ');
    if (input_is_valid(words, curWeek) == false)
    {
        return;
    }
    if (words[1] == "pass_week")
    {
        if (curWeek != 0)
            updateFfpAvailableWeeks(ffPlayers, curWeek);

        passWeek(curWeek, ad);
        readWeeksData(curWeek, realTeams, realPlayers, games);
        updateSuspension(realPlayers, curWeek);
        updateNumOfSoldPlayers(ffPlayers);
        updateFfpAvailableWeeks(ffPlayers, curWeek);
        updateTeamScores(ffPlayers, curWeek);
    }
    else if (words[1] == "register_admin")
    {
        if (numOfUsersLoggedIn == 0)
        {
            if (ad.registerAdmin(words[4], words[6]))
                numOfUsersLoggedIn++;
        }
        else
            cerr << err.Bad_Request;
    }
    else if (words[1] == "team_of_the_week")
    {
        if (words.size() == 3 && curWeek != 0)
            // cur week best team
            findTheBestTeam(curWeek, realPlayers);
        else if (stoi(words[4]) <= curWeek && stoi(words[4]) > 0 && curWeek != 0)
            findTheBestTeam(stoi(words[4]), realPlayers);
        else
            cerr << err.Bad_Request;
    }
    else if (words[1] == "players")
    {
        showTheTeam(words, realTeams, curWeek);
    }
    else if (words[1] == "league_standings")
    {
        leagueStandings(realTeams);
    }
    else if (words[1] == "matches_result_league")
    {
        matchesResultLeague(words, curWeek, games);
    }
    else if (words[1] == "signup")
    {
        signup(words, ffPlayers);
    }
    else if (words[1] == "login")
    {
        if (numOfUsersLoggedIn == 0)
        {
            if (login(words, ffPlayers, CurrUsersUsername))
                numOfUsersLoggedIn++;
        }
        else
            cerr << err.Bad_Request;
    }
    else if (words[1] == "logout")
    {
        logout(CurrUsersUsername, ffPlayers, ad, numOfUsersLoggedIn);
    }
    else if (words[1] == "buy_player")
    {
        if (ad.GetTransferWindowStatus())
            buyPlayer(curWeek, realPlayers, words, CurrUsersUsername, ffPlayers);
        else
            cerr << err.Permission_Denied;
    }
    else if (words[1] == "close_transfer_window")
    {
        if (ad.isLoggedIn())
        {
            ad.CloseTransferWindow();
            cout << "OK\n";
        }
        else
            cerr << err.Permission_Denied;
    }
    else if (words[1] == "open_transfer_window")
    {
        if (ad.isLoggedIn())
        {
            ad.OpenTransferWindow();
            cout << "OK\n";
        }
        else
            cerr << err.Permission_Denied;
    }
    else if (words[1] == "sell_player")
    {
        if (ad.GetTransferWindowStatus())
        {
            sellPlayer(realPlayers, words, CurrUsersUsername, ffPlayers);
        }
        else
        {
            cerr << err.Permission_Denied;
        }
        // POST sell_player ? name <name>
    }
    else if (words[1] == "squad")
    {
        // if (numOfUsersLoggedIn == 0)
        //{
        //    cout << Permission_Denied_Err;
        //  }
        show_squad(words, ffPlayers, CurrUsersUsername, curWeek);
    }
    else if (words[1] == "users_ranking")
    {
        user_rankings(ffPlayers, curWeek); // sort if equal points
    }
    else if (words[1] == "set_captain")
    {
        setCaptain(CurrUsersUsername, words, ffPlayers);
    }
    else if (words[1] == "show_budget")
    {
        show_budget(CurrUsersUsername, ffPlayers);
    }
}
void show_budget(string currUsersUsername, vector<FFPlayer *> ffPlayers);
int main()
{
    Admin ad;
    int curWeek = 0;
    vector<RealPlayer *> realPlayers;
    vector<RealTeam *> realTeams;
    vector<Game *> games;
    vector<FFPlayer *> ffPlayers;
    readLeagueData(realPlayers, realTeams);
    string input;
    int numOfUsersLoggedIn = 0;
    while (getline(cin, input))
    {
        handleUserInput(numOfUsersLoggedIn, curWeek, ad, input, realPlayers, realTeams, games, ffPlayers);
    }
    return 0;
}
void show_budget(string currUsersUsername, vector<FFPlayer *> ffPlayers)
{
    FFPlayer *fpp = find_ffplayer_by_name(currUsersUsername, ffPlayers);
    fpp->show_team_budget();
}
void updateGoalsAssist(int week, vector<string> goalAndAssist, vector<RealPlayer *> &realPlayers)
{
    for (string name : goalAndAssist)
    {
        vector<string> splitedGoalAndAssist = splitInput(name, ':');
        RealPlayer *rpp1 = findPlayer(realPlayers, splitedGoalAndAssist[0]);
        if (splitedGoalAndAssist[1] == "OWN_GOAL")
        {
            rpp1->ownGoal(week);
        }
        else
        {
            RealPlayer *rpp2 = findPlayer(realPlayers, splitedGoalAndAssist[1]);
            rpp1->goal(week);
            rpp2->assist(week);
        }
    }
}

// POST register_admin ? username admin password 123456
// POST pass_week
// POST buy_player ? name J. Henderson
// POST open_transfer_window
// GET team_of_the_week ? week 3
// GET players ? team_name <team_name> +gk/df/md/fw +ranks
// GET matches_result_league ? week_num 2
// POST signup ? team_name Sharks password 021021
//// POST signup ? team_name mss password 021
// POST login ? team_name mss password 021
//  POST login ? team_name Sharks password 021021
//  POST buy_player ? name
//  POST sell_player ? name <name>
//  POST buy_player ? name J. Stones
//  POST buy_player ? name Ederson
//  POST buy_player ? name S. Botman
//  POST sell_player ? name ali