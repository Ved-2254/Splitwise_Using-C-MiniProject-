#include <iostream>
#include<string>
#include <vector>
using namespace std;
#pragma once

class Activity 
{
protected:
    string NameOfActivity;
    double Bill;

public:
    Activity(string nameOfActivity, double bill)
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

    double SplitBill()
    {
        double splitAmount;
        splitAmount = Bill/2;
        return splitAmount;
    }

    void DisplayActivity()
    {
        cout << "Activity: " << NameOfActivity << endl;
        cout << "Bill: " << Bill << endl;
    }

    int validateActivity(string Name)
    {
        if(NameOfActivity.compare(Name) == 0)
            return 1;
        else
            return 0;
    }
    
};

class Person : public Activity
{
protected:
    string name;
    double spendings = 0;
    vector<string> HistoryName;
    vector<double> History;

public:
    Person()
    {
        name = "Not Assigned";
        spendings = 0;
    }

    Person(string Name)
    {
        name = Name;
        cout << "Person Added!!!" << endl;
    }

    void AddActivity(string ActivityName, double Bill)
    {
        spendings += Bill;
        HistoryName.push_back(ActivityName);
        History.push_back(Bill);
    }

    void DisplayPerson()
    {
        cout << "Person: " << name << endl;
        cout << "Kharcha: " << spendings << endl;
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
        if(name.compare(Name) == 0)
            return 1;
        else
            return 0;
    }

};

class Group : public Person
{
    
    vector<string> PersonNames;
    string groupName;

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
        cout << "Displaying Group Details. " << endl;
        cout << "Group Name : " << groupName << endl;
        cout << "Group Members : " << endl;
        for(int i = 0; i < PersonNames.size(); i++)
        {
            cout << "Member " << i+1 << " : " << PersonNames[i] << endl;
        }
    }

    void AddPerson(string Name)
    {
        PersonNames.push_back(Name);
        cout << "Person Added Successfully." << endl;
    }

    double SplitAmount(double Bill)
    {
        return (Bill/ PersonNames.size());
    }

    vector <string> getPersonNames()
    {
        return PersonNames;
    }

    int validateGroup(string Name)
    {
        if(groupName.compare(Name) == 0)
            return 1;
        else
            return 0;
    }

};