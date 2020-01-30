//
//  main.cpp
//  Task Tracker
//
//  Created by Sage Ren  on 1/28/20.
//  Copyright © 2020 Sage Ren . All rights reserved.
//

#pragma warning(disable:4996);
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
                cout << "\nYou have chosen: "<< choice1 << endl;
                string taskInput;
                cout << "\nInput your Task >> ";
                getline(cin, taskInput);
                cout << "\nThe task you have added is: " << taskInput << "\n";
                Tasks.insert(pair<int, string>(i,taskInput));
                i++;
                break;
            }
            case 2: // add a goal
            {
                cout << "\nYou have chosen: "<< choice2 << endl;
                string goalInput;
                cout << "\nInput your Goal >> ";
                getline(cin, goalInput);
                cout << "\nThe Goal you have added is: { " << goalInput << " }\n";
                Goals.insert(pair<string,int>(goalInput,j));
                j++;
                break;
            }
            case 3: //assign a task to a goal //might be this part
            {
                cout << "\nYou have chosen: "<< choice3 << endl;
                
                for(auto elem : Tasks) //print out the task for choice
                {
                    std::cout << "\n{ " << elem.first << " == " << elem.second << " }\n";
                }
                string whichTask;
                cout << "\nWhat task to assign?\n" << "\nInput the task number >> ";
                getline(cin, whichTask); //find out what task to assign
                int chosenTask = stoi(whichTask);
                cout << "\nThe task you have chosen is: "<< Tasks[chosenTask] << endl;
                
                for(auto elem : Goals) //print out the goal for choice
                {
                    std::cout << "\n{ " << elem.first<< " == " << elem.second << " }";
                }
                string whichGoal;
                cout << "\nWhat goal would you like to assign this task to?\n" << endl;
                cout << "\nInput goal number >> ";
                getline(cin, whichGoal); //get the goal to assign to
                int chosenNumber = stoi(whichGoal);
                
                auto target = Goals.begin();
                while (chosenNumber != target->second)
                {
                    target++;
                }
                
                Tasks[chosenTask] = Tasks[chosenTask] +
                " { " + target->first + " }";
                cout << "\nThe Task " << chosenNumber << " has been updated to " << Tasks[chosenTask] << endl;
                
                break;
            }
            /*case 4: //sort task order
            {
                cout << "\nYou have chosen: "<< choice4 << endl;
            }
            case 5: //delete an entry
            {
                cout << "\nYou have chosen: "<< choice5 << endl;
            }*/
            case 6: //exit
            {
                cout << "\nYou have chosen: "<< choice6 << endl;
                cout << "\nThank you so much for using the Task Tracker!" << endl;
                cout << "\nHave a good one! :)\n" << endl;
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
    cout << "\n====== Tasks ======\n" << endl;
    
    // ========= Writing maps to a txt file ==========
    printMap(Tasks, Goals);
    // ======== Writing maps to a txt file ===========
    
    cout << "\n $$$ Menu options $$$ \n"; //menu options
    cout << choice1 << endl;
    cout << choice2 << endl;
    cout << choice3 << endl;
    //cout << choice4 << endl;
    //cout << choice5 << endl;
    cout << choice6 << endl;

    string userSelection;
    cout << "\nEnter 1-6 to make your selection.\n" << endl;
    cout << "\n>> " << endl;
    getline(cin, userSelection);
    //cin only gets the first component, use getline to get everything
    
    int selection;
    selection = stoi(userSelection);

    return selection;
}

void welcome() //error
{
    cout << "Welcome to Task Tracker :)" << endl;
    chrono::system_clock::time_point today = chrono::system_clock::now();
    time_t tt;
    tt = chrono::system_clock::to_time_t(today);
    cout << "It is " << ctime(&tt) << endl;
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
        << elem.second << endl;
        out << elem.first << " " << elem.second << endl;
    }
    
    for(auto elem : goalMap)
    {
        std::cout << "\n[G] { " << elem.first << " } [ "
        << elem.second << " ]\n";
        out << elem.first << " " << elem.second << endl;
    }
    out.close();
}
