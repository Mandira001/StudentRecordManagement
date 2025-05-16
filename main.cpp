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
    ofstream outFile("students.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
    outFile.close();
    cout << "Student record added successfully!\n";
}

void displayAll() {
    Student s;
    ifstream inFile("students.dat", ios::binary);
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        s.display();
        found = true;
    }
    inFile.close();
    if (!found) cout << "No records found.\n";
}

void searchStudent(int roll) {
    Student s;
    bool found = false;
    ifstream inFile("students.dat", ios::binary);
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo == roll) {
            s.display();
            found = true;
            break;
        }
    }
    inFile.close();
    if (!found) cout << "Student not found.\n";
}

void deleteStudent(int roll) {
    Student s;
    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);
    bool found = false;
    while (inFile.read(reinterpret_cast<char*>(&s), sizeof(s))) {
        if (s.rollNo != roll) {
            outFile.write(reinterpret_cast<char*>(&s), sizeof(s));
        } else {
            found = true;
        }
    }
    inFile.close();
    outFile.close();
    remove("students.dat");
    rename("temp.dat", "students.dat");
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