#include <iostream>
using namespace std;

void displayResult(int marks[], int n) {
    int total = 0;
    float average;

    for (int i = 0; i < n; i++) {
        total += marks[i];
    }

    average = (float)total / n;

    cout << "\nTotal Marks: " << total << endl;
    cout << "Average Marks: " << average << endl;

    if (average >= 75)
        cout << "Grade: A" << endl;
    else if (average >= 60)
        cout << "Grade: B" << endl;
    else if (average >= 50)
        cout << "Grade: C" << endl;
    else if (average >= 35)
        cout << "Grade: D" << endl;
    else
        cout << "Result: Fail" << endl;
}

int main() {
    int n;
    int marks[10];

    cout << "Enter number of subjects: ";
    cin >> n;

    if (n <= 0 || n > 10) {
        cout << "Invalid number of subjects.";
        return 0;
    }

    cout << "\nEnter marks for " << n << " subjects:\n";

    for (int i = 0; i < n; i++) {
        cout << "Subject " << i + 1 << ": ";
        cin >> marks[i];

        if (marks[i] < 0 || marks[i] > 100) {
            cout << "Invalid marks!";
            return 0;
        }
    }

    cout << "\n--- Student Result ---";
    displayResult(marks, n);

    return 0;
}