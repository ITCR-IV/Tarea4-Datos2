#ifndef SHA1_H
#define SHA1_H

#include <iostream>
#include <cstring>
#include "List.h"

class SHA1
{
public:
    SHA1(const char phrase[], size_t phraseLength);
    char *getResult();

private:
    unsigned char result[160];
    unsigned char *ogPhrase;
    size_t length;
    List<List<unsigned char>> blocks512;

    void divAndPad();
    void process();

    List<unsigned char> arrToList(unsigned char array[], size_t arrSize);
    unsigned char* ListToArr(List<unsigned char> list);
};

#endif