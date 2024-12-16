#include <iostream>
#include <string>
#include <map>
#include <cctype>

class SubstitutionCipher {
public:
    SubstitutionCipher(const std::string& key) : key_(key) {
        for (size_t i = 0; i < key_.length(); ++i) {
            char originalChar = 'A' + i;
            decryptionMap_[key_[i]] = originalChar;
        }
    }

    std::string encrypt(const std::string& text) {
        std::string encryptedText;
        for (char ch : text) {
            if (isalpha(ch)) {
                int index = toupper(ch) - 'A';
                char substitutedChar = key_[index];
                encryptedText += islower(ch) ? tolower(substitutedChar) : substitutedChar;
            }
            else {
                encryptedText += ch;
            }
        }
        return encryptedText;
    }

    std::string decrypt(const std::string& text) {
        std::string decryptedText;
        for (char ch : text) {
            if (isalpha(ch)) {
                char originalChar = decryptionMap_[toupper(ch)];
                decryptedText += islower(ch) ? tolower(originalChar) : originalChar;
            }
            else {
                decryptedText += ch;
            }
        }
        return decryptedText;
    }

private:
    std::string key_;
    std::map<char, char> decryptionMap_;
};

int main() {
    const std::string key = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
    SubstitutionCipher cipher(key);

    int choice;
    std::string text;

    do {
        std::cout << "Choose an option:\n";
        std::cout << "1. Encrypt\n";
        std::cout << "2. Decrypt\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();
        switch (choice) {
        case 1:
            std::cout << "Enter text to encrypt: ";
            std::getline(std::cin, text);
            std::cout << "Encrypted Text: " << cipher.encrypt(text) << std::endl;
            break;
        case 2:
            std::cout << "Enter text to decrypt: ";
            std::getline(std::cin, text);
            std::cout << "Decrypted Text: " << cipher.decrypt(text) << std::endl;
            break;
        case 3:
            std::cout << "Exiting the program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
            break;
        }
    } while (choice != 3);

    return 0;
}
