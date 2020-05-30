#include "file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//��ȡ�û���Ϣ
int OpenUserFile(UserList* head)
{
    int unt=0;
    user newuser;
    FILE * fp;
    fp=fopen("file/userlist.db","a+");
    if(NULL==fp)
    {
        printf("�û��ļ������ڣ����������������...\n");
        system ("pause");

    }
    while(!feof(fp))
    {
        if(fread(&newuser,sizeof( user),1,fp)==1)
        {
            UserListInsertTail(head,newuser);
            unt++;
        }
    }
    fclose(fp);
    return unt;
}

//�����û�
void SaveUserFile(UserList* head)
{
    FILE*fp;
    fp=fopen("file/userlist.db","w");//���ļ�
    UserList* p = head->next;
    UserList* q = NULL;
    while(p)
    {
        q = p->next;
        fwrite(&p->data,sizeof( user),1,fp);
        free(p);
        p = q;
    }
    head->next=NULL;
    //free(head);// �ͷ�ͷ����ڴ�
    fclose(fp);//�ر��ļ�
    return ;
}

//��ȡ�ʼ�����
int OpenMailFile(MailList* head)
{
    int mnt=0;
    mail newmail;
    FILE * fp;
    fp=fopen("file/maillist.db","a+");
    if(NULL==fp)
    {
        printf("�ʼ��ļ������ڣ����������������...\n");
        system ("pause");

    }
    while(!feof(fp))
    {
        if(fread(&newmail,sizeof( mail),1,fp)==1)
        {
            MailListInsertTail(head,newmail);
            mnt++;
        }
    }
    fclose(fp);
    return mnt;
}

//�����ʼ�
void SaveMailFile(MailList* head)
{
    FILE*fp;
    fp=fopen("file/maillist.db","w");//���ļ�
    MailList* p = head->next;
    MailList* q = NULL;
    while(p)
    {
        q = p->next;
        fwrite(&p->data,sizeof( mail),1,fp);
        free(p);
        p = q;
    }
    head->next=NULL;
    //free(head);// �ͷ�ͷ����ڴ�
    fclose(fp);//�ر��ļ�
    return ;
}

//��ȡ��������
int OpenBulletinFile(BulletinList* head)
{
    int mnt=0;
    bulletin newbulletin;
    FILE * fp;
    fp=fopen("file/bulletinlist.db","a+");
    if(NULL==fp)
    {
        printf("�����ļ������ڣ����������������...\n");
        system ("pause");

    }
    while(!feof(fp))
    {
        if(fread(&newbulletin,sizeof( bulletin),1,fp)==1)
        {
            BulletinListInsertTail(head,newbulletin);
            mnt++;
        }
    }
    fclose(fp);
    return mnt;
}

//���湫��
void SaveBulletinFile(BulletinList* head)
{
    FILE*fp;
    fp=fopen("file/bulletinlist.db","w");//���ļ�
    BulletinList* p = head->next;
    BulletinList* q = NULL;
    while(p)
    {
        q = p->next;
        fwrite(&p->data,sizeof( bulletin),1,fp);
        free(p);
        p = q;
    }
    head->next=NULL;
    //free(head);// �ͷ�ͷ����ڴ�
    fclose(fp);//�ر��ļ�
    return ;
}

/*������������ͷ��ȥ�����ļ���ȡ����Ϣд�뵽��Ӧ��������*/
void initSystem(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head)
{
    OpenUserFile(User_head);
    OpenMailFile(Mail_head);
    OpenBulletinFile(Bulletin_head);
}

/*������������ͷ��ȥ�����������е���Ϣд�뵽��Ӧ���ļ���*/
void uninitSystem(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head)
{
    SaveUserFile(User_head);
    SaveMailFile(Mail_head);
    SaveBulletinFile(Bulletin_head);
}
