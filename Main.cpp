#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "classes.h"
#include "picosha2.h" // For SHA-256 password hashing, downloaded from: https://github.com/okdshin/PicoSHA2
using namespace std;

int main()
{
    cout << "\n\n             _____       ___ __ _       ___         " << endl;
    cout << "            / ___/____  / (_) /| |     / (_)_______ " << endl;
    cout << "            \\__ \\/ __ \\/ / / __/ | /| / / / ___/ _ \\" << endl;
    cout << "           ___/ / /_/ / / / /_ | |/ |/ / (__  )  __/" << endl;
    cout << "          /____/ ____/_/_/\\__/ |__/|__/_/____/\\___/ " << endl;
    cout << "              /_/                                   " << endl;

    vector<User> userVerify;
    vector<Group> group;

    string Username;
    int choice1, choice2;
    int Controller2 = 0;
    int userindex;

    do
    {
        cout << "\n\n+=====================+" << endl;
        cout << "|       Welcome       |" << endl;
        cout << "+=====================+" << endl;
        cout << "| [1] Login.          |" << endl;
        cout << "| [2] Signup.         |" << endl;
        cout << "| [3] Exit.           |" << endl;
        cout << "+---------------------+" << endl;
        cout << "Enter your choice: ";
        cin >> choice1;
        cin.ignore();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Enter an Integer. ";
        }

        Controller2 = 0;
        choice2 = 0;

        switch (choice1)
        {
        case 1:
        {
            string Password;

            do
            {
                cout << "\nEnter your UserName (Enter \"Return\" to go back): ";
                getline(cin, Username);

                if (Username != "Return")
                {
                    cout << "Enter Password: ";
                    getline(cin, Password);

                    Controller2 = User::ValidatePassword(Username, Password);

                    if (Controller2 == 1)
                    {
                        userVerify.push_back(User(Username));
                        for (int i = 0; i < userVerify.size(); i++)
                        {
                            if (Username == userVerify[i].getName())
                            {
                                userindex = i;
                                break;
                            }
                        }
                        cout << "LOGIN SUCCESSFULL!" << endl;
                    }
                    else if (Controller2 == 0)
                    {
                        cout << "INVALID PASSWORD!" << endl;
                    }
                    else if (Controller2 == 2)
                    {
                        cout << "INVALID USERNAME!" << endl;
                    }
                    break;
                }
            } while (Username != "Return");
            break;
        }

        case 2:
        {
            string Password1, Password2;
            int Controller;

            do
            {
                cout << "\nEnter your UserName(Enter \"Return\" to go back): ";
                getline(cin, Username);

                if (Username != "Return")
                {
                    cout << "Enter Password: ";
                    getline(cin, Password1);

                    cout << "Confirm  Password: ";
                    getline(cin, Password2);

                    if (Password1.length() >= 8 && (Password1.length() <= 16))
                    {
                        if (Password1 == Password2)
                        {
                            Controller = User::ValidateUser(Username);

                            if (Controller == 0)
                            {
                                userVerify.push_back(User(Username, Password1));
                                cout << "SIGNED UP SUCCESSFULLY" << endl;
                                for (int i = 0; i < userVerify.size(); i++)
                                {
                                    if (Username == userVerify[i].getName())
                                    {
                                        userindex = i;
                                    }
                                }
                                Controller2 = 1;
                                break;
                            }
                            else if (Controller == 1)
                            {
                                cout << "USERNAME ALREADY TAKEN!" << endl;
                            }
                        }
                        else
                        {
                            cout << "PASSWORD DON'T MATCH!" << endl;
                        }
                    }
                    else
                    {
                        cout << "Password must be between 8 and 16 characters!" << endl;
                    }
                }
            } while (Username != "Return");
            break;
        }

        case 3:
        {
            Controller2 = 0;
            cout << "\n\n\n\n***** Thank you for using our application! *****" << endl;
            break;
        }
        default:
            cout << "Invalid choice! Try again..." << endl;
        }

        while (choice2 != 9 && Controller2 == 1)
        {
            cout << "\n+================================================+" << endl;
            cout << "|                   Dashboard                    |" << endl;
            cout << "+===============================================+" << endl;
            cout << "| [1] Add Friend        | [2] Create Group       |" << endl;
            cout << "| [3] Add Activity      | [4] View Profile       |" << endl;
            cout << "| [5] View Friends list | [6] My Groups          |" << endl;
            cout << "| [7] Activity Details  | [8] Spending History   |" << endl;
            cout << "|------------------------------------------------|" << endl;
            cout << "|                  [9] LOGOUT                    |" << endl;
            cout << "+------------------------------------------------+" << endl;
            cout << "Enter your choice (1-8): ";
            cin >> choice2;
            cin.ignore();

            if (cin.fail())
            {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Enter an Integer, ";
            }

            switch (choice2)
            {
            case 1:
            {
                string Name;
                cout << "\nEnter your Friend's UserName: ";
                getline(cin, Name);

                int Controller1 = 0;
                int Cont;
                int Controller3 = 0;

                Controller1 = User::ValidateUser(Name);

                string user = userVerify[userindex].getName();
                if (Name == user)
                {
                    cout << "You cannot add yourself as a Friend. " << endl;
                    Controller1 = 2;
                }

                if (Controller1 == 1)
                {
                    userVerify[userindex].AddFriend(Name, Cont);
                    for (int i = 0; i < userVerify.size(); i++)
                    {
                        if (Name == userVerify[i].getName())
                        {
                            Controller3 = 1;
                            break;
                        }
                    }
                    if (Controller3 == 0)
                    {
                        userVerify.push_back(User(Name));
                    }
                    for (int i = 0; i < userVerify.size(); i++)
                    {
                        if (Name == userVerify[i].getName())
                        {
                            userVerify[i].AddFriend(Username, Cont);
                            if(Cont == 1)
                            {
                                cout << "IS ALREADY A FRIEND." << endl;
                            }
                        }
                    }
                    cout << "FRIEND ADDED! " << endl;
                    break;
                }
                else
                {
                    cout << "Username not found!" << endl;
                }
                break;
            }

            case 2:
            {
                string Name;
                string GroupName;
                int Controller = 0;
                int Controller3 = 1;
                do
                {                
                    cout << "\nEnter Group Name(Enter \"Return\" to go back): ";
                    getline(cin, GroupName);

                    for (int i = 0; i < group.size(); i++)
                    {
                        vector<string> Names = group[i].getPersonNames();

                        for (int j = 0; j < Names.size(); j++)
                        {
                            if (userVerify[userindex].getName() == Names[j])
                            {
                                cout << "Group already exists with same name. " << endl;
                                Controller = 1;
                                break;
                            }
                        }
                    }
                }while(Controller == 1);

                if (GroupName != "Return" && Controller != 1)
                {
                    group.push_back(Group(GroupName));

                    string user = userVerify[userindex].getName();

                    group[group.size() - 1].AddPerson(user);

                    cout << "\n";

                    do
                    {
                        Controller = 0;

                        cout << "Enter the name of the Person you want to add (OR Enter \"Exit\" to continue): ";
                        getline(cin, Name);

                        Controller = userVerify[userindex].validateFriend(Name);

                        if (Name == user)
                        {
                            cout << "You are already in the Group. " << endl;
                            Controller = 2;
                        }

                        if (Name == user)
                        {
                            Controller = 2;
                        }

                        if (Controller == 1)
                        {
                            group[group.size() - 1].AddPerson(Name);
                            cout << "Member Added Successfully." << endl;
                        }

                        if (Controller == 0 && Name != "Exit" && Controller != 2)
                        {
                            cout << "No such friend exists." << endl;
                        }
                    } while (Name != "Exit");
                    cout << "GROUP CREATED!" << endl;
                }
                break;
            }

            case 3:
            {
                string Name;
                string GroupName;
                string ActivityName;
                float Bill;
                int IDChoice;
                int Controller1 = 0;
                int Controller2 = 0;

                cout << "\n+---------------------------------+" << endl;
                cout << "|1. Add activity with a friend.   |" << endl;
                cout << "|2. Add activity in a group.      |" << endl;
                cout << "+---------------------------------+" << endl;
                cout << "Enter choice: ";
                cin >> IDChoice;
                cin.ignore();
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Enter an integer. ";
                }

                if (IDChoice == 1)
                {
                    cout << "\nEnter the UserName of your Friend: ";
                    getline(cin, Name);

                    int NoOfFriends = userVerify[userindex].getNoOfFriends();
                    Controller1 = userVerify[userindex].validateFriend(Name);

                    if (Controller1 == 1)
                    {
                        for (int i = 0; i < userVerify.size(); i++)
                        {
                            Controller2 = userVerify[i].validatePerson(Name);

                            if (Controller2 == 1)
                            {
                                cout << "Enter the name of the activity: ";
                                getline(cin, ActivityName);

                                cout << "Enter the bill: ";
                                cin >> Bill;
                                cin.ignore();

                                float splitAmount = Bill / 2;

                                userVerify[i].AddActivity(ActivityName, splitAmount);
                                userVerify[userindex].AddActivity(ActivityName, splitAmount);
                                cout << "ACTIVITY ADDED!" << endl;
                                break;
                            }
                        }
                    }

                    if (Controller1 == 0)
                    {
                        cout << "FRIEND NOT FOUND!" << endl;
                    }
                }
                else if (IDChoice == 2)
                {
                    cout << "\nEnter the Name of the Group: ";
                    getline(cin, GroupName);

                    float SplitAmount;

                    for (int i = 0; i < group.size(); i++)
                    {
                        Controller1 = group[i].validateGroup(GroupName);

                        if (Controller1 == 1)
                        {
                            cout << "Enter the name of the activity: ";
                            getline(cin, ActivityName);

                            cout << "Enter Bill: ";
                            cin >> Bill;
                            cin.ignore();

                            SplitAmount = group[i].SplitAmount(Bill);

                            vector<string> Names = group[i].getPersonNames();

                            group[i].AddActivity(ActivityName, Bill);

                            int NoOfFriends = userVerify[userindex].getNoOfFriends();

                            cout << "ACTIVITY ADDED!" << endl;

                            for (int j = 0; j < Names.size(); j++)
                            {
                                for (int k = 0; k < userVerify.size(); k++)
                                {

                                    Controller2 = userVerify[k].validatePerson(Names[j]);

                                    if (Controller2 == 1)
                                    {
                                        userVerify[k].AddActivity(ActivityName, SplitAmount);
                                        break;
                                    }
                                }
                            }
                        }
                        else
                        {
                            cout << "NO GROUOP FOUND!" << endl;
                        }
                    }
                }
                else
                {
                    cout << "INVALID CHOICE!" << endl;
                }

                break;
            }

            case 4:
            {
                int Controller = 0;

                cout << "\n";

                string Name = userVerify[userindex].getName();

                int NoOfFriends = userVerify[userindex].getNoOfFriends();

                Controller = userVerify[userindex].validatePerson(Name);

                if (Controller == 1)
                {
                    userVerify[userindex].DisplayPerson();
                    break;
                }

                break;
            }

            case 5:
            {
                userVerify[userindex].DisplayFriends();
                break;
            }

            case 6:
            {
                string GroupName;
                int Controller = 0;

                cout << "\n";

                for (int i = 0; i < group.size(); i++)
                {
                    vector<string> Names = group[i].getPersonNames();

                    for (int j = 0; j < Names.size(); j++)
                    {
                        if (userVerify[userindex].getName() == Names[j])
                        {
                            group[i].DisplayGroup();
                            Controller = 1;
                            break;
                        }
                    }
                }

                if (Controller == 0)
                {
                    cout << "NO GROUPS ADDED YET!" << endl;
                }
                break;
            }

            case 7:
            {
                string ActivityName;
                int Controller = 0;

                cout << "\nEnter the name of the Activity: ";
                getline(cin, ActivityName);

                userVerify[userindex].DisplayActivity(ActivityName, Controller);

                if (Controller == 0)
                {
                    cout << "No Activity found with such name." << endl;
                }
                break;
            }

            case 8:
            {
                int Controller = 0;

                string Name = userVerify[userindex].getName();

                Controller = userVerify[userindex].validatePerson(Name);

                if (Controller == 1)
                {
                    userVerify[userindex].ShowSpending();
                    break;
                }
                break;
            }

            case 9:
            {
                cout << "              *****LOGGED OUT*****              " << endl;
                break;
            }

            default:
            {
                cout << "Invalid choice! Try again..." << endl;
            }
            }
        }
    } while (choice1 != 3);
    return 0;
}