#include <iostream>
#include <vector>
#include <string>
#include "classes.h"
using namespace std;

int main()
{
    vector<Activity> Act;
    vector<Person> person;
    vector<Group> group;

    string Name;
    string GroupName;
    string ActivityName;
    double Bill;
    int IDChoice, Controller;

    int choice;

    do
    {
        cout << "1. Add Person. " << endl;
        cout << "2. Add Group." << endl;
        cout << "3. Add Activity." << endl;
        cout << "4. Display Person. " << endl;
        cout << "5. Display Activity." << endl;
        cout << "6. Calculate Total Spendings of a person. " << endl;
        cout << "7. Exit." << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "Enter the name of the Person: ";
            cin.ignore();
            getline(cin, Name);
            person.push_back(Person(Name));
            break;
        }

        case 2:
        {
            cout << "Enter Group Name: ";
            getchar();
            getline(cin, GroupName);

            group.push_back(Group(GroupName));

            do
            {
                cout << "Enter the name of the Person you want to add (OR Enter 0 to continue): ";
                cin.ignore();
                getline(cin, Name);

                for (int i = 0; i < person.size(); i++)
                {
                    Controller = person[i].validate(Name);

                    if (Controller == 1)
                    {
                        group[group.size()].AddPerson(Name);
                        break;
                    }
                }

                if (Controller == 0)
                {
                    cout << "No Person found with such name." << endl;
                }
            } while (Name != "0");
            cout << "Group Created!" << endl;
            break;
        }

        case 3:
        {
            cout << "\nEnter: 1. Add activity for a person.\n2. Add activity in a group." << endl;
            cout << "Enter choice";
            cin >> IDChoice;

            if (IDChoice == 1)
            {
                cout << "Enter the name of the person: ";
                cin.ignore();
                getline(cin, Name);

                cout << "Enter the name of the activity: ";
                cin.ignore();
                getline(cin, ActivityName);

                cout << "Enter the bill: ";
                cin >> Bill;

                Act.push_back(Activity(ActivityName, Bill));

                for (int i = 0; i < person.size(); i++)
                {

                    Controller = person[i].validate(Name);

                    if (Controller == 1)
                    {
                        person[i].Editspendings(Bill);
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
                cin.ignore();
                getline(cin, GroupName);

                int SplitAmount;

                for (int i = 0; i < group.size(); i++)
                {
                    Controller = group[i].validate(GroupName);

                    if (Controller == 1)
                    {
                        SplitAmount = group[i].SplitAmount(Bill);

                        vector<string> Names = group[i].getPersonNames();

                        for (int i = 0; i < Names.size(); i++)
                        {
                            for (int j = 0; j < person.size(); j++)
                            {

                                Controller = person[j].validate(Names[i]);

                                if (Controller == 1)
                                {
                                    person[j].Editspendings(Bill);
                                    break;
                                }

                            }
                        }
                    }
                }

                if (Controller == 0)
                {
                    cout << "No Person found with such name." << endl;
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
            cout << "Enter the Person Name: ";
            cin.ignore();
            getline(cin, Name);

            for (int i = 0; i < person.size(); i++)
            {
                Controller = person[i].validate(Name);

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
            cout << "Enter the name of the Activity you want to display: ";
            cin.ignore();
            getline(cin, Name);

            for (int i = 0; i < Act.size(); i++)
            {
                Controller = person[i].validate(Name);

                if (Controller == 1)
                {
                    Act[i].DisplayActivity();
                    break;
                }
            }

            if (Controller == 0)
            {
                cout << "No Activity found with such name." << endl;
            }
            break;

        case 6:
            cout << "Enter the name of the Person: ";
            cin.ignore();
            getline(cin, Name);

            for (int i = 0; i < person.size(); i++)
            {
                Controller = person[i].validate(Name);

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

        case 7:
            cout << "Exiting program." << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }

    } while (choice != 5);

    return 0;
}