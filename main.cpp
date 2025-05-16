#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    int age;
    string course;

    void input() {
        cout << "Enter Roll Number: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cin.ignore();
        cout << "Enter Course: ";
        getline(cin, course);
    }

    void display() const {
        cout << "Roll No: " << rollNo << ", Name: " << name
             << ", Age: " << age << ", Course: " << course << endl;
    }
};

void addStudent() {
    Student s;
    s.input();
    ofstream outFile("students.txt", ios::app);
    outFile << s.rollNo << ',' << s.name << ',' << s.age << ',' << s.course << '\n';
    outFile.close();
    cout << "Student record added successfully!\n";
}

void displayAll() {
    ifstream inFile("students.txt");
    string line;
    bool found = false;
    while (getline(inFile, line)) {
        int roll, age;
        string name, course;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) continue;
        roll = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        course = line.substr(pos3 + 1);
        cout << "Roll No: " << roll << ", Name: " << name << ", Age: " << age << ", Course: " << course << endl;
        found = true;
    }
    inFile.close();
    if (!found) cout << "No records found.\n";
}

void searchStudent(int roll) {
    ifstream inFile("students.txt");
    string line;
    bool found = false;
    while (getline(inFile, line)) {
        int r, age;
        string name, course;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) continue;
        r = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        course = line.substr(pos3 + 1);
        if (r == roll) {
            cout << "Roll No: " << r << ", Name: " << name << ", Age: " << age << ", Course: " << course << endl;
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) cout << "Student not found.\n";
}

void deleteStudent(int roll) {
    ifstream inFile("students.txt");
    ofstream outFile("temp.txt");
    string line;
    bool found = false;
    while (getline(inFile, line)) {
        int r, age;
        string name, course;
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos) continue;
        r = stoi(line.substr(0, pos1));
        name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        age = stoi(line.substr(pos2 + 1, pos3 - pos2 - 1));
        course = line.substr(pos3 + 1);
        if (r != roll) {
            outFile << r << ',' << name << ',' << age << ',' << course << '\n';
        } else {
            found = true;
        }
    }
    inFile.close();
    outFile.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");
    if (found)
        cout << "Student record deleted.\n";
    else
        cout << "Student not found.\n";
}

int main() {
    int choice, roll;
    do {
        cout << "\n--- Student Record Management System ---\n";
        cout << "1. Add Student\n2. Display All Students\n3. Search Student\n4. Delete Student\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayAll(); break;
            case 3:
                cout << "Enter Roll Number to search: ";
                cin >> roll;
                searchStudent(roll);
                break;
            case 4:
                cout << "Enter Roll Number to delete: ";
                cin >> roll;
                deleteStudent(roll);
                break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 5);
    return 0;
} 