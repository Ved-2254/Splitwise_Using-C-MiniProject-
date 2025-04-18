#include <iostream>
#include<string>
#include <vector>
using namespace std;
#pragma once

class Activity 
{
    string NameOfActivity;
    int ActivityID;
    static int Default;
    double Bill;

public:
    Activity(string nameOfActivity, double bill)
    {
        NameOfActivity = nameOfActivity;
        Bill = bill;
    }

    Activity()
    {
        NameOfActivity = "Not Assigned";
        ActivityID = 0;
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

    int validate(string Name)
    {
        if(NameOfActivity.compare(Name) == 0)
            return 1;
        else
            return 0;
    }
    
};

class Person : public Activity
{
    string name;
    int ID;
    static int Default;
    double spendings = 0;
    vector<double> History;

public:
    Person()
    {
        name = "Not Assigned";
        ID = 0;
        spendings = 0;
    }

    Person(string Name)
    {
        name = Name;
        cout << "Person Added!!!" << endl;
        ID = Default;
        Default++;
    }

    void Editspendings(double SplitAmount)
    {
        spendings += SplitAmount;
        History.push_back(SplitAmount);
    }

    void DisplayPerson()
    {
        cout << "Person: " << name << endl;
        cout << "ID: " << ID << endl;
        cout << "Kharcha: " << spendings << endl;
        
    }

    void ShowSpending()
    {
        cout << "\nExpenses: " << endl;
        for (int i = 0; i < History.size(); i++)
        {
            cout << "Expense1 " << i + 1 << ": " << History[i] << endl;
        }
    }

    int validate(string Name)
    {
        if(name.compare(Name) == 0)
            return 1;
        else
            return 0;
    }

};

int Person::Default = 1;

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
    }

    void AddPerson(string Name)
    {
        PersonNames.push_back(Name);
        cout << "Person Added Successfully." << endl;
    }

    double SplitAmount(double Bill)
    {
        return Bill/ PersonNames.size();
    }

    vector <string> getPersonNames()
    {
        return PersonNames;
    }

    int validate(string Name)
    {
        if(groupName.compare(Name) == 0)
            return 1;
        else
            return 0;
    }

};