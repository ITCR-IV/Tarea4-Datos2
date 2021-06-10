#include <iostream>
#include "SHA1/SHA1.h"
#include "MD5/MD5.h"

int main()
{
    SHA1("123456789 10 11 12\n");

    std::string word;
    std::cout << "Ingrese la palabra por encriptar (MD5): ";
    std::cin>> word;
    std::cout << word << ": "<< md5(word) << std::endl;

    return 0;
}