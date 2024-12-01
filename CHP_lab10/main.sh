#!/bin/bash

display_menu() {
    clear
    echo "============================"
    echo "          MENU              "
    echo "============================"
    echo "1. Show IPv4 and IPv6 Addresses"
    echo "2. Trace Network Route (Traceroute)"
    echo "3. Resolve IP Address of Host"
    echo "4. Encrypt Text"
    echo "5. Decrypt Text"
    echo "6. Compress File"
    echo "7. Decompress File"
    echo "8. Calculate File Hash"
    echo "0. Exit"
    echo "============================"
}

caesar_encrypt() {
    read -p "Enter text to encrypt: " plaintext
    echo "$plaintext" | tr 'A-Za-z' 'N-ZA-Mn-za-m'
}

caesar_decrypt() {
    read -p "Enter text to decrypt: " ciphertext
    echo "$ciphertext" | tr 'A-Za-z' 'N-ZA-Mn-za-m'
}

while true; do
    display_menu
    read -p "Choose an option: " choice

    case $choice in
    1)
        echo "IPv4 Address:"
        ifconfig | grep "inet " | grep -v 127.0.0.1 | awk '{print $2}'
        echo "IPv6 Address:"
        ifconfig | grep "inet6 " | awk '{print $2}'
        read -p "Press Enter to return to the menu..."
        ;;
    2)
        read -p "Enter hostname or IP: " target
        traceroute "$target"
        read -p "Press Enter to return to the menu..."
        ;;
    3)
        read -p "Enter hostname: " hostname
        getent ahosts "$hostname" | awk '{print $1}' | sort -u
        read -p "Press Enter to return to the menu..."
        ;;
    4)
        caesar_encrypt
        read -p "Press Enter to return to the menu..."
        ;;
    5)
        caesar_decrypt
        read -p "Press Enter to return to the menu..."
        ;;
    6)
        read -p "Enter file path to compress: " file
        gzip "$file"
        echo "File compressed to ${file}.gz"
        read -p "Press Enter to return to the menu..."
        ;;
    7)
        read -p "Enter file path to decompress: " file
        gunzip "$file"
        echo "File decompressed to ${file%.gz}"
        read -p "Press Enter to return to the menu..."
        ;;
    8)
        read -p "Enter file path: " file
        echo "SHA256 Hash:"
        shasum -a 256 "$file"
        read -p "Press Enter to return to the menu..."
        ;;
    0)
        echo "Goodbye!"
        break
        ;;
    *)
        echo "Invalid choice, please try again."
        read -p "Press Enter to return to the menu..."
        ;;
    esac
done