#include "common.h"
#include <stdio.h>
#include <stdlib.h>

/*�����û�����*/
void HiddenInput(char password[20])
{
    char p=0;
    int i=0;
    while(p=getch())
    {
        if(p==13)
            break;
        if(p!='\b')
        {
            password[i] = p;
            printf("*");
            i++;
        }
        else
        {
            printf("\b \b");
            i--;
        }
    }
    password[i]='\0';
    printf("\n");
}

// ����ָ�����ȵ�����ַ�����Ӣ����ĸ�����֣�
// ע�⣬targetӦ������Ȳ���length��һλ�Ŀռ�
void MakeRandStr(char *target, int length)
{
    int flag, i;
    srand((unsigned) time(NULL));
    for (i = 0; i < length; i++)
    {
        flag = rand() % 3;
        switch (flag)
        {
        case 0:
            target[i] = 'A' + rand() % 26;
            break;
        case 1:
            target[i] = 'a' + rand() % 26;
            break;
        case 2:
            target[i] = '0' + rand() % 10;
            break;
        default:
            break;
        }
    }
    target[length] = '\0';
}

//��������Ƿ���ȷ
/*ʹ��int memcmp(const void* ,const void* ,size_t)����*/
int CheckPassword(UserList* head,char name[20],char password[16])
{
    UserList* p = head->next;
    while(p)
    {
        if(!strcmp(p->data.name,name))
        {
            if(!memcmp(p->data.password,password,16))
                return 1;
            else
                return 0;
        }
        p = p->next;
    }
    return 0;
}


//��������Ƿ�������
void IsNumber(long* x,int i)
{
    while(1)
    {
        if(scanf("%ld",x)!=1)
        {
            fflush(stdin);
            printf("������Ĳ�������!����������:");
        }
        else
        {
            if(i==1)
            fflush(stdin);
            break;
        }

    }
}

