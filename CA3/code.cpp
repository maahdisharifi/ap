#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
int limit = 0;
struct classPlan
{
    string nameOfDay;
    vector<bool> class1 = vector<bool>(3, false);
    vector<bool> class2 = vector<bool>(3, false);
};
struct ans
{
    string nameOfCourse;
    string class1Teacher;
    string class2Teacher;
    string timeOfClass1;
    string timeOfClass2;
};

struct freeDay
{
    string name;
    vector<bool> isBusy = vector<bool>(3, false);
};
struct teacher
{
    string name;
    vector<freeDay> freeDays;
    int numOfFreeDays;
    vector<string> courses;
};
struct Time
{
    int min;
    int hour;
};
struct course
{
    string name;
    string day1;
    string day2;
    Time start;
    Time end;
};
struct weekDay
{
    string name;
    Time start1;
    Time end1;
    Time start2;
    Time end2;
    Time start3;
    Time end3;
};
bool possibleToChooseCourse(weekDay weekDays, course courses,
                            int time, vector<classPlan> &plan, int class1or2)
{

    if (weekDays.name != courses.day1 && weekDays.name != courses.day2)
    {
        return false;
    }
    if (time == 0)
    {
        if (courses.start.hour > weekDays.start1.hour)
        {
            return false;
        }
        if (courses.start.hour == weekDays.start1.hour && courses.start.min > weekDays.start1.min)
        {
            return false;
        }
        if (courses.end.hour < weekDays.end1.hour)
        {
            return false;
        }
        if (courses.end.hour == weekDays.end1.hour && courses.end.min < weekDays.end1.min)
        {
            return false;
        }
    }
    else if (time == 1)
    {
        if (courses.start.hour > weekDays.start2.hour)
        {
            return false;
        }
        if (courses.start.hour == weekDays.start2.hour && courses.start.min > weekDays.start2.min)
        {
            return false;
        }
        if (courses.end.hour < weekDays.end2.hour)
        {
            return false;
        }
        if (courses.end.hour == weekDays.end2.hour && courses.end.min < weekDays.end2.min)
        {
            return false;
        }
    }
    else if (time == 2)
    {
        if (courses.start.hour > weekDays.start3.hour)
        {
            return false;
        }
        if (courses.start.hour == weekDays.start3.hour && courses.start.min > weekDays.start3.min)
        {
            return false;
        }
        if (courses.end.hour < weekDays.end3.hour)
        {
            return false;
        }
        if (courses.end.hour == weekDays.end3.hour && courses.end.min < weekDays.end3.min)
        {
            return false;
        }
    }
    for (int i = 0; i < plan.size(); i++)
    {

        if ((plan[i].nameOfDay == courses.day1 || plan[i].nameOfDay == courses.day2) && (class1or2 == 1))
        {

            if (plan[i].class1[time] == true)
            {
                return false;
            }
        }
        else if ((plan[i].nameOfDay == courses.day1 || plan[i].nameOfDay == courses.day2) && (class1or2 == 2))
        {

            if (plan[i].class2[time] == true)
            {
                return false;
            }
        }
    }
    return true;
}
bool possibleToChooseTeacher(teacher Teacher, course Course, int Time)
{

    if (Teacher.numOfFreeDays <= 0 || Teacher.courses.size() <= 0)
    {

        return false;
    }
    bool flag = true;
    bool flag2 = true;
    for (int i = 0; i < Teacher.courses.size(); i++)
    {
        if (Teacher.courses[i] == Course.name)
        {
            flag = false;
            break;
        }
    }
    if (flag)
    {
        return false;
    }
    flag = true;
    for (int i = 0; i < Teacher.freeDays.size(); i++)
    {
        if (Teacher.freeDays[i].isBusy[Time] == true && (Teacher.freeDays[i].name == Course.day1 || Teacher.freeDays[i].name == Course.day2))
        {
            return false;
        }
        if (Teacher.freeDays[i].name == Course.day1)
        {
            flag = false;
        }
        else if (Teacher.freeDays[i].name == Course.day2)
        {
            flag2 = false;
        }
    }
    if (flag || flag2)
    {
        return false;
    }

    return true;
}
string comparingTeachersNames(vector<teacher> &TeachersWithMinFreeDays)
{
    teacher TheBestTeacher = TeachersWithMinFreeDays[0];
    int index;
    for (int i = 0; i < TeachersWithMinFreeDays.size(); i++)
    {
        if (TheBestTeacher.name > TeachersWithMinFreeDays[i].name)
        {
            TheBestTeacher = TeachersWithMinFreeDays[i];
            index = i;
        }
    }

    return TeachersWithMinFreeDays[index].name;
}
bool compareStrings(const ans &first, const ans &second)
{
    return first.nameOfCourse < second.nameOfCourse;
}
bool compareCoursesNames(const course &first, const course &second)
{
    return first.name < second.name;
}
void printOutput(vector<ans> &answers)
{
    sort(answers.begin(), answers.end(), compareStrings);
    for (int i = 0; i < answers.size(); i++)
    {
        cout << answers[i].nameOfCourse << '\n';
        if (answers[i].timeOfClass1 == "")
        {
            cout << "Not Found\n";
        }
        else
        {
            cout << answers[i].class1Teacher << ": " << answers[i].timeOfClass1 << '\n';
        }
        if (answers[i].timeOfClass2 == "")
        {
            cout << "Not Found\n";
        }
        else
        {
            cout << answers[i].class2Teacher << ": " << answers[i].timeOfClass2 << '\n';
        }
    }
}
string findTheBestTeacher(vector<teacher> &suitalbeTeachers, int time)
{
    vector<teacher> TeachersWithMinFreeDays;
    int minValue = suitalbeTeachers[0].numOfFreeDays;
    for (int i = 0; i < suitalbeTeachers.size(); i++)
    {
        if (minValue > suitalbeTeachers[i].numOfFreeDays)
        {
            minValue = suitalbeTeachers[i].numOfFreeDays;
        }
    }
    for (int i = 0; i < suitalbeTeachers.size(); i++)
    {
        if (minValue == suitalbeTeachers[i].numOfFreeDays)
        {
            TeachersWithMinFreeDays.push_back(suitalbeTeachers[i]);
        }
    }
    if (TeachersWithMinFreeDays.size() >= 2)
    {
        string nameOfChoosedTeacher = comparingTeachersNames(TeachersWithMinFreeDays);
        return nameOfChoosedTeacher;
    }
    if (TeachersWithMinFreeDays.size() == 1)
    {
        return TeachersWithMinFreeDays[0].name;
    }
}
string findTeacher(course Course, vector<teacher> &teachers, int time)
{
    vector<teacher> suitalbeTeachers;
    for (int i = 0; i < teachers.size(); i++)
    {
        if (possibleToChooseTeacher(teachers[i], Course, time))
        {
            suitalbeTeachers.push_back(teachers[i]);
        }
    }
    if (suitalbeTeachers.size() >= 2)
    {
        string nameOfChoosedTeacher = findTheBestTeacher(suitalbeTeachers, time);
        return nameOfChoosedTeacher;
    }
    else if (suitalbeTeachers.size() == 1)
    {
        return suitalbeTeachers[0].name;
    }
    else if (suitalbeTeachers.size() == 0)
    {
        return "";
    }
}
void fillTeacherSchedule(string name, vector<teacher> &teachers, course Course, int Time)
{
    for (int i = 0; i < teachers.size(); i++)
    {
        if (teachers[i].name == name)
        {

            for (int j = 0; j < teachers[i].freeDays.size(); j++)
            {
                if (teachers[i].freeDays[j].name == Course.day1 || teachers[i].freeDays[j].name == Course.day2)
                {
                    switch (Time)
                    {
                    case 0:
                        teachers[i].freeDays[j].isBusy[0] = true;
                        break;
                    case 1:
                        teachers[i].freeDays[j].isBusy[1] = true;
                        break;
                    case 2:
                        teachers[i].freeDays[j].isBusy[2] = true;
                        break;
                    }
                }
            }
            return;
        }
    }
}
void generateOutput(vector<ans> &answers, string courseName, int time, int class1or2, string teachersName)
{
    for (int i = 0; i < answers.size(); i++)
    {
        if (answers[i].nameOfCourse == courseName && class1or2 == 1)
        {
            answers[i].class1Teacher = teachersName;
            switch (time)
            {
            case 0:
                answers[i].timeOfClass1 = "07:30 09:00";
                break;
            case 1:
                answers[i].timeOfClass1 = "09:30 11:00";
                break;
            case 2:
                answers[i].timeOfClass1 = "11:30 13:00";
                break;
            }
        }
        else if (answers[i].nameOfCourse == courseName && class1or2 == 2)
        {
            answers[i].class2Teacher = teachersName;
            switch (time)
            {
            case 0:
                answers[i].timeOfClass2 = "07:30 09:00";
                break;
            case 1:
                answers[i].timeOfClass2 = "09:30 11:00";
                break;
            case 2:
                answers[i].timeOfClass2 = "11:30 13:00";
                break;
            }
        }
    }
}
void deleteCourse(string name, vector<course> &copyOfCourses)
{
    for (int i = 0; i < copyOfCourses.size(); i++)
    {
        if (copyOfCourses[i].name == name)
        {
            copyOfCourses.erase(copyOfCourses.begin() + i);
            return;
        }
    }
}
void fillPlan(string day1, string day2, vector<classPlan> &plan, int class1or2, int time)
{
    for (int i = 0; i < plan.size(); i++)
    {
        if ((plan[i].nameOfDay == day1 || plan[i].nameOfDay == day2) && (class1or2 == 1))
        {
            plan[i].class1[time] = true;
        }
        else if ((plan[i].nameOfDay == day1 || plan[i].nameOfDay == day2) && (class1or2 == 2))
        {
            plan[i].class2[time] = true;
        }
    }
}
void findTheCourse(const vector<course> &courses, const vector<weekDay> &weekDays,
                   vector<classPlan> &plan, vector<teacher> &teachers, vector<ans> &answers)
{
    int static class1or2 = 1;
    vector<course> copyOfCourses = courses;
    for (int i = 0; i < 5; i++)
    {
        for (int time = 0; time < 3; time++)
        {
            vector<course> result;
            for (int j = 0; j < copyOfCourses.size(); j++)
            {
                if (possibleToChooseCourse(weekDays[i], copyOfCourses[j], time, plan, class1or2))
                {
                    result.push_back(copyOfCourses[j]);
                }
            }
            if (i == 4 && copyOfCourses.size() != 0)
            {
                copyOfCourses.clear();
            }
            if (copyOfCourses.size() == 0)
            {
                class1or2 = 2;
                limit++;
                if (limit == 2)
                {
                    printOutput(answers);
                    return;
                }
                findTheCourse(courses, weekDays, plan, teachers, answers);
                return;
            }
            if (result.size() == 1)
            {
                string name = findTeacher(result[0], teachers, time);
                if (name == "")
                {
                    continue;
                }
                fillPlan(result[0].day1, result[0].day2, plan, class1or2, time);
                fillTeacherSchedule(name, teachers, result[0], time);
                deleteCourse(result[0].name, copyOfCourses);
                generateOutput(answers, result[0].name, time, class1or2, name);
            }

            if (result.size() >= 2)
            {
                //   int size=result.size();
            loop:
                for (int i = 0; i < result.size(); i++)
                {
                    string name = findTeacher(result[i], teachers, time);
                    if (name == "")
                    {
                        result.erase(result.begin() + i);
                        goto loop;
                        //    i=0;
                    }
                }

                sort(result.begin(), result.end(), compareCoursesNames);
                string name = findTeacher(result[0], teachers, time);
                if (name == "")
                {
                    continue;
                }
                fillPlan(result[0].day1, result[0].day2, plan, class1or2, time);
                fillTeacherSchedule(name, teachers, result[0], time);
                deleteCourse(result[0].name, copyOfCourses);
                generateOutput(answers, result[0].name, time, class1or2, name);
            }
        }
    }
}

void splitClock(int &min, int &hour, string str)
{

    hour = stoi(str.substr(0, 2));
    min = stoi(str.substr(3, 2));
}
vector<string> splitInputBySpace(string input)
{

    string word = "";
    vector<string> result;
    for (auto x : input)
    {
        if (x == ' ')
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
void assignTheTeahcersData(const vector<string> &splitedWords, vector<teacher> &teachers, int i)
{
    teachers[i].name = splitedWords[0];
    int numOfDays = stoi(splitedWords[1]);

    for (int j = 0; j < numOfDays; j++)
    {
        freeDay day;
        teachers[i].freeDays.push_back(day);
        teachers[i].freeDays.at(j).name = splitedWords[2 + j];
        teachers[i].numOfFreeDays = numOfDays;
    }
    int numOfCourses = stoi(splitedWords[numOfDays + 2]);
    for (int j = 0; j < numOfCourses; j++)
    {
        string str;
        teachers[i].courses.push_back(str);
        teachers[i].courses[j] = splitedWords[3 + numOfDays + j];
    }
}
void assingTheCoursesData(const vector<string> &splitedWords, vector<course> &courses, int i)
{
    int min = 0;
    int hour = 0;
    courses[i].name = splitedWords[0];
    courses[i].day1 = splitedWords[1];
    courses[i].day2 = splitedWords[2];
    splitClock(min, hour, splitedWords[3]);
    courses[i].start.min = min;
    courses[i].start.hour = hour;
    splitClock(min, hour, splitedWords[4]);
    courses[i].end.min = min;
    courses[i].end.hour = hour;
}
void assignTheweekDaysData(int i, vector<weekDay> &weekDays, vector<classPlan> &plan)
{
    weekDays[i].start1.hour = 07;
    weekDays[i].start1.min = 30;
    weekDays[i].start2.hour = 9;
    weekDays[i].start2.min = 30;
    weekDays[i].start3.hour = 11;
    weekDays[i].start3.min = 30;
    weekDays[i].end1.hour = 9;
    weekDays[i].end1.min = 0;
    weekDays[i].end2.hour = 11;
    weekDays[i].end2.min = 0;
    weekDays[i].end3.hour = 13;
    weekDays[i].end3.min = 0;
    switch (i)
    {
    case 0:
        plan[0].nameOfDay = "Saturday";
        weekDays[0].name = "Saturday";
        break;
    case 1:
        plan[1].nameOfDay = "Sunday";
        weekDays[1].name = "Sunday";
        break;
    case 2:
        plan[2].nameOfDay = "Monday";
        weekDays[2].name = "Monday";
        break;
    case 3:
        plan[3].nameOfDay = "Tuesday";
        weekDays[3].name = "Tuesday";
        break;
    case 4:
        plan[4].nameOfDay = "Wednesday";
        weekDays[4].name = "Wednesday";
        break;
    }
}

int main()
{
    vector<classPlan> plan(5);
    vector<weekDay> weekDays(5);
    for (int i = 0; i < 5; i++)
    {
        assignTheweekDaysData(i, weekDays, plan);
    }
    int numOfTeachers = 0;
    int counter = 0;
    cin >> numOfTeachers;
    int numOfCourses;

    vector<teacher> teachers(numOfTeachers);
    for (int i = 0; i < numOfTeachers; i++)
    {
        string input = "";
        vector<string> splitedWords;
        if (counter == 0)
        {
            cin.ignore();
            counter++;
        }
        getline(cin, input);
        splitedWords = splitInputBySpace(input);
        assignTheTeahcersData(splitedWords, teachers, i);
    }
    cin >> numOfCourses;
    vector<course> courses(numOfCourses);
    vector<ans> answers(numOfCourses);
    counter = 0;
    for (int i = 0; i < numOfCourses; i++)
    {
        string input;
        getline(cin >> ws, input);
        vector<string> splitedInput = splitInputBySpace(input);
        assingTheCoursesData(splitedInput, courses, i);
    }
    for (int i = 0; i < courses.size(); i++)
    {
        answers[i].nameOfCourse = courses[i].name;
    }
    findTheCourse(courses, weekDays, plan, teachers, answers);

    return 0;
}
