#include "SHA1.h"

/*!
 * \brief Construct a new SHA1::SHA1 object
 * 
 * \param phrase must be any array of bytes (chars)
 * \param phraseLength must be the size of the phrase (the exact amount of bytes you wish to be read off of it)
 */
SHA1::SHA1(const char phrase[], size_t phraseLength)
{
    this->length = phraseLength;
    memcpy(this->ogPhrase, phrase, phraseLength);
    std::cout << ogPhrase << std::endl;
    divAndPad();
    process();
}

void SHA1::divAndPad()
{
    List<unsigned char> phraseList = arrToList(this->ogPhrase, this->length);
    phraseList += (unsigned char)0x80;

    while (phraseList.length() % 64 != 56)
    {
        phraseList += (unsigned char)0x00;
    }

    // then we add the file size descriptor last 64 bits
    unsigned char fileSize[8]; // 8 because 64/8 = 8 (and we're working with whole bytes)
    memset(fileSize, 0, 8);

    size_t lengthSize = (size_t)(this->length);
    int i = 7;
    for (lengthSize; lengthSize > 0; lengthSize = (size_t)(lengthSize / 256))
    {
        fileSize[i] = lengthSize & 0xFF;
        i--;
    }

    List<unsigned char> sizeBytes = arrToList(fileSize, 8);
    std::cout << "size in bytes: " << *reinterpret_cast<List<int> *>(&sizeBytes) << std::endl;

    phraseList += sizeBytes;

    std::cout << "Final size: " << phraseList.length() << std::endl;

    for (size_t i = 0; i < phraseList.length() / 64; i++)
    {
        List<unsigned char> newList;
        for (size_t j = 0; j < 64; j++)
        {
            newList.push_back(phraseList[j + i * 64]);
        }
        this->blocks512.push_back(newList);
    }
}

void SHA1::process()
{
    // initialize digest
    uint digest[5];
    digest[0] = 0x67452301;
    digest[1] = 0xefcdab89;
    digest[2] = 0x98badcfe;
    digest[3] = 0x10325476;
    digest[4] = 0xc3d2e1f0;
}

List<unsigned char> SHA1::arrToList(unsigned char array[], size_t arrSize)
{
    List<unsigned char> newList;
    for (size_t i = 0; i < arrSize; i++)
    {
        newList.push_back(array[i]);
    }
    return newList;
}

unsigned char *ListToArr(List<unsigned char> list)
{
    unsigned char arr[list.length()];
    for (size_t i = 0; i < list.length(); i++)
    {
        arr[i] = list[i];
    }
    return arr;
}
