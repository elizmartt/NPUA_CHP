#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>

std::string encodeRLE(const std::string& input) {
    std::string encoded = "";
    int n = input.size();

    for (int i = 0; i < n; ++i) {
        int count = 1;
        while (i < n - 1 && input[i] == input[i + 1]) {
            ++i;
            ++count;
        }

        encoded += input[i];
        encoded += static_cast<char>(count);
    }

    return encoded;
}

std::string decodeRLE(const std::string& encoded) {
    std::string decoded = "";

    for (size_t i = 0; i < encoded.length(); i += 2) {
        char value = encoded[i];
        int count = static_cast<unsigned char>(encoded[i + 1]);

        for (int j = 0; j < count; ++j) {
            decoded += value;
        }
    }

    return decoded;
}

void displayMenu() {
    std::cout << "Choose an option:\n";
    std::cout << "1. Encrypt\n";
    std::cout << "2. Decrypt\n";
    std::cout << "3. Exit\n";
}

int main() {
    int choice;
    std::string input;
    std::string encodedString;
    std::string decodedData;

    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::cout << "Input string: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, input);

            encodedString = encodeRLE(input);
            std::cout << "Encoded RLE: " << encodedString << std::endl;
            break;
        }
        case 2: {
            std::cout << "Input encoded RLE string: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::getline(std::cin, encodedString);

            decodedData = decodeRLE(encodedString);
            std::cout << "Decoded RLE: " << decodedData << std::endl;
            break;
        }
        case 3:
            std::cout << "Exiting the program." << std::endl;
            break;
        default:
            std::cout << "Invalid choice" << std::endl;
            break;
        }
    } while (choice != 3);

    return 0;
}