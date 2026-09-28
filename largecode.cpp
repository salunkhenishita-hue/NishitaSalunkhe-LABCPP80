#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];

    int largest = a[0], second = -1;

    for (int i = 1; i < n; i++) {
        if (a[i] > largest) {
            second = largest;
            largest = a[i];
        } 
        else if (a[i] > second && a[i] != largest) {
            second = a[i];
        }
    }

    cout << "Second largest: " << second << endl;
    return 0;
}
