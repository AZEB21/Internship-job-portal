CREATE DATABASE internship_portal;
USE internship_portal;

-- Students Table
CREATE TABLE  students (
    email VARCHAR(255) PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    password VARCHAR(255) NOT NULL
);

-- Employers Table
CREATE TABLE  posters (
    email VARCHAR(255) PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    company VARCHAR(255) NOT NULL,
    password VARCHAR(255) NOT NULL
);

-- Jobs Table
CREATE TABLE jobs (
    job_id INT AUTO_INCREMENT PRIMARY KEY,
    title VARCHAR(255) NOT NULL,
    description TEXT NOT NULL,
    company VARCHAR(255) NOT NULL,
    required_skills VARCHAR(255),
    location VARCHAR(255),
    poster_email VARCHAR(255),
    FOREIGN KEY (poster_email) REFERENCES posters(email)
);

-- Applications Table (without employer_email)
CREATE TABLE  applications (
    application_id INT AUTO_INCREMENT PRIMARY KEY,
    student_email VARCHAR(255),
    job_id INT,
    applied_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
    skills VARCHAR(255),
    resume_path TEXT,
    FOREIGN KEY (student_email) REFERENCES students(email),
    FOREIGN KEY (job_id) REFERENCES jobs(job_id)
);

