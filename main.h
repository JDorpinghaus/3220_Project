#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

class User{
    public:
        User(){};
        ~User(){};
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
        
};

class Employer : public User{
    
    public:
        Employer(){};
        ~Employer(){};
        vector<string> openJobs;
        
        string getCompanyName(){return companyName;};
        void setCompanyName(string newCompanyName){companyName = newCompanyName;};
        string getIndustry(){return industry;};
        void setIndustry(string newIndustry){industry = newIndustry;};
        string getCompanyDescription(){return companyDescription;};
        void setCompanyDescription(string newCompanyDescription){companyDescription = newCompanyDescription;};
        
    private:
        string companyName;
        string industry;
        string companyDescription;
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