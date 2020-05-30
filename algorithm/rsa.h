
//RSA��Կ
typedef struct PubKey
{
    long e;
    long n;
}RsaPubKey;

//RSA˽Կ
typedef struct PriKey
{
    long d;
    long n;
}RsaPriKey;

/*
    ���ܣ����� RSA �㷨���������ַ������õ�����
    ���룺plaintext �����ܵ������ַ���
    ���룺pubkey ��Կ
    ����&�����ciphertext ���ص�����
*/
void RsaEncipher(char *plaintext, long length, long *ciphertext, RsaPubKey pubkey);


/*
    ���ܣ����� RSA �㷨�������ģ��õ������ַ���
    ���룺ciphertext ���ܺ������
    ���룺prikey ˽Կ
    ����&�����plaintext ���ص������ַ���
*/
void RsaDecipher(long *ciphertext, long length, char *plaintext, RsaPriKey prikey);


/*
    ���ܣ�����a��b�η�ģn��ģ�ݣ��Ľ��
    ���룺a ���ķ���
    ���룺b ��Կ�� e �� ˽Կ��d
    ���룺n ��Կ�� n �� ˽Կ��n
    �������ģ���
*/
long modexp(long a, long b, long n);

/*
    ���ܣ������ж�
    ���룺һ������
    �����1��ʾΪ������0��ʾ��Ϊ����
*/
int isPrime(long number);

/*
    ˵������e��n���ص�ʱ��e mod n�г˷���Ԫ
    ���ܣ�����չŷ������㷨��e mod n�ĳ˷���Ԫd����ed = 1 mod n
    ���룺e��n
    �����1��ʾ�г˷���Ԫ����ʱdΪ����ĳ˷���Ԫ
    �����0��ʾû�г˷���Ԫ����ʱdΪe��n���������
*/
int extendedEuclid(int e, int n, int *d);
