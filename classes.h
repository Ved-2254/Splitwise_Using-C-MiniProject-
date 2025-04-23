#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <unordered_map>            // Part of C++ Standard Library (STL) for efficient key-value storage using a hash table       
#include "picosha2.h"               // For SHA-256 password hashing, downloaded from: https://github.com/okdshin/PicoSHA2
using namespace std;
#pragma once

class UserPassword
{
private:
    string username;
    string password;

public:
    UserPassword(string Username, string pass)
    {
        ofstream file;
        username = Username;
        password = hashPassword(pass);

        file.open("UserData.txt", ios::app);

        if (file.is_open())
        {
            file << "UserName: " << username << ", Password: " << password << endl;
            file.close();
        }
        else
        {
            cout << "Cannot access file. ";
        }
    }

    string hashPassword(const string& password) {
        return picosha2::hash256_hex_string(password);
    }

    static string hashPass(const string& password) {
        return picosha2::hash256_hex_string(password);
    }

    static int ValidateUser(string Username)
    {
        ifstream file;

        file.open("UserData.txt", ios::in);

        file.seekg(0);

        if (file.is_open())
        {
            while (!file.eof())
            {
                string user;

                getline(file, user);
                try
                {
                    int userPos = user.find("UserName:");
                    int passPos = user.find("Password:");

                    if (userPos == string::npos || passPos == string::npos || passPos <= userPos)
                    {
                        continue;
                    }

                    string Name = user.substr(userPos + 10, passPos - userPos - 12);
                    if (Username == Name)
                    {
                        file.close();
                        return 1;
                    }
                }
                catch (const std::out_of_range &e)
                {
                    cout << "User not found";
                    file.close();
                    return 0;
                }
            }
        }
    }

    static int ValidatePassword(string Username, string Password)
    {
        ifstream file;

        string pass = hashPass(Password);

        file.open("UserData.txt", ios::in);

        file.seekg(0);

        if (file.is_open())
        {
            do
            {
                string user;

                getline(file, user);
                try
                {
                    int userPos = user.find("UserName:");
                    int passPos = user.find("Password:");

                    string Name = user.substr(userPos + 10, passPos - userPos - 12);

                    if (Username == Name)
                    {
                        string Pass = user.substr(passPos + 10);
                        if (pass == Pass)
                        {
                            file.close();
                            return 1;
                        }
                        else
                        {
                            file.close();
                            return 0;
                        }
                    }
                }
                catch(const std::out_of_range& e)
                {
                    file.close();
                    return 2;
                }
            } while (1);
        }
        else
        {
            cout << "Cannot access file. ";
            file.close();
            return 3;
        }
    }
};

class Activity
{
protected:
    string NameOfActivity;
    float Bill;

public:
    Activity(string nameOfActivity, float bill)
    {
        NameOfActivity = nameOfActivity;
        Bill = bill;
        cout << "Activity added." << endl;
    }

    Activity()
    {
        NameOfActivity = "Not Assigned";
        Bill = 0;
    }

    void DisplayActivity()
    {
        cout << "Activity: " << NameOfActivity << endl;
        cout << "Bill: " << Bill << endl;
    }

    int validateActivity(string Name)
    {
        if (NameOfActivity.compare(Name) == 0)
            return 1;
        else
            return 0;
    }
};

class Person
{
protected:
    string name;
    float spendings = 0;
    vector<string> HistoryName;
    vector<float> History;

public:
    Person()
    {
        name = "Not Assigned";
        spendings = 0;
    }

    Person(string Name)
    {
        name = Name;
        cout << "Friend Added!!!" << endl;
    }

    string getName()
    {
        return name;
    }

    void AddActivity(string ActivityName, float Bill)
    {
        spendings += Bill;
        HistoryName.push_back(ActivityName);
        History.push_back(Bill);
    }

    void DisplayPerson()
    {
        cout << "UserName: " << name << endl;
        cout << "Spendings: " << spendings << endl;
    }

    void ShowSpending()
    {
        cout << "\nExpenses: " << endl;
        for (int i = 0; i < History.size(); i++)
        {
            cout << i + 1 << ". " << HistoryName[i] << ": " << History[i] << endl;
        }
    }

    int validatePerson(string Name)
    {
        if (name.compare(Name) == 0)
            return 1;
        else
            return 0;
    }
};

class Group
{

    vector<string> PersonNames;
    string groupName;
    float Spending = 0;
    vector<string> HistoryName;
    vector<float> History;

public:
    Group()
    {
        groupName = "Not Assigned.";
    }

    Group(string GroupName)
    {
        groupName = GroupName;
        cout << "Group Name Added." << endl;
    }

    void DisplayGroup()
    {
        cout << "\nDisplaying Group Details. " << endl;
        cout << "Group Name : " << groupName << endl;
        cout << "Group Members : " << endl;
        for (int i = 0; i < PersonNames.size(); i++)
        {
            cout << "Member " << i + 1 << " : " << PersonNames[i] << endl;
        }
        cout << "Total Spendings : " << Spending << endl;

        int choice;
        cout << "Enter 1 to see detailed history: " << endl;
        cin >> choice;

        if(choice == 1)
        {
            for(int i = 0; i < HistoryName.size(); i++)
            {
                cout << i + 1 << ". " << HistoryName[i] << ": " << History[i] << endl;
            }
        }
    }

    void AddPerson(string Name)
    {
        PersonNames.push_back(Name);
        cout << "Member Added Successfully." << endl;
    }

    float SplitAmount(float Bill)
    {
        Spending += Bill;
        return (Bill / PersonNames.size());

    }

    void AddActivity(string ActivityName, float Bill)
    {
        HistoryName.push_back(ActivityName);
        History.push_back(Bill);
    }

    vector<string> getPersonNames()
    {
        return PersonNames;
    }

    int validateGroup(string Name)
    {
        if (groupName.compare(Name) == 0)
            return 1;
        else
            return 0;
    }
};