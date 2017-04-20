#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

class User{
    public:
        User(string newUsername, string newPassword){username = newUsername; password = newPassword;};
        User();
        ~User();
        void changePassword(void);
        
        string getUsername(){return username;};
        void setUsername(string newUsername){username = newUsername;};
        string getPassword(){return username;};
        void setPassword(string newPassword){password = newPassword;};
    protected:
        string username;
        string password;
};

class Student : public User{ //student is derived from user class
    private:
        string first_name;
        string last_name;
        int class_standing;
        string major;
        float gpa;
        string skills;
        string preferred_industry;
    public:
         Student(); //default constructor
        ~Student(); //destructor
        void addEdit_studentInfo(void);
    
        //  * setters
        void setFirstName(string entered_first_name){first_name = entered_first_name;};
        void setLastName(string entered_last_name){last_name = entered_last_name;};
        void setClassStanding(int chosen_class_standing){class_standing = chosen_class_standing;};
        void setMajor(string newMajor){major = newMajor;};
        void setGpa(float newGPA){gpa = newGPA;};
        void setSkill(string newSkills){skills = newSkills;};
        void setPreferred_industry(string new_preferred_industry){preferred_industry = new_preferred_industry;};
        
        //  * getters
        string getFirstName(){};
        string getLastName(){};
        int getClassStanding(){};
        string getMajor(){};
        float getGpa(){};
        string getSkill(){};
        string setPreferred_industry(){};
};

class Employer : public User{
    private:
        string companyName;
        string industry;
        string companyDescription;
    public:
        Employer(string newCompanyName,string newIndustry,string newCompanyDescription){ 
            companyName = newCompanyName; 
            industry = newIndustry;
            companyDescription = newCompanyDescription;
        };
        
        ~Employer();
        vector<string> openJobs;
        
        // * setters
        string getCompanyName(){return companyName;};
        string getIndustry(){return industry;};
        string getCompanyDescription(){return companyDescription;};
        
        // * getters
        void setCompanyName(string newCompanyName){companyName = newCompanyName;};
        void setIndustry(string newIndustry){industry = newIndustry;};
        void setCompanyDescription(string newCompanyDescription){companyDescription = newCompanyDescription;};
};

class Job{
    private:
        Employer* company;
        int class_standing_req;
        vector <string> preferred_majors;
        float preferredGPA;
        float salary;
        vector <string> requiredSkills;
    public:
        Job(Employer*); // constructor that assigns to employer right away.
        ~Job(); //destructor
};

User::User(void){ //default user constructor
    username = "\0"; //initializes to null
    password = "\0"; //initializes to null
}

User::~User(void){
    //destructor
}

Student::Student(void){ //default constructor
    first_name = "\0";
    last_name = "\0";
    class_standing = 0;
    major = "\0";
    gpa = 0.0;
    skills = "\0";
    preferred_industry = "\0";
}

Student::~Student(void){
    //destructor
}

Employer::~Employer(void){
    //destructor
}

Job::Job(Employer* comp){
    company = comp;
    class_standing_req = 0;
    vector <string> preferred_majors; //what to initialize to?
    preferredGPA = 0.0;
    salary = 0.0;
    vector <string> requiredSkills; //what to initialize to?
}

Job::~Job(void){
    //destructor
    delete [] company;
}