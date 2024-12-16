#include <iostream>
#include <string>
#include <vector>

using namespace std;

string caesarCipher(string text, int key, bool encrypt) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    string alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < text.length(); i++) {
        if (islower(text[i])) {
            int index = alphabet.find(text[i]);
            int newIndex = encrypt ? (index + key) % 26 : (index - key + 26) % 26;
            text[i] = alphabet[newIndex];
        }
        else if (isupper(text[i])) {
            int index = alphabetUpper.find(text[i]);
            int newIndex = encrypt ? (index + key) % 26 : (index - key + 26) % 26;
            text[i] = alphabetUpper[newIndex];
        }
    }

    return text;
}

string matrixCipher(string text, int n, bool encrypt) {
    int m = (text.size() + n - 1) / n; 
    vector<vector<char>> matrix(m, vector<char>(n, ' '));
    string result;
    int k = 0;

    if (encrypt) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (k < text.length()) {
                    matrix[i][j] = text[k++];
                }
                else {
                    matrix[i][j] = ' ';
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                result += matrix[j][i];
            }
        }
    }
    else {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (k < text.length()) {
                    matrix[j][i] = text[k++];
                }
            }
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] != ' ') {
                    result += matrix[i][j];
                }
            }
        }
    }

    return result;
}

int main() {
    string text;
    int caesarKey, matrixKey;
    int choice;

    cout << "Enter the text: ";
    getline(cin, text);

    cout << "Enter the key for Caesar Cipher: ";
    cin >> caesarKey;

    cout << "Enter the key (number of columns) for Matrix Transposition Cipher: ";
    cin >> matrixKey;

    cout << "Choose an operation: (1) Encrypt or (2) Decrypt: ";
    cin >> choice;

    if (choice == 1) {
        
        string caesarEncrypted = caesarCipher(text, caesarKey, true);
        cout << "After Caesar Cipher Encryption: " << caesarEncrypted << endl;

        string matrixEncrypted = matrixCipher(caesarEncrypted, matrixKey, true);
        cout << "Final Encrypted Text (Matrix): " << matrixEncrypted << endl;
    }
    else if (choice == 2) {
       
        string matrixDecrypted = matrixCipher(text, matrixKey, false);
        cout << "After Matrix Cipher Decryption: " << matrixDecrypted << endl;

        string caesarDecrypted = caesarCipher(matrixDecrypted, caesarKey, false);
        cout << "Final Decrypted Text (Caesar): " << caesarDecrypted << endl;
    }
    else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
