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
