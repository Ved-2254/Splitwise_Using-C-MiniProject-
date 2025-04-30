#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "picosha2.h" // For SHA-256 password hashing, downloaded from: https://github.com/okdshin/PicoSHA2
using namespace std;
#pragma once

class User
{
private:
    string username;
    float spendings = 0;
    vector<string> HistoryName;
    vector<float> History;
    vector<string> Friend;

public:
    User()
    {
        username = "Not Assigned";
    };

    User(string Username, string pass)
    {
        ofstream file;
        username = Username;
        string password = hashPassword(pass);

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

    User(string &Username)
    {
        username = Username;
    }

    string hashPassword(string &password)
    {
        return picosha2::hash256_hex_string(password);
    }

    static string hashPass(string &password)
    {
        return picosha2::hash256_hex_string(password);
    }

    static int ValidateUser(string &Username)
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
                    file.close();
                    return 0;
                }
            }
        }
    }

    static int ValidatePassword(string &Username, string &Password)
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
                catch (const std::out_of_range &e)
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

    void AddFriend(string &Name, int &Cont)
    {
        int Controller = 0;
        for (int i = 0; i < Friend.size(); i++)
        {
            if (Name == Friend[i])
            {
                Controller = 1;
                Cont = 1;
                break;
            }
        }
        if (Controller == 0)
        {
            Friend.push_back(Name);
        }
    }

    void DisplayFriends()
    {
        cout << "Friends list: " << endl;
        for(int i = 0; i < Friend.size(); i++)
        {
            cout << i+1 << ". " << Friend[i] << endl;
        }
    }

    string getName()
    {
        return username;
    }

    int getNoOfFriends()
    {
        return Friend.size();
    }

    void AddActivity(string ActivityName, float Bill)
    {
        spendings += Bill;
        HistoryName.push_back(ActivityName);
        History.push_back(Bill);
    }

    void DisplayPerson()
    {
        cout << "\n+===============================================+" << endl;
        cout << "UserName: " << username << endl;
        cout << "Spendings: " << spendings << endl;
        cout << "+===============================================+" << endl;
    }

    void ShowSpending()
    {
        cout << "\n+===============================================+" << endl;
        cout << "Expenses: " << endl;
        for (int i = 0; i < History.size(); i++)
        {
            cout << i + 1 << ". " << HistoryName[i] << ": " << History[i] << endl;
        }
        cout << "Total Spendings: " << spendings << endl;
        cout << "+===============================================+" << endl;
    }

    int validatePerson(string &Name)
    {
        if (username.compare(Name) == 0)
            return 1;
        else
            return 0;
    }

    int validateFriend(string &Name)
    {
        for (int i = 0; i < Friend.size(); i++)
        {
            if (Friend[i].compare(Name) == 0)
                return 1;
        }
        return 0;
    }

    void DisplayActivity(string &ActivityName, int &Controller)
    {
        cout << "\n+===============================================+";
        for (int i = 0; i < HistoryName.size(); i++)
        {
            if (HistoryName[i] == ActivityName)
            {
                cout << "\nActivity: " << HistoryName[i] << endl;
                cout << "Bill: " << History[i] << endl;
                Controller = 1;
                continue;
            }
        }
        cout << "+===============================================+" << endl;
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

    Group(string &GroupName)
    {
        groupName = GroupName;
        cout << "Group Name Added." << endl;
    }

    void DisplayGroup()
    {
        cout << "\n+===============================================+" << endl;
        cout << "Displaying Group Details. " << endl;
        cout << "Group Name : " << groupName << endl;
        cout << "Group Members : " << endl;
        for (int i = 0; i < PersonNames.size(); i++)
        {
            cout << "Member " << i + 1 << " : " << PersonNames[i] << endl;
        }
        cout << "Total Spendings : " << Spending << endl;

        int choice;
        cout << "\nEnter 1 to see detailed history: ";
        cin >> choice;

        if (choice == 1)
        {
            for (int i = 0; i < HistoryName.size(); i++)
            {
                cout << i + 1 << ". " << HistoryName[i] << ": " << History[i] << endl;
            }
        }
        cout << "+===============================================+" << endl;
    }

    void AddPerson(string &Name)
    {
        PersonNames.push_back(Name);
    }

    float SplitAmount(float &Bill)
    {
        Spending += Bill;
        return (Bill / PersonNames.size());
    }

    void AddActivity(string &ActivityName, float &Bill)
    {
        HistoryName.push_back(ActivityName);
        History.push_back(Bill);
    }

    vector<string> getPersonNames()
    {
        return PersonNames;
    }

    int validateGroup(string &Name)
    {
        if (groupName.compare(Name) == 0)
            return 1;
        else
            return 0;
    }
};