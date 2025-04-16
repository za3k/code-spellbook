#include <stdio.h>//SHA256;public domain by BradConte+za3k;uint bits: C8 I32 L64
typedef unsigned char C;typedef unsigned int I;typedef unsigned long long L;
L b,l;I f[64],si[8]={0x6a09e667,0xbb67ae85,0x3c6ef372,0xa54ff53a,0x510e527f,0x9\
b05688c,0x1f83d9ab,0x5be0cd19},k[64]={0x428a2f98,0x71374491,0xb5c0fbcf,0xe9b5db\
a5,0x3956c25b,0x59f111f1,0x923f82a4,0xab1c5ed5,0xd807aa98,0x12835b01,0x243185be,
0x550c7dc3,0x72be5d74,0x80deb1fe,0x9bdc06a7,0xc19bf174,0xe49b69c1,0xefbe4786,0x\
0fc19dc6,0x240ca1cc,0x2de92c6f,0x4a7484aa,0x5cb0a9dc,0x76f988da,0x983e5152,0xa8\
31c66d,0xb00327c8,0xbf597fc7,0xc6e00bf3,0xd5a79147,0x06ca6351,0x14292967,0x27b7\
0a85,0x2e1b2138,0x4d2c6dfc,0x53380d13,0x650a7354,0x766a0abb,0x81c2c92e,0x92722c\
85,0xa2bfe8a1,0xa81a664b,0xc24b8b70,0xc76c51a3,0xd192e819,0xd6990624,0xf40e3585,
0x106aa070,0x19a4c116,0x1e376c08,0x2748774c,0x34b0bcb5,0x391c0cb3,0x4ed8aa4a,0x\
5b9cca4f,0x682e6ff3,0x748f82ee,0x78a5636f,0x84c87814,0x8cc70208,0x90befffa,0xa4\
506ceb,0xbef9a3f7,0xc67178f2},s[8];//2,3rd root of 1-64th primes, fractional part
void _(){I i;for(i=0;i<16;++i)s[i]=si[i];b=0;}I R(I a,I b){return a>>b|a<<(32-b);
}I S(I v,I a,I b,I c){return R(v,a)^R(v,b)^(v>>c);}I E(I v,I a,I b,I c){return R(
v,a)^R(v,b)^R(v,c);}void U(C i){I a,B,c,d,e,F,g,h,u,v,j,m[64];f[b/32%16]|=i<<8*(3
-b/8%4);b+=8;if(b%512==0){a=s[0];B=s[1];c=s[2];d=s[3];e=s[4];F=s[5];g=s[6];h=s[7]
;for(j=0;j<16;++j){m[j]=f[j];f[j]=0;}for(;j<64;++j)m[j]=S(m[j-2],17,19,10)+m[j-7]
+S(m[j-15],7,18,3)+m[j-16];for(j=0;j<64;++j){u=h+E(e,6,11,25)+(e&F^~e&g)+k[j]+m[j
];v=E(a,2,13,22)+(a&B^a&c^B&c);h=g;g=F;F=e;e=d+u;d=c;c=B;B=a;a=u+v;}s[0]+=a;s[1]
+=B;s[2]+=c;s[3]+=d;s[4]+=e;s[5]+=F;s[6]+=g;s[7]+=h;}}
void F(C *h){I i;l=b;U(0x80);while(b%512!=448)U(0);for(i=0;i<8;++i)U(l>>8*(7-i));
for(i=0;i<64;++i)h[i]="0123456789abcdef"[(s[i/8]>>(7-i%8)*4)&0xf];}
int main(){I c,i;C h[64];_();while((c=getchar())!=EOF)U(c);F(h);for(i=0;i<64;++i)
putchar(h[i]);}void SHA(C *t,L n,C h[64]){L i;_();for(i=0;i<n;++i)U(t[i]);F(h);}
