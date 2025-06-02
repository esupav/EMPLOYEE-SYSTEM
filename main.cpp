#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
struct Employee {
    string emp_full_name;
    string emp_id;
    double emp_salary;
    string emp_department;
    int emp_phoneNumber;
    Employee *prev;
    Employee *next;
};
Employee *head = NULL;
Employee *tail = NULL;
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
void insert_beg() {
    Employee* newEmp = new Employee;

    cout << "  Enter Employee Full Name: ";
    cin.ignore();
    getline(cin, newEmp->emp_full_name);
    do {
        cout << "  Enter Unique Employee ID: ";
        cin >> newEmp->emp_id;
        if (!check_ID(newEmp->emp_id)) cout << "  ID already exists. Try again.\n";
    } while (!check_ID(newEmp->emp_id));
    cout << "  Enter Employee Salary: ";
    cin >> newEmp->emp_salary;
    cout << "  Enter Employee Department: ";
   cin.ignore();
    getline(cin, newEmp->emp_department);
    cout << "  Enter Employee phone Number: ";
    cin >> newEmp->emp_phoneNumber;
    newEmp->prev = NULL;
    newEmp->next = head;
    if (head != NULL) head->prev = newEmp;
    else tail = newEmp;
    head = newEmp;
    cout << "Employee " << newEmp->emp_full_name << " inserted successfully at the beginning.\n\n";
}
void insert_random() {
    int pos;
    cout << "\nEnter the position you want to insert: ";
    cin >> pos;

    if (pos < 1||  pos > (numberOfEmp() + 1)) {
        cout << "Invalid position!\n\n";
        return;
    }
    Employee* newEmp = new Employee;
    cout << "  Enter Employee Full Name: ";
    cin.ignore();
    getline(cin, newEmp->emp_full_name);
    do {
        cout << "  Enter Unique Employee ID: ";
        cin >> newEmp->emp_id;
        if (!check_ID(newEmp->emp_id)) cout << "  ID already exists. Try again.\n";
    } while (!check_ID(newEmp->emp_id));
    cout << "  Enter Employee Salary: ";
    cin >> newEmp->emp_salary;
    cout << "  Enter Employee Department: ";
      cin.ignore();
    getline(cin, newEmp->emp_full_name);
    cout << "  Enter Employee phone Number: ";
    cin >> newEmp->emp_phoneNumber;
    newEmp->prev = NULL;
    newEmp->next = NULL;
    if (pos == 1) {
        newEmp->next = head;
        if (head != NULL) head->prev = newEmp;
        else tail = newEmp;
        head = newEmp;
        cout << "Employee " << newEmp->emp_full_name << " inserted successfully at position " << pos << ".\n\n";
        return;
    }
    if (pos == numberOfEmp() + 1) {
        if (tail != NULL) {
            tail->next = newEmp;
            newEmp->prev = tail;
        } else head = newEmp;
        tail = newEmp;
        cout << "Employee " << newEmp->emp_full_name << " inserted successfully at position " << pos << ".\n\n";
        return;
    }
    Employee* temp = head;
    for (int i = 1; i < pos - 1; i++) temp = temp->next;
    newEmp->next = temp->next;
    newEmp->prev = temp;
    temp->next->prev = newEmp;
    temp->next = newEmp;
    cout << "Employee " << newEmp->emp_full_name << " inserted successfully at position " << pos << ".\n\n";
}
void insert_last() {
    Employee* newEmp = new Employee;
    cout << "  Enter Employee Full Name: ";
    cin.ignore();
    getline(cin, newEmp->emp_full_name);
    do {
        cout << "  Enter Unique Employee ID: ";
        cin >> newEmp->emp_id;
        if (!check_ID(newEmp->emp_id)) cout << "  ID already exists. Try again.\n";
    } while (!check_ID(newEmp->emp_id));
    cout << "  Enter Employee Salary: ";
    cin >> newEmp->emp_salary;
    cout << "  Enter Employee Department: ";
     cin.ignore();
    getline(cin, newEmp->emp_full_name);
    cout << "  Enter Employee phone Number: ";
    cin >> newEmp->emp_phoneNumber;
newEmp->next = NULL;
    if (tail == NULL) {
        newEmp->prev = NULL;
        head = tail = newEmp;

cout << "The list was empty. Employee inserted at beginning.\n\n";
} else {
        newEmp->prev = tail;
        tail->next = newEmp;
        tail = newEmp;
        cout << "Employee " << newEmp->emp_full_name << " inserted successfully at the end.\n\n";
    }
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
    if (pos < 1||  pos > numberOfEmp()) {
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
        cout << "Salary        : " << temp->emp_salary << "\n";
        cout << "Department    : " << temp->emp_department << "\n";
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
        cout << "Salary        : " << temp->emp_salary << "\n";
        cout << "Department    : " << temp->emp_department << "\n";
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
        if (temp->emp_id == id) {cout << "Updating details for " << temp->emp_full_name << "...\n";
            cout << "  Enter new full name: ";
            cin.ignore();
            getline(cin, temp->emp_full_name);
            cout << "  Enter new salary: ";
            cin >> temp->emp_salary;
            cout << "  Enter new department: ";
            cin.ignore();
             getline(cin, temp->emp_department);
            cout << "  Enter new phone number: ";
            cin >> temp->emp_phoneNumber;
            cout << "Employee details updated successfully.\n\n";
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
            cout << "Salary        : " << temp->emp_salary << "\n";
            cout << "Department    : " << temp->emp_department << "\n";
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
                // Swap the data
                swap(ptr1->emp_full_name, ptr1->next->emp_full_name);
                swap(ptr1->emp_id, ptr1->next->emp_id);
                swap(ptr1->emp_salary, ptr1->next->emp_salary);
                swap(ptr1->emp_department, ptr1->next->emp_department);
                swap(ptr1->emp_phoneNumber, ptr1->next->emp_phoneNumber);
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
                swap(ptr1->emp_phoneNumber, ptr1->next->emp_phoneNumber);
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
    cout << "Enter your choice: ";
    cin >> choice;
    switch(choice) {
        case 1:
            sortByName();
            break;
        case 2:
            sortByID();
            break;
        default:
            cout << "Invalid choice!\n";
            return;
    }
    cout << "Employees sorted successfully!\n";
    forward(); // Display the sorted list
}

void menu() {
    int choice;
    do {
        cout <<" ===============EMPLOYEE SYSTEM===============\n";
        cout << "1: Insert employee\n";
        cout << "2: Delete employee\n";
        cout << "3: Display employees\n";
        cout << "4: Search employee\n";
        cout << "5: View group members\n";
        cout << "6: Update employee details\n";
        cout << "7: Retrieve employee by ID\n";
        cout << "8: Sort employee list\n";
        cout << "0: Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
switch (choice) {
            case 1: {
                  int add;
            cout<<" Enter 1 to insert at beginning"<<endl;
            cout<<" Enter 2 to insert at specific position"<<endl; 
            cout<<" Enter 3 to insert at end: ";
                cin >> add;
                if (add == 1) insert_beg();
                else if (add == 2) insert_random();
                else if (add == 3) insert_last();
                else cout << "Invalid insert choice!\n";
                break;
            }
            case 2: {
                int del;
                cout << "Enter 1 to delete at beginning"<<endl;
                cout <<" Enter 2 to delete at specific position" <<endl;
                cout <<" Enter 3 to delete at end: ";
                cin >> del;
                if (del == 1) delete_beg();
                else if (del == 2) delete_random();
                else if (del == 3) delete_last();
                else cout << "Invalid delete choice!\n";
                break;
}
            case 3: {
                
                int display;
         cout << "Enter 1 to display forward"<<endl;
        cout << "Enter 2 to display backward"<<endl;
                cin >> display;
                if (display == 1) forward();
                else if (display == 2) backward();
                else cout << "Invalid display choice!\n";
                break;
            }
            case 4:
                
                break;
            case 5:
                Group_members();
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