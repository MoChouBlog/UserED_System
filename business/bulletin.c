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
    bulletin bulletinnode;//公告结点
    strcpy(bulletinnode.sendname,name);//将发送者写入node中
    usernode=UserPubKey(User_head,name);//获取接收者的公钥
    RsaPriKey Pri;
    long x;
    printf("请输入你的私钥:");
    IsNumber(&x,1);
    Pri.d=x;
    Pri.n=usernode.n;
    printf("请输入你要发的信息:");
    scanf("%s",text);
    fflush(stdin);
    while(strlen(text)>99)
    {
        printf("文字请控制在100个字以内!:");
        scanf("%s",text);
        fflush(stdin);
    }
    strcpy(bulletinnode.bulletintext,text);//将明文写入node中

    time_t timep;
    time (&timep);

    sprintf(text_len_time,"%s%d%ld",text,strlen(text),timep);
    md5(text_len_time,strlen(text_len_time),text_md5);
    RsaEncipher(text_md5, 16, rsa_idkey, Pri);
    memccpy(bulletinnode.idkey,rsa_idkey, 16);//将加密后的md5写入node中
    bulletinnode.timep=timep;//将时间写入node中
    BulletinListInsertTail(Bulletin_head,bulletinnode);
    printf("消息发送成功!\n");
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
    struct tm *p_time;//时间
    while(p)
    {
        if(x==i)
        {
            p_time=gmtime(&p->data.timep);
            printf("\n发送者:%-7s 内容:%s\n",p->data.sendname,p->data.bulletintext);
            printf("发送时间:%-4d-%-2d-%-2d %-2d:%-2d:%-2d\n\n",1900+p_time->tm_year,1+p_time->tm_mon,p_time->tm_mday,8+p_time->tm_hour,p_time->tm_min,p_time->tm_sec);
            usernode=UserPubKey(User_head,p->data.sendname);
            Pub.e=usernode.e;
            Pub.n=usernode.n;
            sprintf(text_len_time,"%s%d%ld",p->data.bulletintext,strlen(p->data.bulletintext),p->data.timep);
            md5(text_len_time,strlen(text_len_time),text_md5);
            RsaDecipher(p->data.idkey, 16, rsa_idkey, Pub);
            if(!memcmp(rsa_idkey,text_md5,16))
                printf("消息正确!\n");
            else
                printf("消息不正确!\n");
        }
        x++;
        p = p->next;
    }
}

void doViewBulletin(UserList* User_head,BulletinList* Bulletin_head)
{
    int i=1;
    int sum=0;
    struct tm *p_time;//时间
    BulletinList* p = Bulletin_head->next;
    printf("****************************************\n");
    while(p)
    {
        p_time=gmtime(&p->data.timep);
        printf(" %-2d|发送者:%-7s 内容:%s\n",i,p->data.sendname,p->data.bulletintext);
        printf("发送时间:%-4d-%-2d-%-2d %-2d:%-2d:%-2d\n",1900+p_time->tm_year,1+p_time->tm_mon,p_time->tm_mday,8+p_time->tm_hour,p_time->tm_min,p_time->tm_sec);
        i++;
        sum++;
        p = p->next;
    }
    if(!sum)
        printf("暂无公告。\n");
    printf("****************************************\n");
    if(!sum)
    {
        return ;
    }
    int checkid;
    while(1)
    {
        printf("请输入需要验证的序号(0退出):");
        IsNumber(&checkid,1);
        if(checkid>=i)
        {
            printf("此消息不存在!\n");
            continue;
        }
        else if(checkid)
            CheckBulletin(User_head,Bulletin_head,checkid);
        else
            return;
    }
}


