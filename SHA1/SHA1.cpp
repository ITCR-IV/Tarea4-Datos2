#include "SHA1.h"

/*!
 * \brief Construct a new SHA1::SHA1 object
 * 
 * \param phrase must be any array of bytes (chars)
 * \param phraseLength must be the size of the phrase (the exact amount of bytes you wish to be read off of it)
 */
SHA1::SHA1(const unsigned char phrase[], size_t phraseLength)
{
    this->length = phraseLength;
    std::cout << phrase << std::endl;
    divAndPad(phrase);
    process();
}

void SHA1::divAndPad(const unsigned char *phrase)
{
    List<unsigned char> phraseList = arrToList(phrase, this->length);
    phraseList += (unsigned char)0x80;

    while (phraseList.length() % 64 != 56)
    {
        phraseList += (unsigned char)0x00;
    }

    // then we add the file size descriptor last 64 bits
    unsigned char fileSize[8]; // 8 because 64/8 = 8 (and we're working with whole bytes)
    memset(fileSize, 0, 8);

    size_t lengthSize = (this->length) * 8;
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
    uint32_t digest[5];
    digest[0] = 0x67452301;
    digest[1] = 0xefcdab89;
    digest[2] = 0x98badcfe;
    digest[3] = 0x10325476;
    digest[4] = 0xc3d2e1f0;

    for (size_t i = 0; i < this->blocks512.length(); i++)
    {
        uint32_t a = digest[0];
        uint32_t b = digest[1];
        uint32_t c = digest[2];
        uint32_t d = digest[3];
        uint32_t e = digest[4];
        uint32_t words[80];
        for (size_t round = 0; round < 80; round++)
        {
            std::cout << std::dec << "\nRound [" << round << "]:\n";
            if (round < 16)
            {
                words[round] = generateWord(blocks512[i], round % 16);
            }
            else
            {
                words[round] = leftrotate(words[round - 3] ^ words[round - 8] ^ words[round - 14] ^ words[round - 16], 1);
            }
            std::cout << "Current word: " << std::hex << words[round] << std::endl;

            uint32_t f;
            uint32_t k;
            if (round < 20)
            {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            }
            else if (round < 40)
            {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            }
            else if (round < 60)
            {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            }
            else if (round < 80)
            {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = (leftrotate(a, 5)) + f + e + k + words[round];
            e = d;
            d = c;
            c = leftrotate(b, 30);
            b = a;
            a = temp;
            // if (round < 6)
            // {
            std::cout << "A: " << std::hex << a << std::endl;
            std::cout << "B: " << std::hex << b << std::endl;
            std::cout << "C: " << std::hex << c << std::endl;
            std::cout << "D: " << std::hex << d << std::endl;
            std::cout << "E: " << std::hex << e << std::endl;
            // }
        }
        digest[0] += a;
        digest[1] += b;
        digest[2] += c;
        digest[3] += d;
        digest[4] += e;
    }

    for (size_t i = 0; i < 5; i++)
    {
        memcpy(result + i * 4 + 3, reinterpret_cast<unsigned char *>(&digest[i]) + 0, 1);
        memcpy(result + i * 4 + 2, reinterpret_cast<unsigned char *>(&digest[i]) + 1, 1);
        memcpy(result + i * 4 + 1, reinterpret_cast<unsigned char *>(&digest[i]) + 2, 1);
        memcpy(result + i * 4 + 0, reinterpret_cast<unsigned char *>(&digest[i]) + 3, 1);
    }
}

List<unsigned char> SHA1::arrToList(const unsigned char array[], size_t arrSize)
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

uint32_t SHA1::generateWord(List<unsigned char> block64byte, int index)
{
    List<unsigned char> newList;
    for (size_t i = 0; i < 4; i++)
    {
        newList.push_back(block64byte[i + index * 4]);
    }
    uint32_t value = 0;

    value |= newList[0] << 24;
    value |= newList[1] << 16;
    value |= newList[2] << 8;
    value |= newList[3];
    return value;
}

uint32_t SHA1::leftrotate(const uint32_t value, const size_t bits)
{
    return (value << bits) | (value >> (32 - bits));
}

void SHA1::printResultHex()
{
    std::cout << "hex hash: ";
    for (size_t i = 0; i < 20; i++)
    {
        std::cout << std::hex << (int)(this->result[i]);
    }
    std::cout << std::endl;
}