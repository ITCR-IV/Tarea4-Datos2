#ifndef SHA1_H
#define SHA1_H

#include <iostream>
#include <cstring>
#include "List.h"

class SHA1
{
public:
    SHA1(const char phrase[]);
    char *getResult();

private:
    char result[160];
    char *ogPhrase;
    List<char *> blocks512;

    void divAndPad();
};

#endif