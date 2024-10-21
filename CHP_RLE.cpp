#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>

std::string encodeRLE(const std::vector<int>& input) {
    std::string encoded = "";
    int n = input.size();

    for (int i = 0; i < n; ++i) {
        int count = 1;
        while (i < n - 1 && input[i] == input[i + 1]) {
            ++i;
            ++count;
        }

        encoded += std::to_string(input[i]);
        encoded += 'x';
        encoded += std::to_string(count);
        encoded += " ";
    }

    return encoded;
}

std::vector<int> decodeRLE(const std::string& encoded) {
    std::vector<int> decoded;
    std::stringstream ss(encoded);
    std::string part;

    while (ss >> part) {
        std::size_t xPos = part.find('x');
        int value = std::stoi(part.substr(0, xPos));
        int count = std::stoi(part.substr(xPos + 1));

        for (int i = 0; i < count; ++i) {
            decoded.push_back(value);
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
    std::vector<int> input;
    std::string encodedString;
    std::vector<int> decodedData;

    do {
        displayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            input.clear();
            int value;
            std::cout << "Input integers: ";

            while (std::cin >> value) {
                input.push_back(value);
            }

            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            encodedString = encodeRLE(input);
            std::cout << "Encoded RLE: " << encodedString << std::endl;
            break;
        }
        case 2: {
            std::cout << "Input encoded RLE string: ";
            std::cin.clear();
            std::getline(std::cin >> std::ws, encodedString);

            decodedData = decodeRLE(encodedString);
            std::cout << "Decoded RLE: ";
            for (int val : decodedData) {
                std::cout << val << " ";
            }
            std::cout << std::endl;
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
