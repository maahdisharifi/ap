#pragma once
#include <string>
using namespace std;
struct error
{
   string Bad_Request = "Bad Request\n";
   string Permission_Denied = "Permission Denied\n";
   string Not_Found = "Not Found\n";
   string Empty = "Empty\n";
};
const error err;