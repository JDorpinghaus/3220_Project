#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "main.h"

using namespace std;


//declares functions:
Student* registerStudent(string userFile); //creates student profile
Student* readInStudent(string,string); //reads in student information
vector<Student*> readInStudents(); 
Employer* readInEmployer(string,string); //reads in employer info from text file
vector<Employer*> readInEmployers(void);
string loginUser();

int userType = 0; //global variable for user type. 0 = student, 1 = employer. default to student
vector <Employer*> masterEmployers; //global variable for vector of all Employers
vector <Student*> masterStudents; 

int main(int argc, char* argv[]){
    //intializes variables
    int choice, runFlag;
    Student *std;
    runFlag = 1;
    masterEmployers = readInEmployers(); //read in all employers and store in vector
    masterStudents = readInStudents();
    cout << "1. Register\t\t2. Login\n"; //initially asks the user if they want to make an account or sign in
    
    while(cin >> choice){
    try{
    if(choice == 1){
       std = registerStudent("users.txt"); //can only register a student if 1 is selected
       exit(0);
    } else if (choice == 2){ //if loging in
        //logging in
        string username;
        string password;
        username = loginUser(); //asks for user name and password to make sure logged in successfully
        
        while(username.empty()){ 
            cout << "Incorrect username/password combination. Try again." << endl;
            username = loginUser(); //if not a valid combination, calls again
        }
        if(userType == 0){
            string firstName;
            try{
                std = readInStudent(username,password); //read in student from text file
            }catch(const ifstream::failure& e){
                cout << "Error openning a file.";
                exit(0);
            }
            while(runFlag == 1){
                std->printMenu(); //prints menu for student
                while(cin >> choice){
                    try{
                    if(choice < 1 || choice > 4){ //exception handling for main menu
                        throw choice;
                    }
                    }catch(const int s){
                        cout << "\nInvalid choice, try again: ";
                        continue;
                    }
                    break;
                }
                switch(choice){
                    case 1:
                        std->editStudentInfo(); //edits student informaition
                        break;
                    case 2:
                        std->viewJobs(masterEmployers); //views matched jobs
                        break;
                    case 3:
                        std->changePassword(); //calls function that changes the password
                        std->studentUpdate(); //writes new password to file
                    case 4:
                        cout << "\nExiting program." << endl;
                        exit(0);
                    default:
                        break;
                }
            }
        }else if (userType == 1){ //type 1 is employer
            //employer
            Employer* e;
            e = readInEmployer(username, password); //reads info in from file
            while(runFlag == 1){
                e->printMenu(); //displayes options menu
                cin >> choice;
                while(choice < 1 || choice > 5){ //prints errpr if invalid option
                    cout << "\nInvalid choice, try again: ";
                    cin >> choice;
                }
                switch(choice){
                    case 1:
                        e->addJob(); //adds a job to their profile
                        break;
                    case 2:
                        e->deleteJob(); //deletes a job from comany profile
                        break;
                    case 3:
                        e->viewMatchedCandidates(masterStudents); //displays macthed candidates
                        break;
                    case 4:
                        e->changePassword(); //method changed password
                        e->employerUpdate(); //writes the new, current info to a file
                    case 5:
                        cout << "\nExiting program." << endl;
                        exit(0);
                    default:
                        break;
                }
            }
        } else {
            //not good
            cout << "Bad userType" << endl; //error check for type of user
            exit(0);
        }
    }else{
        throw choice;
    }
        }catch(const int c){
            cout << choice << " is not valid." << endl;
            cout << "Enter a new choice[1/2]: ";
            continue;
        }catch(...){
            cout << "Something wrong." << endl;
            cout << "Enter a new choice[1/2]: ";
            continue;
        }
    }
    
    delete std; // *Important* delete student object
    return 0;
}

Student* registerStudent(string userFile){
    //initializes variables:
    int count = 0,numUsers;
    string userName, password;
    string username, tempUsername, tempPassword, tempAuthorization;
    vector<string> usernames;
    vector<string> usernames2;
    vector<string> passwords;
    vector<int> authorizations; //vector of ints, 0 means user is student, 1 means user is employer
    vector<string> skillz;
    
    cout << "Create username: ";
    cin >> userName;
    
    // ------------------check if username already exist in the file----------------------------------//
    fstream userFp;
    userFp.open(userFile.c_str(),ios::in); //opens file
    userFp >> numUsers; //first number is the number of users
    while(!userFp.eof()){ //loop until end of file
        userFp >> tempUsername;
        userFp >> tempPassword;
        userFp >> tempAuthorization;
        usernames.push_back(tempUsername); //pushes into vector old usernames
        passwords.push_back(tempPassword);
        authorizations.push_back(stoi(tempAuthorization)); //converts character to integer for type of user 
        count++;
    }
    userFp.close(); //closes file
    for(int i = 0; i < count; i++){ //loops through the vector of usernames
        if(userName == usernames[i]){ //error checks for identical usernames
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
  
    userFp.open(userFile.c_str(),ios::out); //opens file
    userFp << ++count << endl;
    for(int x = 0; x < count; x++){ //reads in information
        userFp << usernames[x] << endl;
        userFp << passwords[x] << endl;
        userFp << authorizations[x] << endl;
    }
    userFp.close(); //closes file
    cout << "Username and Password Register Completed...." << endl;
    // -------------------------------------------------------------------------------------------------//
    
    string first_name;
    string last_name;
    int class_standing;
    string major;
    float gpa;
    string skills;
    string preferred_industry;
    
    //reads in profile information:
    cout << "--------------------------------------------Profile-------------------------------------------------\n\n";
    cout << "First name: ";
    cin >> first_name;
    cout << "Last name: ";
    cin >> last_name;
    cout << "Class standing: ";
    cout << "\n1) Freshman\n2) Sophomore\n3) Junior\n4) Senior";
    cout << "\nPlease enter the number associated with your class standing: ";
    cin >> class_standing;
    cout << "Major: ";
    getline(cin, major); //gets the whole line instead of one word
    getline(cin, major);
    cout << "Gpa: ";
    cin >> gpa;
    cout << "Technical skill(Seperate by comma): ";
    cin >> skills;
    cout << "Preferred industry: ";
    cin >> preferred_industry;
    
    istringstream ss(skills);
    string substr;

    while(getline(ss, substr, ',')) { //gets string until a comma and pushes onto the skills stack
        skillz.push_back(substr);
    }
    
    // ------------------------------------------- create student -------------------------------------------
    //calls the student constructor:
    Student *stobj;
    try{
        stobj = new Student(userName,password,first_name,last_name,class_standing,major,gpa,skillz,preferred_industry);
        if(stobj == NULL){
            throw "Could not create object\n";
        }
    }catch(const char * s){
        cout << s << endl;
        exit(0);
    }
    
    // --------------------------------------------Store student info ---------------------------------------
    userFp.open(("users/" + userName + ".txt"),ios::out); //opens the file
    //write the folloring information:
    userFp << first_name << endl;
    userFp << last_name << endl;
    userFp << class_standing << endl;
    userFp << major << endl;
    userFp << gpa << endl;
    userFp << skills << endl;
    userFp << preferred_industry << endl; 
    userFp.close(); //closes file 
    
    //-----------------------------------store user to studentList.txt--------------------------------/
    count = 0;
    userFp.open("studentList.txt",ios::in); //opens file
    userFp >> count;
    for(int x = 0; x < count; x++){ //reads in information
        userFp >> tempUsername;
        usernames2.push_back(tempUsername);
    }
    userFp.close(); //closes file
    
    userFp.open("studentList.txt",ios::out); //opens file
    userFp << count+1 << endl;
    for(int x = 0; x < count; x++){ 
        userFp << usernames2[x] << endl; //writes to new file to keep track of users
    }
    userFp << userName;
    userFp.close(); //closes file
    
    cout << "\nProfile Completed...." << endl;
    
    return stobj;
}

string loginUser(){
    //declares varibles:
    fstream usersFile;
    int choice, i, numUsers;
    string username, password, tempUsername, tempPassword, tempAuthorization;
    vector<string> usernames;
    vector<string> passwords;
    vector<int> authorizations; //vector of ints, 0 means user is student, 1 means user is employer
    
    usersFile.open("users.txt"); //opens file
    usersFile >> numUsers;
    getline(usersFile, tempUsername); //advance file pointer
    for(i=0;i<numUsers;i++){ //read in list of users from users file and store values in vectors
        getline(usersFile, tempUsername);
        getline(usersFile, tempPassword);
        getline(usersFile, tempAuthorization);
        usernames.push_back(tempUsername);
        passwords.push_back(tempPassword);
        authorizations.push_back(stoi(tempAuthorization)); //converts to integer before pushing onto vector
    }
    usersFile.close(); //closes file
    
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
            return username;
        }
    }
    
    return "";
}

Student* readInStudent(string username,string password){
    //declares variables:
    string first_name;
    string last_name;
    int class_standing;
    string major;
    float gpa;
    string skill;
    vector<string> skills;
    string preferred_industry;
    
    fstream fp;
    try{
        fp.open(("users/" + username + ".txt"),ios::in); //opens the file for that specific username
    }catch(const ifstream::failure& e){
        throw;
    }
    fp >> first_name;
    fp >> last_name;
    fp >> class_standing;
    getline(fp, major); //chew up existing newline
    getline(fp, major);
    fp >> gpa;
    fp >> skill;
    fp >> preferred_industry; 
    fp.close(); //closes file
    
    istringstream ss(skill);
    string substr;

    while(getline(ss, substr, ',')) {
        skills.push_back(substr); //pushes strings separated by commas onto the vector
    }
    //cout << skills[0] << endl;
    //calls Student constructor:
    Student *stobj = new Student(username,password,first_name,last_name,class_standing,major,gpa,skills,preferred_industry);
    return stobj;
}


Employer* readInEmployer(string username,string password){ 
    //declares variables:
    string companyName, companyIndustry, companyDescription, jobTitle, major, skill, title;;
    int numJobs, i, j, classStanding, numMajors, numSkills;
    float gpa, salary;
    vector<Job> jobs;
    
    fstream fp, fp2;
    fp.open(("employers/" + username + "/" + username + ".txt"),ios::in); //opens the employer text file
    fp >> companyName;
    fp >> companyIndustry;
    fp >> numJobs;
    getline(fp, companyDescription); //getline to read full line
    fp.close(); //closes file
    Employer* employer = new Employer(username, password, companyName, companyIndustry, companyDescription);
    
    for(i=0;i<numJobs;i++){
        Job* newJob = new Job(employer); //calls Joc constructor
        title = "job" + to_string(i);
        fp.open("employers/" + username + "/jobs/" + title + "/" + title + ".txt");
        //reads in all the information
        fp >> jobTitle;
        fp >> classStanding;
        fp >> gpa;
        fp >> salary;
        fp >> numMajors;
        fp >> numSkills;
        fp.close(); //closes file
        newJob->setTitle(jobTitle); //using setters to assign the variables
        newJob->setClassStanding(classStanding);
        newJob->setPreferredGPA(gpa);
        newJob->setSalary(salary);
        fp2.open(("employers/" + username + "/jobs/" + title + "/majors.txt"), ios::in);
        for(j=0;j<numMajors;j++){
            getline(fp2, major); //reads in the major
            newJob->addPreferredMajor(major); //adds a major to the job object
        }
        fp2.close();
        
        fp2.open(("employers/" + username + "/jobs/" + title + "/skills.txt"), ios::in);
        for(j=0;j<numSkills;j++){
            fp2 >> skill; //reads in a skill
            newJob->addRequiredSkill(skill); //adds required skills to the job
        }
        fp2.close();
        
        employer->pushJob(*newJob); //pushes the job onto the vector in employer
    }
    return employer;
}

vector <Employer*> readInEmployers(){
    //declares variables:
    fstream fp, fp2;
    vector<Employer*> employers;
    string tempName;
    fstream usersFile;
    int choice, i, numUsers;
    string username, password, tempUsername, tempPassword, tempAuthorization;
    vector<string> usernames;
    vector<string> passwords;
    vector<int> authorizations; //vector of ints, 0 means user is student, 1 means user is employer
    
    //--------read in users from file, only necessary to get password for each employer------
    usersFile.open("users.txt");
    usersFile >> numUsers;
    getline(usersFile, tempUsername); //advance file pointer
    for(i=0;i<numUsers;i++){ //read in list of users from users file and store values in vectors
        getline(usersFile, tempUsername);
        getline(usersFile, tempPassword);
        getline(usersFile, tempAuthorization);
        usernames.push_back(tempUsername);
        passwords.push_back(tempPassword);
        authorizations.push_back(stoi(tempAuthorization)); //converts to integer when pushing it to vector
    }
    usersFile.close();
    //--------------------------------------------------------------------------------------
    
    //Exception handling:
    int numEmployers;
    try{
        fp.open("companyList.txt", ios::in); //tries to open the file
    }
    catch(...){
        cout << "Could not open companyList.txt"; //if can't open, print this
    }
    fp >> numEmployers;
    for(i=0;i<numEmployers;i++){
        fp >> tempName;
        employers.push_back(readInEmployer(tempName, "")); //blank password for now, later change to proper password from user.txt file
    }
    return employers;
}
vector<Student*> readInStudents(){
    //declares variables:
    string first_name;
    string last_name;
    int class_standing;
    string major;
    float gpa;
    string skill;
    vector<string> skills;
    string preferred_industry;
    vector<Student*> studs;
    
    
    fstream firstp,fp;
    int numberOfStudent;
    string username;
    try{ //exception handling
        firstp.open("studentList.txt", ios::in); //tries to open file
    }
    catch(...){
        cout << "Could not open companyList.txt"; //if can't open then print
    }
    firstp >> numberOfStudent;
    for(int i=0;i<numberOfStudent;i++){
        firstp >> username;
        fp.open(("users/" + username + ".txt"),ios::in); //open file
        fp >> first_name;
        fp >> last_name;
        fp >> class_standing;
        getline(fp, major); //chew up newline
        getline(fp, major);
        fp >> gpa;
        fp >> skill;
        fp >> preferred_industry; 
        fp.close();
    
    istringstream ss(skill);
    string substr;

    while(getline(ss, substr, ',')) {
        skills.push_back(substr);
    }
    //cout << skills[0] << endl;
    //calls the student constructor
    Student *stobj = new Student(username,"",first_name,last_name,class_standing,major,gpa,skills,preferred_industry);
    studs.push_back(stobj); //pushes onto the vector of students
    }
    firstp.close();
    fp.close();
    return studs;
}