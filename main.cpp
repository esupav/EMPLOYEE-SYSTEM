#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cctype>

using namespace std;

struct Employee {
    string emp_full_name;
    string emp_id;
    double emp_salary;
    string emp_department;
    string emp_education;
    int emp_experience;
    string emp_phoneNumber;
    string emp_gender;
    Employee *prev;
    Employee *next;
};

Employee *head = NULL;
Employee *tail = NULL;

const double TEACHING_BASE = 13000;
const double ADMIN_BASE = 15000;
const double OTHER_BASE = 2000;
const string FILENAME = "employees.txt";

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
    
    if (department == "Teaching") {
        base_salary = TEACHING_BASE;
    } else if (department == "Administrative") {
        base_salary = ADMIN_BASE;
    } else {
        base_salary = OTHER_BASE;
    }
    
    if (education == "PhD") {
        base_salary *= 1.5;
    } else if (education == "Master") {
        base_salary *= 1.3;
    } else if (education == "Bachelor") {
        base_salary *= 1.1;
    } else if (education == "Diploma") {
        base_salary *= 1.05;
    }
    
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
    
}

void displayGenderOptions() {
    cout << "Gender Options:\n";
    cout << "1. Male\n";
    cout << "2. Female\n";
}

string getDepartment(int choice) {
    switch(choice) {
        case 1: return "Teaching";
        case 2: return "Administrative";
        case 3: return "Other";
        default:
            cout << "Invalid choice! Defaulting to Other.\n";
            return "Other";
    }
}

string getEducationLevel(int choice) {
    switch(choice) {
        case 1: return "PhD";
        case 2: return "Master";
        case 3: return "Bachelor";
        case 4: return "Diploma";
        default: 
            cout << "Invalid choice! Defaulting to Bachelor.\n";
            return "Bachelor";
    }
}

string getGender(int choice) {
    switch(choice) {
        case 1: return "Male";
        case 2: return "Female";
        default:
            cout << "Invalid choice! Defaulting to Male.\n";
            return "Male";
    }
}

void getEmployeeDetails(Employee* newEmp) {
    string name;
    bool correct;

    cin.ignore(); 

    do {
        correct = true;
        cout << "  Enter Employee Full Name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "  Name cannot be empty.\n";
            correct = false;
            continue;
        }

        for (char c : name) {
            if (!isalpha(c) && c != ' ') {
                cout << "  Invalid input. Only letters and spaces are allowed.\n";
                correct = false;
                break;
            }
        }
    } while (!correct);

    newEmp->emp_full_name = name;
    
    int genderChoice;
    displayGenderOptions();
    do {
        cout << "  Select Gender (1-2): ";
        cin >> genderChoice;
        if(genderChoice < 1 || genderChoice > 2)
            cout << "  Invalid input\n";
    } while(genderChoice < 1 || genderChoice > 2);
    newEmp->emp_gender = getGender(genderChoice);
    
    do {
        cout << "  Enter Unique Employee ID: ";
        cin >> newEmp->emp_id;
        if (!check_ID(newEmp->emp_id)) 
            cout << "  ID already exists. Try again.\n";
    } while (!check_ID(newEmp->emp_id));
    
    int deptChoice;
    displayDepartments();
    do {
        cout << "  Select Department (1-3): ";
        cin >> deptChoice;
        if(deptChoice < 1 || deptChoice > 3)
            cout << "  Invalid input\n";
    } while(deptChoice < 1 || deptChoice > 3);
    newEmp->emp_department = getDepartment(deptChoice);
    
    int eduChoice;
    displayEducationLevels();
    do {
        cout << "  Select Education Level (1-3): ";
        cin >> eduChoice;
        if(eduChoice < 1 || eduChoice > 3)
            cout << "  Invalid input\n";
    } while(eduChoice < 1 || eduChoice > 3);
    newEmp->emp_education = getEducationLevel(eduChoice);
    
    do {
     cout << "  Enter Experience (1 to 20 years): ";
    cin >> newEmp->emp_experience;
    if (newEmp->emp_experience < 1 || newEmp->emp_experience > 20)
        cout << "  Invalid input. Please enter a value between 1 and 20.\n";
    } while (newEmp->emp_experience < 1 || newEmp->emp_experience > 20);

    newEmp->emp_salary = calculateSalary(newEmp->emp_department, newEmp->emp_education, newEmp->emp_experience);
    
    string phone;
    bool valid;
    do {
        cout << "  Enter the Employee Phone Number (12 digits): ";
        cin >> phone;
        valid = true;
        
        if (phone.length() != 12) {
            cout << "  Phone number must be exactly 12 digits.\n";
            valid = false;
            continue;
        }

        for (char c : phone) {
            if (!isdigit(c)) {
                cout << "  Invalid input. Only digits are allowed.\n";
                valid = false;
                break;
            }
        }
    } while (!valid);

    newEmp->emp_phoneNumber = phone;
}

void insert_emp() {
    Employee* newEmp = new Employee;
    cout << "\nInserting Employee information:\n";
    getEmployeeDetails(newEmp);
    
    newEmp->prev = NULL;
    newEmp->next = head;
    if (head != NULL) 
        head->prev = newEmp;
    else 
        tail = newEmp;
    head = newEmp;
    
    cout << "Employee " << newEmp->emp_full_name << " inserted successfully .\n";
    cout << "Calculated Salary: " << newEmp->emp_salary<<"etb" << "\n\n";
}

void delete_emp() {
    if (head == NULL) {
        cout << "No employees to delete.\n";
        return;
    }

    int option;
    cout << "Delete by:\n";
    cout << "1. Employee ID\n";
    cout << "2. Employee Name\n";
    cout << "Enter your choice: ";
    cin >> option;
    cin.ignore();

    Employee* current = head;
    bool found = false;
    string searchTerm;

    if (option == 1) {
        cout << "Enter Employee ID to delete: ";
        getline(cin, searchTerm);
        while (current != NULL) {
            if (current->emp_id == searchTerm) {
                found = true;
                break;
            }
            current = current->next;
        }
    } else if (option == 2) {
        cout << "Enter Employee Name to delete: ";
        getline(cin, searchTerm);
        while (current != NULL) {
            if (current->emp_full_name == searchTerm) {
                found = true;
                break;
            }
            current = current->next;
        }
    } else {
        cout << "Invalid option.\n";
        return;
    }

    if (!found) {
        cout << "Employee not found.\n";
        return;
    }
  
    if (current == head && current == tail) { 
        head = tail = NULL;
    } else if (current == head) {
        head = current->next;
        head->prev = NULL;
    } else if (current == tail) {
        tail = current->prev;
        tail->next = NULL;
    } else {
        current->prev->next = current->next;
        current->next->prev = current->prev;
    }

    delete current;
    cout << "Employee deleted successfully.\n";
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
            cout << "Salary        : " << temp->emp_salary<<"etb" << "\n";
            cout << "Phone Number  : " << temp->emp_phoneNumber << "\n";
            cout << "-------------------------------\n\n";   
            return;
        }
        temp = temp->next;
    }
    cout << "Employee with ID " << id << " not found.\n\n";
}

void display_emp() {
    if (head == NULL) {
        cout << "The list is empty.\n";
        return;
    }
    Employee* temp = head;
    cout << "\n--- Employee List ---\n";
    while (temp != NULL) {
        cout << "Full Name     : " << temp->emp_full_name << "\n";
        cout << "Employee ID   : " << temp->emp_id << "\n";
        cout << "Gender        : " << temp->emp_gender << "\n";
        cout << "Department    : " << temp->emp_department << "\n";
        cout << "Education     : " << temp->emp_education << "\n";
        cout << "Experience    : " << temp->emp_experience << " years\n";
        cout << "Salary        : " << temp->emp_salary<<"etb" << "\n";
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
            
            cout << "  Enter new full name: ";
            cin.ignore();
            getline(cin, temp->emp_full_name);
            
            int genderChoice;
            displayGenderOptions();
            cout << "  Select new Gender (1-2, 0 to keep current [" << temp->emp_gender << "]): ";
            cin >> genderChoice;
            if (genderChoice > 0 && genderChoice < 3) {
                temp->emp_gender = getGender(genderChoice);
            }
            
            int deptChoice;
            displayDepartments();
            cout << "  Select new Department (1-3, 0 to keep current [" << temp->emp_department << "]): ";
            cin >> deptChoice;
            if (deptChoice > 0 && deptChoice < 4) {
                temp->emp_department = getDepartment(deptChoice);
            }
            
            int eduChoice;
            displayEducationLevels();
            cout << "  Select new Education Level (1-4, 0 to keep current [" << temp->emp_education << "]): ";
            cin >> eduChoice;
            if (eduChoice > 0 && eduChoice < 5) {
                temp->emp_education = getEducationLevel(eduChoice);
            }
            
            cout << "  Enter new years of experience (current: " << temp->emp_experience << "): ";
            cin >> temp->emp_experience;
            
            temp->emp_salary = calculateSalary(temp->emp_department, temp->emp_education, temp->emp_experience);
            
            string phone;
            bool valid;
            do {
                cout << "  Enter new phone number (current: " << temp->emp_phoneNumber << "): ";
                cin >> phone;
                valid = true;
                
                if (phone.length() != 12) {
                    cout << "  Phone number must be exactly 12 digits.\n";
                    valid = false;
                    continue;
                }

                for (char c : phone) {
                    if (!isdigit(c)) {
                        cout << "  Invalid input. Only digits are allowed.\n";
                        valid = false;
                        break;
                    }
                }
            } while (!valid);
            temp->emp_phoneNumber = phone;
            
            cout << "Employee details updated successfully.\n";
            cout << "New calculated salary: " << temp->emp_salary<< "etb" << "\n\n";
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
            cout << "Salary        : " << temp->emp_salary<<"etb" << "\n";
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
    display_emp();
}

void savetofile() {
    ofstream outFile(FILENAME);
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
    ifstream inFile(FILENAME);
    if (!inFile) {
        cout << "No existing employee data found.\n";
        return;
    }

    while (head != NULL) {
        Employee* temp = head;
        head = head->next;
        delete temp;
    }
    tail = NULL;

    string line;
    while (true) {
        Employee* newEmp = new Employee;

        if (!getline(inFile, newEmp->emp_full_name)) {
            delete newEmp;
            break;
        }
        if (!getline(inFile, newEmp->emp_id)) {
            delete newEmp;
            break;
        }
        if (!getline(inFile, newEmp->emp_gender)) {
            delete newEmp;
            break;
        }
        if (!getline(inFile, newEmp->emp_department)) {
            delete newEmp;
            break;
        }
        if (!getline(inFile, newEmp->emp_education)) {
            delete newEmp;
            break;
        }
        if (!getline(inFile, line)) {
            delete newEmp;
            break;
        }
        newEmp->emp_experience = stoi(line);
        
        if (!getline(inFile, line)) {
            delete newEmp;
            break;
        }
        newEmp->emp_salary = stod(line);
        
        if (!getline(inFile, newEmp->emp_phoneNumber)) {
            delete newEmp;
            break;
        }

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
    loadfromfile(); 
    
    int choice;
    do {
        cout << "=============== EMPLOYEE REGISTRATION SYSTEM ===============\n";
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
            case 1: 
                insert_emp();
                break;
            case 2: 
                delete_emp();
                break;
            case 3: 
                display_emp();
                break;
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