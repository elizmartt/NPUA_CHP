#include <iostream>
#include <string>
#include <vector>

class TextCipher {
public:
    TextCipher(const std::string& text, int rows)
        : text(text), n(rows) {
        m = (text.size() + n - 1) / n;  
        array.resize(m, std::vector<char>(n, ' ')); 
    }

    void encrypt() {
        fillMatrixForEncryption();
        printMatrix();
        std::cout << "Encrypted text: " << getEncryptedText() << std::endl;
    }

    void decrypt() {
        fillMatrixForDecryption();
        printMatrix();
        std::cout << "Decrypted text: " << getDecryptedText() << std::endl;
    }

private:
    std::string text;
    int n; 
    int m; 
    std::vector<std::vector<char>> array;

    void fillMatrixForEncryption() {
        int k = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (k < text.length()) {
                    array[i][j] = text[k++];
                } else {
                    array[i][j] = ' ';
                }
            }
        }
    }

    void fillMatrixForDecryption() {
        int k = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (k < text.length()) {
                    array[j][i] = text[k++];
                }
            }
        }
    }

    void printMatrix() const {
        std::cout << "Matrix form:\n";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << array[i][j];
            }
            std::cout << std::endl;
        }
    }

    std::string getEncryptedText() const {
        std::string encrypted;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                encrypted += array[j][i];
            }
        }
        return encrypted;
    }

    std::string getDecryptedText() const {
        std::string decrypted;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (array[i][j] != ' ') {
                    decrypted += array[i][j];
                }
            }
        }
        return decrypted;
    }
};

int main() {
    std::string text;
    int n;
    int choice;

    std::cout << "Enter the text: ";
    std::getline(std::cin, text);

    std::cout << "What do you want to do? (1) Encrypt or (2) Decrypt: ";
    std::cin >> choice;

    std::cout << "Enter the key (number of rows): ";
    std::cin >> n;

    TextCipher cipher(text, n);

    switch (choice) {
    case 1:
        cipher.encrypt();
        break;
    case 2:
        cipher.decrypt();
        break;
    default:
        std::cout << "Invalid option!" << std::endl;
    }

    return 0;
}
