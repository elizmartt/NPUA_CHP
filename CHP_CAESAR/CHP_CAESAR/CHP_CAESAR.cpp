#include <iostream>
#include <string>

using namespace std;

class CaesarCipher {
private:
    int key;

public:
    CaesarCipher(int k) : key(k % 256) {} // Use modulo 256 for extended ASCII range

    string encrypt(const string& text) {
        string encryptedText = text;
        for (int i = 0; i < encryptedText.length(); i++) {
            encryptedText[i] = (encryptedText[i] + key) % 256; // Shift with wrap-around in extended ASCII range
        }
        return encryptedText;
    }

    string decrypt(const string& text) {
        string decryptedText = text;
        for (int i = 0; i < decryptedText.length(); i++) {
            decryptedText[i] = (decryptedText[i] - key + 256) % 256; // Shift back with wrap-around
        }
        return decryptedText;
    }
};

int main() {
    string OriginalString;
    int key, choice;

    cout << "Enter the Original text: ";
    getline(cin, OriginalString);

    cout << "Do you want to encrypt(1) or decrypt(2) this text?: ";
    cin >> choice;

    cout << "Enter the key for Caesar's algorithm: ";
    cin >> key;

    CaesarCipher cipher(key);

    if (choice == 1) {
        cout << "Encrypted text: " << cipher.encrypt(OriginalString) << endl;
    }
    else if (choice == 2) {
        cout << "Decrypted text: " << cipher.decrypt(OriginalString) << endl;
    }
    else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
