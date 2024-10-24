#include <iostream>
#include <vector>
#include <fstream>  // For file handling
using namespace std;

// Structure to store information about each course
struct Course {
    string courseName;
    float grade;
    int creditHours;
};

// Function to calculate GPA for a semester
float calculateGPA(vector<Course> &courses) {
    float totalGradePoints = 0.0;
    int totalCredits = 0;
    
    for (const Course &course : courses) {
        totalGradePoints += course.grade * course.creditHours;
        totalCredits += course.creditHours;
    }
    
    return (totalCredits > 0) ? totalGradePoints / totalCredits : 0;
}

// Function to calculate CGPA across multiple semesters
float calculateCGPA(vector<vector<Course>> &allSemesters) {
    float totalGradePoints = 0.0;
    int totalCredits = 0;
    
    for (const auto &semester : allSemesters) {
        for (const Course &course : semester) {
            totalGradePoints += course.grade * course.creditHours;
            totalCredits += course.creditHours;
        }
    }
    
    return (totalCredits > 0) ? totalGradePoints / totalCredits : 0;
}

// Function to display course details
void displayCourses(const vector<Course> &courses) {
    cout << "Course\tGrade\tCredits\n";
    for (const Course &course : courses) {
        cout << course.courseName << "\t" << course.grade << "\t" << course.creditHours << endl;
    }
}

// Function to handle input and file I/O
void loadSemesterData(vector<Course> &courses) {
    int n;
    cout << "Enter the number of courses: ";
    cin >> n;
    
    for (int i = 0; i < n; ++i) {
        Course course;
        cout << "Enter course name: ";
        cin >> course.courseName;
        cout << "Enter course grade (as a number, e.g., 4 for A, 3 for B, etc.): ";
        cin >> course.grade;
        cout << "Enter course credit hours: ";
        cin >> course.creditHours;
        courses.push_back(course);
    }
}

// File handling function to save data
void saveToFile(const string &filename, const vector<Course> &courses) {
    ofstream outfile(filename);
    if (outfile.is_open()) {
        for (const Course &course : courses) {
            outfile << course.courseName << " " << course.grade << " " << course.creditHours << endl;
        }
        outfile.close();
        cout << "Data saved to " << filename << endl;
    } else {
        cout << "Unable to open file for writing." << endl;
    }
}

int main() {
    vector<vector<Course>> allSemesters;
    char addAnotherSemester = 'y';
    
    while (addAnotherSemester == 'y' || addAnotherSemester == 'Y') {
        vector<Course> semester;
        loadSemesterData(semester);
        displayCourses(semester);
        allSemesters.push_back(semester);
        
        cout << "Semester GPA: " << calculateGPA(semester) << endl;
        cout << "Add another semester? (y/n): ";
        cin >> addAnotherSemester;
    }
    
    cout << "Cumulative CGPA: " << calculateCGPA(allSemesters) << endl;

    // Save data to file if required
    char saveData = 'n';
    cout << "Do you want to save the data to a file? (y/n): ";
    cin >> saveData;
    
    if (saveData == 'y' || saveData == 'Y') {
        string filename;
        cout << "Enter filename to save: ";
        cin >> filename;
        for (const auto &semester : allSemesters) {
            saveToFile(filename, semester);
        }
    }
    
    return 0;
}
