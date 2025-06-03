
# Employee Management System (EMS) - C++ Application 
 
## Table of Contents 
1. [Introduction](#introduction) 
2. [Features](#features) 
3. [Compilation and Execution](#compilation-and-execution) 
4. [Usage Guide](#usage-guide) 
5. [File Structure](#file-structure) 
6. [Limitations](#limitations) 
7. [Future Improvements](#future-improvements) 
 
## Introduction 
 
The Employee Management System (EMS) is a comprehensive C++ application that manages employee records using a doubly linked list data structure. It automates salary calculations based on department, education level, and work experience while providing full CRUD (Create, Read, Update, Delete) functionality. 
 
Key Capabilities: 
- Automated salary calculations with department-specific base pay 
- Complete employee record management 
- Data persistence through file storage 
- Flexible sorting and searching 
- Bidirectional data traversal 
 
## Features 
 
### Core Functionality 
- Automated Salary Calculation: 
  - Base salaries: Teaching ($30,000), Administrative ($25,000), Other ($20,000) 
  - Education multipliers: PhD (1.5×), Master (1.3×), Bachelor (1.1×), Diploma (1.05×) 
  - Experience bonus: 5% increase per year 
- Employee Management: 
  - Add employees at beginning, end, or any position 
  - Delete employees from any position 
  - Update employee details with automatic salary recalculation 
- Data Operations: 
  - Search by employee ID 
  - Sort by name, ID, salary (descending), or gender 
  - Display records forward or backward 
- Data Persistence: 
  - Auto-load from employees.txt on startup 
  - Auto-save on exit 
  - Manual save option 
 
## Compilation and Execution 
 
### Prerequisites 
- C++11 compatible compiler (g++ recommended) 
- Linux/macOS terminal or Windows command prompt 
 
### Compilation 
g++ -std=c++11 employees.cpp -o ems 
 
 
### Execution 
./ems 
 
 
## Usage Guide 
 
### Main Menu 
=============== EMPLOYEE SYSTEM =============== 
1: Insert employee 
2: Delete employee 
3: Display employees 
4: Search employee 
5: Save to file 
6: Update employee details 
7: Retrieve employee by ID 
8: Sort employee list 
0: Exit 
 
 
### Adding an Employee 
Inserting Employee at Beginning: 
  Enter Employee Full Name: Dr. Sarah Johnson 
  Gender Options: 
  1. Male 
  2. Female 
  3. Other 
  Select Gender (1-3): 2 
  Enter Unique Employee ID: TEA-PhD-885 
  Available Departments: 
  1. Teaching 
  2. Administrative 
  3. Other 
  Select Department (1-3): 1 
  Education Levels: 
  1. PhD 
  2. Master 
  3. Bachelor 
  4. Diploma 
  Select Education Level (1-4): 1 
  Enter Years of Work Experience: 12 
  Enter Employee Phone Number: 5551234567 
Employee Dr. Sarah Johnson inserted successfully at the beginning. 
Calculated Salary: $63000 
 
 
### Searching for an Employee 
Enter the employee ID to search: TEA-PhD-885 
 
--- Employee Details --- 
Full Name     : Dr. Sarah Johnson 
Employee ID   : TEA-PhD-885 
Gender        : Female 
Department    : Teaching 
Education     : PhD 
Experience    : 12 years 
Salary        : $63000 
Phone Number  : 5551234567 
 
 
### Sorting Employees 
Sort Employees by: 
1. Name 
2. ID 
3. Salary (Highest to Lowest) 
4. Gender 
Enter your choice: 3 
 
Employees sorted successfully! 
 
--- Employee List (Forward) --- 
Full Name     : Dr. Ahmed Khan 
Salary        : $72000 
... 
Full Name     : John Smith 
Salary        : $28000 
 
 
### Updating Employee Details 
` 
Enter the Employee ID to update: TEA-PhD-885 
Updating details for Dr. Sarah Johnson... 
  Enter new full name: Dr. Sarah Johnson-Smith 
  Gender Options: 
  1. Male 
  2. Female 
  3. Other 
  Select new Gender (1-3, 0 to keep current): 0 
  Available Departments: 
  1. Teaching 
  2. Administrative

Ŋę mæřø, [6/3/2025 10:20 PM]
3. Other 
  Select new Department (1-3, 0 to keep current): 2 
  Education Levels: 
  1. PhD 
  2. Master 
  3. Bachelor 
  4. Diploma 
  Select new Education Level (1-4, 0 to keep current): 0 
  Enter new years of experience (current: 12): 13 
  Enter new phone number: 5557654321 
Employee details updated successfully. 
New calculated salary: $48750 
 
## File Structure 
 
### employees.cpp 
The main application source code containing all functionality. 
 
### employees.txt 
Data storage file created automatically with format: 
 
Employee Full Name 
Employee ID 
Gender 
Department 
Education Level 
Experience Years 
Salary 
Phone Number 
 
## Limitations 
 
1. **Phone Number Handling**: 
   - Stored as integer (limited to 10 digits) 
   - Solution: Change to string in struct 
 
2. **Input Validation**: 
   - Limited validation for names and phone numbers 
   - Solution: Add regex validation 
 
3. **Performance**: 
   - O(n²) bubble sort for large datasets 
   - Solution: Implement merge sort (O(n log n)) 
 
4. **Error Handling**: 
   - Basic file I/O error handling 
   - Solution: Add detailed error messages 
 
## Future Improvements 
 
1. **Enhanced Validation**: 
   
cpp 
   // Phone number validation example 
   while (!(cin >> phone) || phone.length() > 15) { 
       cout << "Invalid! Max 15 digits: "; 
       cin.clear(); 
       cin.ignore(); 
   } 
   ` 
 
2. **Improved Sorting**: 
   - Implement merge sort for O(n lAdvanced Search 
3. **Advanced Search**: 
   - Add search by name, departmentData Encryption 
4. **Data Encryption**: 
   - Encrypt sensitive dataUser Interface
 
5. **User Interface**: 
   - Implement GUI using Qt or Database Integration**Database Integration**: 
   - Migrate from file storage tMulti-user Support. **Multi-user Support**: 
   - Add login system with different access levels