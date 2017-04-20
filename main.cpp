#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include "main.h"

using namespace std;

vector<Employer> generateCompanies(string filename);
void generateStudents(string filename);
Employer companyFileToObject(string filename);
string loginUser(void);
void printCompanyMenu(void);
void printStudentMenu(void);

int userType = 0; //global variable for user type. 0 = student, 1 = employer

int main(int argc, char* argv[]){
    //logging in
    string username;
    username = loginUser();
    while(username.empty()){
        cout << "Incorrect username/password combination. Try again." << endl;
        username = loginUser();
    }
    if(userType == 0){
        //student
        printStudentMenu();
    } else if (userType == 1){
        //employer
        printCompanyMenu();
    } else {
        //not good
        cout << "Bad userType" << endl;
        exit(0);
    }
    
    // testing //
    int i;
    vector<Employer> companies;
    
    // -- generateCompanies function takes in a companyList.txt file as argument
    // -- open that file and create an object for each company
    // -- return a vector of type Employer
     companies = generateCompanies("companyList.txt");
    
    cout << companies.size() << endl;
    for (i=0; i<companies.size(); i++){
        //cout << companies[i].companyName << ": " << companies[i].industry << endl <<  companies[i].companyDescription << endl << endl;
        cout << companies[i].getCompanyName() << ": " << companies[i].getIndustry() << endl <<  companies[i].getCompanyDescription() << endl << endl;
    }
    
    
    // genarateStudents will store a student first and last name to the studentList.txt file
    // maybe we can also store their username and password for the account.
    //generateStudents("studentList.txt");
    
    
    
    return 0;
}

vector<Employer> generateCompanies(string filename){
    ifstream companiesFile;
    vector<Employer> companies;
    fstream currentFile;
    string line;
    int i;
    int numCompanies;
    
    companiesFile.open(filename.c_str()); //change to filename
    
    // * get number of companies that will be attending career fair
    companiesFile >> numCompanies;
    
    cout << "number of companies: " << numCompanies << endl;
    for(i=0;i<numCompanies;i++){
        //getline(companiesFile, line);
        companiesFile >> line;
        
        //test printing that line out
        cout << line << endl;
        
        companies.push_back(companyFileToObject("employers/" + line + ".txt"));
    }
    companiesFile.close();
    return companies;
}

void generateStudents(string filename){
    fstream studentFiles;
    studentFiles.open(filename.c_str(),ios::app);
    string firstName = "justin", lastName = "bieber";
    
    // print first and last name to the studentList.txt file
    studentFiles << firstName + " " + lastName << endl;
    studentFiles.close();
    
    // test code
    string n,l;
    studentFiles.open(filename.c_str(),ios::in);
    studentFiles >> n >> l;
    cout << n + " " + l << endl;
}

Employer companyFileToObject(string filename){
    
     ifstream currentFile;
     string name,industry,description;
     
     
     //   * open a company file that locate in folder called "employers"
     //   * store those informations in variable and close a file
     currentFile.open(filename.c_str());
     getline(currentFile, name);
     getline(currentFile, industry);
     getline(currentFile, description);
     currentFile.close();
     
     // create an object with constructor
     Employer company(name,industry,description);
     
     
     return company;
}

string loginUser(void){
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
            return username;
        }
    }
    
    return "";
}

void printCompanyMenu(void){
    cout << "\nWhat would you like to do?\n\t1: Add a job\n\t2: Edit a job\n\t3: View matched candidates" << endl << endl;
}

void printStudentMenu(void){
    cout << "\nWhat would you like to do?\n\t1: Edit matching information\n\t2: View matched jobs" << endl << endl;
}

void Student::addEdit_studentInfo(void){
    //print info
    //ask what to add/edit
    //assign changes
}