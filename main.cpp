#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <map>
#include <cctype>

using namespace std;

// -------------------- Data Models --------------------

struct Student {
    int id;
    string name;
    string email;
    string department;
    int graduationYear;
    double cgpa;
    int backlogs;
    vector<string> skills;
    int projects;
};

struct Recruiter {
    int id;
    string name;
    string email;
    string company;
};

struct Job {
    int id;
    string company;
    string role;
    string type;
    string location;
    string packageOffered;
    double minCGPA;
    int maxBacklogs;
    vector<string> requiredSkills;
    string deadline;
    int recruiterId;
};

struct Application {
    int id;
    int studentId;
    int jobId;
    string status;
};

// -------------------- Utility Functions --------------------

bool hasSkill(const Student& student, const string& skill) {
    for (const string& s : student.skills) {
        if (equal(s.begin(), s.end(), skill.begin(), skill.end(),
                  [](char a, char b) {
                      return tolower(static_cast<unsigned char>(a)) ==
                             tolower(static_cast<unsigned char>(b));
                  }) && s.size() == skill.size()) {
            return true;
        }
    }
    return false;
}

bool isEligible(const Student& student, const Job& job) {
    if (student.cgpa < job.minCGPA)
        return false;

    if (student.backlogs > job.maxBacklogs)
        return false;

    for (const string& skill : job.requiredSkills) {
        if (!hasSkill(student, skill))
            return false;
    }

    return true;
}

void showEligibility(const Student& student, const Job& job) {
    cout << "\nEligibility for " << job.role << " at " << job.company << ":\n";

    if (student.cgpa < job.minCGPA)
        cout << "- CGPA below required " << job.minCGPA << "\n";

    if (student.backlogs > job.maxBacklogs)
        cout << "- Active backlogs exceed allowed limit\n";

    for (const string& skill : job.requiredSkills) {
        if (!hasSkill(student, skill))
            cout << "- Missing skill: " << skill << "\n";
    }

    if (isEligible(student, job))
        cout << "Result: ELIGIBLE\n";
    else
        cout << "Result: NOT ELIGIBLE\n";
}

void printStudent(const Student& s) {
    cout << "\nID: " << s.id
         << "\nName: " << s.name
         << "\nEmail: " << s.email
         << "\nDepartment: " << s.department
         << "\nGraduation Year: " << s.graduationYear
         << "\nCGPA: " << s.cgpa
         << "\nBacklogs: " << s.backlogs
         << "\nProjects: " << s.projects
         << "\nSkills: ";

    for (const auto& skill : s.skills)
        cout << skill << " ";

    cout << "\n";
}

void printJob(const Job& j) {
    cout << "\n[" << j.id << "] "
         << j.company << " - " << j.role
         << "\nType: " << j.type
         << "\nLocation: " << j.location
         << "\nPackage: " << j.packageOffered
         << "\nMinimum CGPA: " << j.minCGPA
         << "\nMaximum Backlogs: " << j.maxBacklogs
         << "\nDeadline: " << j.deadline
         << "\nRequired Skills: ";

    for (const auto& skill : j.requiredSkills)
        cout << skill << " ";

    cout << "\n";
}

// -------------------- Placement System --------------------

class PlacementSystem {
private:
    vector<Student> students;
    vector<Recruiter> recruiters;
    vector<Job> jobs;
    vector<Application> applications;

    int nextStudentId = 1;
    int nextRecruiterId = 1;
    int nextJobId = 1;
    int nextApplicationId = 1;

public:

    void seedData() {
        students.push_back({
            nextStudentId++, "Aarav Mehta", "student@campus.edu",
            "Computer Science", 2026, 8.6, 0,
            {"Python", "Java", "DSA", "SQL", "React"}, 3
        });

        students.push_back({
            nextStudentId++, "Maya Iyer", "maya@campus.edu",
            "Information Technology", 2026, 7.9, 0,
            {"Java", "DSA", "Spring Boot", "SQL"}, 2
        });

        recruiters.push_back({
            nextRecruiterId++, "Rhea Kapoor",
            "recruiter@northstar.io", "Northstar Labs"
        });

        jobs.push_back({
            nextJobId++, "Northstar Labs", "Software Engineer",
            "Full-time", "Bengaluru - Hybrid", "18-24 LPA",
            7.5, 0, {"Java", "DSA", "SQL"}, "2026-10-22", 1
        });

        jobs.push_back({
            nextJobId++, "Vertex AI", "Applied AI Intern",
            "Internship", "Remote - India", "65k/month",
            8.0, 0, {"Python", "Machine Learning", "SQL"},
            "2026-10-18", 1
        });

        jobs.push_back({
            nextJobId++, "Finora", "Backend Developer",
            "Full-time", "Mumbai - On-site", "14-19 LPA",
            7.0, 0, {"Java", "Spring Boot", "DSA"},
            "2026-10-28", 1
        });

        applications.push_back({
            nextApplicationId++, 1, 1, "Shortlisted"
        });
    }

    Student* findStudent(int id) {
        for (auto& s : students)
            if (s.id == id)
                return &s;
        return nullptr;
    }

    Job* findJob(int id) {
        for (auto& j : jobs)
            if (j.id == id)
                return &j;
        return nullptr;
    }

    void displayJobs(const Student* student = nullptr) {
        cout << "\n========== AVAILABLE JOBS ==========\n";

        for (const auto& job : jobs) {
            printJob(job);

            if (student) {
                showEligibility(*student, job);
            }
            cout << "------------------------------------\n";
        }
    }

    void applyForJob(int studentId) {
        Student* student = findStudent(studentId);

        if (!student) {
            cout << "Student not found.\n";
            return;
        }

        displayJobs(student);

        int jobId;
        cout << "\nEnter Job ID to apply: ";
        cin >> jobId;

        Job* job = findJob(jobId);

        if (!job) {
            cout << "Job not found.\n";
            return;
        }

        for (const auto& app : applications) {
            if (app.studentId == studentId && app.jobId == jobId) {
                cout << "You have already applied for this job.\n";
                return;
            }
        }

        if (!isEligible(*student, *job)) {
            cout << "Application rejected: You are not eligible.\n";
            showEligibility(*student, *job);
            return;
        }

        applications.push_back({
            nextApplicationId++, studentId, jobId, "Applied"
        });

        cout << "Application submitted successfully!\n";
    }

    void showApplications(int studentId) {
        cout << "\n========== MY APPLICATIONS ==========\n";

        bool found = false;

        for (const auto& app : applications) {
            if (app.studentId == studentId) {
                found = true;

                Job* job = findJob(app.jobId);

                if (job) {
                    cout << "Application ID: " << app.id << "\n"
                         << "Company: " << job->company << "\n"
                         << "Role: " << job->role << "\n"
                         << "Status: " << app.status << "\n"
                         << "------------------------------------\n";
                }
            }
        }

        if (!found)
            cout << "No applications found.\n";
    }

    void updateApplicationStatus() {
        int applicationId;
        cout << "\nEnter Application ID: ";
        cin >> applicationId;

        for (auto& app : applications) {
            if (app.id == applicationId) {
                cout << "Choose new status:\n";
                cout << "1. In review\n";
                cout << "2. Shortlisted\n";
                cout << "3. Interview\n";
                cout << "4. Rejected\n";
                cout << "5. Placed\n";

                int choice;
                cin >> choice;

                vector<string> statuses = {
                    "", "In review", "Shortlisted",
                    "Interview", "Rejected", "Placed"
                };

                if (choice >= 1 && choice <= 5) {
                    app.status = statuses[choice];
                    cout << "Application status updated.\n";
                } else {
                    cout << "Invalid status.\n";
                }

                return;
            }
        }

        cout << "Application not found.\n";
    }

    void addJob() {
        Job job;

        job.id = nextJobId++;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nCompany: ";
        getline(cin, job.company);

        cout << "Role: ";
        getline(cin, job.role);

        cout << "Type (Full-time/Internship): ";
        getline(cin, job.type);

        cout << "Location: ";
        getline(cin, job.location);

        cout << "Package: ";
        getline(cin, job.packageOffered);

        cout << "Minimum CGPA: ";
        cin >> job.minCGPA;

        cout << "Maximum Backlogs: ";
        cin >> job.maxBacklogs;

        cout << "Number of required skills: ";
        int n;
        cin >> n;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter skills:\n";
        for (int i = 0; i < n; i++) {
            string skill;
            getline(cin, skill);
            job.requiredSkills.push_back(skill);
        }

        cout << "Application deadline: ";
        getline(cin, job.deadline);

        job.recruiterId = 1;

        jobs.push_back(job);

        cout << "Job posted successfully!\n";
    }

    void showDashboard(int studentId) {
        Student* student = findStudent(studentId);

        if (!student)
            return;

        int eligible = 0;
        int applied = 0;
        int shortlisted = 0;

        for (const auto& job : jobs) {
            if (isEligible(*student, job))
                eligible++;
        }

        for (const auto& app : applications) {
            if (app.studentId == studentId) {
                applied++;

                if (app.status == "Shortlisted")
                    shortlisted++;
            }
        }

        cout << "\n========== STUDENT DASHBOARD ==========\n";
        cout << "Student: " << student->name << "\n";
        cout << "Eligible Jobs: " << eligible << "\n";
        cout << "Applications: " << applied << "\n";
        cout << "Shortlisted: " << shortlisted << "\n";
    }

    void studentMenu(int studentId) {
        while (true) {
            cout << "\n========== STUDENT MENU ==========\n";
            cout << "1. View Profile\n";
            cout << "2. View Jobs\n";
            cout << "3. Check Eligibility\n";
            cout << "4. Apply for Job\n";
            cout << "5. My Applications\n";
            cout << "6. Dashboard\n";
            cout << "0. Logout\n";
            cout << "Choose: ";

            int choice;
            cin >> choice;

            Student* student = findStudent(studentId);

            if (!student)
                return;

            switch (choice) {
                case 1:
                    printStudent(*student);
                    break;

                case 2:
                    displayJobs();
                    break;

                case 3: {
                    int jobId;
                    cout << "Enter Job ID: ";
                    cin >> jobId;

                    Job* job = findJob(jobId);

                    if (job)
                        showEligibility(*student, *job);
                    else
                        cout << "Job not found.\n";

                    break;
                }

                case 4:
                    applyForJob(studentId);
                    break;

                case 5:
                    showApplications(studentId);
                    break;

                case 6:
                    showDashboard(studentId);
                    break;

                case 0:
                    return;

                default:
                    cout << "Invalid choice.\n";
            }
        }
    }

    void recruiterMenu() {
        while (true) {
            cout << "\n========== RECRUITER MENU ==========\n";
            cout << "1. View Jobs\n";
            cout << "2. Post New Job\n";
            cout << "3. Update Application Status\n";
            cout << "4. View All Applications\n";
            cout << "0. Logout\n";
            cout << "Choose: ";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1:
                    displayJobs();
                    break;

                case 2:
                    addJob();
                    break;

                case 3:
                    updateApplicationStatus();
                    break;

                case 4:
                    cout << "\n========== APPLICATIONS ==========\n";
                    for (const auto& app : applications) {
                        Job* job = findJob(app.jobId);
                        Student* student = findStudent(app.studentId);

                        if (job && student) {
                            cout << "Application ID: " << app.id
                                 << "\nStudent: " << student->name
                                 << "\nCompany: " << job->company
                                 << "\nRole: " << job->role
                                 << "\nStatus: " << app.status
                                 << "\n----------------------------------\n";
                        }
                    }
                    break;

                case 0:
                    return;

                default:
                    cout << "Invalid choice.\n";
            }
        }
    }

    void run() {
        seedData();

        while (true) {
            cout << "\n\n========================================\n";
            cout << "       CAMPUS PLACEMENT PORTAL\n";
            cout << "========================================\n";
            cout << "1. Student Login\n";
            cout << "2. Recruiter Login\n";
            cout << "0. Exit\n";
            cout << "Choose: ";

            int choice;
            cin >> choice;

            switch (choice) {
                case 1: {
                    int id;
                    cout << "Enter Student ID (1 or 2): ";
                    cin >> id;

                    if (findStudent(id))
                        studentMenu(id);
                    else
                        cout << "Invalid student ID.\n";

                    break;
                }

                case 2:
                    recruiterMenu();
                    break;

                case 0:
                    cout << "Thank you for using Campus Placement Portal!\n";
                    return;

                default:
                    cout << "Invalid choice.\n";
            }
        }
    }
};

// -------------------- Main --------------------

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    PlacementSystem system;
    system.run();

    return 0;
}
