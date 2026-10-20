#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Stores information about one course.
struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Finds a course using its course number.
int findCourse(const vector<Course>& courses, const string& courseNumber) {
    for (int i = 0; i < static_cast<int>(courses.size()); i++) {
        if (courses[i].courseNumber == courseNumber) {
            return i;
        }
    }

    return -1;
}

// Loads course information from the CSV file.
bool loadCourses(const string& filename, vector<Course>& courses) {
    ifstream inputFile(filename);

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open file: " << filename << endl;
        return false;
    }

    vector<Course> loadedCourses;
    string line;

    while (getline(inputFile, line)) {
        // Remove the hidden carriage return left by Windows-style line endings.
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        Course course;
        string field;

        // Read the course number.
        if (!getline(ss, course.courseNumber, ',')) {
            continue;
        }

        // Read the course title.
        if (!getline(ss, course.courseTitle, ',')) {
            cout << "Error: Invalid course data." << endl;
            inputFile.close();
            return false;
        }

        // Read any prerequisite course numbers.
        while (getline(ss, field, ',')) {
            if (!field.empty()) {
                course.prerequisites.push_back(field);
            }
        }

        // Remove extra spaces from course information.
        course.courseNumber.erase(
            0, course.courseNumber.find_first_not_of(" \t\r"));
        course.courseTitle.erase(
            0, course.courseTitle.find_first_not_of(" \t\r"));

        loadedCourses.push_back(course);
    }

    inputFile.close();

    if (loadedCourses.empty()) {
        cout << "Error: No course data was loaded." << endl;
        return false;
    }

    courses = loadedCourses;
    cout << courses.size() << " courses loaded successfully." << endl;

    return true;
}

// Prints all courses in alphanumeric order.
void printCourseList(vector<Course> courses) {
    if (courses.empty()) {
        cout << "Please load the course data first." << endl;
        return;
    }

    // Sort by course number from lowest to highest.
    sort(courses.begin(), courses.end(),
         [](const Course& a, const Course& b) {
             return a.courseNumber < b.courseNumber;
         });

    cout << "\nHere is a sample schedule:\n" << endl;

    for (const Course& course : courses) {
        cout << course.courseNumber << ", "
             << course.courseTitle << endl;
    }
}

// Displays a course and its prerequisite information.
void printCourse(const vector<Course>& courses) {
    if (courses.empty()) {
        cout << "Please load the course data first." << endl;
        return;
    }

    string courseNumber;

    cout << "What course do you want to know about? ";
    cin >> courseNumber;

    int index = findCourse(courses, courseNumber);

    if (index == -1) {
        cout << "Course not found. Please check the course number."
             << endl;
        return;
    }

    const Course& course = courses[index];

    cout << course.courseNumber << ", "
         << course.courseTitle << endl;

    if (course.prerequisites.empty()) {
        cout << "Prerequisites: None" << endl;
        return;
    }

    cout << "Prerequisites:" << endl;

    for (const string& prerequisite : course.prerequisites) {
        int prereqIndex = findCourse(courses, prerequisite);

        if (prereqIndex != -1) {
            cout << prerequisite << ", "
                 << courses[prereqIndex].courseTitle << endl;
        } else {
            cout << prerequisite << ", title unavailable" << endl;
        }
    }
}

// Displays the program menu.
void displayMenu() {
    cout << "\nWelcome to the course planner." << endl;
    cout << "1. Load Data Structure." << endl;
    cout << "2. Print Course List." << endl;
    cout << "3. Print Course." << endl;
    cout << "9. Exit" << endl;
    cout << "What would you like to do? ";
}

int main() {
    vector<Course> courses;
    int choice = 0;

    while (choice != 9) {
        displayMenu();

        if (!(cin >> choice)) {
            cout << "Invalid input. Please enter a number." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                string filename;

                cout << "Enter the course data filename: ";
                cin >> filename;

                loadCourses(filename, courses);
                break;
            }

            case 2:
                printCourseList(courses);
                break;

            case 3:
                printCourse(courses);
                break;

            case 9:
                cout << "Thank you for using the course planner!"
                     << endl;
                break;

            default:
                cout << choice
                     << " is not a valid option. Please try again."
                     << endl;
                break;
        }
    }

    return 0;
}
