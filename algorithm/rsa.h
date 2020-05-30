
//RSA公钥
typedef struct PubKey
{
    long e;
    long n;
}RsaPubKey;

//RSA私钥
typedef struct PriKey
{
    long d;
    long n;
}RsaPriKey;

/*
    功能：采用 RSA 算法加密明文字符串，得到密文
    输入：plaintext 待加密的明文字符串
    输入：pubkey 公钥
    输入&输出：ciphertext 返回的密文
*/
void RsaEncipher(char *plaintext, long length, long *ciphertext, RsaPubKey pubkey);


/*
    功能：采用 RSA 算法解密密文，得到明文字符串
    输入：ciphertext 加密后的密文
    输入：prikey 私钥
    输入&输出：plaintext 返回的明文字符串
*/
void RsaDecipher(long *ciphertext, long length, char *plaintext, RsaPriKey prikey);


/*
    功能：计算a的b次方模n（模幂）的结果
    输入：a 明文分组
    输入：b 公钥的 e 或 私钥的d
    输入：n 公钥的 n 或 私钥的n
    输出：幂模结果
*/
long modexp(long a, long b, long n);

/*
    功能：素数判断
    输入：一个整数
    输出：1表示为素数，0表示不为素数
*/
int isPrime(long number);

/*
    说明：当e和n互素的时候，e mod n有乘法逆元
    功能：用扩展欧几里得算法求e mod n的乘法逆元d，即ed = 1 mod n
    输入：e和n
    输出：1表示有乘法逆元，此时d为求出的乘法逆元
    输出：0表示没有乘法逆元，此时d为e和n的最大公因子
*/
int extendedEuclid(int e, int n, int *d);
