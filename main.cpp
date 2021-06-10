#include <iostream>
#include "SHA1/SHA1.h"
#include "MD5/MD5.h"

int main()
{
    char phrase[] = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";
    const unsigned char *uphrase = reinterpret_cast<const unsigned char *>(phrase);
    // std::cout << strlen(phrase) << std::endl;
    SHA1(uphrase, strlen(phrase)).printResultHex();

    // std::string word;
    // std::cout << "Ingrese la palabra por encriptar (MD5): ";
    // std::cin>> word;
    // std::cout << word << ": "<< md5(word) << std::endl;

    return 0;
}