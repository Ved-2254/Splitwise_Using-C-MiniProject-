#include <iostream>
#include <vector>
#include <string>
#include "classes.h"
using namespace std;

int main()
{
    vector<Activity> activity;
    vector<Person> person;
    vector<Group> group;

    int choice;

    do
    {
        cout << "\n|--------------------------------------------------|" << endl;
        cout << "| 1. Add Person.                                   |" << endl;
        cout << "| 2. Add Group.                                    |" << endl;
        cout << "| 3. Add Activity.                                 |" << endl;
        cout << "| 4. Display Person.                               |" << endl;
        cout << "| 5. Display Group.                                |" << endl;
        cout << "| 6. Display Activity.                             |" << endl;
        cout << "| 7. Calculate Total Spendings of a person.        |" << endl;
        cout << "| 8. Exit.                                         |" << endl;
        cout << "|--------------------------------------------------|" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            string Name;

            cout << "Enter the name of the Person: ";
            getline(cin, Name);

            person.push_back(Person(Name));
            break;
        }

        case 2:
        {
            string Name;
            string GroupName;
            int Controller = 0;

            cout << "Enter Group Name: ";
            getline(cin, GroupName);

            group.push_back(Group(GroupName));

            do
            {
                cout << "Enter the name of the Person you want to add (OR Enter \"Exit\" to continue): ";
                getline(cin, Name);

                for (int i = 0; i < person.size(); i++)
                {
                    Controller = person[i].validatePerson(Name);

                    if (Controller == 1)
                    {
                        group[group.size() - 1].AddPerson(Name);
                        break;
                    }
                }

                if (Controller == 0 && Name != "Exit")
                {
                    cout << "No Person found with such name." << endl;
                }
            } while (Name != "Exit");
            cout << "Group Created!" << endl;
            break;
        }

        case 3:
        {
            string Name;
            string GroupName;
            string ActivityName;
            double Bill;
            int IDChoice;
            int Controller = 0;

            cout << "\nEnter: \n1. Add activity for a person.\n2. Add activity in a group." << endl;
            cout << "Enter choice: ";
            cin >> IDChoice;
            cin.ignore();

            if (IDChoice == 1)
            {
                cout << "Enter the name of the person: ";
                getline(cin, Name);

                for (int i = 0; i < person.size(); i++)
                {

                    Controller = person[i].validatePerson(Name);

                    if (Controller == 1)
                    {
                        cout << "Enter the name of the activity: ";
                        getline(cin, ActivityName);

                        cout << "Enter the bill: ";
                        cin >> Bill;
                        cin.ignore();

                        activity.push_back(Activity(ActivityName, Bill));

                        person[i].AddActivity(ActivityName, Bill);
                        break;
                    }
                }

                if (Controller == 0)
                {
                    cout << "No Person found with such name." << endl;
                }
            }
            else if (IDChoice == 2)
            {
                cout << "Enter group name: ";
                getline(cin, GroupName);

                int SplitAmount;

                for (int i = 0; i < group.size(); i++)
                {
                    Controller = group[i].validateGroup(GroupName);

                    if (Controller == 1)
                    {
                        cout << "Enter the name of the activity: ";
                        getline(cin, ActivityName);

                        cout << "Enter Bill: ";
                        cin >> Bill;
                        cin.ignore();

                        activity.push_back(Activity(ActivityName, Bill));

                        SplitAmount = group[i].SplitAmount(Bill);

                        vector<string> Names = group[i].getPersonNames();

                        for (int i = 0; i < Names.size(); i++)
                        {
                            for (int j = 0; j < person.size(); j++)
                            {

                                Controller = person[j].validatePerson(Names[i]);

                                if (Controller == 1)
                                {
                                    person[j].AddActivity(ActivityName, SplitAmount);
                                    break;
                                }
                            }
                        }
                    }
                }

                if (Controller == 0)
                {
                    cout << "No Group found with such name." << endl;
                }
            }
            else
            {
                cout << "Invalid Choice";
            }

            break;
        }

        case 4:
        {
            string Name;
            string ActivityName;
            int Controller = 0;

            cout << "Enter the Person Name: ";
            getline(cin, Name);

            for (int i = 0; i < person.size(); i++)
            {
                Controller = person[i].validatePerson(Name);

                if (Controller == 1)
                {
                    person[i].DisplayPerson();
                    break;
                }
            }

            if (Controller == 0)
            {
                cout << "No Person found with such name." << endl;
            }
            break;
        }

        case 5:
        {
            string GroupName;
            int Controller = 0;

            cout << "Enter the group name that you want to display: ";
            getline(cin, GroupName);

            for (int i = 0; i < group.size(); i++)
            {
                Controller = group[i].validateGroup(GroupName);

                if (Controller == 1)
                {
                    group[i].DisplayGroup();
                    break;
                }
            }

            if (Controller == 0)
            {
                cout << "No Group found with such name." << endl;
            }
            break;
        }
        case 6:
        {
            string Name;
            int Controller = 0;

            cout << "Enter the name of the Activity you want to display: ";
            getline(cin, Name);

            for (int i = 0; i < activity.size(); i++)
            {
                Controller = activity[i].validateActivity(Name);

                if (Controller == 1)
                {
                    activity[i].DisplayActivity();
                    break;
                }
            }

            if (Controller == 0)
            {
                cout << "No Activity found with such name." << endl;
            }
            break;
        }
        case 7:
        {
            {
                string Name;
                int Controller = 0;

                cout << "Enter the name of the Person: ";
                getline(cin, Name);

                for (int i = 0; i < person.size(); i++)
                {
                    Controller = person[i].validatePerson(Name);

                    if (Controller == 1)
                    {
                        person[i].ShowSpending();
                        break;
                    }
                }

                if (Controller == 0)
                {
                    cout << "No Person found with such name." << endl;
                }
                break;
            }
        case 8:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
        }
    } while (choice != 8);

    return 0;
}
