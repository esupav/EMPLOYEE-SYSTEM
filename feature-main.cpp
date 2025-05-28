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