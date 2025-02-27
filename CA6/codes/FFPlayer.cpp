#include "FFPlayer.hpp"
#include "err.hpp"
#include "funcs.hpp"
bool FFPlayer::checkNameDup(string name_)
{
    if (TeamName == name_)
    {
        cout << "Bad Request\n";
        return true;
    }
    return false;
}
bool FFPlayer::checkPassword(string pass)
{
    if (pass == passWord)
    {
        return true;
    }
    return false;
}
double FFPlayer::calcTeamTotalScore(int weekNum, vector<bool> availableWeeks)
{

    if (this->isCompleted())
    {
        points = gk->calTotalScore(weekNum, availableWeeks, captainName) + df1->calTotalScore(weekNum, availableWeeks, captainName) +
                 df2->calTotalScore(weekNum, availableWeeks, captainName) + md->calTotalScore(weekNum, availableWeeks, captainName) +
                 st->calTotalScore(weekNum, availableWeeks, captainName);
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