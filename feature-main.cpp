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
                
                break;
}
            case 3: {
               
                break;
            }
            case 4:
                
                break;
            case 5:
               
          break;
               case 6:
             
         break;
         case 7:
         
      break;
             case 8:
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