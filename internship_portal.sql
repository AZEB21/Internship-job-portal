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

-- Sample data for the students table
INSERT INTO students (name, email, skills, resume_path) VALUES
    ('Azeb', 'azeb@example.com', 'C++, MySQL, HTML, CSS, JavaScript', 'https://drive.google.com/file1'),
    ('Arsema', 'arsema@example.com', 'Python, SQL, Data Structures', 'https://drive.google.com/file2'),
    ('Azaria', 'azaria@example.com', 'Java, Spring Boot, SQL', 'https://drive.google.com/file3'),
    ('Bamlak', 'bamlak@example.com', 'C, C++, Git, Agile', 'https://drive.google.com/file4');

-- Sample data for the posters table
INSERT INTO posters (email, name, company) VALUES
    ('selam@example.com', 'Selam', 'TechCo'),
    ('haymanot@example.com', 'Haymanot', 'SoftSolutions'),
    ('mahlet@example.com', 'Mahlet', 'DevPartners');

-- Sample data for the jobs table
INSERT INTO jobs (title, description, company, required_skills, location, poster_email) VALUES
    ('Software Developer', 'Developing backend systems in C++ and MySQL.',
    'TechCo', 'C++, MySQL', 'Addis Ababa', 'selam@example.com'),
    ('Data Analyst', 'Analyzing data and creating reports using Python and SQL.',
    'SoftSolutions', 'Python, SQL', 'Addis Ababa', 'haymanot@example.com'),
    ('Full Stack Developer', 'Building web applications using Java and Spring Boot.',
    'DevPartners', 'Java, Spring Boot', 'Addis Ababa', 'mahlet@example.com');

-- Sample data for the applications table
INSERT INTO applications (student_email, job_id, skills, resume_path) VALUES
    ('azeb@example.com', 1, 'C++, MySQL', 'https://drive.google.com/resume_azeb'),
    ('arsema@example.com', 2, 'Python, SQL', 'https://drive.google.com/resume_arsema'),
    ('azaria@example.com', 3, 'Java, Spring Boot', 'https://drive.google.com/resume_azaria'),
    ('bamlak@example.com', 1, 'C++, MySQL', 'https://drive.google.com/resume_bamlak');


