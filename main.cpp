#include <iostream>
#include <string>
#include <limits>
#include <cppconn/driver.h>
#include <cppconn/connection.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <mysql_driver.h>
#include <mysql_connection.h>

using namespace std;

class Database {
public:
    static sql::Connection* getConnection() {
        sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
        return driver->connect("tcp://127.0.0.1:3306", "root", "mysql_password");
    }
};

class User {
public:
    virtual void login() = 0;
    virtual void registerUser() = 0;
};

class Student : public User {
private:
    string email;

public:
    void registerUser() override {
        string name, password;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Student Name: ";
        getline(cin, name);
        cout << "Enter Student Email: ";
        getline(cin, email);
        cout << "Enter Student Password: ";
        getline(cin, password);

        try {
            sql::Connection* con = Database::getConnection();
            con->setSchema("internship_portal");
            sql::PreparedStatement* pstmt = con->prepareStatement(
                "INSERT INTO students (name, email, password) VALUES (?, ?, ?)"
            );
            pstmt->setString(1, name);
            pstmt->setString(2, email);
            pstmt->setString(3, password);
            pstmt->execute();
            cout << "Student registered successfully!\n";
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

void login() override {
        string inputPassword;
        cout << "Enter Student Email: ";
        cin >> email;
        cout << "Enter Password: ";
        cin >> inputPassword;

        try {
            sql::Connection* con = Database::getConnection();
            con->setSchema("internship_portal");
            sql::PreparedStatement* pstmt = con->prepareStatement(
                "SELECT * FROM students WHERE email = ? AND password = ?"
            );
            pstmt->setString(1, email);
            pstmt->setString(2, inputPassword);
            sql::ResultSet* res = pstmt->executeQuery();

            if (res->next()) {
                cout << "Logged in as Student: " << email << endl;
            }
            else {
                cout << "Invalid email or password.\n";
                email = "";
            }

            delete res;
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    string getEmail() { return email; }
    void applyForJob() {
        int jobId;
        string skills, resumePath;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Job ID to apply for: ";
        cin >> jobId;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter your skills: ";
        getline(cin, skills);
        cout << "Please Enter your valid resume Google Drive link (e.g. https://drive.google.com/...): ";
        getline(cin, resumePath);

        try {
            sql::Connection* con = Database::getConnection();
            con->setSchema("internship_portal");
            sql::PreparedStatement* pstmt = con->prepareStatement(
                "INSERT INTO applications (student_email, job_id, skills, resume_path) VALUES (?, ?, ?, ?)"
            );
            pstmt->setString(1, getEmail());
            pstmt->setInt(2, jobId);
            pstmt->setString(3, skills);
            pstmt->setString(4, resumePath);
            pstmt->execute();
            cout << "Application submitted successfully!\n";
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
};

class Poster : public User {
private:
    string email;

public:
    void registerUser() override {
        string name, company, password;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Employer Name: ";
        getline(cin, name);
        cout << "Enter Email: ";
        getline(cin, email);
        cout << "Enter Password: ";
        getline(cin, password);
        cout << "Enter Company Name: ";
        getline(cin, company);

        try {
            sql::Connection* con = Database::getConnection();
            con->setSchema("internship_portal");
            sql::PreparedStatement* pstmt = con->prepareStatement(
                "INSERT INTO posters (name, email, company, password) VALUES (?, ?, ?, ?)"
            );
            pstmt->setString(1, name);
            pstmt->setString(2, email);
            pstmt->setString(3, company);
            pstmt->setString(4, password);
            pstmt->execute();
            cout << "Employer registered successfully!\n";
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
void login() override {
        string inputPassword;
        cout << "Enter Employer Email: ";
        cin >> email;
        cout << "Enter Password: ";
        cin >> inputPassword;

        try {
            sql::Connection* con = Database::getConnection();
            con->setSchema("internship_portal");
            sql::PreparedStatement* pstmt = con->prepareStatement(
                "SELECT * FROM posters WHERE email = ? AND password = ?"
            );
            pstmt->setString(1, email);
            pstmt->setString(2, inputPassword);
            sql::ResultSet* res = pstmt->executeQuery();

            if (res->next()) {
                cout << "Logged in as Employer : " << email << endl;
            }
            else {
                cout << "Invalid email or password.\n";
                email = "";
            }

            delete res;
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

    string getEmail() { return email; }

      void postJob() {
        string title, description, company, skills, location;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Job Title: ";
        getline(cin, title);
        cout << "Enter Job Description: ";
        getline(cin, description);
        cout << "Enter Company Name: ";
        getline(cin, company);
        cout << "Enter Required Skills: ";
        getline(cin, skills);
        cout << "Enter Job Location: ";
        getline(cin, location);

        try {
            sql::Connection* con = Database::getConnection();
            con->setSchema("internship_portal");
            sql::PreparedStatement* pstmt = con->prepareStatement(
                "INSERT INTO jobs (title, description, company, required_skills, location, poster_email) VALUES (?, ?, ?, ?, ?, ?)"
            );
            pstmt->setString(1, title);
            pstmt->setString(2, description);
            pstmt->setString(3, company);
            pstmt->setString(4, skills);
            pstmt->setString(5, location);
            pstmt->setString(6, getEmail());
            pstmt->execute();
            cout << "Job posted successfully!\n";
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
            void viewApplications() {
        try {
            sql::Connection* con = Database::getConnection();
            con->setSchema("internship_portal");
            sql::PreparedStatement* pstmt = con->prepareStatement(
                "SELECT a.student_email, j.title, a.applied_at, a.skills, a.resume_path "
                "FROM applications a JOIN jobs j ON a.job_id = j.job_id "
                "WHERE j.poster_email = ?"
            );
            pstmt->setString(1, getEmail());
            sql::ResultSet* res = pstmt->executeQuery();

            cout << "\nApplications to Your Jobs:\n";
            while (res->next()) {
                cout << "Student Email: " << res->getString("student_email")
                    << ", Job Title: " << res->getString("title")
                    << ", Applied At: " << res->getString("applied_at")
                    << ", Skills: " << res->getString("skills")
                    << ", Resume: " << res->getString("resume_path") << endl;
            }

            delete res;
            delete pstmt;
            delete con;
        }
        catch (sql::SQLException& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
};

class Job {
public:
    void viewJobs() {
        try {
            sql::Connection* con = Database::getConnection();
            con->setSchema("internship_portal");
            sql::Statement* stmt = con->createStatement();
            sql::ResultSet* res = stmt->executeQuery("SELECT job_id, title, company, location FROM jobs");

            cout << "\nAvailable Jobs:\n";
            while (res->next()) {
                cout << "Job ID: " << res->getInt("job_id")
                    << ", Title: " << res->getString("title")
                    << ", Company: " << res->getString("company")
                    << ", Location: " << res->getString("location") << endl;
            }

            delete res;
            delete stmt;
            delete con;
        }
        catch (sql::SQLException& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
};
int main() {
    int choice;
    Student student;
    Poster poster;
    Job job;
    User* currentUser = nullptr;

    cout << "\n================================================================================\n";
    cout << "               Welcome to the Student Internship & Job Portal\n";
    cout << "================================================================================\n";

    do {
        cout << "\nInternship & Job Portal\n";
        cout << "1. Register as Student\n";
        cout << "2. Register as Employer \n";
        cout << "3. Login as Student\n";
        cout << "4. Login as Employer \n";
        cout << "5. View Jobs\n";
        cout << "6. Apply for Job (Student)\n";
        cout << "7. Post Job (Employer  Only)\n";
        cout << "8. View Applications to Your Jobs (Poster Only)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
switch (choice) {
        case 1:
            student.registerUser();
            break;
        case 2:
            poster.registerUser();
            break;
        case 3:
            student.login();
            currentUser = &student;
            break;
        case 4:
            poster.login();
            currentUser = &poster;
            break;
        case 5:
            job.viewJobs();
            break;
        case 6:
            if (currentUser == nullptr || dynamic_cast<Student*>(currentUser) == nullptr) {
                cout << "You must login as a student first!\n";
            }
            else {
                student.applyForJob();
            }
            break;
        case 7:
            if (currentUser == nullptr || dynamic_cast<Poster*>(currentUser) == nullptr) {
                cout << "You must login as a Employer  first!\n";
            }
            else {
                poster.postJob();
            }
            break;
        case 8:
            if (currentUser == nullptr || dynamic_cast<Poster*>(currentUser) == nullptr) {
                cout << "You must login as a Employer  first!\n";
            }
            else {
                poster.viewApplications();
            }
            break;
        case 0:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
