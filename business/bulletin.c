#include "bulletin.h"
#include <stdio.h>
#include <stdlib.h>

void doPublishBulletin(UserList* User_head,BulletinList* Bulletin_head,char name[20])
{
    char text[100];
    char text_md5[16];
    long rsa_idkey[16];
    char text_len_time[112];
    user usernode;
    bulletin bulletinnode;//������
    strcpy(bulletinnode.sendname,name);//��������д��node��
    usernode=UserPubKey(User_head,name);//��ȡ�����ߵĹ�Կ
    RsaPriKey Pri;
    long x;
    printf("���������˽Կ:");
    IsNumber(&x,1);
    Pri.d=x;
    Pri.n=usernode.n;
    printf("��������Ҫ������Ϣ:");
    scanf("%s",text);
    fflush(stdin);
    while(strlen(text)>99)
    {
        printf("�����������100��������!:");
        scanf("%s",text);
        fflush(stdin);
    }
    strcpy(bulletinnode.bulletintext,text);//������д��node��

    time_t timep;
    time (&timep);

    sprintf(text_len_time,"%s%d%ld",text,strlen(text),timep);
    md5(text_len_time,strlen(text_len_time),text_md5);
    RsaEncipher(text_md5, 16, rsa_idkey, Pri);
    memccpy(bulletinnode.idkey,rsa_idkey, 16);//�����ܺ��md5д��node��
    bulletinnode.timep=timep;//��ʱ��д��node��
    BulletinListInsertTail(Bulletin_head,bulletinnode);
    printf("��Ϣ���ͳɹ�!\n");
    SaveBulletinFile(Bulletin_head);
    OpenBulletinFile(Bulletin_head);
}

int CheckBulletin(UserList* User_head,BulletinList* Bulletin_head,int i)
{
    RsaPubKey Pub;
    user usernode;
    char text_md5[16];
    char rsa_idkey[16];
    char text_len_time[112];
    int x=1;
    BulletinList* p = Bulletin_head->next;
    struct tm *p_time;//ʱ��
    while(p)
    {
        if(x==i)
        {
            p_time=gmtime(&p->data.timep);
            printf("\n������:%-7s ����:%s\n",p->data.sendname,p->data.bulletintext);
            printf("����ʱ��:%-4d-%-2d-%-2d %-2d:%-2d:%-2d\n\n",1900+p_time->tm_year,1+p_time->tm_mon,p_time->tm_mday,8+p_time->tm_hour,p_time->tm_min,p_time->tm_sec);
            usernode=UserPubKey(User_head,p->data.sendname);
            Pub.e=usernode.e;
            Pub.n=usernode.n;
            sprintf(text_len_time,"%s%d%ld",p->data.bulletintext,strlen(p->data.bulletintext),p->data.timep);
            md5(text_len_time,strlen(text_len_time),text_md5);
            RsaDecipher(p->data.idkey, 16, rsa_idkey, Pub);
            if(!memcmp(rsa_idkey,text_md5,16))
                printf("��Ϣ��ȷ!\n");
            else
                printf("��Ϣ����ȷ!\n");
        }
        x++;
        p = p->next;
    }
}

void doViewBulletin(UserList* User_head,BulletinList* Bulletin_head)
{
    int i=1;
    int sum=0;
    struct tm *p_time;//ʱ��
    BulletinList* p = Bulletin_head->next;
    printf("****************************************\n");
    while(p)
    {
        p_time=gmtime(&p->data.timep);
        printf(" %-2d|������:%-7s ����:%s\n",i,p->data.sendname,p->data.bulletintext);
        printf("����ʱ��:%-4d-%-2d-%-2d %-2d:%-2d:%-2d\n",1900+p_time->tm_year,1+p_time->tm_mon,p_time->tm_mday,8+p_time->tm_hour,p_time->tm_min,p_time->tm_sec);
        i++;
        sum++;
        p = p->next;
    }
    if(!sum)
        printf("���޹��档\n");
    printf("****************************************\n");
    if(!sum)
    {
        return ;
    }
    int checkid;
    while(1)
    {
        printf("��������Ҫ��֤�����(0�˳�):");
        IsNumber(&checkid,1);
        if(checkid>=i)
        {
            printf("����Ϣ������!\n");
            continue;
        }
        else if(checkid)
            CheckBulletin(User_head,Bulletin_head,checkid);
        else
            return;
    }
}


