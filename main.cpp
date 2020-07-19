//
//  main.cpp
//  InterviewQuestioner
//
//  Created by Mack Ragland on 4/11/20.
//  Copyright © 2020 PersonalReview. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
using namespace std;

int main(int argc, const char * argv[]) {
    
    string filePath = "/Users/mackragland/Desktop/InterviewQA.txt";
    srand (time(NULL));
    vector<string> questions;
    vector<vector<string>> answers;
    bool questionPosed = false;
    int answersCounter = 0;
    int questionsCounter = 0;
    answers.clear();
    
    vector<string> tempAnswerHolder;
    tempAnswerHolder.clear();
    
    string line;
    string prevLine = "A";
    ifstream myfile (filePath);
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            if (line[0] == 'Q' && line[1] == ':') { // if the line is a question
                questionsCounter++;
                //cout << "Number of questions taken: " << questionsCounter << endl;
                questions.push_back(line); // add a question to the list
                questionPosed = true; // say that a question has been posed
                
                if ((prevLine[0] == 'Q' && prevLine[1] == ':') && tempAnswerHolder.empty()) { // if the previous line was a question and there are no answers
                    answersCounter++;
                    //cout << "Number of answers taken: " << answersCounter << endl;
                    tempAnswerHolder.push_back("No answer given");
                    answers.push_back(tempAnswerHolder);
                    tempAnswerHolder.clear();
                }
                else if (!(prevLine[0] == 'Q' && prevLine[1] == ':') && tempAnswerHolder.empty() ){
                    //cout << "do nothing!!" << endl;
                } // if the previous line was not a question and there are no answers, do nothing
                
                else if (!(prevLine[0] == 'Q' && prevLine[1] == ':') && !tempAnswerHolder.empty() ){ // if the previous line was not a question and there are answers, then add those answers to the list
                    answersCounter++;
                    //cout << "Number of answers taken: " << answersCounter << endl;
                    answers.push_back(tempAnswerHolder);
                    tempAnswerHolder.clear();
                }
                else if ((prevLine[0] == 'Q' && prevLine[1] == ':') && !tempAnswerHolder.empty()){ // if the previous line was a question and there are answers,
                    cout << "error, answer already filled prior to question" << endl;
                }
                
            }
            else if (questionPosed) {
                
                tempAnswerHolder.push_back(line);
            }
            else {
                cout << "Proper line starting characters not found, please check file so each line begins with Q: or A:";
                questionPosed = false;
                
            }
            prevLine = line;
        }
        myfile.close();
        
    }
    
    else cout << "Unable to open file";
    string response;
    while (1) {
        int numberOfQuestions = questions.size();
        int questionNumberToPose = rand() % numberOfQuestions;
        
        cout << questions[questionNumberToPose-1] << endl;
        getline(cin, response);
        
        if (response == " ") {
            cout << "Answers:" << endl;
            for (auto it = answers[questionNumberToPose-1].begin(); it != answers[questionNumberToPose-1].end(); it++) {
                if (*it == "") {
                    continue;
                }
                cout << *it << endl;
            }
        }
        else{
            break;
        }
        
        cout << endl << endl;
        
    }
    
    
    
}
