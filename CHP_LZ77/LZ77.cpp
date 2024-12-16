#include <iostream>
#include <string>
#include <vector>
using namespace std;

string lz77_compress(const string& input) {
    string compressed;
    int windowSize = 50; 
    int inputLen = input.length();

    for (int i = 0; i < inputLen;) {
        int matchLength = 0;
        int matchOffset = 0;

        for (int j = max(0, i - windowSize); j < i; ++j) {
            int k = 0;
            while (i + k < inputLen && input[j + k] == input[i + k])
                ++k;

            if (k > matchLength) {
                matchLength = k;
                matchOffset = i - j;
            }
        }

        if (matchLength > 2) {
            compressed += "[" + to_string(matchOffset) + "|" + to_string(matchLength) + "]";
            i += matchLength; 
        }
        else {
            compressed += input[i];
            i++;
        }
    }
    return compressed;
}

string lz77_decompress(const string& compressed) {
    string decompressed;
    int inputLen = compressed.length();

    for (int i = 0; i < inputLen;) {
        if (compressed[i] == '[') {
            int offset = 0, length = 0;
            i++;
            while (compressed[i] != '|') {
                offset = offset * 10 + (compressed[i] - '0');
                i++;
            }
            i++; 
            while (compressed[i] != ']') {
                length = length * 10 + (compressed[i] - '0');
                i++;
            }
            i++; 

            
            int start = decompressed.length() - offset;
            for (int j = 0; j < length; j++) {
                decompressed += decompressed[start + j];
            }
        }
        else {
            decompressed += compressed[i];
            i++;
        }
    }
    return decompressed;
}

int main() {
    string input = "The compression and the decompression the leave an impression an. Hahahahaha!";
    cout << "Original String:\n" << input << "\n\n";

    string compressed = lz77_compress(input);
    cout << "Compressed String:\n" << compressed << "\n\n";

    string decompressed = lz77_decompress(compressed);
    cout << "Decompressed String:\n" << decompressed << "\n";

    return 0;
}
