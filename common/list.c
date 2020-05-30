#include "list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//�����û����
UserList* CreatUserNode(user data)
{
    UserList* node = (UserList*)malloc(sizeof(UserList));
    if(!node)
    {
        printf("����ڴ����ʧ��!\n");
        return NULL;
    }
    memset(node, 0x00, sizeof(UserList)); //node->next = NULL;//ָ����Ϊ��
    node->data = data;
    return node;
}

//β�巨�����û����뵽L��β��
int UserListInsertTail(UserList* L, user data)
{
    UserList* newNode = CreatUserNode(data);//�����½��
    UserList* current = L;
    while(current->next != NULL)
    {
        current = current->next;
    }
    //��β���֮������½��
    current->next = newNode;
    return 1;
}

//�����ʼ����
MailList* CreatMailNode(mail data)
{
    MailList* node = (MailList*)malloc(sizeof(MailList));
    if(!node)
    {
        printf("����ڴ����ʧ��!\n");
        return NULL;
    }
    memset(node, 0x00, sizeof(MailList)); //node->next = NULL;//ָ����Ϊ��
    node->data = data;
    return node;
}

//β�巨�����û����뵽L��β��
int MailListInsertTail(MailList* L, mail data)
{
    MailList* newNode = CreatMailNode(data);//�����½��
    MailList* current = L;
    while(current->next != NULL)
    {
        current = current->next;
    }
    //��β���֮������½��
    current->next = newNode;
    return 1;
}

//����������
BulletinList* CreatBulletinNode(bulletin data)
{
    BulletinList* node = (BulletinList*)malloc(sizeof(BulletinList));
    if(!node)
    {
        printf("����ڴ����ʧ��!\n");
        return NULL;
    }
    memset(node, 0x00, sizeof(BulletinList)); //node->next = NULL;//ָ����Ϊ��
    node->data = data;
    return node;
}

//β�巨����������뵽L��β��
int BulletinListInsertTail(BulletinList* L, bulletin data)
{
    BulletinList* newNode = CreatBulletinNode(data);//�����½��
    BulletinList* current = L;
    while(current->next != NULL)
    {
        current = current->next;
    }
    //��β���֮������½��
    current->next = newNode;
    return 1;
}

//�����û����Ƿ����
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

//�����û����Ƿ��ܹ���½
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
                printf("��ǰ�û�����������%d�����\n",(p->data.time)-timep);
                return 0;
            }

            else
                return 1;

        }

        p = p->next;
    }
    return 0;
}

//��ֹ�û�����½
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

//����û�
int UserListTraverse(UserList* L)
{
    UserList* p = L->next;
    int i=0;
    if(!p)
        printf("����һ���ձ�\n");
    printf("\n");
    printf("************************************\n");
    while(p)
    {
        printf("%-2d | ������%-7s | ��Կe��%-5d | ��Կn��%-5d\n", i+1,p->data.name,p->data.e,p->data.n);
        p = p->next;
        i++;
    }
    printf("************************************\n");
    printf("\n");
    return i;
}

//����ʼ�
int MailListTraverse(MailList* L)
{
    MailList* p = L->next;
    int i=0;
    struct tm *p_time;//ʱ��
    if(!p)
        printf("����һ���ձ�\n");
    printf("\n");
    printf("************************************\n");
    while(p)
    {
        p_time=gmtime(&p->data.timep);
        printf(" %-2d|������:%-7s ������:%-7s ����:����״̬���޷��鿴��\n", i+1,p->data.sendname,p->data.receivename);
        printf("����ʱ��:%-4d-%-2d-%-2d %-2d:%-2d:%-2d\n",1900+p_time->tm_year,1+p_time->tm_mon,p_time->tm_mday,8+p_time->tm_hour,p_time->tm_min,p_time->tm_sec);
        p = p->next;
        i++;
    }
    printf("************************************\n");
    printf("\n");
    return i;
}

//�������
int BulletinListTraverse(BulletinList* L)
{
    BulletinList* p = L->next;
    int i=0;
    struct tm *p_time;//ʱ��
    if(!p)
        printf("����һ���ձ�\n");
    printf("\n");
    printf("************************************\n");
    while(p)
    {
        p_time=gmtime(&p->data.timep);
        printf(" %-2d|������:%-7s ����:%s\n", i+1,p->data.sendname,p->data.bulletintext);
        printf("����ʱ��:%-4d-%-2d-%-2d %-2d:%-2d:%-2d\n",1900+p_time->tm_year,1+p_time->tm_mon,p_time->tm_mday,8+p_time->tm_hour,p_time->tm_min,p_time->tm_sec);
        p = p->next;
        i++;
    }
    printf("************************************\n");
    printf("\n");
    return i;
}

//��ȡ�û��Ĺ�Կ
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

//�����û���ָ��
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

//�����û����
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
