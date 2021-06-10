#ifndef SHA1_H
#define SHA1_H

#include <iostream>
#include <cstring>
#include <cstdint>
#include "List.h"

class SHA1
{
public:
    SHA1(const unsigned char phrase[], size_t phraseLength);
    char *getResult();
    void printResultHex();

private:
    unsigned char result[160];
    unsigned char *ogPhrase;
    size_t length;
    List<List<unsigned char>> blocks512;

    void divAndPad(const unsigned char *phrase);
    void process();

    List<unsigned char> arrToList(const unsigned char array[], size_t arrSize);
    unsigned char *ListToArr(List<unsigned char> list);

    uint32_t generateWord(List<unsigned char> block512bit, int index);
    uint32_t leftrotate(const uint32_t value, const size_t bits);
};

#endif