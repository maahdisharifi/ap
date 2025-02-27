#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>
using namespace std;
struct info
{
  string date;
  string caption;
  int wordOccurence;
};
int compareDate(struct info max, struct info day)
{

  string maxDay, maxYear, maxMonth, dayD, dayY, dayM;
  int i = 0;
  maxYear = max.date.substr(6);
  dayY = day.date.substr(6);
  for (i = 0; i < 5; i++)
  {
    if (i >= 0 && i <= 1)
    {
      maxDay += max.date[i];
      dayD += day.date[i];
    }
    else if (i == 3 || i == 4)
    {
      maxMonth += max.date[i];
      dayM += day.date[i];
    }
  }
  if (dayY < maxYear)
  {
    return 1;
  }
  if (dayY == maxYear && dayM < maxMonth)
  {
    return 1;
  }
  if (dayY == maxYear && dayM == maxMonth && dayD < maxDay)
  {
    return 1;
  }
  return 0;
}
void showTheLongestDay(vector<info> &days)
{
  struct info max = days[0];
  int i = 0;
  for (i = 0; i < days.size(); i++)
  {
    if (max.caption.length() < days[i].caption.length())
    {
      max = days[i];
    }
  }
  if (max.caption.length() <= 20)
  {
    cout << max.date << endl;
    cout << max.caption << endl;
  }
  else
  {
    cout << max.date << endl;
    for (i = 0; i < 20; i++)
    {
      cout << max.caption[i];
    }
    cout << "..." << endl;
  }
}
int wordCounter(char *str, string word)
{
  char *names;

  vector<string> spilitedWords;

  names = strtok(str, " ");
  while (names != NULL)
  {
    spilitedWords.push_back(names);
    names = strtok(NULL, " ");
  }

  int counter = 0;
  for (int i = 0; i < spilitedWords.size(); i++)
  {

    if (word == spilitedWords[i])
    {
      counter++;
    }
  }
  return counter;
}
void writingMemory(vector<info> &days, string input)
{
  if (days.size() == 0)
  {
    if (days[days.size()].caption == "")
    {
      days[days.size()].caption.append(input);
    }
    else
    {
      days[days.size()].caption.append("\n" + input);
    }
    days[0].wordOccurence = 0;
  }
  else
  {
    if (days[days.size() - 1].caption == "")
    {
      days[days.size() - 1].caption.append(input);
    }
    else
    {
      days[days.size() - 1].caption.append("\n" + input);
    }
    days[days.size() - 1].wordOccurence = 0;
  }
}
void identify(string input, vector<info> &days)

{
  string command = input.substr(0, input.find(" "));
  if (command == "start_day")
  {

    struct info day;
    day.date = input.substr(input.find(" ") + 1);
    days.push_back(day);
  }
  else if (command == "show_day")
  {
    string test = input.substr(input.find(" ") + 1);
    int i;
    for (i = 0; i < days.size(); i++)
    {
      if (days[i].date == test)
      {
        cout << days[i].caption << endl;
        break;
      }
    }
  }
  else if (command == "show_the_longest_day")
  {

    showTheLongestDay(days);
  }
  else if (command == "show_the_best_day")
  {
    struct info max = days[0];
    ifstream positiveWords("positive-words.txt");
    string word;
    int i = 0;
    while (getline(positiveWords, word))
    {
      for (i = 0; i < days.size(); i++)
      {

        char *str = strcpy(new char[days[i].caption.length() + 1], days[i].caption.c_str());
        days[i].wordOccurence += wordCounter(str, word);
        delete[] str;
      }
    }
    for (i = 0; i < days.size(); i++)
    {
      if (max.wordOccurence < days[i].wordOccurence)
      {
        max = days[i];
      }
    }
    for (i = 0; i < days.size(); i++)
    {
      if (days[i].wordOccurence == max.wordOccurence)
      {

        int result = compareDate(max, days[i]);
        if (result)
        {
          max = days[i];
        }
      }
    }
    for (i = 0; i < days.size(); i++)
    {
      days[i].wordOccurence = 0;
    }

    cout << max.date << endl;
    if (max.caption.length() < 20)
    {
      cout << max.caption << endl;
    }
    else
    {
      for (i = 0; i < 20; i++)
      {
        cout << max.caption[i];
      }
      cout << "..." << endl;
    }
    positiveWords.close();
  }

  else
  {
    writingMemory(days, input);
  }
}

int main()
{
  vector<info> days;

  string input;
  while (getline(cin, input))
  {

    identify(input, days);
  }
  return 0;
}