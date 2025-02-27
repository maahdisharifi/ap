#include "Admin.hpp"
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