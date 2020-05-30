#ifndef _HEADER_LIST
#define _HEADER_LIST
#include "list.h"
#endif

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

void HiddenInput(char password[20]);
void MakeRandStr(char *target, int length);
int CheckPassword(UserList* head,char name[20],char password[16]);

