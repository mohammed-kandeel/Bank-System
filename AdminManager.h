#pragma once
#include"EmployeeManager.h"

class AdminManager{

	static void printAdminMenu() {
		system("cls");
		cout << "=====   Admin Menu   =====\n\n";
		cout << " 1. Add New Client\n";
		cout << " 2. Issuing New Card for Client\n";
		cout << " 3. Open USD Account for Client\n";
		cout << " 4. Search for Client\n";
		cout << " 5. List All Clients\n";
		cout << " 6. Edit Client Information\n";

		cout << " 7. Add New Employee\n";
		cout << " 8. Search for Employee\n";
		cout << " 9. Edit Employee Information\n";
		cout << "10. List All Employees\n";

		cout << "11. Display My Information\n";
		cout << "12. Update My Password\n";
		cout << " 0. Return to Login Menu\n";
		cout << "\nEnter your choice (0-12): ";
	}
<<<<<<< HEAD
	//static void addNewEmployee(Admin* admin) {

	//	int id, count = 0;
	//	string name, password, line, temp;
	//	double salary;

	//	line = "\n========  New Employee  ========\n\n";

	//	id = 1 + FilesHelper::getLastId("LastEmployeeId.txt");
	//	line += "ID: " + to_string(id);

	//	//get name
	//	name = EmployeeManager::getName(line, "Employee");
	//	if (name == "") return;
	//	line += "\nName: " + name;

	//	//get password
	//	password = EmployeeManager::getPassword(line,"Employee");
	//	if (password == "") return;
	//	line += "\nPassword: " + password;

	//	//get EGP balance
	//	EGPbalance = EmployeeManager::getBalance(line, "EGP");
	//	if (EGPbalance == -1.0)
	//		return;
	//	line += "\nEgyptian account:\n   ->EGP Balance = " + to_string(EGPbalance) + " EGP\n";

	//	//get USD balance
	//	system("cls");
	//	cout << line << endl;
	//	hasUSD = EmployeeManager::askForUSD();
	//	if (hasUSD) {
	//		USDbalance = EmployeeManager::getBalance(line, "USD");
	//		if (USDbalance == -1.0)
	//			hasUSD = false;
	//		else
	//			line += "Dollar account:\n   ->USD Balance: " + to_string(USDbalance) + " USD\n";
	//	}
	//}



=======
>>>>>>> fd18b56e38e82a3dcc7224a31ace6eb5d37b15ef


};


class EmployeeManager {
public:
    static void newEmployee(Employee* admin);
    static void searchForEmployee(Employee* admin);
    static void listAllEmployees(Employee* admin);
    static void editEmployeeInfo(Employee* admin);

private:

    // ========= Add New Employee =========
    static void newEmployee(Employee* admin) {
        system("cls");
        cout << "\n========  Add New Employee  ========\n\n";

        string name, password;
        double salary;

        cout << "Enter employee name: ";
        getline(cin, name);

        cout << "Enter employee password: ";
        getline(cin, password);

        cout << "Enter employee salary: ";
        cin >> salary;
        cin.ignore();

        // validationة
        if (!Validation::is_valid_name(name) || !Validation::is_valid_password(password) || salary < 3000) {
            cout << "\nInvalid employee details, please try again!\n";
            system("pause");
            return;
        }

        // إضافة موظف
        admin->addEmployee(name, password, salary);
        cout << "\nEmployee added successfully!\n";
        system("pause");
    }

    // ========= Search For Employee =========
    static void searchForEmployee(Employee* admin) {
        string line = "\n========  Search For Employee  ========\n\n";
        EmployeeInfo* employeeInfo = getEmployee(admin, line);
        if (employeeInfo == nullptr) return;
        system("cls");
        line += "Employee found\n";
        showEmployeeScreen(line, employeeInfo);
        system("pause");
    }

    // ========= List All Employees =========
    static void listAllEmployees(Employee* admin) {
        system("cls");
        cout << "\n========  List All Employees  ========\n\n";
        cout << "Do you want to display the employee details with history? (y/n): ";
        char choice;
        cin >> choice;
        cin.ignore();
        system("cls");
        if (tolower(choice) == 'y') {
            admin->listEmployeesWithDetails();
            system("pause");
        }
        else {
            admin->listEmployees();
            system("pause");
        }
    }

    // ========= Edit Employee Info =========
    static void editEmployeeInfo(Employee* admin) {
        int count;
        string line, temp;

        system("cls");
        line = "\n========  Edit Employee Info  ========\n\n";
        EmployeeInfo* employeeInfo = getEmployee(admin, line);
        if (employeeInfo == nullptr)
            return;

        count = 0;
        do {
            showEmployeeScreen(line, employeeInfo);

            cout << "\n-----  Edit Menu  ------\n";
            cout << "1. Edit Name\n";
            cout << "2. Edit Password\n";
            cout << "3. Edit Salary\n";
            cout << "0. Return to Main Menu\n";
            cout << "\nEnter your choice (0-3): ";
            getline(cin, temp);

            if (cancelOperation(temp)) return;
            if (temp != "1" && temp != "2" && temp != "3") {
                count++;
                if (maxTry(count)) return;
                showError("\nInvalid choice, Try Again.\n");
            }
            else break;
        } while (true);

        // name
        if (temp == "1") {
            string name;
            count = 0;
            do {
                showEmployeeScreen(line, employeeInfo);
                cout << "\nEnter new employee's name (or press '0' to cancel): ";
                getline(cin, name);

                if (cancelOperation(name)) return;

                if (!(Validation::is_valid_name(name))) {
                    count++;
                    if (maxTry(count)) return;
                    showError("\nInvalid name, Try Again.\n");
                }
                else {
                    admin->editEmployee(employeeInfo->getID(), name, "-1", -1);
                    showEmployeeScreen(line, employeeInfo);
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
                showEmployeeScreen(line, employeeInfo);
                cout << "\nSet a new password for the employee (or press '0' to cancel): ";
                getline(cin, password);

                if (cancelOperation(password)) return;

                if (!Validation::is_valid_password(password)) {
                    count++;
                    if (maxTry(count)) return;
                    showError("\nInvalid password, Try Again.\n");
                }
                else {
                    admin->editEmployee(employeeInfo->getID(), "-1", password, -1);
                    showEmployeeScreen(line, employeeInfo);
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
                showEmployeeScreen(line, employeeInfo);
                cout << "\nEnter new salary for employee (or press '0' to cancel): ";
                getline(cin, temp);

                if (cancelOperation(temp)) return;
                if (!tryParseNumber(temp, salary)) {
                    showError("\nInvalid input. Please enter a valid number.\n");
                    count++;
                    continue;
                }
                if (salary < 3000) {
                    count++;
                    showError("\nInvalid salary, The minimum is 3000. Try Again.\n");
                }
                else {
                    admin->editEmployee(employeeInfo->getID(), "-1", "-1", salary);
                    showEmployeeScreen(line, employeeInfo);
                    cout << "\nSalary updated successfully!\n";
                    system("pause");
                    return;
                }
            } while (true);
        }
    }

};

#endif
