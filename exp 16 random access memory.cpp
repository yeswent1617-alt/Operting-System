#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "employee.dat"

typedef struct {
    int id;
    char name[30];
    float salary;
} Employee;

// Function to add employee
void addEmployee() {
    FILE *fp = fopen(FILENAME, "ab"); // append in binary
    if (!fp) {
        printf("Error opening file!\n");
        return;
    }

    Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    printf("Enter Name: ");
    scanf("%s", emp.name);
    printf("Enter Salary: ");
    scanf("%f", &emp.salary);

    fwrite(&emp, sizeof(Employee), 1, fp);
    fclose(fp);
    printf("Employee added successfully!\n");
}

// Function to display all employees
void displayEmployees() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        printf("No employee records found.\n");
        return;
    }

    Employee emp;
    printf("\n--- Employee Records ---\n");
    while (fread(&emp, sizeof(Employee), 1, fp)) {
        printf("ID: %d | Name: %s | Salary: %.2f\n", emp.id, emp.name, emp.salary);
    }
    fclose(fp);
}

// Function to search employee by ID
void searchEmployee() {
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp) {
        printf("No employee records found.\n");
        return;
    }

    int id;
    printf("Enter Employee ID to search: ");
    scanf("%d", &id);

    Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(Employee), 1, fp)) {
        if (emp.id == id) {
            printf("Record Found: ID: %d | Name: %s | Salary: %.2f\n", emp.id, emp.name, emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }
    fclose(fp);
}

// Function to update employee by ID (Random Access)
void updateEmployee() {
    FILE *fp = fopen(FILENAME, "rb+"); // open for reading and writing
    if (!fp) {
        printf("No employee records found.\n");
        return;
    }

    int id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &id);

    Employee emp;
    int found = 0;

    while (fread(&emp, sizeof(Employee), 1, fp)) {
        if (emp.id == id) {
            printf("Existing Record: ID: %d | Name: %s | Salary: %.2f\n", emp.id, emp.name, emp.salary);
            printf("Enter New Name: ");
            scanf("%s", emp.name);
            printf("Enter New Salary: ");
            scanf("%f", &emp.salary);

            // Move file pointer one record back
            fseek(fp, -sizeof(Employee), SEEK_CUR);
            fwrite(&emp, sizeof(Employee), 1, fp);

            printf("Record updated successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", id);
    }

    fclose(fp);
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Employee Management System (Random Access File) ---\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: displayEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: updateEmployee(); break;
            case 5: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

