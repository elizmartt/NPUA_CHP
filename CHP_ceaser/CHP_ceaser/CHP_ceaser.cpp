#include <iostream>
#include <string>

using namespace std;

int main()
{
    string OriginalString;
    int key;
    int answer;
    cout << "Enter the Original text: ";
    getline(cin, OriginalString);
    cout << "Do you want to encrypt(1) or decrypt(2) this text?:";
    cin >> answer;

    cout << "Enter the key for Caesar's algorithm: ";
    cin >> key;

    string Enalphabet = "abcdefghijklmnopqrstuvwxyz";
    string EnalphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    switch (answer) {
    case 1:
        for (int i = 0; i < OriginalString.length(); i++) {

            if (islower(OriginalString[i])) {
                int index = Enalphabet.find(OriginalString[i]);
                int newIndex = (index + key) % 26;
                OriginalString[i] = Enalphabet[newIndex];
            }

            else if (isupper(OriginalString[i])) {
                int index = EnalphabetUpper.find(OriginalString[i]);
                int newIndex = (index + key) % 26;
                OriginalString[i] = EnalphabetUpper[newIndex];
            }
        }

        cout << "Encrypted text: " << OriginalString << endl;
        break;
    case 2:
        for (int i = 0; i < OriginalString.length(); i++) {

            if (islower(OriginalString[i])) {
                int index = Enalphabet.find(OriginalString[i]);
                int newIndex = (index - key + 26) % 26;
                OriginalString[i] = Enalphabet[newIndex];
            }

            else if (isupper(OriginalString[i])) {
                int index = Enalphabet.find(OriginalString[i]);
                int newIndex = (index - key + 26) % 26;
                OriginalString[i] = EnalphabetUpper[newIndex];
            }




        }
        cout << "Decrypted text: " << OriginalString << endl;
        break;
    }
    return 0;
}
