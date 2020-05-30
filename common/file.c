#include "file.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//读取用户信息
int OpenUserFile(UserList* head)
{
    int unt=0;
    user newuser;
    FILE * fp;
    fp=fopen("file/userlist.db","a+");
    if(NULL==fp)
    {
        printf("用户文件不存在，按任意进入主界面...\n");
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

//保存用户
void SaveUserFile(UserList* head)
{
    FILE*fp;
    fp=fopen("file/userlist.db","w");//打开文件
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
    //free(head);// 释放头结点内存
    fclose(fp);//关闭文件
    return ;
}

//读取邮件内容
int OpenMailFile(MailList* head)
{
    int mnt=0;
    mail newmail;
    FILE * fp;
    fp=fopen("file/maillist.db","a+");
    if(NULL==fp)
    {
        printf("邮件文件不存在，按任意进入主界面...\n");
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

//保存邮件
void SaveMailFile(MailList* head)
{
    FILE*fp;
    fp=fopen("file/maillist.db","w");//打开文件
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
    //free(head);// 释放头结点内存
    fclose(fp);//关闭文件
    return ;
}

//读取公告内容
int OpenBulletinFile(BulletinList* head)
{
    int mnt=0;
    bulletin newbulletin;
    FILE * fp;
    fp=fopen("file/bulletinlist.db","a+");
    if(NULL==fp)
    {
        printf("公告文件不存在，按任意进入主界面...\n");
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

//保存公告
void SaveBulletinFile(BulletinList* head)
{
    FILE*fp;
    fp=fopen("file/bulletinlist.db","w");//打开文件
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
    //free(head);// 释放头结点内存
    fclose(fp);//关闭文件
    return ;
}

/*传递三个链表头进去，将文件读取的信息写入到对应的链表中*/
void initSystem(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head)
{
    OpenUserFile(User_head);
    OpenMailFile(Mail_head);
    OpenBulletinFile(Bulletin_head);
}

/*传递三个链表头进去，将文链表中的信息写入到对应的文件中*/
void uninitSystem(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head)
{
    SaveUserFile(User_head);
    SaveMailFile(Mail_head);
    SaveBulletinFile(Bulletin_head);
}
