#include <stddef.h> 
#include <cstring> 
#include <iostream> 
#include <algorithm> 
 
const unsigned int TemplateSize = 256; 
 
// Abstract base class for crypto classes. 
class Crypto { 
public:  
    virtual int Encrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz) = 0; 
    virtual int Decrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz) = 0; 
}; 
 
class Shablon : public Crypto { 
public: 
    Shablon(); 
    virtual ~Shablon(); 
 
    virtual int Encrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz) override; 
    virtual int Decrypt(const unsigned char* pSrc, unsigned int SrcSz, unsigned char* pOut, unsigned int& Outsz) override; 
 
    int SetTemplateTable(const unsigned char* pEncodeArr, const unsigned char* pDecodeArr, size_t size); 
 
private: 
    unsigned char mEncryptTable[2][TemplateSize]; 
    unsigned char mDecryptTable[2][TemplateSize]; 
    size_t mArrSize; 
}; 
 
// Implementation of Shablon class methods 
 
Shablon::Shablon() : mArrSize(0) { 
    std::memset(mEncryptTable, 0, sizeof(mEncryptTable)); 
    std::memset(mDecryptTable, 0, sizeof(mDecryptTable)); 
} 
 
Shablon::~Shablon() {} 
 
int Shablon::Encrypt(const unsigned char* pSource, unsigned int sourceSize, unsigned char* pOut, unsigned int& outSize) { 
    if (!pSource  !pOut  sourceSize == 0 || outSize < sourceSize) { 
        return -1; // Invalid input 
    } 
 
    outSize = sourceSize; // Set output size to the size of input 
    for (unsigned int i = 0; i < sourceSize; ++i) { 
        pOut[i] = mEncryptTable[1][pSource[i]]; 
    } 
    return 0; // Success 
} 
 
int Shablon::Decrypt(const unsigned char* pSource, unsigned int sourceSize, unsigned char* pOut, unsigned int& outSize) { 
    if (!pSource  !pOut  sourceSize == 0 || outSize < sourceSize) { 
        return -1; // Invalid input 
    } 
 
    outSize = sourceSize; // Set output size to the size of input 
    for (unsigned int i = 0; i < sourceSize; ++i) { 
        pOut[i] = mDecryptTable[1][pSource[i]]; 
    } 
    return 0; // Success 
} 
 
int Shablon::SetTemplateTable(const unsigned char* pEncodeArr, const unsigned char* pDecodeArr, size_t size) { 
    if (!pEncodeArr  !pDecodeArr  size == 0 || size > TemplateSize) { 
        return -1; // Invalid input 
    } 
 
    std::memcpy(mEncryptTable[0], pEncodeArr, size); 
    std::memcpy(mEncryptTable[1], pDecodeArr, size); 
 
    // Initialize decryption table 
    for (size_t i = 0; i < size; ++i) { 
        mDecryptTable[0][mEncryptTable[0][i]] = i; 
        mDecryptTable[1][mEncryptTable[1][i]] = i; 
    } 
 
    mArrSize = size; 
    return 0; // Success 
} 
int main() { 
    Shablon shablon; 
 
    unsigned char encodeArr[TemplateSize]; 
    unsigned char decodeArr[TemplateSize]; 
 
    // Initialize encoding and decoding arrays 
    for (unsigned int i = 0; i < TemplateSize; ++i) { 
        encodeArr[i] = (i + 1) % TemplateSize;  // Simple shift encoding 
        decodeArr[i] = (i - 1 + TemplateSize) % TemplateSize; // Simple shift decoding 
    } 
 
    // Set the template tables 
    if (shablon.SetTemplateTable(encodeArr, decodeArr, TemplateSize) != 0) { 
        std::cerr << "Failed to set template tables!" << std::endl; 
        return -1; 
    } 
 
    const char* originalText = "Hello World!"; 
    unsigned int srcSize = strlen(originalText); 
    unsigned char encryptedText[TemplateSize]; 
    unsigned int encSize = sizeof(encryptedText); 
     
    // Encrypt 
    if (shablon.Encrypt(reinterpret_cast<const unsigned char*>(originalText), srcSize, encryptedText, encSize) != 0) { 
        std::cerr << "Encryption failed!" << std::endl; 
        return -1; 
    } 
 
    // Decrypt 
    unsigned char decryptedText[TemplateSize]; 
    unsigned int decSize = sizeof(decryptedText); 
    if (shablon.Decrypt(encryptedText, encSize, decryptedText, decSize) != 0) { 
        std::cerr << "Decryption failed!" << std::endl; 
        return -1; 
    } 
 
    decryptedText[srcSize] = '\0'; //
Null terminate the decrypted string 
    std::cout << "Decrypted text: " << decryptedText << std::endl; 
 std::cout << "Encrypted text: " << encryptedText << std::endl; 
    return 0; 
}
