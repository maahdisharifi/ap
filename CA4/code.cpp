#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
const int NUM_OF_LEVELS = 4;
const int NUM_OF_CMDS = 11;
#define DAY_START 0
#define DAY_END 24
#define NUM_OF_DAYS_IN_MONTH 30
const vector<string> levels = {"junior", "senior", "expert", "team_led"};
const vector<string> commands = {"report_salaries", "report_employee_salary", "report_team_salary", "report_total_hours_per_day",
                                 "report_employee_per_hour", "show_salary_config", "update_salary_config", "add_working_hours", "delete_working_hours",
                                 "update_team_bonus", "find_teams_for_bonus"};
class Salary_configs;
class Teams;
class Employee
{
private:
    int id;
    int totalWorkingHours;
    string name;
    int age;
    string level;
    struct Working_days_hours
    {
        int day;
        vector<string> hours;
    };
    int salary;
    float total_er;
    vector<Working_days_hours> working_days_hours;
    int team_id;
    // cal_total_salary
    // cal_total_er
public:
    void delete_working_hours(int emp_id, int day, vector<Employee> &employees);
    void report_total_hours_per_day(vector<Teams> &teams, int start_day, int end_day, vector<int> &Days, vector<int> &days);
    void cal_total_er(vector<Salary_configs> &salary_configs, vector<Teams> &teams);
    void cal_total_salary(vector<Salary_configs> &salary_configs);
    int calculate_twh(vector<Employee> &employees);
    string get_name() { return name; }
    void assign_working_hours_data(int Day, string time);
    int get_id() { return id; }
    void set_data(int Id, string Name, int Age, string Level);
    int get_twh() { return totalWorkingHours; }
    int get_age() { return age; }
    string get_level() { return level; }
    int get_team_id() { return team_id; }
    int num_of_absent_days();
    int get_salary() { return salary; }
    float get_total_er() { return total_er; }
    void add_working_hours(int day, int start_hour, int end_hour, int emp_id);
    void get_wh_within_period(int start, int end, Employee emp, int one_hour_periods[]);
    ~Employee()
    {
    }
};
class Teams
{
private:
    int team_id;
    int team_head_id;
    vector<int> member_ids;
    int bonus_min_working_hours;
    double bonus_working_hours_max_variance;
    int bonus;

public:
    Teams(int team_id, int team_head_id, vector<int> member_ids, int bonus_min_working_hours, double bonus_working_hours_max_variance)
    {
        this->team_id = team_id;
        this->team_head_id = team_head_id;
        for (int i = 0; i < member_ids.size(); i++)
        {
            this->member_ids.push_back(member_ids[i]);
        }
        this->bonus_min_working_hours = bonus_min_working_hours;
        this->bonus_working_hours_max_variance = bonus_working_hours_max_variance;
        this->bonus = 0;
    }
    ~Teams()
    {
    }
    void print_team_data()
    {
        cout << "Id : " << team_id << endl;
        cout << "head id : " << team_head_id << endl;
        cout << "members : " << endl;
        for (auto x : member_ids)
        {
            cout << x << ' ';
        }
        cout << "bmwh : " << bonus_min_working_hours << endl;
        cout << "bwhmv : " << bonus_working_hours_max_variance << endl;
    }
    int get_team_id() { return team_id; }
    int get_team_head_id() { return team_head_id; }
    int get_bonus() { return bonus; }
    void set_bonus(int bonus_percentage) { bonus = bonus_percentage; }
    vector<int> get_member_ids() { return member_ids; }
    int get_bonus_min_wh() { return bonus_min_working_hours; }
    double get_bonus_wh_max_variance() { return bonus_working_hours_max_variance; }
};
class Salary_configs
{
private:
    string level;
    int base_salary;
    int salary_per_hour;
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;

public:
    int c(int twh);
    string get_level() { return level; }
    Salary_configs(string level, int base_salary, int salary_per_hour, int salary_per_extra_hour, int official_working_hours, int tax_percentage)
    {
        this->level = level;
        this->base_salary = base_salary;
        this->salary_per_hour = salary_per_hour;
        this->salary_per_extra_hour = salary_per_extra_hour;
        this->official_working_hours = official_working_hours;
        this->tax_percentage = tax_percentage;
    }
    int tax_get() { return tax_percentage; }

    ~Salary_configs()
    {
    }
    void print_salary_config(string level)
    {
        cout << "Base Salary: " << base_salary << endl;
        cout << "Salary Per Hour: " << salary_per_hour << endl;
        cout << "Salary Per Extra Hour: " << salary_per_extra_hour << endl;
        cout << "Official Working Hours: " << official_working_hours << endl;
        cout << "Tax: " << tax_percentage << '%' << endl;
    }
    void update(int base_salary, int salary_per_hour, int salary_per_extra_hour, int official_working_hours, int tax_percentage)
    {
        if (base_salary != -1)
            this->base_salary = base_salary;
        if (salary_per_hour != -1)
            this->salary_per_hour = salary_per_hour;
        if (salary_per_extra_hour != -1)
            this->salary_per_extra_hour = salary_per_extra_hour;
        if (official_working_hours != -1)
            this->official_working_hours = official_working_hours;
        if (tax_percentage != -1)
            this->tax_percentage = tax_percentage;
    }
};

vector<int> get_team_member_ids(string input);
void split_time(int &hour1, int &hour2, string time);
vector<Employee> get_employee_data();
void assign_working_hours_to_employees(vector<Employee> &employees);
vector<int> convert_member_ids_to_int(vector<string> id_list_str);
vector<Salary_configs> get_salary_config_data();
void handle_user_input(vector<Employee> &employees, vector<Teams> &teams, vector<Salary_configs> &salary_configs);
vector<Teams> get_teams_data();
void handle_user_command(vector<Employee> &employees, vector<Teams> &teams, vector<Salary_configs> &salary_configs, string line, string command);
string find_command(string line);
void cal_assets(vector<Employee> &employees, vector<Salary_configs> &salary_configs, vector<Teams> &teams);
int get_empOrteam_id(string line, string command);
int find_emp_with_given_id(vector<Employee> employees, int id);
int find_employees_team(int emp_id, vector<Teams> teams);
int find_employees_tax(string emp_level, vector<Salary_configs> salary_configs);
int team_bonus_percentage(int team_id, vector<Teams> teams);
void report_team_salary(vector<Teams> teams, vector<Employee> employees, int given_team_id);
int find_teams_twh(vector<Employee> employees, vector<Teams> teams, int given_team_id);
int find_team_with_given_id(vector<Teams> teams, int given_team_id);
vector<string> split_input_by_space(string input);
void show_salary_config(vector<Salary_configs> salary_configs, string given_level);
void report_employee_per_hour(vector<Employee> employees, string line);
int find_max_in_arr(int emps_in_each_hour[], int input_period_len);
int find_min_in_arr(int emps_in_each_hour[], int input_period_len);
void print_emp_per_hour_data(int start, int end, int one_hour_periods[]);
void print_report_total_hours_per_day(const vector<int> &days, const vector<int> &Days, int start_day);
void update_team_bonus(string line, vector<Teams> &teams);
void update_salary_config(vector<Salary_configs> &salary_configs, string line);
void delete_wh(vector<Employee> &employees, string line);
void add_wh(vector<Employee> &employees, string line);
void report_total_hours_per_day(vector<Employee> employees, string line, vector<Teams> teams);
void find_teams_for_bonus(vector<Teams> teams, vector<Employee> employees, string line);
double calc_wh_variance(vector<int> member_whs);
vector<Teams> find_teams_with_enough_variance(vector<Teams> teams_with_enough_wh, vector<Employee> employees);
vector<Teams> find_teams_with_enough_wh(vector<Teams> teams, vector<Employee> employees);

int main()
{
    vector<Salary_configs> salary_configs = get_salary_config_data();
    vector<Teams> teams = get_teams_data();
    vector<Employee> employees = get_employee_data();
    assign_working_hours_to_employees(employees);
    cal_assets(employees, salary_configs, teams);
    handle_user_input(employees, teams, salary_configs);
    return 0;
}
void Employee::cal_total_er(vector<Salary_configs> &salary_configs, vector<Teams> &teams)
{
    for (int i = 0; i < NUM_OF_LEVELS; i++)
    {
        if (level == salary_configs[i].get_level())
        {
            total_er = ((100 - salary_configs[i].tax_get()) / 100.0) * salary;
            break;
        }
    }
    int emp_team = find_employees_team(id, teams);
    if (emp_team != -1)
    {
        for (int i = 0; i < teams.size(); i++)
        {
            if (teams[i].get_team_id() == emp_team)
            {
                total_er += (teams[i].get_bonus()/100) * salary;
            }
        }
    }
    total_er = ceil(total_er);

}
int Salary_configs::c(int twh)
{
    int extra_hours = twh - official_working_hours;
    if (extra_hours > 0)
    {
        int result = (base_salary + extra_hours * salary_per_extra_hour + official_working_hours * salary_per_hour);
        return result;
    }
    int result = (base_salary + twh * salary_per_hour);
    return result;
}

void Employee::cal_total_salary(vector<Salary_configs> &salary_configs)
{
    for (int i = 0; i < NUM_OF_LEVELS; i++)
    {
        if (level == salary_configs[i].get_level())
        {
            this->salary = salary_configs[i].c(totalWorkingHours);
            break;
        }
    }
}
int Employee::calculate_twh(vector<Employee> &employees)
{
    int totalWH = 0;
    for (int i = 0; i < working_days_hours.size(); i++)
    {
        for (int j = 0; j < working_days_hours[i].hours.size(); j++)
        {
            int hour1, hour2;
            split_time(hour1, hour2, working_days_hours[i].hours[j]);
            totalWH += hour2 - hour1;
        }
    }
    totalWorkingHours = totalWH;
    return 0;
}
vector<string> split_input_by_comma(string input)
{
    string word = "";
    vector<string> result;
    for (auto x : input)
    {
        if (x == ',')
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
vector<Employee> get_employee_data()
{
    vector<Employee> employees;
    string junk, line;
    fstream f_emp("employees.csv", ios::in);
    getline(f_emp, junk);
    while (getline(f_emp, line))
    {
        vector<string> splited_words = split_input_by_comma(line);
        Employee emp;
        emp.set_data(stoi(splited_words[0]), splited_words[1], stoi(splited_words[2]), splited_words[3]);
        employees.push_back(emp);
    }
    return employees;
}
void assign_working_hours_to_employees(vector<Employee> &employees)
{
    string line, junk;
    fstream f_working_hours("working_hours.csv", ios::in);
    getline(f_working_hours, junk);
    while (getline(f_working_hours, line))
    {
        vector<string> splited_words = split_input_by_comma(line);
        int emp_index = find_emp_with_given_id(employees, stoi(splited_words[0]));
        if (emp_index != -1)
            employees[emp_index].assign_working_hours_data(stoi(splited_words[1]), splited_words[2]);
    }
}
void split_time(int &hour1, int &hour2, string time)
{
    hour1 = stoi(time.substr(0, time.find('-')));
    hour2 = stoi(time.substr(time.find('-') + 1));
}
void Employee::assign_working_hours_data(int Day, string time)
{
    for (int i = 0; i < working_days_hours.size(); i++)
    {
        if (Day == working_days_hours[i].day)
        {
            working_days_hours[i].hours.push_back(time);
            return;
        }
    }
    Working_days_hours wdh;
    working_days_hours.push_back(wdh);
    working_days_hours.back().day = Day;
    working_days_hours.back().hours.push_back(time);
}
void Employee::set_data(int Id, string Name, int Age, string Level)
{
    id = Id;
    name = Name;
    age = Age;
    level = Level;
}
vector<Teams> get_teams_data()
{
    string line, junk;
    fstream f_teams("teams.csv", ios::in);
    getline(f_teams, junk);
    vector<Teams> teams;
    while (getline(f_teams, line))
    {
        vector<string> splited_words = split_input_by_comma(line);

        int team_id = stoi(splited_words[0]), team_head_id = stoi(splited_words[1]);
        vector<int> member_ids_str = get_team_member_ids(splited_words[2]);
        int bonus_min_working_hours = stoi(splited_words[3]);
        double bonus_working_hours_max_variance = stod(splited_words[4]);
        Teams team(team_id, team_head_id, member_ids_str, bonus_min_working_hours, bonus_working_hours_max_variance);
        teams.push_back(team);
    }
    return teams;
}
vector<int> get_team_member_ids(string input)
{
    string id_str = "";
    vector<string> id_list_str;
    vector<int> member_ids;
    vector<int> member_list;
    for (auto x : input)
    {
        if (x == '$')
        {
            id_list_str.push_back(id_str);
            id_str = "";
        }
        else
        {
            id_str += x;
        }
    }
    id_list_str.push_back(id_str);
    member_ids = convert_member_ids_to_int(id_list_str);
    return member_ids;
}
vector<int> convert_member_ids_to_int(vector<string> id_list_str)
{
    vector<int> member_ids;
    for (int i = 0; i < id_list_str.size(); i++)
    {
        member_ids.push_back(stoi(id_list_str[i]));
    }
    return member_ids;
}
vector<Salary_configs> get_salary_config_data()
{
    string line, junk;
    fstream f_salary_configs("salary_configs.csv", ios::in);
    getline(f_salary_configs, junk);
    vector<Salary_configs> salary_configs;
    while (getline(f_salary_configs, line))
    {
        vector<string> splited_words = split_input_by_comma(line);
        string level = splited_words[0];
        int base_salary = stoi(splited_words[1]), salary_per_hour = stoi(splited_words[2]), salary_per_extra_hour = stoi(splited_words[3]),
            official_working_hours = stoi(splited_words[4]), tax_percentage = stoi(splited_words[5]);
        Salary_configs salary_config(level, base_salary, salary_per_hour, salary_per_extra_hour, official_working_hours, tax_percentage);
        salary_configs.push_back(salary_config);
    }
    return salary_configs;
}
void handle_user_input(vector<Employee> &employees, vector<Teams> &teams, vector<Salary_configs> &salary_configs)
{
    string line;
    while (getline(cin, line))
    {
        string command = find_command(line);
        if (command == "Invalid input")
        {
            continue;
        }
        else
        {
            handle_user_command(employees, teams, salary_configs, line, command);
        }
    }
}
string find_command(string line)
{
    string cmd;
    for (int i = 0; i < NUM_OF_CMDS; i++)
    {
        if (line.substr(0, commands[i].length()) == commands[i])
        {
            cmd = commands[i];
            return cmd;
        }
    }
    return "Invalid input";
}
void report_salaries(vector<Employee> &employees)
{
    for (int i = 0; i < employees.size(); i++)
    {
        cout << "ID: " << employees[i].get_id() << endl;
        cout << "Name: " << employees[i].get_name() << endl;
        cout << "Total Working Hours: " << employees[i].get_twh() << endl;
        cout << "Total Earning: " << employees[i].get_total_er() << endl;
        cout << "---" << endl;
    }
}
void cal_assets(vector<Employee> &employees, vector<Salary_configs> &salary_configs, vector<Teams> &teams)
{
    for (int i = 0; i < employees.size(); i++)
    {
        employees[i].calculate_twh(employees);
        employees[i].cal_total_salary(salary_configs);
        employees[i].cal_total_er(salary_configs, teams);
    }
}
int get_empOrteam_id(string line, string command)
{
    string id_str = line.substr(command.length() + 1, line.length());
    int id = stoi(id_str);
    return id;
}
void report_employee_salary(vector<Employee> employees, vector<Teams> teams, vector<Salary_configs> salary_configs, int id)
{
    int emp_index = find_emp_with_given_id(employees, id);
    int salary = employees[emp_index].get_salary();
    int bonus = (team_bonus_percentage(find_employees_team(id, teams), teams) / 100.0) * salary;
    int total_earning = (find_employees_tax(employees[emp_index].get_level(), salary_configs) / 100.0) * (salary + bonus);
    if (emp_index != -1)
    {
        cout << "ID: " << employees[emp_index].get_id() << endl;
        cout << "Name: " << employees[emp_index].get_name() << endl;
        cout << "Age: " << employees[emp_index].get_age() << endl;
        cout << "Level: " << employees[emp_index].get_level() << endl;
        if (find_employees_team(id, teams) != -1)
        {
            cout << "Team ID: " << find_employees_team(id, teams) << endl;
        }
        else
        {
            cout << "Team ID: N/A" << endl;
        }
        cout << "Total Working Hours: " << employees[emp_index].get_twh() << endl;
        cout << "Absent Days: " << employees[emp_index].num_of_absent_days() << endl;
        cout << "Salary: " << salary << endl;
        cout << "Bonus: " << bonus << endl;
        cout << "Tax: " << total_earning << endl;
        cout << "Total Earning: " << employees[emp_index].get_total_er() << endl;
    }
    else
        cout << "EMPLOYEE_NOT_FOUND" << endl;
}
int find_employees_tax(string emp_level, vector<Salary_configs> salary_configs)
{
    for (int i = 0; i < salary_configs.size(); i++)
    {
        if (salary_configs[i].get_level() == emp_level)
            return salary_configs[i].tax_get();
    }
    return -1;
}
int team_bonus_percentage(int team_id, vector<Teams> teams)
{
    for (int i = 0; i < teams.size(); i++)
    {
        if (teams[i].get_team_id() == team_id)
        {
            return teams[i].get_bonus();
        }
    }
    return 0;
}
int Employee::num_of_absent_days()
{
    return 30 - working_days_hours.size();
}
int find_emp_with_given_id(vector<Employee> employees, int id)
{
    for (int i = 0; i < employees.size(); i++)
    {
        if (employees[i].get_id() == id)
            return i;
    }
    return -1;
}
int find_employees_team(int emp_id, vector<Teams> teams)
{
    for (int i = 0; i < teams.size(); i++)
    {
        int team_size = teams[i].get_member_ids().size();
        vector<int> team_member_ids = teams[i].get_member_ids();
        for (int j = 0; j < team_size; j++)
        {
            if (emp_id == team_member_ids[j])
            {
                return teams[i].get_team_id();
            }
        }
    }
    return -1;
}
void report_team_salary(vector<Teams> teams, vector<Employee> employees, int given_team_id)
{
    int team_index = find_team_with_given_id(teams, given_team_id);
    if (team_index == -1)
    {
        cout << "TEAM_NOT_FOUND" << endl;
        return;
    }
    vector<int> team_members = teams[team_index].get_member_ids();
    cout << "ID: " << given_team_id << endl;
    cout << "Head ID: " << teams[team_index].get_team_head_id() << endl;
    cout << "Head Name: " << employees[find_emp_with_given_id(employees, teams[team_index].get_team_head_id())].get_name() << endl;
    cout << "Team Total Working Hours: " << (double)find_teams_twh(employees, teams, given_team_id) << endl;
    cout << "Average Member Working Hours: " << find_teams_twh(employees, teams, given_team_id) / (double)team_members.size() << endl;
    cout << "Bonus: " << teams[team_index].get_bonus() << endl;
    cout << "---" << endl;
    for (int i = 0; i < team_members.size(); i++)
    {
        cout << "Member ID: " << team_members[i] << endl;
        cout << "Total Earning: " << employees[find_emp_with_given_id(employees, team_members[i])].get_total_er() << endl;
        cout << "---" << endl;
    }
}
int find_teams_twh(vector<Employee> employees, vector<Teams> teams, int given_team_id)
{
    int team_index = find_team_with_given_id(teams, given_team_id);
    vector<int> team_members = teams[team_index].get_member_ids();
    int team_twh = 0;
    for (int i = 0; i < team_members.size(); i++)
    {
        int emp_id = team_members[i];
        int emp_index = find_emp_with_given_id(employees, emp_id);
        team_twh += employees[emp_index].get_twh();
    }
    return team_twh;
}
int find_team_with_given_id(vector<Teams> teams, int given_team_id)
{
    for (int i = 0; i < teams.size(); i++)
    {
        if (teams[i].get_team_id() == given_team_id)
        {
            return i;
        }
    }
    return -1;
}
vector<string> split_input_by_space(string input)
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
void show_salary_config(vector<Salary_configs> salary_configs, string given_level)
{
    for (int i = 0; i < NUM_OF_LEVELS; i++)
    {
        if (salary_configs[i].get_level() == given_level)
        {
            salary_configs[i].print_salary_config(given_level);
            return;
        }
    }
    cout << "INVALID_LEVEL" << endl;
}
void update_salary_config(vector<Salary_configs> &salary_configs, string line)
{
    vector<string> words = split_input_by_space(line);
    string given_level = words[1];
    for (int i = 0; i < words.size(); i++)
    {
        if (words[i] == "-")
        {
            words[i] = "-1";
        }
    }
    int base_sal = stoi(words[2]), sal_per_hr = stoi(words[3]), sal_per_ex_hr = stoi(words[4]),
        official_wh = stoi(words[5]), tax_perc = stoi(words[6]);

    int sal_config_index = -1;
    for (int i = 0; i < salary_configs.size(); i++)
    {
        if (salary_configs[i].get_level() == given_level)
            sal_config_index = i;
    }
    if (sal_config_index != -1)
    {
        salary_configs[sal_config_index].update(base_sal, sal_per_hr, sal_per_ex_hr, official_wh, tax_perc);
        cout << "OK" << endl;
    }
    else
        cout << "INVALID_LEVEL" << endl;
}
void Employee::report_total_hours_per_day(vector<Teams> &teams, int start_day, int end_day, vector<int> &Days, vector<int> &days)
{
    int sum = 0;
    int hour1 = 0;
    int hour2 = 0;
    for (int i = 0; i < working_days_hours.size(); i++)
    {
        for (int j = 0; j < days.size(); j++)
            if (working_days_hours[i].day == days[j])
            {
                for (int z = 0; z < working_days_hours[i].hours.size(); z++)
                {
                    split_time(hour1, hour2, working_days_hours[i].hours[z]);
                    sum = hour2 - hour1;
                    Days[j] += sum;
                }
            }
    }
}
void Employee::get_wh_within_period(int start, int end, Employee emp, int one_hour_periods[])
{
    for (int i = 0; i < working_days_hours.size(); i++)
    {
        for (int j = 0; j < working_days_hours[i].hours.size(); j++)
        {
            int hour1, hour2;
            string period = working_days_hours[i].hours[j];
            split_time(hour1, hour2, period);
            if (hour1 >= end || hour2 <= start)
                continue;
            if (hour1 >= start && hour2 <= end)
            {
                for (int k = hour1 - start; k < hour2 - start; k++)
                {
                    one_hour_periods[k]++;
                }
                continue;
            }
            if (hour1 >= start && hour2 > end)
            {
                for (int k = hour1 - start; k < end - start; k++)
                {
                    one_hour_periods[k]++;
                }
                continue;
            }
            if (hour1 < start && hour2 <= end)
            {
                for (int k = 0; k < hour2 - start; k++)
                {
                    one_hour_periods[k]++;
                }
                continue;
            }
            if (hour1 <= start && hour2 >= end)
            {
                for (int k = 0; k < end - start; k++)
                {
                    one_hour_periods[k]++;
                }
                continue;
            }
        }
    }
}
void report_employee_per_hour(vector<Employee> employees, string line)
{
    vector<string> words = split_input_by_space(line);
    int start = stoi(words[1]), end = stoi(words[2]);
    if (end <= start || end < DAY_START || end > DAY_END || start < DAY_START || start > DAY_END)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return;
    }
    int one_hour_periods[end - start] = {0};
    for (int i = 0; i < employees.size(); i++)
    {
        employees[i].get_wh_within_period(start, end, employees[i], one_hour_periods);
    }
    print_emp_per_hour_data(start, end, one_hour_periods);
}

void print_emp_per_hour_data(int start, int end, int one_hour_periods[])
{
    double period_avg[end - start] = {0};
    for (int i = start; i < end; i++)
    {
        int curr_period = i - start;
        period_avg[curr_period] = one_hour_periods[curr_period] / NUM_OF_DAYS_IN_MONTH;
        cout << i << '-' << i + 1 << ": " << setprecision(1) << fixed << period_avg[curr_period] << endl;
    }
    int max = find_max_in_arr(one_hour_periods, end - start);
    int min = find_min_in_arr(one_hour_periods, end - start);
    cout << "Period(s) with Max Working Employees: ";
    for (int i = 0; i < end - start; i++)
    {
        if (one_hour_periods[i] == max)
            cout << i + start << '-' << i + start + 1 << ' ';
    }
    cout << endl
         << "Period(s) with Min Working Employees: ";
    for (int i = 0; i < end - start; i++)
    {
        if (one_hour_periods[i] == min)
            cout << i + start << '-' << i + start + 1 << ' ';
    }
    cout << endl;
}
int find_max_in_arr(int emps_in_each_hour[], int input_period_len)
{
    int max = emps_in_each_hour[0];
    for (int i = 0; i < input_period_len; i++)
    {
        if (emps_in_each_hour[i] > max)
            max = emps_in_each_hour[i];
    }
    return max;
}
int find_min_in_arr(int emps_in_each_hour[], int input_period_len)
{
    int min = emps_in_each_hour[0];
    for (int i = 0; i < input_period_len; i++)
    {
        if (emps_in_each_hour[i] < min)
            min = emps_in_each_hour[i];
    }
    return min;
}
bool delete_working_hours_error(int day, int index)
{
    if (index == -1)
    {
        cout << "EMPLOYEE_NOT_FOUND" << endl;
        return false;
    }
    if (day > 30 || day <= 0)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return false;
    }
    return true;
}
void Employee::delete_working_hours(int emp_id, int day, vector<Employee> &employees)
{
    for (int i = 0; i < working_days_hours.size(); i++)
    {
        if (working_days_hours[i].day == day)
        {
            working_days_hours.erase(working_days_hours.begin() + i);
        }
    }
    cout << "OK" << endl;
}
bool report_total_hours_per_day_error(int start_day, int end_day)
{
    if (start_day > end_day || start_day <= 0 || end_day <= 0 || end_day > 30 || start_day > 30)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return false;
    }
    return true;
}
void print_report_total_hours_per_day(const vector<int> &days, const vector<int> &Days, int start_day)
{
    for (int i = 0; i < Days.size(); i++)
    {
        cout << "Day #" << start_day << ": " << Days[i] << endl;
        start_day++;
    }
    cout << "---" << endl;
    cout << endl
         << "Day(s) with Max Working Hours: ";
    auto minmax = minmax_element(Days.begin(), Days.end());
    for (int i = 0; i < Days.size(); i++)
    {
        if (Days[i] == *minmax.second)
        {
            cout << days[i] << " ";
        }
    }
    cout << "\nDay(s) with Min Working Hours: ";
    for (int i = 0; i < Days.size(); i++)
    {
        if (Days[i] == *minmax.first)
        {
            cout << days[i] << " ";
        }
    }
    cout << endl;
}
bool add_working_hours_error(int day, int start_hour, int end_hour, int emp_id,
                             vector<Employee> &employees)
{
    int index = find_emp_with_given_id(employees, emp_id);
    if (index == -1)
    {
        cout << "EMPLOYEE_NOT_FOUND" << endl;
        return true;
    }
    if (day <= 0 || day > 30 || start_hour >= end_hour || start_hour > 24 || end_hour > 24 || start_hour < 0 || end_hour < 0)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return true;
    }
    return false;
}
bool invalid_interval(int h1, int h2, int emp_h1, int emp_h2)
{
    if (h1 < emp_h1 && h2 < emp_h2 && h1 < emp_h2 && h2 < emp_h2)
    {
        cout << "INVALID_INTERVAL" << endl;
        return false;
    }
    return true;
}
void Employee::add_working_hours(int day, int start_hour, int end_hour, int emp_id)
{
    int index = -1;
    for (int i = 0; i < working_days_hours.size(); i++)
    {
        if (day == working_days_hours[i].day)
        {
            index = i;
            for (int j = 0; j < working_days_hours[i].hours.size(); j++)
            {
                int emp_h1, emp_h2;
                split_time(emp_h1, emp_h2, working_days_hours[i].hours[j]);
                if ((invalid_interval(start_hour, end_hour, emp_h1, emp_h2)) == false)
                {
                    return;
                }
            }
        }
    }
    if (index == -1)
    {
        Working_days_hours wdh;
        wdh.day = day;
        wdh.hours.push_back(to_string(start_hour) + "-" + to_string(end_hour));
        working_days_hours.push_back(wdh);
    } ///
    else
    {
        working_days_hours[index].hours.push_back(to_string(start_hour) + "-" + to_string(end_hour));
    }
    cout << "OK" << endl;
}
void update_team_bonus(string line, vector<Teams> &teams)
{
    vector<string> words = split_input_by_space(line);
    int given_team_id = stoi(words[1]), bonus_percentage = stoi(words[2]);
    int team_index = find_team_with_given_id(teams, given_team_id);
    if (team_index == -1)
    {
        cout << "TEAM_NOT_FOUND" << endl;
        return;
    }
    if (bonus_percentage < 0 || bonus_percentage > 100)
    {
        cout << "INVALID_ARGUMENTS" << endl;
        return;
    }
    teams[team_index].set_bonus(bonus_percentage);
    cout << "OK" << endl;
}
void delete_wh(vector<Employee> &employees, string line)
{
    vector<string> result = split_input_by_space(line);
    int emp_id = stoi(result[1]), day = stoi(result[2]), index = find_emp_with_given_id(employees, emp_id);
    if (delete_working_hours_error(day, index) == true)
    {
        employees[index].delete_working_hours(emp_id, day, employees);
    }
}
void add_wh(vector<Employee> &employees, string line)
{
    vector<string> result = split_input_by_space(line);
    int emp_id = stoi(result[1]), day = stoi(result[2]), start_hour = stoi(result[3]), end_hour = stoi(result[4]);
    if (add_working_hours_error(day, start_hour, end_hour, emp_id, employees) == false)
    {
        int index = find_emp_with_given_id(employees, emp_id);
        employees[index].add_working_hours(day, start_hour, end_hour, emp_id);
    }
}
void report_total_hours_per_day(vector<Employee> employees, string line, vector<Teams> teams)
{

    vector<string> result = split_input_by_space(line);
    int start_day = stoi(result[1]), end_day = stoi(result[2]);
    if (report_total_hours_per_day_error(start_day, end_day) == false)
    {
        return;
    }
    vector<int> days, Days(end_day - start_day + 1, 0);
    for (int i = start_day; i <= end_day; i++)
    {
        days.push_back(i);
    }
    for (auto emp : employees)
    {
        emp.report_total_hours_per_day(teams, start_day, end_day, Days, days);
    }
    print_report_total_hours_per_day(days, Days, start_day);
}
void find_teams_for_bonus(vector<Teams> teams, vector<Employee> employees, string line)
{

    vector<Teams> teams_with_enough_wh = find_teams_with_enough_wh(teams, employees);
    vector<Teams> teams_for_bonus = find_teams_with_enough_variance(teams_with_enough_wh, employees);
    if (teams_for_bonus.size() > 0)
    {
        for (int i = 0; i < teams_for_bonus.size(); i++)
        {
            cout << "ID: " << teams_for_bonus[i].get_team_id() << endl;
        }
    }
    else
    {
        cout << "NO_BONUS_TEAMS" << endl;
    }
}
vector<Teams> find_teams_with_enough_variance(vector<Teams> teams_with_enough_wh, vector<Employee> employees)
{
    vector<Teams> teams_for_bonus;
    for (int i = 0; i < teams_with_enough_wh.size(); i++)
    {
        vector<int> member_ids = teams_with_enough_wh[i].get_member_ids();
        vector<int> member_whs;
        double team_variance = 0;
        for (int j = 0; j < member_ids.size(); j++)
        {
            int emp_index = find_emp_with_given_id(employees, member_ids[j]);
            member_whs.push_back(employees[emp_index].get_twh());
        }
        double team_wh_variance = calc_wh_variance(member_whs);
        if (team_wh_variance < teams_with_enough_wh[i].get_bonus_wh_max_variance())
        {
            teams_for_bonus.push_back(teams_with_enough_wh[i]);
        }
    }
    return teams_for_bonus;
}
vector<Teams> find_teams_with_enough_wh(vector<Teams> teams, vector<Employee> employees)
{
    vector<Teams> teams_with_enough_wh;
    for (int i = 0; i < teams.size(); i++)
    {
        vector<int> member_ids = teams[i].get_member_ids();
        int team_twh = 0;
        for (int j = 0; j < member_ids.size(); j++)
        {
            int emp_index = find_emp_with_given_id(employees, member_ids[j]);
            team_twh += employees[emp_index].get_twh();
        }
        if (team_twh > teams[i].get_bonus_min_wh())
        {
            teams_with_enough_wh.push_back(teams[i]);
        }
    }
    return teams_with_enough_wh;
}
double calc_wh_variance(vector<int> member_whs)
{
    int sum = 0;
    for (int i = 0; i < member_whs.size(); i++)
    {
        sum += member_whs[i];
    }
    double mean = (double)sum / (double)member_whs.size();
    double sqDiff = 0;
    for (int i = 0; i < member_whs.size(); i++)
    {
        sqDiff += (member_whs[i] - mean) * (member_whs[i] - mean);
    }
    return sqDiff / member_whs.size();
}
void handle_user_command(vector<Employee> &employees, vector<Teams> &teams, vector<Salary_configs> &salary_configs, string line, string command)
{
    if (command == commands[0])
    {
        report_salaries(employees); 
    }
    else if (command == commands[1])
    {
        int id = get_empOrteam_id(line, command);
        report_employee_salary(employees, teams, salary_configs, id); 
    }
    else if (command == commands[2])
    {
        int team_id = get_empOrteam_id(line, command);
        report_team_salary(teams, employees, team_id); 
    }
    else if (command == commands[3])
    {

        report_total_hours_per_day(employees, line, teams); 
    }
    else if (command == commands[4])
    {
        report_employee_per_hour(employees, line); 
    }
    else if (command == commands[5])
    {
        vector<string> words = split_input_by_space(line);
        string given_level = words[1];
        show_salary_config(salary_configs, given_level); 
    }
    else if (command == commands[6])
    {
        update_salary_config(salary_configs, line); 
        cal_assets(employees, salary_configs, teams);
    }
    else if (command == commands[7])
    {
        add_wh(employees, line); 
        cal_assets(employees, salary_configs, teams);
    }
    else if (command == commands[8])
    {
        delete_wh(employees, line); 
        cal_assets(employees, salary_configs, teams);
    }
    else if (command == commands[9])
    {
        update_team_bonus(line, teams); 
        cal_assets(employees, salary_configs, teams);
    }
    else if (command == commands[10])
    {
        find_teams_for_bonus(teams, employees, line);
    }

    //...
}
