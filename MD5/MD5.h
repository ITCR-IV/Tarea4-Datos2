#ifndef MD5_H
#define MD5_H
#include <cstring>
#include <iostream>

class MD5
{
public:
    typedef unsigned int size_type; // 32bit

    MD5();
    MD5(const std::string& text);
    void update(const unsigned char *buf, size_type length);
    void update(const char *buf, size_type length);
    MD5& setLen();
    std::string hexdigest() const;
    friend std::ostream& operator<<(std::ostream&, MD5 md5);

private:
    void init_md5();
    typedef unsigned char uint1; //  8bit
    typedef unsigned int uint4;  // 32bit
    enum {blocksize = 64};

    void transform(const uint1 block[blocksize]);
    static void decode(uint4 output[], const uint1 input[], size_type len);
    static void encode(uint1 output[], const uint4 input[], size_type len);

    bool finalized;
    uint1 buffer[blocksize]; // bytes que no entraron en el bloque anterior
    uint4 count[2];   // 64bit contador
    uint4 state[4];   // mensaje dijerido
    uint1 digest[16]; // resultado

    // Funciones aux
    static inline uint4 F(uint4 x, uint4 y, uint4 z);
    static inline uint4 G(uint4 x, uint4 y, uint4 z);
    static inline uint4 H(uint4 x, uint4 y, uint4 z);
    static inline uint4 I(uint4 x, uint4 y, uint4 z);
    static inline uint4 rotate_left(uint4 x, int n);
    static inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
};

std::string md5(const std::string str);


#endif //MD5_H
