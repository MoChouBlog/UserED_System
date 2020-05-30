#include "Mail.h"
#include <stdio.h>
#include <stdlib.h>

void doSendMail(UserList* User_head,MailList* Mail_head,char name[20])
{
    char receivename[20];//接收者
    char des_plaintext[100] = "";//邮件内容
    char des_cipertext[100] = "\0";//密文
    char de_des_plaintext[100] = "\0";//由密文解密的明文
    int des_plaintext_len ;//明文长度
    int des_cipertext_len = 0;//密文长度
    int de_des_plaintext_len = 0;//由密文解密的明文长度
    mail mailnode;//邮件
    user usernode;//用户
    printf("请输入接收者:");
    scanf("%s",receivename);
    fflush(stdin);
    while(!LookUser(User_head,receivename)||!strcmp(receivename,name))
    {
        if(!strcmp(receivename,name))
        {fflush(stdin);
            printf("你想给自己发么？不得行哦~,请重新输入:");
        }
        else
            printf("用户名不存在,请输入用户名：");
        scanf("%s",receivename);
        fflush(stdin);
    }
    strcpy(mailnode.sendname,name);//发送者写入node中
    strcpy(mailnode.receivename,receivename);//接收者写入node中
    printf("请输入发送信息:\n");
    scanf("%s",des_plaintext);
    fflush(stdin);
    des_plaintext_len=strlen(des_plaintext);
    char key[8]="\0";
    MakeRandStr(key, 8);//随机产生密钥
    //执行DES加密，加密密钥必须为64位字符串
    des_cipertext_len = DES_Encrypt(des_plaintext, des_plaintext_len, key,des_cipertext);
    memcpy(mailnode.mailtext,des_cipertext, 100);//将加密的密文写入node中
    usernode=UserPubKey(User_head,receivename);//获取接收者的公钥
    long rsa_key[100] = {0};//密文
    RsaPubKey Pub;
    Pub.e=usernode.e;
    Pub.n=usernode.n;
    //执行RSA加密
    RsaEncipher(key, 8, rsa_key, Pub);
    memcpy(mailnode.DesKey,rsa_key, 100);//将加密的密钥写入node中

    time_t timep;
    time (&timep);
    mailnode.timep=timep;//将时间写入node中


    MailListInsertTail(Mail_head,mailnode);
    printf("发送邮件成功!\n");
    SaveMailFile(Mail_head);
    OpenMailFile(Mail_head);
    return ;
}

void doRecvMail(UserList* User_head,MailList* Mail_head,char name[20])
{
    int sum=0;
    char de_des_plaintext[100] = "\0";//由密文解密的明文
    user usernode;
    usernode=UserPubKey(User_head,name);//获取接收者的公钥
    RsaPriKey Pri;
    long x;
    printf("请输入你的私钥:");
    IsNumber(&x,1);
    Pri.d=x;
    Pri.n=usernode.n;
    char de_rsa_key[100] = "\0";//由密文解密的明文
    MailList* p = Mail_head->next;
    struct tm *p_time;//时间
    while(p)
    {
        memset(de_des_plaintext, 0x00, sizeof(de_des_plaintext));//把解密后的赋值为空
        if(!strcmp(p->data.receivename,name))
        {
            p_time=gmtime(&p->data.timep);
            printf("****************************************\n");
            RsaDecipher(p->data.DesKey, 8, de_rsa_key, Pri);
            DES_Decrypt(p->data.mailtext, strlen(p->data.mailtext), de_rsa_key,de_des_plaintext);
            printf("发送者:%s\n",p->data.sendname);
            printf("内容:%s\n",de_des_plaintext);
            printf("时间:%-4d-%-2d-%-2d %-2d:%-2d:%-2d\n",1900+p_time->tm_year,1+p_time->tm_mon,p_time->tm_mday,8+p_time->tm_hour,p_time->tm_min,p_time->tm_sec);
            sum++;
        }
        p = p->next;
    }
    if(!sum)
        printf("暂无消息。\n");
    printf("\n");
    return ;
}
