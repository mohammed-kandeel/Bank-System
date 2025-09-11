#pragma once
#include "Validation.h"
#include"FileManager.h"
#include "EmployeeManager.h"

class AdminManager {
private:
    static void showEmployeeScreen(string header, Employee* employee) {
        system("cls");
        cout << header << "--------  Employee Info  --------\n";
        employee->displayEmployeeInfo();
        cout << "-------------------------------\n";
    }

    static Employee* getEmployee(Admin* admin, string line) {
        int id, count = 0;
        Employee* employee;
        string temp;

        do {
            system("cls");
            cout << line;
            if (Validation::maxTry(count)) return nullptr;

            cout << "Enter employee ID (or press '0' to cancel): ";
            getline(cin, temp);

            if (Validation::cancelOperation(temp)) return nullptr;
            if (!Validation::tryParseNumber(temp, id)) {
                Validation::showError("Invalid input. Please enter a valid number.\n");
                count++;
                continue;
            }
            employee = admin->searchEmployee(id);
            if (employee == nullptr) {
                Validation::showError("No employee found with this ID. Try Again.\n");
                count++;
            }
            else return employee;
        } while (true);
    }
    static string getName(string line, string person) {
        string name;
        int count = 0;
        do {
            system("cls");
            cout << line << endl;

            cout << "\nEnter the " << person << "'s name (or press '0' to cancel): ";
            getline(cin, name);

            if (Validation::cancelOperation(name)) return "";

            if (!(Validation::is_valid_name(name))) {
                count++;
                if (Validation::maxTry(count)) return "";
                Validation::showError("Invalid name, try Again.\n");
            }
            else return name;
        } while (true);
    }
    static string getPassword(string line) {
        string password;
        int count = 0;
        do {
            system("cls");
            cout << line << endl;

            cout << "\nSet a password for the employee (or press '0' to cancel): ";
            getline(cin, password);

            if (Validation::cancelOperation(password)) return "";

            if (!Validation::is_valid_password(password)) {
                count++;
                if (Validation::maxTry(count)) return "";
                Validation::showError("Invalid password, Try Again.\n");
            }
            else return password;
        } while (true);
    }
    static double getSalary(string line) {
        double salary;
        int count = 0;

        string temp;
        do {
            if (Validation::maxTry(count)) return -1.0;
            system("cls");
            cout << line << endl;

            cout << "\nEnter the employee's salary (or press '0' to cancel): ";
            getline(cin, temp);

            if (Validation::cancelOperation(temp)) return -1.0;

            if (!Validation::tryParseNumber(temp, salary)) {
                Validation::showError("Invalid input. Please enter a valid number.\n");
                count++;
                continue;
            }
            if (!Validation::is_min_salary(salary)) {
                count++;
                Validation::showError("Invalid salary, The minimum is 1500. Try Again.\n");
            }
            else
                return salary;
        } while (true);
    }

    static void printAdminMenu() {
        system("cls");
        cout << "=====   Admin Menu   =====\n\n";
        cout << " 1. Add New Client\n";
        cout << " 2. Issuing New Card for Client\n";
        cout << " 3. Open USD Account for Client\n";
        cout << " 4. Search for Client\n";
        cout << " 5. Edit Client Information\n";
        cout << " 6. List All Clients\n\n";

        cout << " 7. Add New Employee\n";
        cout << " 8. Search for Employee\n";
        cout << " 9. Edit Employee Information\n";
        cout << "10. List All Employees\n\n";

        cout << "11. Display My Information\n";
        cout << "12. Update My Password\n";
        cout << " 0. Return to Login Menu\n";
        cout << "\nEnter your choice (0-12): ";
    }

    static void addNewEmployee(Admin* admin) {
        int id, count = 0;
        string name, password, line, temp;
        double salary;

        line = "\n========  New Employee  ========\n\n";

        id = 1 + FilesHelper::getLastId("LastEmployeeId.txt");
        line += "ID: " + to_string(id);

        //get name
        name = getName(line, "Employee");
        if (name == "") return;
        line += "\nName: " + name;

        //get password
        password = getPassword(line);
        if (password == "") return;
        line += "\nPassword: " + password;

        //get EGP balance
        salary = getSalary(line);
        if (salary == -1.0)
            return;
        line += "\nSalary: " + to_string(salary) + " EGP\n";

        system("cls");
        cout << line << endl;
        Employee* employee = new Employee(id, name, password, salary);
        admin->addEmployee(employee);
        FilesHelper::saveLastId("LastEmployeeId.txt", id);
        cout << endl;
        system("pause");
    }
    static void searchForEmployee(Admin* admin) {
        string line = "\n========  Search For Employee  ========\n\n";
        Employee* employeeInfo = getEmployee(admin, line);
        if (employeeInfo == nullptr) return;
        system("cls");
        line += "Employee found\n";
        showEmployeeScreen(line, employeeInfo);
        system("pause");
    }
    static void editEmployeeInfo(Admin* admin) {
        int count;
        string line, temp;

        system("cls");
        line = "\n========  Edit Employee Info  ========\n\n";
        Employee* employee = getEmployee(admin, line);
        if (employee == nullptr)
            return;

        count = 0;
        do {
            showEmployeeScreen(line, employee);

            cout << "\n-----  Edit Menu  ------\n";
            cout << "1. Edit Name\n";
            cout << "2. Edit Password\n";
            cout << "3. Edit Salary\n";
            cout << "0. Return to Main Menu\n";
            cout << "\nEnter your choice (0-3): ";
            getline(cin, temp);

            if (Validation::cancelOperation(temp)) return;
            if (temp != "1" && temp != "2" && temp != "3") {
                count++;
                if (Validation::maxTry(count)) return;
                Validation::showError("\nInvalid choice, Try Again.\n");
            }
            else break;
        } while (true);

        // name
        if (temp == "1") {
            string name;
            count = 0;
            do {
                showEmployeeScreen(line, employee);
                cout << "\nEnter new employee's name (or press '0' to cancel): ";
                getline(cin, name);

                if (Validation::cancelOperation(name)) return;

                if (!(Validation::is_valid_name(name))) {
                    count++;
                    if (Validation::maxTry(count)) return;
                    Validation::showError("\nInvalid name, Try Again.\n");
                }
                else {
                    admin->editEmployee(employee->getID(), name, "-1", -1);
                    showEmployeeScreen(line, employee);
                    cout << "\nName updated successfully!\n";
                    system("pause");
                    return;
                }
            } while (true);
        }

        // password
        else if (temp == "2") {

            string password;
            count = 0;
            do {
                showEmployeeScreen(line, employee);
                cout << "\nSet a new password for the employee (or press '0' to cancel): ";
                getline(cin, password);

                if (Validation::cancelOperation(password)) return;

                if (!Validation::is_valid_password(password)) {
                    count++;
                    if (Validation::maxTry(count)) return;
                    Validation::showError("\nInvalid password, Try Again.\n");
                }
                else {
                    admin->editEmployee(employee->getID(), "-1", password, -1);
                    showEmployeeScreen(line, employee);
                    cout << "\nPassword updated successfully!\n";
                    system("pause");
                    return;
                }
            } while (true);
        }

        // salary
        else if (temp == "3") {

            double salary;
            count = 0;
            do {
                showEmployeeScreen(line, employee);
                cout << "\nEnter new salary for employee (or press '0' to cancel): ";
                getline(cin, temp);

                if (Validation::cancelOperation(temp)) return;
                if (!Validation::tryParseNumber(temp, salary)) {
                    Validation::showError("\nInvalid input. Please enter a valid number.\n");
                    count++;
                    continue;
                }
                if (!Validation::is_min_salary(salary)) {
                    count++;
                    Validation::showError("\nInvalid salary, The minimum is 5000. Try Again.\n");
                }
                else {
                    admin->editEmployee(employee->getID(), "-1", "-1", salary);
                    showEmployeeScreen(line, employee);
                    cout << "\nSalary updated successfully!\n";
                    system("pause");
                    return;
                }
            } while (true);
        }
    }
    static void listAllEmployees(Admin* admin) {
        system("cls");
        cout << "\n========  List All Employees  ========\n\n";
        system("cls");
        admin->listEmployees();
        system("pause");
    }
    static void displayMyInformation(Admin* admin) {
        system("cls");
        cout << "\n======== Display My Info ========\n\n";
        admin->displayEmployeeInfo();
        cout << endl;
        system("pause");
    }
    static void updateMyPassword(Admin* admin) {
        string newPassword, oldPassword;
        system("cls");
        cout << "\n======== Update My Password ========\n\n";

        cout << "Enter your current password (or 0 to cancel): ";
        getline(cin, oldPassword);
        if (Validation::cancelOperation(oldPassword))
            return;
        if ((admin->getPassword() != oldPassword) && newPassword != oldPassword) {
            Validation::showError("\nInvalid password!\nReturning to main menu...\n");
            return;
        }

        system("cls");
        cout << "\n======== Update My Password ========\n\n";
        cout << "Enter The New Password: ";
        getline(cin, newPassword);
        if (!Validation::is_valid_password(newPassword) && newPassword != oldPassword) {
            Validation::showError("Invalid password!\nReturning to main menu...\n");
            return;
        }

        admin->setPassword(newPassword);
        cout << "\nPassword updated successfully!\n";
        cout << endl;
        system("pause");
    }

public:
    static Admin* login(int id, string password) {
        auto i = Admin::admins.find(id);
        if (i == Admin::admins.end() || i->second->getPassword() != password) {
            Validation::showError("Wrong ID or password.\nReturning to main Login menu...\n");
            return nullptr;
        }
        return i->second;
    }
    static bool employeeOptions(Admin* admin) {
        int i, count = 0;
        string choice;

        while (true) {
            system("cls");
            printAdminMenu();
            getline(cin, choice);
            if (!Validation::tryParseNumber(choice, i)) {
                Validation::showError("Invalid input. Please enter a valid number.\n");
                count++;
            }
            switch (i) {
                case 1: { EmployeeManager::newClient(admin); return true; } break;
                case 2: { EmployeeManager::newCard(admin); return true; } break;
                case 3: { EmployeeManager::openUSDAccount(admin); return true; } break;
                case 4: { EmployeeManager::searchForClient(admin); return true; } break;
                case 5: { EmployeeManager::editClientInfo(admin); return true; } break;
                case 6: { EmployeeManager::listAllClients(admin); return true; } break;
                case 7: { addNewEmployee(admin); return true; } break;
                case 8: { searchForEmployee(admin); return true; } break;
                case 9: { editEmployeeInfo(admin); return true; } break;
                case 10: { listAllEmployees(admin); return true; } break;
                case 11: { displayMyInformation(admin); return true; } break;
                case 12: { updateMyPassword(admin); return true; } break;
                case 0: { return false; } break;
                default: { Validation::showError("Wrong input\n"); count++; if (Validation::maxTry(count)) return false; } break;
            }
        }
    }
};