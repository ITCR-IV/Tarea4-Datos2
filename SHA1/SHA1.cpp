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
}

void SHA1::divAndPad()
{
    List<List<unsigned char>> incompleteBlocks448;

    // since we're dealing with bytes: 56 = 448/8
    for (int i = 0; i < (int)(this->length / 56); i++)
    {
        unsigned char block[56];
        memcpy(block, ogPhrase + i * 56, 56);
        incompleteBlocks448.push_back(arrToList(block, 56));
    }
    //after for is done the last incomplete block remains
    int remainingBytesAmount = this->length % 56;
    if (remainingBytesAmount > 0)
    {
        unsigned char lastBlock[56];
        memcpy(lastBlock, ogPhrase + this->length - remainingBytesAmount, remainingBytesAmount); // add the remaining bytes to lastBlock (excluding \0)

        *(lastBlock + remainingBytesAmount) = 0b10000000; // Add the first 1 and 7 0s
        for (size_t i = 1; i < 56 - remainingBytesAmount; i++)
        {
            *(lastBlock + remainingBytesAmount + i) = 0; // Add the remaining 0s
        }

        incompleteBlocks448.push_back(arrToList(lastBlock, 56));
    }

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

    for (size_t i = 0; i < incompleteBlocks448.length(); i++)
    {
        this->blocks512.push_back(incompleteBlocks448[i] + sizeBytes);
    }

    std::cout << "512 blocks: " << blocks512 << std::endl;
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
