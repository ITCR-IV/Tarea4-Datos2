#include <iostream>
#include "SHA1/SHA1.h"
#include "MD5/MD5.h"

int main()
{
    unsigned char zero = 0;
    const unsigned char *phrase = reinterpret_cast<const unsigned char *>("abc");
    // std::cout << strlen(phrase) << std::endl;
    SHA1(phrase, 3).printResultHex();

    // std::string word;
    // std::cout << "Ingrese la palabra por encriptar (MD5): ";
    // std::cin>> word;
    // std::cout << word << ": "<< md5(word) << std::endl;

    return 0;
}