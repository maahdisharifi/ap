#ifndef __invalidArg_H__
#define __invalidArg_H__
#include<iostream>
class invalidArg
{
public:
    void what() { std::cout << "INVALID_ARGUMENTS\n"; }
};
#endif