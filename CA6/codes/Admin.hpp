#pragma once
#include <string>
#include <iostream>
#include "err.hpp"
using namespace std;
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