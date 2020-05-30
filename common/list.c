#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//创建用户结点
UserList* CreatUserNode(user data)
{
    UserList* node = (UserList*)malloc(sizeof(UserList));
    if(!node)
    {
        printf("结点内存分配失败!\n");
        return NULL;
    }
    memset(node, 0x00, sizeof(UserList)); //node->next = NULL;//指针域为空
    node->data = data;
    return node;
}

//尾插法，将用户插入到L的尾部
int UserListInsertTail(UserList* L, user data)
{
    UserList* newNode = CreatUserNode(data);//生成新结点
    UserList* current = L;
    while(current->next != NULL)
    {
        current = current->next;
    }
    //在尾结点之后插入新结点
    current->next = newNode;
    return 1;
}

//创建邮件结点
MailList* CreatMailNode(mail data)
{
    MailList* node = (MailList*)malloc(sizeof(MailList));
    if(!node)
    {
        printf("结点内存分配失败!\n");
        return NULL;
    }
    memset(node, 0x00, sizeof(MailList)); //node->next = NULL;//指针域为空
    node->data = data;
    return node;
}

//尾插法，将用户插入到L的尾部
int MailListInsertTail(MailList* L, mail data)
{
    MailList* newNode = CreatMailNode(data);//生成新结点
    MailList* current = L;
    while(current->next != NULL)
    {
        current = current->next;
    }
    //在尾结点之后插入新结点
    current->next = newNode;
    return 1;
}

//创建公告结点
BulletinList* CreatBulletinNode(bulletin data)
{
    BulletinList* node = (BulletinList*)malloc(sizeof(BulletinList));
    if(!node)
    {
        printf("结点内存分配失败!\n");
        return NULL;
    }
    memset(node, 0x00, sizeof(BulletinList)); //node->next = NULL;//指针域为空
    node->data = data;
    return node;
}

//尾插法，将公告插入到L的尾部
int BulletinListInsertTail(BulletinList* L, bulletin data)
{
    BulletinList* newNode = CreatBulletinNode(data);//生成新结点
    BulletinList* current = L;
    while(current->next != NULL)
    {
        current = current->next;
    }
    //在尾结点之后插入新结点
    current->next = newNode;
    return 1;
}

//查找用户名是否存在
int LookUser(UserList* head,char name[20])
{
    UserList* p = head->next;
    while(p)
    {
        if(!strcmp(p->data.name,name))
        {
            return 1;
        }

        p = p->next;
    }
    return 0;
}

//查找用户名是否能够登陆
int LookUserBan(UserList* head,char name[20])
{
    time_t timep;
    time (&timep);
    UserList* p = head->next;
    while(p)
    {
        if(!strcmp(p->data.name,name))
        {
            if(timep<p->data.time)
            {
                printf("当前用户被锁！请在%d秒后尝试\n",(p->data.time)-timep);
                return 0;
            }

            else
                return 1;

        }

        p = p->next;
    }
    return 0;
}

//禁止用户名登陆
int UserBan(UserList* head,char name[20])
{
    time_t timep;
    time (&timep);
    UserList* p = head->next;
    while(p)
    {
        if(!strcmp(p->data.name,name))
        {
            p->data.time=timep+120;
            return 1;
        }
        p = p->next;
    }
    return 0;
}

//输出用户
int UserListTraverse(UserList* L)
{
    UserList* p = L->next;
    int i=0;
    if(!p)
        printf("这是一个空表！\n");
    printf("\n");
    printf("************************************\n");
    while(p)
    {
        printf("%-2d | 姓名：%-7s | 公钥e：%-5d | 公钥n：%-5d\n", i+1,p->data.name,p->data.e,p->data.n);
        p = p->next;
        i++;
    }
    printf("************************************\n");
    printf("\n");
    return i;
}

//输出邮件
int MailListTraverse(MailList* L)
{
    MailList* p = L->next;
    int i=0;
    struct tm *p_time;//时间
    if(!p)
        printf("这是一个空表！\n");
    printf("\n");
    printf("************************************\n");
    while(p)
    {
        p_time=gmtime(&p->data.timep);
        printf(" %-2d|发送者:%-7s 接收者:%-7s 内容:密文状态，无法查看！\n", i+1,p->data.sendname,p->data.receivename);
        printf("发送时间:%-4d-%-2d-%-2d %-2d:%-2d:%-2d\n",1900+p_time->tm_year,1+p_time->tm_mon,p_time->tm_mday,8+p_time->tm_hour,p_time->tm_min,p_time->tm_sec);
        p = p->next;
        i++;
    }
    printf("************************************\n");
    printf("\n");
    return i;
}

//输出公告
int BulletinListTraverse(BulletinList* L)
{
    BulletinList* p = L->next;
    int i=0;
    struct tm *p_time;//时间
    if(!p)
        printf("这是一个空表！\n");
    printf("\n");
    printf("************************************\n");
    while(p)
    {
        p_time=gmtime(&p->data.timep);
        printf(" %-2d|发送者:%-7s 内容:%s\n", i+1,p->data.sendname,p->data.bulletintext);
        printf("发送时间:%-4d-%-2d-%-2d %-2d:%-2d:%-2d\n",1900+p_time->tm_year,1+p_time->tm_mon,p_time->tm_mday,8+p_time->tm_hour,p_time->tm_min,p_time->tm_sec);
        p = p->next;
        i++;
    }
    printf("************************************\n");
    printf("\n");
    return i;
}

//获取用户的公钥
user UserPubKey(UserList* head,char name[20])
{
    UserList* p = head->next;
    while(p)
    {
        if(!strcmp(p->data.name,name))
        {
            return p->data;
        }
        p = p->next;
    }
    return ;
}

//返回用户的指针
user* P_User(UserList* head,char name[20])
{
    UserList* p = head->next;
    while(p)
    {
        if(!strcmp(p->data.name,name))
        {
            return &p->data;
        }
        p = p->next;
    }
    return ;
}

//查找用户结点
user LookUserInfo(UserList* head,char name[20])
{
    user UserInfo;
    UserList* p = head->next;
    while(p)
    {
        if(!strcmp(p->data.name,name))
        {
            return p->data;
        }

        p = p->next;
    }
    return UserInfo;
}
