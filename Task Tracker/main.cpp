//
//  main.cpp
//  Task Tracker
//
//  Created by Sage Ren  on 1/28/20.
//  Copyright © 2020 Sage Ren . All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

string choice1 = " 1. Add a task ";
string choice2 = " 2. Add a goal ";
string choice3 = " 3. Assign a task to a goal ";
//string choice4 = "4. Sort task order";
//string choice5 = "5. Delete task or goal";
string choice6 = " 6. Exit the tracker ";

vector<string> Tasks; //task order, and input
vector<string> Goals; //goal input and ID

void welcome();
void txtToV(); // read only
void printT(); // read only
void printG();
string mainMenu();
string getDate(); //read only
int parseUser(string);

void welcome()
{
    cout << "======== Welcome to Task Tracker :) ======== " << endl;
    string date = getDate();
    cout << "==== It is " << date << " ====\n";
}
void txtToV()//generate vectors
{
    // Creating vectors from Parsing a txt file =========
    fstream out;
    out.open("tasks.txt");
    string line;
    vector<string> entries;
    
    while (getline(out, line)) //input each line into a vector
    {
        entries.push_back(line);
    }
    
    string str;
    vector<string>::iterator it; //declaring iterator
    for (it = entries.begin(); it < entries.end(); it++)
    {
        str = *it;
        char c = '@';
        if (str.front() != c) //if 1st elem is @ -- goal
        {
            Tasks.push_back(str);
        }
        else
        {
            Goals.push_back(str);
        }
    }
    out.close();
    //Creating vectors from Parsing a txt file =========
} //read only
void printT()
{
    int i = 0;
    fstream out("tasks.txt");
    vector<int> taskSequence;
    for (string elem : Tasks){
        i++;
        cout << " ( Task ) " << i << " [ " << elem << " ]" << endl;
        taskSequence.push_back(i);
    }
    out.close();
}
void printG()
{
    fstream out("tasks.txt");
    vector<int> goalSequence;
    int j = 0;
    for (string elem : Goals){
        j++;
        cout << " < Goal > " << j << " {{ " << elem << " }}" << endl;
        goalSequence.push_back(j);
    }
    out.close();
}
string mainMenu()
{
    cout << "\n \\\\\\\\\\==== TASKS ====////////// \n" << endl;
    // ========= print v to console ==========
    printT();
    printG();
    // ======== print v to console ===========
    cout << "\n //////////==== TASKS ====\\\\\\\\\\ \n" << endl;
    
    cout << "\n $$$ Menu options $$$ \n"; //menu options
    cout << choice1 << choice2 << choice3 << choice6 << endl;
    //cout << choice4 << endl;
    //cout << choice5 << endl;
    
    string userSelection;
    cout << "\n *** Enter 1-6 to Make Your Selection >> ";
    getline(cin, userSelection);
    //cin only gets the first component, use getline to get everything
    
    return userSelection;
}
string getDate()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int day = ltm->tm_mday;
    
    string date = to_string(year) + to_string(month) + to_string(day);
    
    return date;
}
int parseUser(string input)
{
    getline(cin, input);
    stringstream geek(input);
    int x = 0;
    geek >> x;
    
    return x;
}

int main()
{
    txtToV();
    welcome();
    string userSelection = mainMenu();
    int selection = parseUser(userSelection);
    
    while ( selection )
    {
        switch ( selection )
        {
            case 1: // add new task
            {
                //FILE OPEN
                fstream out("tasks.txt", ios::app); // open txt
                string taskInput;
                cout << "\n\n *** Please Enter New Task Here >> ";
                getline(cin, taskInput);
                string task = getDate() + " - " + taskInput; // format input into Tasks
                Tasks.push_back(task);
                out << task << endl; // to txt
                cout << "\n ==== Added Task >> " << task << endl; // to console
                //FILE CLOSE
                out.close(); // close txt
                break;
            }
            case 2: // add new goal
            {
                //FILE OPEN
                fstream out("tasks.txt", ios::app); // open txt
                string goalInput;
                cout << "\n\n *** Please Enter New Goal Here >> ";
                getline(cin, goalInput);
                string goal = "@" + getDate() + " { " + goalInput + " } "; // format input to Goals
                Goals.push_back(goal);
                out << goal << endl; // to txt
                cout << "\n ==== Added Goal >> { " << goal << " }" << endl; // to console
                //FILE CLOSE
                out.close(); // close txt
                break;
            }
            case 3: //assign a goal to a task
            {
                string taskNumber;
                string goalNumber;
                
                //get the task
                cout << "\n\n ==== To assign a task to a goal";
                cout << "\n ==== Please first select your task by entering the task number";
                cout << "\n ==== Please then select the goal by entering the goal number" << endl;
                printT();
                cout << "\n *** Please First Enter Task Number Here >> ";
                int taskN = parseUser(taskNumber); // transfer user answer to an int
                string selectedT = Tasks[taskN];
                
                //get the goal to assign the task to
                cout << "\n\n ==== What goal would you like to assign " << selectedT << " to?";
                printG();
                cout << "\n *** Please Enter the Goal Number Here >> ";
                int goalN = parseUser(goalNumber);
                string selectedG = Goals[goalN];
                
                //update the task
                Tasks[taskN] = Tasks[taskN] + " { " + Goals[goalN] + " } ";
                
                // FILE OPEN
                fstream out("tasks.txt", ios::trunc); // open the file to rewrite everything
                
                for (string elem : Tasks){ out << elem << endl; } // rewriting tasks
                for (string elem : Goals){ out << elem << endl; } // rewriting goals
                
                cout << "\n\n ==== Congratulations! Your task has been updated! ==== " << endl;
                cout << " ==== " << Tasks[taskN] << " ==== " << endl;
                // FILE CLOSE
                out.close();
                break;
            }
            case 6: //exit command
            {
                cout << "\n ==== You have chosen: "<< choice6 << endl;
                cout << "\n ==== Thank you so much for using the Task Tracker! ==== " << endl;
                cout << "\n ==== Have a good one! :) ====\n" << endl;
                exit(1);
            }
        }
        mainMenu(); //looping
    }
    
    printT();
    printG();
    cout << " !!!!!! BOOOM! !!!!!\n" << " !!!!! Your Tracker Exploded !!!!! \n";
    
    return 0;
}

/*#pragma warning(disable:4996);
#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>
#include <ctime>
#include <vector>
#include <fstream>
#include <map>
#include <algorithm>

using namespace std;

map<int, string> Tasks; //task order, and input
map<string, int> Goals; //goal input and ID

string choice1 = "1. Add a task";
string choice2 = "2. Add a goal";
string choice3 = "3. Assign a task to a goal";
//string choice4 = "4. Sort task order";
//string choice5 = "5. Delete task or goal";
string choice6 = "6. Exit the tracker";

//Task newTask(int i, int j, string Input);
//Goal newGoal(int g, string Input);

int getChoice();
void welcome();
void txtToMap(string); //opens the txt file
void printMap(map<int, string>, map<string, int>); //writes to txt file, and print in console

int main() {
    txtToMap("tasks.txt"); //generate Map Goals and Tasks
    welcome(); //greeting
    auto lastTask = Tasks.rbegin();
    auto lastGoal = Goals.end();
    int i = lastTask->first + 1; //task order, task does not have ID
    int j = lastGoal->second + 1;
    int choice = getChoice(); //user option
    
    while (choice > 0)
    {
        switch (choice)
        {
            case 1: //add a task
            {
                cout << "\n ==== You have chosen: "<< choice1 << endl;
                string taskInput;
                cout << " ==== Input your Task >> ";
                getline(cin, taskInput);
                cout << "\n ==== The task you have added is: " << taskInput << "\n";
                Tasks.insert(pair<int, string>(i,taskInput));
                i++;
                break;
            }
            case 2: // add a goal
            {
                cout << "\n ==== You have chosen: "<< choice2 << endl;
                string goalInput;
                cout << " ==== Input your Goal >> ";
                getline(cin, goalInput);
                cout << "\n ==== The Goal you have added is: { " << goalInput << " }\n";
                Goals.insert(pair<string,int>(goalInput,j));
                j++;
                break;
            }
            case 3: //assign a task to a goal //might be this part
            {
                cout << "\n ==== You have chosen: "<< choice3 << endl;
                
                for(auto elem : Tasks) //print out the task for choice
                {
                    std::cout << "\nTasks = [ " << elem.first << " == " << elem.second << " ]";
                }
                string whichTask;
                cout << "\n\n ==== What task to assign? ==== \n" << "\n ==== Input the task number >> ";
                getline(cin, whichTask); //find out what task to assign
                int chosenTask = stoi(whichTask);
                cout << "\n ==== The task you have chosen is: "<< Tasks[chosenTask] << endl;
                
                for(auto elem : Goals) //print out the goal for choice
                {
                    std::cout << "\nGoals = { " << elem.first<< " == " << elem.second << " }";
                }
                string whichGoal;
                cout << "\n\n ==== What goal would you like to assign this task to? ==== \n" << endl;
                cout << "\n ==== Input goal number >> ";
                getline(cin, whichGoal); //get the goal to assign to
                int chosenNumber = stoi(whichGoal);
                
                auto target = Goals.begin();
                while (chosenNumber != target->second)
                {
                    target++;
                }
                
                Tasks[chosenTask] = Tasks[chosenTask] +
                " { " + target->first + " }";
                cout << "\n ==== The Task " << chosenNumber << " has been updated to " << Tasks[chosenTask] << endl;
                
                break;
            }
            case 4: //sort task order
            {
                cout << "\nYou have chosen: "<< choice4 << endl;
            }
            case 5: //delete an entry
            {
                cout << "\nYou have chosen: "<< choice5 << endl;
            }*/
/*
            case 6: //exit
            {
                cout << "\n ==== You have chosen: "<< choice6 << endl;
                cout << "\n ==== Thank you so much for using the Task Tracker! ==== " << endl;
                cout << "\n ==== Have a good one! :) ====\n" << endl;
                exit(1);
            }
            default: //input a positive integer outside of 1-6
            {
                cout << "\n!!!Please input a number from 1 to 6 in the menu.!!!\n" << endl;
                break;
            }
        }
        choice = getChoice(); //execute in loop till user select 6.exit
    }

    cout << "\n!!!!Boom! Your program exploded!!!!\n" << endl;
    return 0;
}


int getChoice()
{
    cout << " -------------- TASKS --------------- " << endl;
    
    // ========= Writing maps to a txt file ==========
    printMap(Tasks, Goals);
    // ======== Writing maps to a txt file ===========
    cout << "\n-------------- TASKS ---------------\n" << endl;
    
    cout << "\n $$$ Menu options $$$ \n"; //menu options
    cout << choice1 << endl;
    cout << choice2 << endl;
    cout << choice3 << endl;
    //cout << choice4 << endl;
    //cout << choice5 << endl;
    cout << choice6 << endl;

    string userSelection;
    cout << "\n ==== Enter 1-6 to make your selection ==== " << endl;
    cout << "\n ==== >> " << endl;
    getline(cin, userSelection);
    //cin only gets the first component, use getline to get everything
    
    int selection;
    selection = stoi(userSelection);

    return selection;
}

void welcome() //error
{
    cout << "======== Welcome to Task Tracker :) ======== " << endl;
    chrono::system_clock::time_point today = chrono::system_clock::now();
    time_t tt;
    tt = chrono::system_clock::to_time_t(today);
    cout << "==== It is " << ctime(&tt) << endl;
}

void txtToMap(string fileName)//generate maps
{
    // ========== Creating Maps from Parsing a txt file =========
    fstream out;
    out.open(fileName);
    string line;
    vector<string> entries;
    
    while (getline(out, line)) //input each line into a vector
    {
        entries.push_back(line);
    }
    
    string str;
    vector<string>::iterator it; //declaring iterator
    for (it = entries.begin(); it < entries.end(); it++)
    {
        str = *it;
        if (isdigit(str.front())) //if 1st elem is int --> tasks
        {
            int i = (int)str.front();
            str.erase(remove_if(str.begin(), str.end(), [](char c) { return isdigit(c); } ), str.end());
            Tasks.insert(pair<int, string>(i,str));
        }
        else // if last elem is int --> Goals
        {
            int j = (int)str.back();
            str.erase(remove_if(str.begin(), str.end(), [](char c) { return isdigit(c); } ), str.end());
            Goals.insert(pair<string, int>(str,j));
        }
    }
    out.close();
    // ========== Creating Maps from Parsing a txt file =========
}

//print the map
void printMap(map<int,string> taskMap, map<string, int> goalMap)
{
    ofstream out ("tasks.txt", ios::out | ios::trunc);
    
    for(auto elem : taskMap)
    {
        std::cout << "\n(T) " << elem.first << " >> "
        << elem.second ;
        out << elem.first << elem.second << endl;
    }
    
    for(auto elem : goalMap)
    {
        std::cout << "\n[G] { " << elem.first << " } [ "
        << elem.second << " ]";
        out << elem.first << elem.second << endl;
    }
    out.close();
}
*/
