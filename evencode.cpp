#include <iostream>
using namespace std;

int main() {
    int number;

    cout << "Enter an integer to check: ";
    cin >> number;

    // If the remainder of dividing by 2 is 0, the number is even
    if (number % 2 == 0) {
        cout << number << " is an even number." << endl;
    } else {
        cout << number << " is an odd number." << endl;
    }

    return 0;
}