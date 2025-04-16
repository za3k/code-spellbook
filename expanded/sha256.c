// The following code is adapted from Brad Conte's public domain code
// The original is available at https://github.com/B-Con/crypto-algorithms
// The specification is at http://csrc.nist.gov/publications/fips/fips180-2/fips180-2withchangenotice.pdf
#include <stdio.h>
typedef unsigned char u8;
typedef unsigned int  u32;
typedef unsigned long long u64;

u32 data[64];

// Fractional parts of square roots of primes
u64 bitlen;
u32 state[8], istate[8] = {
	0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9b05688c,0x1f83d9ab,0x5be0cd19,
};

// Fractional parts of cube roots of primes
u32 k[64] = {
	0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5dba5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,
	0xd807aa98,0x12835b01,0x243185be,0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,
	0xe49b69c1,0xefbe4786,0x0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,
	0x983e5152,0xa831c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,
	0x27b70a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c85,
	0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,0x106aa070,
	0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x5b9cca4f,0x682e6ff3,
	0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4506ceb,0xbef9a3f7,0xc67178f2
};

u32 ROTRIGHT(u32 a,u32 b){return a>>b|a<<(32-b);}
u32 SIG(u32 x,u32 a,u32 b,u32 c){return ROTRIGHT(x,a)^ROTRIGHT(x,b)^(x>>c);}
u32 EP(u32 x,u32 a,u32 b,u32 c){return ROTRIGHT(x,a)^ROTRIGHT(x,b)^ROTRIGHT(x,c);}
void update(u8 c) {
    u32 i;

    // Add one byte
    data[bitlen/32%16] |= c << 8*(3-bitlen/8%4);
    bitlen += 8;

    if (bitlen % 512 == 0) {
        // Calculate SHA update for the message block
        u32 a, b, c, d, e, f, g, h, i, t1, t2, m[64];

        for (i = 0; i < 16; ++i) {
            m[i] = data[i];
            data[i] = 0;
        }
        for ( ; i < 64; ++i) m[i] = SIG(m[i-2],17,19,10) + m[i-7] + SIG(m[i-15],7,18,3) + m[i-16];

        a = state[0];
        b = state[1];
        c = state[2];
        d = state[3];
        e = state[4];
        f = state[5];
        g = state[6];
        h = state[7];

        for (i=0; i<64; ++i) {
            t1 = h+EP(e,6,11,25)+(e&f^~e&g)+k[i]+m[i];
            t2 = EP(a,2,13,22)+(a&b^a&c^b&c);
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }

        state[0] += a;
        state[1] += b;
        state[2] += c;
        state[3] += d;
        state[4] += e;
        state[5] += f;
        state[6] += g;
        state[7] += h;
    }
}

void init() {
    u32 i;

    for (i=0;i<16;++i) state[i]=istate[i];
    bitlen=0;
}

int main() {
    u64 len;
    u32 i, c;

    init();

    // Read from stdin
    while ((c = getchar()) != EOF) update(c);

    // Pad
    len = bitlen;
    update(0x80);
    while (bitlen % 512 != 448) update(0);
    for (i=0; i<8; ++i) update(len >> 8*(7-i));

    // Print the hash
	for (i=0; i<64; ++i) putchar("0123456789abcdef"[(state[i/8] >> (7-i%8)*4) & 0xf]);
}
