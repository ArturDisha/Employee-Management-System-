//
//  Main.c
//Employee Management System
//
//  Created by Artur Disha on 28.5.23.
//


#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_EMPLOYEES 100

struct Employee {
    int id;
    char name[100];
    char contact[100];
    char employmentStatus[100];
    double salary;
    int isPresent;
};

void addEmployee(struct Employee* employees, int* count) {
    if (*count == MAX_EMPLOYEES) {
          printf("Employee database is full. Cannot add more employees.\n");
          return;
      }
      
      struct Employee employee;
      
      printf("\nEnter employee details:\n");
      
      printf("Employee ID: ");
      scanf("%d", &employee.id);
      
      printf("Name: ");
      scanf(" %[^\n]s", employee.name);
      
      printf("Contact: ");
      scanf(" %[^\n]s", employee.contact);
      
      printf("Employment Status: ");
      scanf(" %[^\n]s", employee.employmentStatus);
      
      printf("Salary: ");
      scanf("%lf", &employee.salary);
      
      employee.isPresent = false;
      
      employees[*count] = employee;
      (*count)++;
      
      printf("Employee added successfully.\n");
  }



void updateEmployee(struct Employee* employees, int count) {
    int employeeId;
    printf("\nEnter the ID of the employee to update: ");
    scanf("%d", &employeeId);
    
    int index = -1;
    
    for (int i = 0; i < count; i++) {
        if (employees[i].id == employeeId) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Employee with ID %d not found.\n", employeeId);
        return;
    }
    
    struct Employee* employee = &employees[index];
    
    printf("Updating employee with ID %d\n", employeeId);
    printf("Employee Name: %s\n", employee->name);
    
    printf("New Contact: ");
    scanf(" %[^\n]s", employee->contact);
    
    printf("New Employment Status: ");
    scanf(" %[^\n]s", employee->employmentStatus);
    
    printf("New Salary: ");
    scanf("%lf", &employee->salary);
    
    printf("Employee information updated successfully.\n");
}

void deleteEmployee(struct Employee* employees, int* count) {
    int employeeId;
    printf("\nEnter the ID of the employee to delete: ");
    scanf("%d", &employeeId);
    
    int index = -1;
    
    for (int i = 0; i < *count; i++) {
        if (employees[i].id == employeeId) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Employee with ID %d not found.\n", employeeId);
        return;
    }
    
    struct Employee* employee = &employees[index];
    
    printf("Deleting employee with ID %d\n", employeeId);
    printf("Employee Name: %s\n", employee->name);
    
    for (int i = index; i < *count - 1; i++) {
        employees[i] = employees[i + 1];
    }
    
    (*count)--;
    
    printf("Employee deleted successfully.\n");
}

void viewEmployees(struct Employee* employees, int count) {
    if (count == 0) {
        printf("No employees to display.\n");
        return;
    }
    
    printf("\nEmployee Records:\n");
    printf("--------------------------------------------------\n");
    printf("ID\tName\t\tContact\t\t\tEmployment Status\tSalary\n");
    printf("--------------------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        struct Employee* employee = &employees[i];
        printf("%d\t%s\t\t%s\t\t%s\t\t%.2lf\n", employee->id, employee->name, employee->contact, employee->employmentStatus, employee->salary);
    }
    
    printf("--------------------------------------------------\n");
}

void calculatePayroll(struct Employee* employees, int count) {
    if (count == 0) {
        printf("No employees in the database.\n");
        return;
    }
    
    double totalSalary = 0;
    
    for (int i = 0; i < count; i++) {
        struct Employee* employee = &employees[i];
        totalSalary += employee->salary;
    }
    
    printf("\nPayroll Summary:\n");
    printf("Total Number of Employees: %d\n", count);
    printf("Total Salary: $%.2lf\n", totalSalary);
}

void markAttendance(struct Employee* employees, int count) {
    if (count == 0) {
        printf("No employees in the database.\n");
        return;
    }
    
    int employeeId;
    printf("\nEnter the ID of the employee to mark attendance: ");
    scanf("%d", &employeeId);
    
    int index = -1;
    
    for (int i = 0; i < count; i++) {
        if (employees[i].id == employeeId) {
            index = i;
            break;
        }
    }
    
    if (index == -1) {
        printf("Employee with ID %d not found.\n", employeeId);
        return;
    }
    
    struct Employee* employee = &employees[index];
    
    printf("Marking attendance for employee with ID %d\n", employeeId);
    printf("Employee Name: %s\n", employee->name);
    
    employee->isPresent = true;
    
    printf("Attendance marked successfully.\n");
}

void viewAttendance(struct Employee* employees, int count) {
    if (count == 0) {
        printf("No employees in the database.\n");
        return;
    }
    
    printf("\nAttendance Records:\n");
    printf("-----------------------------------------\n");
    printf("ID\tName\t\tAttendance\n");
    printf("-----------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        struct Employee* employee = &employees[i];
        printf("%d\t%s\t\t%s\n", employee->id, employee->name, (employee->isPresent ? "Present" : "Absent"));
    }
    
    printf("-----------------------------------------\n");
}

void saveDataToFile(struct Employee* employees, int count) {
    FILE* file = fopen("employee_data.txt", "w");
    
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    for (int i = 0; i < count; i++) {
        struct Employee* employee = &employees[i];
        fprintf(file, "%d,%s,%s,%s,%.2lf,%d\n", employee->id, employee->name, employee->contact, employee->employmentStatus, employee->salary, employee->isPresent);
    }
    
    fclose(file);
    
    printf("Data saved to file successfully.\n");
}

void loadDataFromFile(struct Employee* employees, int* count) {
    FILE* file = fopen("employee_data.txt", "r");
    
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    
    *count = 0;
    
    while (!feof(file)) {
        struct Employee* employee = &employees[*count];
        fscanf(file, "%d,%[^,],%[^,],%[^,],%lf,%d\n", &employee->id, employee->name, employee->contact, employee->employmentStatus, &employee->salary, &employee->isPresent);
        (*count)++;
    }
    
    fclose(file);
    
    printf("Data loaded from file successfully.\n");
}

int main(void) {
    struct Employee employees[MAX_EMPLOYEES];
    int count = 0;
    
    int choice;
    
    do {
        printf("\nEmployee Management System\n");
        printf("1. Add Employee\n");
        printf("2. Update Employee\n");
        printf("3. Delete Employee\n");
        printf("4. View Employees\n");
        printf("5. Calculate Payroll\n");
        printf("6. Mark Attendance\n");
        printf("7. View Attendance\n");
        printf("8. Save Data to File\n");
        printf("9. Load Data from File\n");
        printf("0. Exit\n");
        
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                addEmployee(employees, &count);
                break;
            case 2:
                updateEmployee(employees, count);
                break;
            case 3:
                deleteEmployee(employees, &count);
                break;
            case 4:
                viewEmployees(employees, count);
                break;
            case 5:
                calculatePayroll(employees, count);
                break;
            case 6:
                markAttendance(employees, count);
                break;
            case 7:
                viewAttendance(employees, count);
                break;
            case 8:
                saveDataToFile(employees, count);
                break;
            case 9:
                loadDataFromFile(employees, &count);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 0);
    
    return 0;
}
