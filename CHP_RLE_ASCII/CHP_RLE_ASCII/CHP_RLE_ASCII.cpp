#include <iostream>
#include <string>
#include <sstream>

class RLE {
public:
    std::string compress(const std::string& input);
    std::string decompress(const std::string& input);
};

std::string RLE::compress(const std::string& input) {
    std::stringstream result;
    int count = 1;

    for (size_t i = 1; i <= input.size(); ++i) {
        if (i < input.size() && input[i] == input[i - 1]) {
            ++count;
        }
        else {
            result << input[i - 1];
            result << (char)count; // Store count as char
            count = 1;
        }
    }

    return result.str();
}

std::string RLE::decompress(const std::string& input) {
    std::stringstream result;

    for (size_t i = 0; i < input.size(); i += 2) {
        char ch = input[i];
        int count = (char)input[i + 1]; // Convert char to int

        result << std::string(count, ch);
    }

    return result.str();
}

int main() {
    RLE rle;
    std::string input;

    std::cout << "Enter text to compress: ";
    std::getline(std::cin, input);

    std::string compressed = rle.compress(input);
    std::cout << "Compressed text: " << compressed << std::endl;

    std::string decompressed = rle.decompress(compressed);
    std::cout << "Decompressed text: " << decompressed << std::endl;

    if (input == decompressed) {
        std::cout << "Success: Original and decompressed texts match!" << std::endl;
    }
    else {
        std::cout << "Error: Original and decompressed texts do not match!" << std::endl;
    }

    return 0;
}
