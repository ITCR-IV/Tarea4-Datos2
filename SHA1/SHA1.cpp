#include "SHA1.h"

SHA1::SHA1(const char phrase[])
{
    memcpy(this->ogPhrase, phrase, strlen(phrase) + 1);
    std::cout << ogPhrase;
    divAndPad();
}

void SHA1::divAndPad()
{
}
