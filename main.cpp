#include <iostream>
#include "SHA1/SHA1.h"

int main()
{
    char *phrase = "khfghkfdghsdfhgfdghfsdkhfghkfdghsdfhgfdghfsdgjksdgsdglsdfhglsdfhgldfhgklsdfhglskhfghkfdghsdfhgfdghfsdgjksdgsdglsdfhglsdfhgldfhgklsdfhglskhfghkfdghsdfhgfdghfsdgjksdgsdglsdfhglsdfhgldfhgklsdfhglskhfghkfdghsdfhgfdghfsdgjksdgsdglsdfhglsdfhgldfhgklsdfhglsgjksdgsdglsdfhglsdfhgldfhgklsdfhgls";
    std::cout << strlen(phrase) << std::endl;
    SHA1(phrase, strlen(phrase));

    return 0;
}