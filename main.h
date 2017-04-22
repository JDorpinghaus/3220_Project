#include <cstdlib>
#include <iostream>
#include <vector>
using namespace std;

class User{
    public:
        User(string newUsername, string newPassword){username = newUsername; password = newPassword;};
        User();
        ~User();
        void changePassword(string);
        
        // *getters
        string getUsername(){return username;};
        string getPassword(){return username;};
        
        // *setters
        void setUsername(string newUsername){username = newUsername;};
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
        vector <string> skills;
        string preferred_industry;
        void studentUpdate();
    public:
         Student(); //default constructor
         Student(string, string, string,string,int,string,float,string,string);
        ~Student(); //destructor
        void editStudentInfo(void);
    
        //  * setters
        void setFirstName(string entered_first_name){first_name = entered_first_name;};
        void setLastName(string entered_last_name){last_name = entered_last_name;};
        void setClassStanding(int chosen_class_standing){class_standing = chosen_class_standing;};
        void setMajor(string newMajor){major = newMajor;};
        void setGpa(float newGPA){gpa = newGPA;};
        void addSkill(string newSkill){skills.push_back(newSkill);};
        void setPreferred_industry(string new_preferred_industry){preferred_industry = new_preferred_industry;};
        
        //  * getters
        string getFirstName(){return first_name;};
        string getLastName(){return last_name;};
        int getClassStanding(){return class_standing;};
        string getMajor(){return major;};
        float getGpa(){return gpa;};
        vector <string> getSkills(){return skills;};
        string getPreferred_industry(){return preferred_industry;};
};

class Employer; //forward declaration

class Job{
    private:
        Employer* company;
        string title;
        int class_standing_req;
        vector <string> preferred_majors;
        float preferredGPA;
        float salary;
        vector <string> requiredSkills;
        
    public:
        Job(Employer*); // constructor that assigns to employer right away.
        ~Job(); //destructor
        
        //getters
        Employer* getEmployer(){return company;};
        string getTitle(){return title;};
        int getClassStanding(){return class_standing_req;};
        vector <string> getPreferredMajors(){return preferred_majors;};
        float getPreferredGPA(){return preferredGPA;};
        float getSalary(){return salary;};
        vector <string> getRequiredSkills(){return requiredSkills;};
        
        //setters
        void setCompany(Employer* newCompany){company = newCompany;};
        void setTitle(string newTitle){title = newTitle;};
        void setClassStanding(int newClassStanding){class_standing_req = newClassStanding;};
        void addPreferredMajor(string newMajor){preferred_majors.push_back(newMajor);};
        void setPreferredGPA(float newGPA){preferredGPA = newGPA;};
        void setSalary(float newSalary){salary = newSalary;};
        void addRequiredSkill(string newSkill){requiredSkills.push_back(newSkill);};
};

class Employer : public User{
    private:
        string companyName;
        string industry;
        string companyDescription;
        vector<Job> openJobs;
        
        void employerUpdate();
    public:
        Employer(string newUsername, string newPassword, string newCompanyName,string newIndustry,string newCompanyDescription){ 
            companyName = newCompanyName; 
            industry = newIndustry;
            companyDescription = newCompanyDescription;
            username = newUsername;
            password = newPassword;
        };
        void addJob();
        void deleteJob();
        
        ~Employer();
        
        // * getters
        string getCompanyName(){return companyName;};
        string getIndustry(){return industry;};
        string getCompanyDescription(){return companyDescription;};
        
        // * setters
        void setCompanyName(string newCompanyName){companyName = newCompanyName;};
        void setIndustry(string newIndustry){industry = newIndustry;};
        void setCompanyDescription(string newCompanyDescription){companyDescription = newCompanyDescription;};
        void pushJob(Job newJob){openJobs.push_back(newJob);};
};

User::User(void){ //default user constructor
    username = "\0"; //initializes to null
    password = "\0"; //initializes to null
}

User::~User(void){
    //destructor
}

Student::Student(void){ //default constructor
    first_name = "";
    last_name = "";
    class_standing = 0;
    major = "\0";
    gpa = 0.0;
    //skills = "\0"; //don't need to initialize vector
    preferred_industry = "\0";
}
Student::Student(string newUsername, string newPassword, string firstName, string lastName, int classStrand, string newMajor, float newGpa, string skill, string preferred_ind){ //default constructor
    username = newUsername;
    password = newPassword;
    first_name = firstName;
    last_name = lastName;
    class_standing = classStrand;
    major = newMajor;
    gpa = newGpa;
    skills.push_back(skill); //push_back the skill because skills is a vector of strings
    preferred_industry = preferred_ind;
}

Student::~Student(void){
    //destructor
}

Employer::~Employer(void){
    //destructor
}

void Employer::addJob(){
    int choice, counter, i;
    float gpa, salary;
    string enteredMajor, enteredSkill, title;
    choice = 0;
    Job newJob(this);
    
    cout << "\nEnter job title: ";
    cin >> title;
    newJob.setTitle(title);
    
    cout << "\n1) Freshman\n2) Sophomore\n3) Junior\n4)Senior\nEnter the minimum class standing required: ";
    cin >> choice;
    while(choice < 1 || choice > 4){
        cout << "\nInvalid choice, try again: ";
        cin >> choice;
    }
    newJob.setClassStanding(choice);
    
    cout << "\nEnter number of preferred majors: ";
    cin >> counter;
    for(i=0;i<counter;i++){
        cout << "Enter preferred major #" + to_string(i+1) + ": ";
        cin >> enteredMajor;
        newJob.addPreferredMajor(enteredMajor);
    }
    
    cout << "\nEnter minimum required GPA, between 0 and 4: ";
    cin >> gpa;
    while(gpa < 0 || gpa > 4){
        cout << "\nInvalid choice, try again: ";
        cin >> gpa;
    }
    newJob.setPreferredGPA(gpa);
    
    cout << "\nEnter position salary: ";
    cin >> salary;
    newJob.setSalary(salary);
    
    cout << "\nEnter number of required skills: ";
    cin >> counter;
    for(i=0;i<counter;i++){
        cout << "\nEnter required skill #" << (i+1) << ": ";
        cin >> enteredSkill;
        newJob.addRequiredSkill(enteredSkill);
    }
    openJobs.push_back(newJob);
    this->employerUpdate();
    cout << "Job saved successfully." << endl;
}

void Employer::deleteJob(){
    int i, choice;
    string oldTitle;
    if(openJobs.size() != 0){
        for(i=0;i<openJobs.size();i++){
            cout << endl << (i+1) << ") " << openJobs[i].getTitle();
        }
        cout << "\nEnter the number of the job to delete: ";
        cin >> choice;
        while(choice < 0 || choice > openJobs.size()){
            cout << "\nInvalid choice, try again: ";
            cin >> choice;
        }
        oldTitle = openJobs[choice - 1].getTitle();
        openJobs.erase(openJobs.begin() + (choice - 1)); //necessary to add index to openJobs.begin() to avoid error when only one element is in the vector (http://stackoverflow.com/a/875117/5336262)
        cout << oldTitle << " deleted successfully.";
    } else {
        cout << "\nNo jobs to delete." << endl;
    }
    this->employerUpdate();
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
}

void Student::editStudentInfo(void){
    int choice;
    int preferred_industry_int; 
    int flag1=0;
    int i=0;
    int skillsLength=0;
    string editMore;
    
    do{
        //print info
        if(first_name != ""){ //if first_name is empty, assume first student has not entered info yet so we can't print current info
            cout << "\nCurrent information: " << "\n1) First Name: " << first_name 
                 << "\n2) Last Name: " << last_name << endl; 
             
            switch(class_standing){
                case 1:
                    cout << "3) Class Standing: Freshman" << endl;
                    break;
                case 2:
                    cout << "3) Class Standing: Sophomore" << endl;
                    break;
                case 3:
                    cout << "3) Class Standing: Junior" << endl;
                    break;
                case 4:
                    cout << "3) Class Standing: Senior" << endl;
                    break;
                default:
                    cout << "3) Class Standing: Not specified." << endl;
                    break;
            }
        
            cout << "4) Major: " << major << "\n5) GPA: " << gpa << endl; 
            
            skillsLength = skills.size(); //assigns the length of the skills vector 
            cout << "6) Skills: ";
            for(i=0;i<skillsLength;i++){
                 cout << skills[i] << "\n";
            }
            
            cout << "7) Preferred Industry: " << preferred_industry << endl;
        }
        //ask what to add/edit
        cout << "Please enter the number of the information you would like to edit: ";
        cin >> choice;
        
        switch(choice){
            case 1:
                cout << "\nPlease enter your first name: ";
                cin >> first_name;
                break;
            case 2:
                cout << "\nPlease enter your last name: ";
                cin >> last_name;
                break;
            case 3:
                cout << "\n1) Freshman\n2) Sophomore\n3) Junior\n4) Senior";
                cout << "\nPlease enter the number associated with your class standing: ";
                cin >> class_standing;
                break;
            case 4:
                cout << "\nPlease enter your major: ";
                cin >> major;
                break;
            case 5:
                cout << "\nPlease enter your GPA: ";
                cin >> gpa;
                break;
            case 6: //skills
                //add, or deleting a skill from the vector ************************************
                break;
            case 7:
            {
                int flag2=0;
                preferred_industry_int = 0;
                
                do{
                    cout << "\nIndustries: \n1)Automotive\n2) Construction\n3) Technology\n4) Power" << endl;
                    cout << "\nPlease enter the number corresponding to your preferred industry: ";
                    cin >> preferred_industry_int;
                    
                    if(preferred_industry_int==1){
                        preferred_industry = "Automotive";
                        flag2 = 1;
                    }
                    else if(preferred_industry_int==2){
                        preferred_industry = "Construction";
                        flag2 = 1;
                    }
                    else if(preferred_industry_int==3){
                        preferred_industry = "Technology";
                        flag2 = 1;
                    }
                    else if(preferred_industry_int==4){
                        preferred_industry = "Power";
                        flag2 = 1;
                    }
                    else
                      flag2 = 0;
                }while(flag2==0);
                
                break;
            }
            default:
                cout << "\nInvalid option." << endl;
        }
        
        cout << "\nWould you like to edit another piece of information?" << endl
            << "Please enter yes/no: ";
        cin >> editMore;
        
        if(editMore == "yes")
            flag1 = 0; //keeps looping
        else
            flag1 = 1; //breaks loop
            
    }while(flag1==0);
    
    //call function to write to text file *******************************************
    this->studentUpdate();
    return;
}
void Student::studentUpdate(){
    fstream fp;
    fp.open(("users/" + username + ".txt"),ios::out);
    fp << first_name << endl;
    fp << last_name << endl;
    fp << class_standing << endl;
    fp << major << endl;
    fp << gpa << endl;
    //fp << skills << endl;
    fp << preferred_industry << endl; 
    fp.close();
    cout << "\nProfile Completed...." << endl;
    //------------------------------------------Read "StudentInfo.txt"------------------------------------------------
    fstream userFp;
    //userFp.open(userFile.c_str(),ios::in); //userFile not yet declared, commenting out for now to compile
}

void Employer::employerUpdate(){
    fstream fp;
    int i,j,k;
    fp.open(("employers/" + username + "/" + username + ".txt"),ios::out);
    fp << companyName << endl;
    fp << industry << endl;
    fp << companyDescription << endl;
    fp << openJobs.size() << endl;
    fp.close();
    for(i=0;i<openJobs.size();i++){
        string title = "job" + to_string(i);
        fp.open(("employers/" + username + "/jobs/" + title + "/" + title + ".txt"),ios::out);
        fp << openJobs[i].getTitle() << endl;
        fp << openJobs[i].getClassStanding() << endl;
        fp << openJobs[i].getPreferredGPA() << endl;
        fp << openJobs[i].getSalary() << endl;
        fp << openJobs[i].getPreferredMajors().size() << endl;
        fp << openJobs[i].getRequiredSkills().size() << endl;
        fp.close();
        fp.open(("employers/" + username + "/jobs/" + title + "/majors.txt"),ios::out);
        for(j=0;j < openJobs[i].getPreferredMajors().size();j++){
            fp << openJobs[i].getPreferredMajors()[j] << endl;
        }
        fp.close();
        
        fp.open(("employers/" + username + "/jobs/" + title + "/skills.txt"),ios::out);
        for(k=0;k<openJobs[i].getRequiredSkills().size();k++){
            fp << openJobs[i].getRequiredSkills()[k] << endl;
        }
        fp.close();
    }
}