#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>

using namespace std;

struct Employee {
    string emp_full_name;
    string emp_id;
    double emp_salary;
    string emp_department;
    string emp_education;
    int emp_experience;
    int emp_phoneNumber;
    string emp_gender;
    Employee *prev;
    Employee *next;
};

Employee *head = NULL;
Employee *tail = NULL;

// Department salary ranges
const double TEACHING_BASE = 30000;
const double ADMIN_BASE = 25000;
const double OTHER_BASE = 20000;

int numberOfEmp() {
    Employee *temp = head;
    int count = 0;
    while (temp != NULL) {
        temp = temp->next;
        count++;
    }
    return count;
}

bool check_ID(const string& id) {
    Employee* temp = head;
    while (temp != NULL) {
        if (temp->emp_id == id) return false;
        temp = temp->next;
    }
    return true;
}

double calculateSalary(const string& department, const string& education, int experience) {
    double base_salary = 0;
    
    // Set base salary based on department
    if (department == "Teaching") {
        base_salary = TEACHING_BASE;
    } else if (department == "Administrative") {
        base_salary = ADMIN_BASE;
    } else {
        base_salary = OTHER_BASE;
    }
    
    // Adjust for education level
    if (education == "PhD") {
        base_salary *= 1.5;
    } else if (education == "Master") {
        base_salary *= 1.3;
    } else if (education == "Bachelor") {
        base_salary *= 1.1;
    } else if (education == "Diploma") {
        base_salary *= 1.05;
    }
    
    // Adjust for experience (5% increase per year)
    base_salary *= (1 + (0.05 * experience));
    
    return base_salary;
}

void displayDepartments() {
    cout << "Available Departments:\n";
    cout << "1. Teaching\n";
    cout << "2. Administrative\n";
    cout << "3. Other\n";
}

void displayEducationLevels() {
    cout << "Education Levels:\n";
    cout << "1. PhD\n";
    cout << "2. Master\n";
    cout << "3. Bachelor\n";
    cout << "4. Diploma\n";
}

void displayGenderOptions() {
    cout << "Gender Options:\n";
    cout << "1. Male\n";
    cout << "2. Female\n";
    cout << "3. Other\n";
}

string getDepartment(int choice) {
    switch(choice) {
        case 1: return "Teaching";
        case 2: return "Administrative";
        case 3: return "Other";
        default: return "Other";
    }
}

string getEducationLevel(int choice) {
    switch(choice) {
        case 1: return "PhD";
        case 2: return "Master";
        case 3: return "Bachelor";
        default: return "Diploma";
    }
}

string getGender(int choice) {
    switch(choice) {
        case 1: return "Male";
        case 2: return "Female";
      //  default: return "Other";
    }
}

void getEmployeeDetails(Employee* newEmp) {
    cout << "  Enter Employee Full Name: ";
    cin.ignore();
    getline(cin, newEmp->emp_full_name);
    
    // Gender selection
    int genderChoice;
    displayGenderOptions();
    cout << "  Select Gender (1-2): ";
    cin >> genderChoice;
    newEmp->emp_gender = getGender(genderChoice);
    
    do {
        cout << "  Enter Unique Employee ID: ";
        cin >> newEmp->emp_id;
        if (!check_ID(newEmp->emp_id)) cout << "  ID already exists. Try again.\n";
    } while (!check_ID(newEmp->emp_id));
    
    // Department selection
    int deptChoice;
    displayDepartments();
    cout << "  Select Department (1-3): ";
    cin >> deptChoice;
    newEmp->emp_department = getDepartment(deptChoice);
    
    // Education level
    int eduChoice;
    displayEducationLevels();
    cout << "  Select Education Level (1-4): ";
    cin >> eduChoice;
    newEmp->emp_education = getEducationLevel(eduChoice);
    
    // Work experience
    cout << "  Enter Years of Work Experience: ";
    cin >> newEmp->emp_experience;
    
    // Calculate salary based on department, education, and experience
    newEmp->emp_salary = calculateSalary(newEmp->emp_department, newEmp->emp_education, newEmp->emp_experience);
    
    cout << "  Enter Employee Phone Number: ";
    cin >> newEmp->emp_phoneNumber;
}

void insert_beg() {
    Employee* newEmp = new Employee;
    cout << "\nInserting Employee at Beginning:\n";
    getEmployeeDetails(newEmp);
    
    newEmp->prev = NULL;
    newEmp->next = head;
    if (head != NULL) head->prev = newEmp;
    else tail = newEmp;
    head = newEmp;
    
    cout << "Employee " << newEmp->emp_full_name << " inserted successfully at the beginning.\n";
    cout << "Calculated Salary: $" << newEmp->emp_salary << "\n\n";
}

void insert_random() {
    int pos;
    cout << "\nEnter the position you want to insert: ";
    cin >> pos;

    if (pos < 1 || pos > (numberOfEmp() + 1)) {
        cout << "Invalid position!\n\n";
        return;
    }
    
    Employee* newEmp = new Employee;
    cout << "\nInserting Employee at Position " << pos << ":\n";
    getEmployeeDetails(newEmp);
    
    newEmp->prev = NULL;
    newEmp->next = NULL;
    
    if (pos == 1) {
        newEmp->next = head;
        if (head != NULL) head->prev = newEmp;
        else tail = newEmp;
        head = newEmp;
        cout << "Employee " << newEmp->emp_full_name << " inserted successfully at position " << pos << ".\n";
        cout << "Calculated Salary: $" << newEmp->emp_salary << "\n\n";
        return;
    }
    
    if (pos == numberOfEmp() + 1) {
        if (tail != NULL) {
            tail->next = newEmp;
            newEmp->prev = tail;
        } else {
            head = newEmp;
        }
        tail = newEmp;
        cout << "Employee " << newEmp->emp_full_name << " inserted successfully at position " << pos << ".\n";
        cout << "Calculated Salary: $" << newEmp->emp_salary << "\n\n";
        return;
    }
    
    Employee* temp = head;
    for (int i = 1; i < pos - 1; i++) temp = temp->next;
    
    newEmp->next = temp->next;
    newEmp->prev = temp;
    temp->next->prev = newEmp;
    temp->next = newEmp;
    
    cout << "Employee " << newEmp->emp_full_name << " inserted successfully at position " << pos << ".\n";
    cout << "Calculated Salary: $" << newEmp->emp_salary << "\n\n";
}

void insert_last() {
    Employee* newEmp = new Employee;
    cout << "\nInserting Employee at End:\n";
    getEmployeeDetails(newEmp);
    
    newEmp->next = NULL;
    
    if (tail == NULL) {
        newEmp->prev = NULL;
        head = tail = newEmp;
        cout << "The list was empty. Employee inserted at beginning.\n";
    } else {
        newEmp->prev = tail;
        tail->next = newEmp;
        tail = newEmp;
        cout << "Employee " << newEmp->emp_full_name << " inserted successfully at the end.\n";
    }
    
    cout << "Calculated Salary: $" << newEmp->emp_salary << "\n\n";
}

void delete_beg() {
    if (head == NULL) {
        cout << "The list is empty.\n\n";
        return;
    }
    Employee* temp = head;
    head = head->next;

    if (head != NULL) head->prev = NULL;
    else tail = NULL;

    cout << temp->emp_full_name << " deleted successfully from the beginning.\n\n";
    delete temp;
}

void delete_random() {
    if (head == NULL) {
        cout << "The list is empty.\n";
        return;
    }
    int pos;
    cout << "Enter the position of employee to delete: ";
    cin >> pos;
    if (pos < 1 || pos > numberOfEmp()) {
        cout << "Invalid position!\n";
        return;
    }
    Employee* temp = head;
    if (pos == 1) {
        head = head->next;
        if (head != NULL) head->prev = NULL;
        else tail = NULL;
        cout << temp->emp_full_name << " deleted successfully from position " << pos << ".\n\n";
        delete temp;
        return;
    }
    for (int i = 1; i < pos; i++) temp = temp->next;
    if (temp->next == NULL) {
        tail = temp->prev;
        tail->next = NULL;
    } else {
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
    cout << temp->emp_full_name << " deleted successfully from position " << pos << ".\n\n";
    delete temp;
}

void delete_last() {
    if (head == NULL) {
        cout << "The list is empty.\n";
        return;
    }
    Employee* temp = tail;
    tail = tail->prev;
    if (tail != NULL) tail->next = NULL;
    else head = NULL;

    cout << temp->emp_full_name << " deleted successfully from the end.\n\n";
    delete temp;
}

void searching() {
    string id;
    cout << "\nEnter the employee ID to search: ";
    cin >> id;
    if (head == NULL) {
        cout << "The list is empty.\n";
        return;
    }
    Employee* temp = head;
    while (temp != NULL) {
        if (temp->emp_id == id) {
            cout << "\n--- Employee Details ---\n";
            cout << "Full Name     : " << temp->emp_full_name << "\n";
            cout << "Employee ID   : " << temp->emp_id << "\n";
            cout << "Gender        : " << temp->emp_gender << "\n";
            cout << "Department    : " << temp->emp_department << "\n";
            cout << "Education     : " << temp->emp_education << "\n";
            cout << "Experience    : " << temp->emp_experience << " years\n";
            cout << "Salary        : $" << temp->emp_salary << "\n";
            cout << "Phone Number  : " << temp->emp_phoneNumber << "\n";
            cout << "-------------------------------\n\n";   
            return;
        }
        temp = temp->next;
    }
    cout << "Employee with ID " << id << " not found.\n\n";
}

void backward() {
    if (tail == NULL) {
        cout << "The list is empty.\n";
        return;
    }
    Employee* temp = tail;
    cout << "\n--- Employee List (Backward) ---\n";
    while (temp != NULL) {
        cout << "Full Name     : " << temp->emp_full_name << "\n";
        cout << "Employee ID   : " << temp->emp_id << "\n";
        cout << "Gender        : " << temp->emp_gender << "\n";
        cout << "Department    : " << temp->emp_department << "\n";
        cout << "Education     : " << temp->emp_education << "\n";
        cout << "Experience    : " << temp->emp_experience << " years\n";
        cout << "Salary        : $" << temp->emp_salary << "\n";
        cout << "Phone Number  : " << temp->emp_phoneNumber << "\n";
        cout << "-------------------------------\n";
        temp = temp->prev;
    }
    cout << "\n";
}

void forward() {
    if (head == NULL) {
        cout << "The list is empty.\n";
        return;
    }
    Employee* temp = head;
    cout << "\n--- Employee List (Forward) ---\n";
    while (temp != NULL) {
        cout << "Full Name     : " << temp->emp_full_name << "\n";
        cout << "Employee ID   : " << temp->emp_id << "\n";
        cout << "Gender        : " << temp->emp_gender << "\n";
        cout << "Department    : " << temp->emp_department << "\n";
        cout << "Education     : " << temp->emp_education << "\n";
        cout << "Experience    : " << temp->emp_experience << " years\n";
        cout << "Salary        : $" << temp->emp_salary << "\n";
        cout << "Phone Number  : " << temp->emp_phoneNumber << "\n";
        cout << "-------------------------------\n";
        temp = temp->next;
    }
    cout << "\n";
}

void update() {
    string id;
    cout << "Enter the Employee ID to update: ";
    cin >> id;
    Employee* temp = head;
    while (temp != NULL) {
        if (temp->emp_id == id) {
            cout << "Updating details for " << temp->emp_full_name << "...\n";
            
            // Update basic information
            cout << "  Enter new full name: ";
            cin.ignore();
            getline(cin, temp->emp_full_name);
            
            // Update gender
            int genderChoice;
            displayGenderOptions();
            cout << "  Select new Gender (1-3, 0 to keep current): ";
            cin >> genderChoice;
            if (genderChoice > 0 && genderChoice < 4) {
                temp->emp_gender = getGender(genderChoice);
            }
            
            // Update department
            int deptChoice;
            displayDepartments();
            cout << "  Select new Department (1-3, 0 to keep current): ";
            cin >> deptChoice;
            if (deptChoice > 0 && deptChoice < 4) {
                temp->emp_department = getDepartment(deptChoice);
            }
            
            // Update education
            int eduChoice;
            displayEducationLevels();
            cout << "  Select new Education Level (1-4, 0 to keep current): ";
            cin >> eduChoice;
            if (eduChoice > 0 && eduChoice < 5) {
                temp->emp_education = getEducationLevel(eduChoice);
            }
            
            // Update experience
            cout << "  Enter new years of experience (current: " << temp->emp_experience << "): ";
            cin >> temp->emp_experience;
            
            // Recalculate salary
            temp->emp_salary = calculateSalary(temp->emp_department, temp->emp_education, temp->emp_experience);
            
            cout << "  Enter new phone number: ";
            cin >> temp->emp_phoneNumber;
            
            cout << "Employee details updated successfully.\n";
            cout << "New calculated salary: $" << temp->emp_salary << "\n\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Employee ID not found.\n";
}

void retrieve() {
    string id;
    cout << "Enter the Employee ID to retrieve details: ";
    cin >> id;
    if (head == NULL) {
        cout << "The list is empty.\n\n";
        return;
    }
    Employee* temp = head;
    while (temp != NULL) {
        if (temp->emp_id == id) {
            cout << "\n--- Employee Found ---\n";
            cout << "Full Name     : " << temp->emp_full_name << "\n";
            cout << "Employee ID   : " << temp->emp_id << "\n";
            cout << "Gender        : " << temp->emp_gender << "\n";
            cout << "Department    : " << temp->emp_department << "\n";
            cout << "Education     : " << temp->emp_education << "\n";
            cout << "Experience    : " << temp->emp_experience << " years\n";
            cout << "Salary        : $" << temp->emp_salary << "\n";
            cout << "Phone Number  : " << temp->emp_phoneNumber << "\n";
            cout << "-------------------------------\n\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Employee with ID " << id << " not found.\n\n";
}

void sortByName() {
    if (head == NULL || head->next == NULL) return;
    bool swapped;
    Employee *ptr1;
    Employee *lptr = NULL;
    do {
        swapped = false;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->emp_full_name > ptr1->next->emp_full_name) {
                swap(ptr1->emp_full_name, ptr1->next->emp_full_name);
                swap(ptr1->emp_id, ptr1->next->emp_id);
                swap(ptr1->emp_salary, ptr1->next->emp_salary);
                swap(ptr1->emp_department, ptr1->next->emp_department);
                swap(ptr1->emp_education, ptr1->next->emp_education);
                swap(ptr1->emp_experience, ptr1->next->emp_experience);
                swap(ptr1->emp_phoneNumber, ptr1->next->emp_phoneNumber);
                swap(ptr1->emp_gender, ptr1->next->emp_gender);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void sortByID() {
    if (head == NULL || head->next == NULL) return;
    bool swapped;
    Employee *ptr1;
    Employee *lptr = NULL;
    do {
        swapped = false;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->emp_id > ptr1->next->emp_id) {
                swap(ptr1->emp_full_name, ptr1->next->emp_full_name);
                swap(ptr1->emp_id, ptr1->next->emp_id);
                swap(ptr1->emp_salary, ptr1->next->emp_salary);
                swap(ptr1->emp_department, ptr1->next->emp_department);
                swap(ptr1->emp_education, ptr1->next->emp_education);
                swap(ptr1->emp_experience, ptr1->next->emp_experience);
                swap(ptr1->emp_phoneNumber, ptr1->next->emp_phoneNumber);
                swap(ptr1->emp_gender, ptr1->next->emp_gender);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void sortBySalary() {
    if (head == NULL || head->next == NULL) return;
    bool swapped;
    Employee *ptr1;
    Employee *lptr = NULL;
    do {
        swapped = false;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->emp_salary < ptr1->next->emp_salary) {
                swap(ptr1->emp_full_name, ptr1->next->emp_full_name);
                swap(ptr1->emp_id, ptr1->next->emp_id);
                swap(ptr1->emp_salary, ptr1->next->emp_salary);
                swap(ptr1->emp_department, ptr1->next->emp_department);
                swap(ptr1->emp_education, ptr1->next->emp_education);
                swap(ptr1->emp_experience, ptr1->next->emp_experience);
                swap(ptr1->emp_phoneNumber, ptr1->next->emp_phoneNumber);
                swap(ptr1->emp_gender, ptr1->next->emp_gender);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void sortByGender() {
    if (head == NULL || head->next == NULL) return;
    bool swapped;
    Employee *ptr1;
    Employee *lptr = NULL;
    do {
        swapped = false;
        ptr1 = head;
        while (ptr1->next != lptr) {
            if (ptr1->emp_gender > ptr1->next->emp_gender) {
                swap(ptr1->emp_full_name, ptr1->next->emp_full_name);
                swap(ptr1->emp_id, ptr1->next->emp_id);
                swap(ptr1->emp_salary, ptr1->next->emp_salary);
                swap(ptr1->emp_department, ptr1->next->emp_department);
                swap(ptr1->emp_education, ptr1->next->emp_education);
                swap(ptr1->emp_experience, ptr1->next->emp_experience);
                swap(ptr1->emp_phoneNumber, ptr1->next->emp_phoneNumber);
                swap(ptr1->emp_gender, ptr1->next->emp_gender);
                swapped = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void sortEmployees() {
    if (head == NULL) {
        cout << "The list is empty.\n";
        return;
    }  
    int choice;
    cout << "\nSort Employees by:\n";
    cout << "1. Name\n";
    cout << "2. ID\n";
    cout << "3. Salary (Highest to Lowest)\n";
    cout << "4. Gender\n";
    cout << "Enter your choice: ";
    cin >> choice;
    switch(choice) {
        case 1:
            sortByName();
            break;
        case 2:
            sortByID();
            break;
        case 3:
            sortBySalary();
            break;
        case 4:
            sortByGender();
            break;
        default:
            cout << "Invalid choice!\n";
            return;
    }
    cout << "Employees sorted successfully!\n";
    forward(); // Display the sorted list
}

void savetofile() {
    ofstream outFile("employees.txt");
    if (!outFile) {
        cout << "Error opening file for writing!\n";
        return;
    }
    
    Employee* temp = head;
    while (temp != NULL) {
        outFile << temp->emp_full_name << "\n"
                << temp->emp_id << "\n"
                << temp->emp_gender << "\n"
                << temp->emp_department << "\n"
                << temp->emp_education << "\n"
                << temp->emp_experience << "\n"
                << temp->emp_salary << "\n"
                << temp->emp_phoneNumber << "\n";
        temp = temp->next;
    }
    
    outFile.close();
    cout << "Employee data saved to file successfully!\n";
}
void loadfromfile() {
    ifstream inFile("employees.txt");
    if (!inFile) {
        cout << "No existing employee data found.\n";
        return;
    }

    // Clear existing list
    while (head != NULL) {
        Employee* temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;

    string line;
    while (true) {
        Employee* newEmp = new Employee;

        // Read full name
        if (!getline(inFile, newEmp->emp_full_name)) {
            delete newEmp;
            break;
        }

        // Read ID
        if (!getline(inFile, newEmp->emp_id)) {
            delete newEmp;
            break;
        }

        // Read gender
        if (!getline(inFile, newEmp->emp_gender)) {
            delete newEmp;
            break;
        }

        // Read department
        if (!getline(inFile, newEmp->emp_department)) {
            delete newEmp;
            break;
        }

        // Read education
        if (!getline(inFile, newEmp->emp_education)) {
            delete newEmp;
            break;
        }

        // Read experience (convert string to int)
        if (!getline(inFile, line)) {
            delete newEmp;
            break;
        }
        newEmp->emp_experience = stoi(line); // <-- stoi used here

        // Read salary (convert string to double)
        if (!getline(inFile, line)) {
            delete newEmp;
            break;
        }
        newEmp->emp_salary = stod(line); // <-- stod used here

        // Read phone number (convert string to int)C
        if (!getline(inFile, line)) {
            delete newEmp;
            break;
        }
        newEmp->emp_phoneNumber = stoi(line); // <-- stoi used here

        // Link the new employee to the list
        newEmp->prev = tail;
        newEmp->next = NULL;

        if (tail == NULL) {
            head = tail = newEmp;
        } else {
            tail->next = newEmp;
            tail = newEmp;
        }
    }

    inFile.close();
    cout << "Employee data loaded from file successfully!\n";
}

void menu() {
    loadfromfile(); // Load data when program starts
    
    int choice;
    do {
        cout << "=============== EMPLOYEE SYSTEM ===============\n";
        cout << "1: Insert employee\n";
        cout << "2: Delete employee\n";
        cout << "3: Display employees\n";
        cout << "4: Search employee\n";
        cout << "5: Save to file\n";
        cout << "6: Update employee details\n";
        cout << "7: Retrieve employee by ID\n";
        cout << "8: Sort employee list\n";
        cout << "0: Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int add;
                cout << " Enter 1 to insert at beginning\n";
                cout << " Enter 2 to insert at specific position\n"; 
                cout << " Enter 3 to insert at end: ";
                cin >> add;
                if (add == 1) insert_beg();
                else if (add == 2) insert_random();
                else if (add == 3) insert_last();
                else cout << "Invalid insert choice!\n";
                break;
            }
            case 2: {
                int del;
                cout << "Enter 1 to delete at beginning\n";
                cout << "Enter 2 to delete at specific position\n";
                cout << "Enter 3 to delete at end: ";
                cin >> del;
                if (del == 1) delete_beg();
                else if (del == 2) delete_random();
                else if (del == 3) delete_last();
                else cout << "Invalid delete choice!\n";
                break;
            }
            case 3: { 
                int display;
                cout << "Enter 1 to display forward\n";
                cout << "Enter 2 to display backward: ";
                cin >> display;
                if (display == 1) forward();
                else if (display == 2) backward();
                else cout << "Invalid display choice!\n";
                break;
            }
            case 4:
                searching();
                break;
            case 5:
                savetofile();
                break;
            case 6:
                update();
                break;
            case 7:
                retrieve();
                break;
            case 8:
                sortEmployees();   
                break;
            case 0:
                savetofile(); 
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid main menu choice!\n";
        }
    } while (choice != 0);
}

int main() {
    menu();
    return 0; 
}