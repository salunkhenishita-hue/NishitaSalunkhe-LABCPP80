#include <iostream>
using namespace std;

int main()
{
    int choice, a, b;

    cout << "===== MENU =====" << endl;
    cout << "1. Addition" << endl;
    cout << "2. Subtraction" << endl;
    cout << "3. Multiplication" << endl;
    cout << "4. Division" << endl;
    cout << "5. Modulo" << endl;

    cout << "Enter your choice: ";
    cin >> choice;

    cout << "Enter two numbers: ";
    cin >> a >> b;

    switch (choice)
    {
        case 1:
            cout << "Addition = " << a + b << endl;
            break;

        case 2:
            cout << "Subtraction = " << a - b << endl;
            break;

        case 3:
            cout << "Multiplication = " << a * b << endl;
            break;

        case 4:
            if (b != 0)
                cout << "Division = " << (float)a / b << endl;
            else
                cout << "Division by zero is not allowed." << endl;
            break;

        case 5:
            if (b != 0)
                cout << "Modulo = " << a % b << endl;
            else
                cout << "Modulo by zero is not allowed." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}