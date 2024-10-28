#include <iostream>
#include <cmath>  
using namespace std;

int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);

    while (b != 0) {
        int remainder = a % b;
        a = b;
        b = remainder;
    }
    return a;
}
int main() {

    int a, b;
    cout << "Enter the first number: ";
    cin >> a;
    cout << "Enter the second number: ";
    cin >> b;

    if (a == 0 && b == 0) {
        cout << "GCD is undefined for two zeros." << endl;
    }
    else {
        cout << "The greatest common divisor is: " << gcd(a, b) << endl;
    }
    return 0;
}
