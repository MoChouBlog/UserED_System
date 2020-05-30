#include "common.h"
#include <stdio.h>
#include <stdlib.h>

/*隐藏用户输入*/
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

// 产生指定长度的随机字符串（英文字母、数字）
// 注意，target应当申请比参数length多一位的空间
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

//检查密码是否正确
/*使用int memcmp(const void* ,const void* ,size_t)函数*/
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


//检查输入是否是数字
void IsNumber(long* x,int i)
{
    while(1)
    {
        if(scanf("%ld",x)!=1)
        {
            fflush(stdin);
            printf("你输入的不是数字!请重新输入:");
        }
        else
        {
            if(i==1)
            fflush(stdin);
            break;
        }

    }
}

