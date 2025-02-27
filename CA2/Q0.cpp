#include <iostream>
#include <string>
#include <cctype>
using namespace std;
string toUpper(string input)
{
    if (input == "")
    {
        return "";
    }
    string result;
    result += char(toupper(input[0]));
    return result + toUpper(input.substr(1));
}

int main()
{

    string input;
    while (getline(cin, input))
    {
        string result = toUpper(input);
        cout << result << endl;
    }

    return 0;
}