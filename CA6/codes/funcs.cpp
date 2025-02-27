#include "funcs.hpp"
#include "RealTeam.hpp"
#include <cmath>
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
bool cmpNames(RealPlayer *first, RealPlayer *second)
{
    return (first->getName() < second->getName());
}
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
        vector<string> words, twoTeams, gameResult, injuries, yCards, rCards, goalWithAssist, team1, team2;
        substring(line, words, twoTeams, gameResult, injuries, yCards, rCards, goalWithAssist, team1, team2);
        updateGAandGf(twoTeams, gameResult, realTeams);
        updateTeamsScores(twoTeams, gameResult, realTeams);
        updateCleensheet(curWeek, realTeams, twoTeams, gameResult);
        updateGoalsAssist(curWeek, goalWithAssist, realPlayers);
        updatePlayerScoreR1(curWeek, realPlayers, team1, team2, gameResult);
        updatePlayerScoreR2(curWeek, gameResult, team1, team2, realPlayers);
        updatePlayerScoreR3(curWeek, team1, team2, realPlayers);
        updateInjuries(injuries, curWeek, realPlayers);
        updateYCards(yCards, realPlayers);
        updateRCards(curWeek, rCards, realPlayers);
        Game *game = new Game(twoTeams[0], twoTeams[1], stoi(gameResult[0]), stoi(gameResult[1]), curWeek);
        games.push_back(game);
    }
    weeks_statsFile.close();
}
void updatePlayerScoreR2(int week, vector<string> gameResult, vector<string> team1, vector<string> team2, vector<RealPlayer *> &realPlayers)
{
    for (auto playerName : team1)
    {
        findPlayer(realPlayers, playerName)->calPlayerScoreR2(stoi(gameResult[0]), week);
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
void updateNumOfSoldPlayers(vector<FFPlayer *> &ffPlayers)
{
    for (auto ffp : ffPlayers)
    {
        ffp->resetNumOFSoldPlayers();
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
void show_budget(string currUsersUsername, vector<FFPlayer *> ffPlayers)
{
    FFPlayer *fpp = find_ffplayer_by_name(currUsersUsername, ffPlayers);
    fpp->show_team_budget();
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
        if (curWeek == 0)
            ad.OpenTransferWindow();
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
    }
    else if (words[1] == "squad")
    {
        show_squad(words, ffPlayers, CurrUsersUsername, curWeek);
    }
    else if (words[1] == "users_ranking")
    {
        user_rankings(ffPlayers, curWeek);
    }
}