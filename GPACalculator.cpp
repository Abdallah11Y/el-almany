#include <iostream>
#include <vector>
#include <string>
#include <iomanip> // For std::setprecision and std::fixed
#include <limits>  // For std::numeric_limits

// --- Course Class ---
class Course {
public:
    std::string name;
    double grade; // Numeric grade (e.g., 4.0 for A, 3.0 for B, etc.)
    int credits;

    Course(const std::string& n = "", double g = 0.0, int c = 0)
        : name(n), grade(g), credits(c) {}

    // Function to calculate grade points for a course
    double getGradePoints() const {
        return grade * credits;
    }

    // You might want a function to convert letter grades to numeric grades
    // For simplicity, we'll assume numeric grades are entered directly for now.
    // double convertLetterToNumeric(char letterGrade) { ... }
};

// --- Semester Class ---
class Semester {
public:
    std::string name; // e.g., "Fall 2023", "Spring 2024"
    std::vector<Course> courses;

    Semester(const std::string& n = "") : name(n) {}

    // Function to add a course to the semester
    void addCourse(const Course& course) {
        courses.push_back(course);
    }

    // Function to calculate semester GPA
    double calculateGPA() const {
        double totalGradePoints = 0.0;
        int totalCredits = 0;

        if (courses.empty()) {
            return 0.0; // No courses, GPA is 0
        }

        for (const auto& course : courses) {
            totalGradePoints += course.getGradePoints();
            totalCredits += course.credits;
        }

        if (totalCredits == 0) {
            return 0.0; // Avoid division by zero
        }

        return totalGradePoints / totalCredits;
    }

    // Function to display semester details
    void displaySemesterDetails() const {
        std::cout << "\n--- Semester: " << name << " ---" << std::endl;
        if (courses.empty()) {
            std::cout << "No courses recorded for this semester." << std::endl;
            return;
        }
        std::cout << std::setw(30) << std::left << "Course Name"
                  << std::setw(10) << std::left << "Grade"
                  << std::setw(10) << std::left << "Credits" << std::endl;
        std::cout << std::string(50, '-') << std::endl;
        for (const auto& course : courses) {
            std::cout << std::setw(30) << std::left << course.name
                      << std::setw(10) << std::left << std::fixed << std::setprecision(2) << course.grade
                      << std::setw(10) << std::left << course.credits << std::endl;
        }
        std::cout << std::string(50, '-') << std::endl;
        std::cout << "Semester GPA: " << std::fixed << std::setprecision(2) << calculateGPA() << std::endl;
    }
};

// --- Global Functions for User Interaction and Data Management ---
std::vector<Semester> allSemesters; // To store all semesters

// Function to get valid integer input
int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < 0) { // Check for invalid input (non-numeric or negative)
            std::cout << "Invalid input. Please enter a positive integer." << std::endl;
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the rest of the line
            return value;
        }
    }
}

// Function to get valid double input
double getDoubleInput(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail() || value < 0.0 || value > 4.0) { // Assuming 0.0-4.0 GPA scale
            std::cout << "Invalid input. Please enter a numeric grade (e.g., 0.0 to 4.0)." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

// Function to add a new semester
void addSemester() {
    std::string semesterName;
    std::cout << "\nEnter semester name (e.g., Fall 2023): ";
    std::getline(std::cin, semesterName);

    Semester newSemester(semesterName);

    int numCourses = getIntInput("How many courses for this semester? ");

    for (int i = 0; i < numCourses; ++i) {
        std::string courseName;
        double grade;
        int credits;

        std::cout << "\n--- Enter details for Course " << (i + 1) << " ---" << std::endl;
        std::cout << "Course name: ";
        std::getline(std::cin, courseName);
        grade = getDoubleInput("Grade (e.g., 4.0 for A, 3.0 for B): ");
        credits = getIntInput("Credits: ");

        newSemester.addCourse(Course(courseName, grade, credits));
    }

    allSemesters.push_back(newSemester);
    std::cout << "\nSemester '" << semesterName << "' added successfully!" << std::endl;
}

// Function to display all semesters and their GPAs
void displayAllSemesters() {
    if (allSemesters.empty()) {
        std::cout << "\nNo semesters recorded yet." << std::endl;
        return;
    }
    std::cout << "\n--- All Recorded Semesters ---" << std::endl;
    for (size_t i = 0; i < allSemesters.size(); ++i) {
        std::cout << (i + 1) << ". " << allSemesters[i].name
                  << " (GPA: " << std::fixed << std::setprecision(2) << allSemesters[i].calculateGPA() << ")" << std::endl;
    }
}

// Function to view details of a specific semester
void viewSemesterDetails() {
    if (allSemesters.empty()) {
        std::cout << "\nNo semesters to view. Please add a semester first." << std::endl;
        return;
    }

    displayAllSemesters();
    int choice = getIntInput("Enter the number of the semester you want to view: ");

    if (choice > 0 && choice <= allSemesters.size()) {
        allSemesters[choice - 1].displaySemesterDetails();
    } else {
        std::cout << "Invalid semester number." << std::endl;
    }
}

// --- Main Function (Application Entry Point) ---
int main() {
    int choice;

    do {
        std::cout << "\n--- GPA Calculator Menu ---" << std::endl;
        std::cout << "1. Add New Semester" << std::endl;
        std::cout << "2. View All Semesters (and their GPAs)" << std::endl;
        std::cout << "3. View Details of a Specific Semester" << std::endl;
        std::cout << "4. Exit" << std::endl;
        choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1:
                addSemester();
                break;
            case 2:
                displayAllSemesters();
                break;
            case 3:
                viewSemesterDetails();
                break;
            case 4:
                std::cout << "Exiting GPA Calculator. Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
    } while (choice != 4);

    return 0;
}