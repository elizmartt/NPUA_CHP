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
        encoded += 'x';
        encoded += std::to_string(count);
        encoded += " ";
    }

    return encoded;
}

std::string decodeRLE(const std::string& encoded) {
    std::string decoded = "";
    std::stringstream ss(encoded);
    std::string part;

    while (ss >> part) {
        std::size_t xPos = part.find('x');
        char value = part.substr(0, xPos)[0]; // Get the character
        int count = std::stoi(part.substr(xPos + 1));

        for (int i = 0; i < count; ++i) {
            decoded += value; // Append the character count times
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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline
            std::getline(std::cin, input); 

            encodedString = encodeRLE(input);
            std::cout << "Encoded RLE: " << encodedString << std::endl;
            break;
        }
        case 2: {
            std::cout << "Input encoded RLE string: ";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the newline
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
