#include <cstdlib>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include "main.h"

using namespace std;

Student* registerStudent(string userFile);
Student* readInStudent(string,string);
Employer* readInEmployer(string,string);
string loginUser(string &pw);
void printCompanyMenu(void);
void printStudentMenu(void);

int userType = 0; //global variable for user type. 0 = student, 1 = employer. default to student

int main(int argc, char* argv[]){
    int choice, runFlag;
    Student *std;
    runFlag = 1;
    
    cout << "1. Register\t\t2. Login\n";
    cin >> choice;
    
    if(choice == 1){
       std = registerStudent("users.txt");
    } else if (choice == 2){
    //logging in
    string username;
    string password;
    username = loginUser(password);
    
    while(username.empty()){
        cout << "Incorrect username/password combination. Try again." << endl;
        username = loginUser(password);
    }
    if(userType == 0){
        string firstName;
        //student
        std = readInStudent(username,password); //read in student from text file
        while(runFlag == 1){
            printStudentMenu();
            cin >> choice;
            while(choice < 1 || choice > 3){
                cout << "\nInvalid choice, try again: ";
                cin >> choice;
            }
            
            switch(choice){
                case 1:
                    std->editStudentInfo();
                    break;
                case 2:
                    //std->viewJobs() iteration 2
                    break;
                case 3:
                    cout << "\nExiting program." << endl;
                    exit(0);
                default:
                    break;
            }
        }
    } else if (userType == 1){
        //employer
        Employer* e;
        e = readInEmployer(username, password);
        while(runFlag == 1){
            printCompanyMenu();
            cin >> choice;
            while(choice < 1 || choice > 4){
                cout << "\nInvalid choice, try again: ";
                cin >> choice;
            }
            switch(choice){
                case 1:
                    e->addJob();
                    break;
                case 2:
                    e->deleteJob();
                    break;
                case 3:
                    //e->viewMatchedCandidates() //iteration 2
                    break;
                case 4:
                    cout << "\nExiting program." << endl;
                    exit(0);
                default:
                    break;
            }
        }
    } else {
        //not good
        cout << "Bad userType" << endl;
        exit(0);
    }
    
    // testing //
    /*int i;
    vector<Employer> companies;
    
    // -- generateCompanies function takes in a companyList.txt file as argument
    // -- open that file and create an object for each company
    // -- return a vector of type Employer
     companies = generateCompanies("companyList.txt");
     
    cout << companies.size() << endl;
    for (i=0; i<companies.size(); i++){
        //cout << companies[i].companyName << ": " << companies[i].industry << endl <<  companies[i].companyDescription << endl << endl;
        cout << companies[i].getCompanyName() << ": " << companies[i].getIndustry() << endl <<  companies[i].getCompanyDescription() << endl << endl;
    }*/
    

    }
    
    // *Important* delete student object
    delete std;
    
    return 0;
}

Student* registerStudent(string userFile){
    int count = 0,numUsers;
    string userName, password;
    string username, tempUsername, tempPassword, tempAuthorization;
    vector<string> usernames;
    vector<string> passwords;
    vector<int> authorizations; //vector of ints, 0 means user is student, 1 means user is employer
    
    cout << "Create username: ";
    cin >> userName;
    
    // ------------------check if username already exist in the file----------------------------------//
    fstream userFp;
    userFp.open(userFile.c_str(),ios::in);
    userFp >> numUsers;
    while(!userFp.eof()){
        userFp >> tempUsername;
        userFp >> tempPassword;
        userFp >> tempAuthorization;
        usernames.push_back(tempUsername);
        passwords.push_back(tempPassword);
        authorizations.push_back(stoi(tempAuthorization));
        count++;
    }
    userFp.close();
    for(int i = 0; i < count; i++){
        if(userName == usernames[i]){
            cout << "Username already been taken!\nPlease enter new username: ";
            cin >> userName;
            i = -1;
        }
    }
    // ------------------------------------------------------------------------------------------------//
    
    cout << "Create password: ";
    cin >> password;
    
    // ------------------------------- Update the users.txt file ---------------------------------------//
    usernames.push_back(userName);
    passwords.push_back(password);
    authorizations.push_back(0);
  
    userFp.open(userFile.c_str(),ios::out);
    userFp << ++count << endl;
    for(int x = 0; x < count; x++){
        userFp << usernames[x] << endl;
        userFp << passwords[x] << endl;
        userFp << authorizations[x] << endl;
    }
    userFp.close();
    cout << "Username and Password Register Completed...." << endl;
    // -------------------------------------------------------------------------------------------------//
    
    string first_name;
    string last_name;
    int class_standing;
    string major;
    float gpa;
    string skills;
    string preferred_industry;
    
    cout << "--------------------------------------------Profile-------------------------------------------------\n\n";
    cout << "First name: ";
    cin >> first_name;
    cout << "Last name: ";
    cin >> last_name;
    cout << "Class standing: ";
    cin >> class_standing;
    cout << "Major: ";
    cin >> major;
    cout << "Gpa: ";
    cin >> gpa;
    cout << "Technical skill(Seperate by comma): ";
    cin >> skills;
    cout << "Preferred industry: ";
    cin >> preferred_industry;
    
    
    
    // ------------------------------------------- create student -------------------------------------------
    Student *stobj = new Student(userName,password,first_name,last_name,class_standing,major,gpa,skills,preferred_industry);
    
    // --------------------------------------------Store student info ---------------------------------------
    userFp.open(("students/" + userName + ".txt"),ios::out);
    userFp << first_name << endl;
    userFp << last_name << endl;
    userFp << class_standing << endl;
    userFp << major << endl;
    userFp << gpa << endl;
    userFp << skills << endl;
    userFp << preferred_industry << endl; 
    userFp.close();
    cout << "\nProfile Completed...." << endl;
    
    return stobj;
}

string loginUser(string& pw){
    fstream usersFile;
    int choice, i, numUsers;
    string username, password, tempUsername, tempPassword, tempAuthorization;
    vector<string> usernames;
    vector<string> passwords;
    vector<int> authorizations; //vector of ints, 0 means user is student, 1 means user is employer
    
    usersFile.open("users.txt");
    usersFile >> numUsers;
    getline(usersFile, tempUsername); //advance file pointer
    for(i=0;i<numUsers;i++){ //read in list of users from users file and store values in vectors
        getline(usersFile, tempUsername);
        getline(usersFile, tempPassword);
        getline(usersFile, tempAuthorization);
        usernames.push_back(tempUsername);
        passwords.push_back(tempPassword);
        authorizations.push_back(stoi(tempAuthorization));
    }
    usersFile.close();
    
    //debugging
    //cout << "testUsername: " << usernames[1] << " testPassword: " << passwords[1] << endl;
    
    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    
    for(i=0;i<numUsers;i++){ //check each stored username for a match, when match is found check password for that index value
        if(usernames[i] == username && passwords[i] == password){
            //account found, login successful
            userType = authorizations[i]; //set global userType (0 for student, 1 for employer)
            pw = password;
            return username;
        }
    }
    
    return "";
}

void printCompanyMenu(void){
    cout << "\n\nWhat would you like to do?\n\t1: Add a job\n\t2: Delete a job\n\t3: View matched candidates\n\t4: Quit" << endl << endl;
}

void printStudentMenu(void){
    cout << "\n\nWhat would you like to do?\n\t1: Edit matching information\n\t2: View matched jobs\n\t3: Quit" << endl << endl;
}

Student* readInStudent(string username,string password){
    string first_name;
    string last_name;
    int class_standing;
    string major;
    float gpa;
    string skills;
    string preferred_industry;
    
    fstream fp;
    fp.open(("users/" + username + ".txt"),ios::in);
    fp >> first_name;
    fp >> last_name;
    fp >> class_standing;
    fp >> major;
    fp >> gpa;
    fp >> skills;
    fp >> preferred_industry; 
    fp.close();
    Student *stobj = new Student(username,password,first_name,last_name,class_standing,major,gpa,skills,preferred_industry);
    return stobj;
}

Employer* readInEmployer(string username,string password){
    string companyName, companyIndustry, companyDescription, jobTitle, major, skill, title;;
    int numJobs, i, j, classStanding, numMajors, numSkills;
    float gpa, salary;
    vector<Job> jobs;
    
    fstream fp, fp2;
    fp.open(("employers/" + username + "/" + username + ".txt"),ios::in);
    fp >> companyName;
    fp >> companyIndustry;
    getline(fp, companyDescription); //getline to read full line
    fp >> numJobs;
    fp.close();
    Employer* employer = new Employer(username, password, companyName, companyIndustry, companyDescription);
    
    for(i=0;i<numJobs;i++){
        Job newJob(NULL);
        title = "job" + to_string(i);
        fp.open("employers/" + username + "/jobs/" + title + "/" + title + ".txt");
        fp >> jobTitle;
        fp >> classStanding;
        fp >> gpa;
        fp >> salary;
        fp >> numMajors;
        fp >> numSkills;
        newJob.setTitle(jobTitle);
        newJob.setClassStanding(classStanding);
        newJob.setPreferredGPA(gpa);
        newJob.setSalary(salary);
        fp2.open(("employers/" + username + "/jobs/" + title + "/majors.txt"), ios::in);
        for(j=0;j<numMajors;j++){
            fp >> major;
            newJob.addPreferredMajor(major);
        }
        fp2.close();
        
        fp2.open(("employers/" + username + "/jobs/" + title + "/skills.txt"), ios::in);
        for(j=0;j<numSkills;j++){
            fp >> skill;
            newJob.addRequiredSkill(skill);
        }
        fp2.close();
        employer->pushJob(newJob);
    }
    return employer;
}