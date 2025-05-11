Student Internship & Job Portal System
This is a C++ console-based Internship and Job Portal system connected to a MySQL database using the MySQL Connector/C++ library. It allows students to register, log in, and apply for jobs. Employers can post job opportunities and view applications from students.

 Features
 Student Registration/Login
 Employer (Poster) Registration/Login
 Post Jobs (Employers)
 View Available Jobs (Everyone)
 Apply for Jobs (Students)
 View Applications (Employers Only)

 Technologies Used
C++
MySQL
MySQL Connector/C++
OOP concepts (Inheritance, Polymorphism)
Prepared Statements (for SQL injection prevention)
Configuration
1.MySQL Credentials
Update the credentials in your code:
driver->connect("tcp://127.0.0.1:3306", "root", "mysql_password");
2.MySQL Connector
Make sure to link your C++ project with the MySQL Connector/C++ library. Install it using vcpkg or manually from MySQL official site.

How to Run
Compile the program using a C++ compiler that supports MySQL Connector/C++.

Run the executable.

Choose from the main menu to register, login, post or apply for jobs.

