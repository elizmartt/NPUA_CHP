#include <iostream>
#include <string>
#include <vector>

int main() {
    std::string text;
    int n;
    int answer;

    std::cout << "Enter the text: ";
    std::getline(std::cin, text);

    std::cout << "What do you want to do? (1) Encrypt or (2) Decrypt: ";
    std::cin >> answer;

    std::cout << "Enter the key (number of rows): ";
    std::cin >> n;

    int m = (text.size() + n - 1) / n;  

    std::vector<std::vector<char>> array(m, std::vector<char>(n, ' '));

    int k = 0;
    switch (answer) {
    case 1:  
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (k < text.length()) {
                    array[i][j] = text[k++];
                }
                else {
                    array[i][j] = ' ';  
                }
            }
        }

        std::cout << "Matrix form:\n";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << array[i][j];
            }
            std::cout << std::endl;
        }

        std::cout << "Encrypted text: ";
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                std::cout << array[j][i];
            }
        }
        std::cout << std::endl;
        break;

    case 2: 
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (k < text.length()) {
                    array[j][i] = text[k++];
                }
            }
        }

        
        std::cout << "Matrix form:\n";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << array[i][j];
            }
            std::cout << std::endl;
        }

        std::cout << "Decrypted text: ";
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (array[i][j] != ' ') {  
                    std::cout << array[i][j];
                }
            }
        }
        std::cout << std::endl;
  
    }

    return 0;
}
