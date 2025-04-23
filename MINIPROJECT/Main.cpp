#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unordered_map>
#include "classes.h"
#include "picosha2.h" // For SHA-256 password hashing, downloaded from: https://github.com/okdshin/PicoSHA2
using namespace std;

int main()
{
    vector<UserPassword> userVerify;
    vector<Person> person;
    vector<Group> group;
    vector<Activity> activity;

    int choice1, choice2;
    int controller2 = 0;
    int userindex;

    do
    {
        cout << "|-------------------|" << endl;
        cout << "|Enter:             |" << endl;
        cout << "|1. Login.          |" << endl;
        cout << "|2. Signup.         |" << endl;
        cout << "|3. Exit.           |" << endl;
        cout << "|-------------------|" << endl;
        cin >> choice1;
        cin.ignore();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter an Integer. ";
        }

        choice2 = 0;

        switch (choice1)
        {
        case 1:
        {
            string Username;
            string Password;

            cout << "Enter your UserName: ";
            getline(cin, Username);

            cout << "Enter Password: ";
            getline(cin, Password);

            controller2 = UserPassword::ValidatePassword(Username, Password);

            if (controller2 == 1)
            {
                person.push_back(Person(Username));
                userindex = person.size() - 1;
                cout << "Login Successful." << endl;
            }
            else if (controller2 == 0)
            {
                cout << "Invalid Password." << endl;
            }
            else if (controller2 == 2)
            {
                cout << "Invalid Username." << endl;
            }
            break;
        }
        break;

        case 2:
        {
            string Username;
            string Password1, Password2;

            do
            {
                cout << "\nEnter your UserName: ";
                getline(cin, Username);

                cout << "Enter Password: ";
                getline(cin, Password1);

                cout << "Confirm  Password: ";
                getline(cin, Password2);

                if (Password1 == Password2)
                {
                    userVerify.push_back(UserPassword(Username, Password1));
                    person.push_back(Person(Username));
                    userindex = person.size() - 1;
                    controller2 = 1;
                    break;
                }
                else
                {
                    cout << "Password don't match. " << endl;
                }
            } while (1);
            break;
        }

        case 3:
        {
            controller2 = 0;
            cout << "Thank you for using our program. " << endl;
            break;
        }
        default:
            cout << "Invalid Choice!!!" << endl;
        }

        while (choice2 != 8 && controller2 == 1)
        {
            cout << "\n|--------------------------------------------------|" << endl;
            cout << "| 1. Add Friend.                                   |" << endl;
            cout << "| 2. Add Group.                                    |" << endl;
            cout << "| 3. Add Activity.                                 |" << endl;
            cout << "| 4. Display profile.                              |" << endl;
            cout << "| 5. Display Groups.                               |" << endl;
            cout << "| 6. Display Activity.                             |" << endl;
            cout << "| 7. Show Spendings History.                       |" << endl;
            cout << "| 8. Log out.                                      |" << endl;
            cout << "|--------------------------------------------------|" << endl;
            cout << "Enter your choice: ";
            cin >> choice2;
            cin.ignore();

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter an Integer. ";
            }

            switch (choice2)
            {
            case 1:
            {
                string Name;
                cout << "Enter Friend's UserName: ";
                getline(cin, Name);

                int controller1 = 0;

                controller1 = UserPassword::ValidateUser(Name);

                if (controller1 == 1)
                {
                    person.push_back(Person(Name));
                    break;
                }
                else
                {
                    cout << "User Not Found";
                }
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

                string user = person[userindex].getName();

                group[group.size() - 1].AddPerson(user);

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
                        cout << "No Person found with such username." << endl;
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
                float Bill;
                int IDChoice;
                int Controller = 0;

                cout << "\nEnter: \n1. Add activity with a friend.\n2. Add activity in a group." << endl;
                cout << "Enter choice: ";
                cin >> IDChoice;
                cin.ignore();
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Enter an integer!! ";
                }

                if (IDChoice == 1)
                {
                    cout << "Enter the UserName of the friend: ";
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

                            float splitAmount = Bill / 2;

                            person[i].AddActivity(ActivityName, splitAmount);
                            person[userindex].AddActivity(ActivityName, splitAmount);
                            break;
                        }
                    }

                    if (Controller == 0)
                    {
                        cout << "User not found." << endl;
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

                            group[i].AddActivity(ActivityName, Bill);

                            for (int j = 0; j < Names.size(); j++)
                            {
                                for (int k = 0; k < person.size(); k++)
                                {

                                    Controller = person[k].validatePerson(Names[j]);

                                    if (Controller == 1)
                                    {
                                        person[k].AddActivity(ActivityName, SplitAmount);
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
                    cout << "Invalid Choice!!!";
                }

                break;
            }

            case 4:
            {
                int Controller = 0;

                string Name = person[userindex].getName();

                for (int i = 0; i < person.size(); i++)
                {
                    Controller = person[i].validatePerson(Name);

                    if (Controller == 1)
                    {
                        person[i].DisplayPerson();
                        break;
                    }
                }

                break;
            }
            case 5:
            {
                string GroupName;
                int Controller = 0;

                for (int i = 0; i < group.size(); i++)
                {
                    vector<string> Names = group[i].getPersonNames();

                    for (int j = 0; j < Names.size(); j++)
                    {
                        if (person[userindex].getName() == Names[j])
                        {
                            group[i].DisplayGroup();
                            Controller = 1;
                            break;
                        }
                    }

                    if (Controller == 0)
                    {
                        cout << "You are not a member of any groups." << endl;
                    }
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
                int Controller = 0;

                string Name = person[userindex].getName();

                for (int i = 0; i < person.size(); i++)
                {
                    Controller = person[i].validatePerson(Name);

                    if (Controller == 1)
                    {
                        person[i].ShowSpending();
                        break;
                    }
                }
                break;
            }
            case 8:
                cout << "Logged out successfully." << endl;
                break;

            default:
                cout << "Invalid choice. Try again." << endl;
            }
        }
    } while (choice1 != 3);
    return 0;
}