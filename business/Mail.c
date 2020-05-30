#include "Mail.h"
#include <stdio.h>
#include <stdlib.h>

void doSendMail(UserList* User_head,MailList* Mail_head,char name[20])
{
    char receivename[20];//������
    char des_plaintext[100] = "";//�ʼ�����
    char des_cipertext[100] = "\0";//����
    char de_des_plaintext[100] = "\0";//�����Ľ��ܵ�����
    int des_plaintext_len ;//���ĳ���
    int des_cipertext_len = 0;//���ĳ���
    int de_des_plaintext_len = 0;//�����Ľ��ܵ����ĳ���
    mail mailnode;//�ʼ�
    user usernode;//�û�
    printf("�����������:");
    scanf("%s",receivename);
    fflush(stdin);
    while(!LookUser(User_head,receivename)||!strcmp(receivename,name))
    {
        if(!strcmp(receivename,name))
        {fflush(stdin);
            printf("������Լ���ô��������Ŷ~,����������:");
        }
        else
            printf("�û���������,�������û�����");
        scanf("%s",receivename);
        fflush(stdin);
    }
    strcpy(mailnode.sendname,name);//������д��node��
    strcpy(mailnode.receivename,receivename);//������д��node��
    printf("�����뷢����Ϣ:\n");
    scanf("%s",des_plaintext);
    fflush(stdin);
    des_plaintext_len=strlen(des_plaintext);
    char key[8]="\0";
    MakeRandStr(key, 8);//���������Կ
    //ִ��DES���ܣ�������Կ����Ϊ64λ�ַ���
    des_cipertext_len = DES_Encrypt(des_plaintext, des_plaintext_len, key,des_cipertext);
    memcpy(mailnode.mailtext,des_cipertext, 100);//�����ܵ�����д��node��
    usernode=UserPubKey(User_head,receivename);//��ȡ�����ߵĹ�Կ
    long rsa_key[100] = {0};//����
    RsaPubKey Pub;
    Pub.e=usernode.e;
    Pub.n=usernode.n;
    //ִ��RSA����
    RsaEncipher(key, 8, rsa_key, Pub);
    memcpy(mailnode.DesKey,rsa_key, 100);//�����ܵ���Կд��node��

    time_t timep;
    time (&timep);
    mailnode.timep=timep;//��ʱ��д��node��


    MailListInsertTail(Mail_head,mailnode);
    printf("�����ʼ��ɹ�!\n");
    SaveMailFile(Mail_head);
    OpenMailFile(Mail_head);
    return ;
}

void doRecvMail(UserList* User_head,MailList* Mail_head,char name[20])
{
    int sum=0;
    char de_des_plaintext[100] = "\0";//�����Ľ��ܵ�����
    user usernode;
    usernode=UserPubKey(User_head,name);//��ȡ�����ߵĹ�Կ
    RsaPriKey Pri;
    long x;
    printf("���������˽Կ:");
    IsNumber(&x,1);
    Pri.d=x;
    Pri.n=usernode.n;
    char de_rsa_key[100] = "\0";//�����Ľ��ܵ�����
    MailList* p = Mail_head->next;
    struct tm *p_time;//ʱ��
    while(p)
    {
        memset(de_des_plaintext, 0x00, sizeof(de_des_plaintext));//�ѽ��ܺ�ĸ�ֵΪ��
        if(!strcmp(p->data.receivename,name))
        {
            p_time=gmtime(&p->data.timep);
            printf("****************************************\n");
            RsaDecipher(p->data.DesKey, 8, de_rsa_key, Pri);
            DES_Decrypt(p->data.mailtext, strlen(p->data.mailtext), de_rsa_key,de_des_plaintext);
            printf("������:%s\n",p->data.sendname);
            printf("����:%s\n",de_des_plaintext);
            printf("ʱ��:%-4d-%-2d-%-2d %-2d:%-2d:%-2d\n",1900+p_time->tm_year,1+p_time->tm_mon,p_time->tm_mday,8+p_time->tm_hour,p_time->tm_min,p_time->tm_sec);
            sum++;
        }
        p = p->next;
    }
    if(!sum)
        printf("������Ϣ��\n");
    printf("\n");
    return ;
}
