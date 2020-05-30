#include "Authority.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//����RSA�����e,d,n
void RSA(user* node)
{
    long p,q,e,d;//��Կ
    while(1)
    {
        //����RSA��p
        printf("������p:");
        scanf("%ld",&p);
        getchar();
        while(!isPrime(p))
        {
            printf("������������������:");
            scanf("%ld",&p);
            getchar();
        }

        //����RSA��p
        printf("������q:");
        scanf("%ld",&q);
        getchar();
        while(!isPrime(q))
        {
            printf("������������������:");
            scanf("%ld",&q);
            getchar();
        }
        if(p*q < 128)
            printf("p��q ����С��128\n");
        else
            break;
    }

    //��ӡp q
    printf("p:%ld q:%ld\n",p,q);

    //����RSA��Կ��e
    printf("������e(0~%ld):",(p-1)*(q-1));
    scanf("%ld",&e);
    getchar();
    while(!extendedEuclid(e, (p-1)*(q-1), &d))
    {
        printf("e��%ld������,����������:",(p-1)*(q-1));
        scanf("%ld",&e);
        getchar();
    }

    //����Կ˽Կ��Ϣд��
    node->n=p*q;//��Կn
    node->e=e;//��Կe

    //��ӡ��˽Կ��Ϣ
    printf("��Կ{n=%ld ,e=%ld}\n",node->n,node->e);
    printf("˽Կ{d=%ld ,n=%ld}\n",d,node->n);
    printf("���μ����˽Կ:%ld\n",d);
}

//�޸�����
void ModifyPassword(UserList* head,char name[20])
{
    char password_old[20] ="\0";
    char password[20] ="\0";
    int password_len = 0;
    char password_agin[20] ="\0";
    char password_md5[16] ="\0";
    char password_key[29]="\0";
    user UserInfo;
    UserInfo=LookUserInfo(head,name);
    printf("�����������:");
    HiddenInput(password_old);
    sprintf(password_key,"%s%s",password_old,UserInfo.Slat);
    password_len=strlen(password_key);
    md5(password_key,password_len,password_md5);
    while(!CheckPassword(head,name,password_md5))
    {
        printf("��������֤����!����������:");
        HiddenInput(password_old);
        sprintf(password_key,"%s%s",password_old,UserInfo.Slat);
        password_len=strlen(password_key);
        md5(password_key,password_len,password_md5);
    }
    printf("������������:");
    HiddenInput(password);
    printf("���ٴ�����������:");
    HiddenInput(password_agin);
    while(strcmp(password,password_agin))
    {
        printf("�������벻һ��������������:");
        HiddenInput(password);
        printf("���ٴ�����:");
        HiddenInput(password_agin);
    }
    sprintf(password_key,"%s%s",password,UserInfo.Slat);
    password_len=strlen(password_key);
    md5(password_key,password_len,password_md5);

    user* P_user;
    P_user=P_User(head,name);
    memcpy(P_user->password,password_md5,16);
    SaveUserFile(head);
    OpenUserFile(head);
    printf("�޸ĳɹ�!\n");
}

//ע��
void doRegister(UserList* head)
{
    user newnode;
    char password[20] ="\0";
    char password_key[29]="\0";
    int password_len = 0;
    char password_agin[20] ="\0";
    char password_md5[16] = "\0";
    char name[20];
    printf("�������û�����");
    scanf("%s",name);
    getchar();
    while(LookUser(head,name))
    {
        printf("�û�������,�������û�����");
        scanf("%s",name);
        getchar();
    }
    strcpy(newnode.name,name);//�����ִ���
    printf("����������:");
    HiddenInput(password);
    printf("���ٴ���������:");
    HiddenInput(password_agin);
    while(strcmp(password,password_agin))
    {
        printf("�������벻һ��������������:");
        HiddenInput(password);
        printf("���ٴ�����:");
        HiddenInput(password_agin);
    }
    char key[8]="\0";
    MakeRandStr(key, 8);//���������Կ
    strcpy(newnode.Slat,key);//��Slat����
    sprintf(password_key,"%s%s",password,key);
    password_len=strlen(password_key);
    md5(password_key,password_len,password_md5);
    memcpy(newnode.password,password_md5,16);//���������
    RSA(&newnode);
    UserListInsertTail(head,newnode);
    SaveUserFile(head);
    OpenUserFile(head);
    return ;
}

//��½
void doLogin(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head)
{
    char name[20];
    char password[20]="\0";
    char password_key[29]="\0";
    int password_len = 0;
    char password_md5[16] ="\0";
    user UserInfo;
    int Exit=0;
    printf("�������û�����");
    scanf("%s",name);
    getchar();
    if(!LookUser(User_head,name))
    {
        printf("�û���������!\n");
        return ;
    }

    if(!LookUserBan(User_head,name))
    {
        return ;
    }

    UserInfo=LookUserInfo(User_head,name);
    printf("����������:");
    HiddenInput(password);
    sprintf(password_key,"%s%s",password,UserInfo.Slat);
    password_len=strlen(password_key);
    md5(password_key,password_len,password_md5);
    while(!CheckPassword(User_head,name,password_md5)&&Exit<3)
    {
        printf("�������!��������������:");
        HiddenInput(password);
        sprintf(password_key,"%s%s",password,UserInfo.Slat);
        password_len=strlen(password_key);
        md5(password_key,password_len,password_md5);
        Exit++;
    }


    if(Exit==3)
    {
        printf("�������볬�����Σ�\n");
        UserBan(User_head,name);
        return ;
    }
    else
        printf("\n��½�ɹ�!\n");
    int choice=0;
    while(1)
    {
        subMenu(name);
        if(!strcmp(name,"admin"))
        {
            printf("����������Ҫ���еĲ�����1~7����");
        }
        else
            printf("����������Ҫ���еĲ�����1~6����");
        IsNumber(&choice,1);
        switch(choice)
        {
        case 1:
            doSendMail(User_head,Mail_head,name);
            break;
        case 2:
            doRecvMail(User_head,Mail_head,name);
            break;
        case 3:
            doPublishBulletin(User_head,Bulletin_head,name);
            break;
        case 4:
            doViewBulletin(User_head,Bulletin_head);
            break;
        case 5:
            ModifyPassword(User_head,name);
            break;
        case 6:
            printf("�˳��ɹ���\n");
            return ;
            break;
        case 7:
            if(!strcmp(name,"admin"))
            {
                printf("��ӭʹ�ó���Ȩ��\n");
                SuperPower(User_head,Mail_head,Bulletin_head);
            }
            else
                printf("�������������������ѡ��\n");
            break;

        default:
            printf("�������������������ѡ��\n");
            fflush(stdin);
            break;
        }
    }

}

void SuperPower(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head)
{
    int choice=0;
    while(1)
    {
        superMenu();
        printf("����������Ҫ���еĲ�����1~5����");
        IsNumber(&choice,1);
        switch(choice)
        {
        case 1:
            DelMail(Mail_head);
            SaveMailFile(Mail_head);
            OpenMailFile(Mail_head);
            break;
        case 2:
            DelBulletin(Bulletin_head);
            SaveBulletinFile(Bulletin_head);
            OpenBulletinFile(Bulletin_head);
            break;
        case 3:
            DelUser(User_head);
            SaveUserFile(User_head);
            OpenUserFile(User_head);
            break;
        case 4:
            ModifyUserPassword(User_head);
            SaveUserFile(User_head);
            OpenUserFile(User_head);
            break;
        case 5:
            printf("�˳��ɹ���\n");
            return ;
        default:
            printf("�������������������ѡ��\n");
            fflush(stdin);
            break;
        }
    }

}

void DelMail(MailList* head)
{
    int id,i;
    i=MailListTraverse(head);
    while(1)
    {
        printf("��������Ҫɾ�������(0�˳�):");
        IsNumber(&id);
        if(id>i)
        {
            printf("��˽�Ų�����!\n");
            continue;
        }
        else if(id)
        {
            DelMailNode(head,id);
            MailListTraverse(head);
        }
        else
            return;
    }
}

void DelMailNode(MailList* head,int id)
{
    int i=1;
    MailList* p = head->next;
    MailList* p_L= head;
    while(p)
    {
        if(i==id)
        {
            p_L->next=p->next;
            free(p);
            printf("ɾ���ɹ�!\n");
            return ;
        }
        p_L= p;
        p = p->next;
        i++;
    }
    return ;
}

void DelBulletin(BulletinList* head)
{
    int id,i;
    i=BulletinListTraverse(head);
    while(1)
    {
        printf("��������Ҫɾ�������(0�˳�):");
        IsNumber(&id);
        if(id>i)
        {
            printf("�˹��治����!\n");
            continue;
        }
        else if(id)
        {
            DelBulletinNode(head,id);
            BulletinListTraverse(head);
        }
        else
            return;
    }
}

void DelBulletinNode(BulletinList* head,int id)
{
    int i=1;
    BulletinList* p = head->next;
    BulletinList* p_L= head;
    while(p)
    {
        if(i==id)
        {
            p_L->next=p->next;
            free(p);
            printf("ɾ���ɹ�!\n");
            return ;
        }
        p_L= p;
        p = p->next;
        i++;
    }
    return ;
}

void DelUser(UserList* head)
{
    int id,i;
    i=UserListTraverse(head);
    while(1)
    {
        printf("��������Ҫɾ�������(0�˳�):");
        IsNumber(&id);
        getchar();
        if(id>i)
        {
            printf("���û�������!\n");
            continue;
        }
        else if(id)
        {
            DelUserNode(head,id);
            UserListTraverse(head);
        }
        else
            return;
    }
}

void DelUserNode(UserList* head,int id)
{
    int i=1;
    UserList* p = head->next;
    UserList* p_L= head;
    while(p)
    {
        if(i==id&&strcmp(p->data.name,"admin"))
        {
            p_L->next=p->next;
            free(p);
            printf("ɾ���ɹ�!\n");
            return ;
        }
        if(i==id&&!strcmp(p->data.name,"admin"))
        {
            printf("�޷�ɾ��admin�˺�!\n");
            return ;
        }
        p_L= p;
        p = p->next;
        i++;
    }
    return ;
}

void ModifyUserPassword(UserList* head)
{
    int id,i;
    i=UserListTraverse(head);
    while(1)
    {
        printf("��������Ҫ�޸���������(0�˳�):");
        IsNumber(&id,1);
        if(id>i)
        {
            printf("���û�������!\n");
            continue;
        }
        else if(id)
        {
            ModifyUserPasswordNode(head,id);
            UserListTraverse(head);
        }
        else
            return;
    }
}

void ModifyUserPasswordNode(UserList* head,int id)
{
    int i=1;
    UserList* p = head->next;
    char password[20]="\0";
    char password_agin[20]="\0";
    int password_len = 0;
    char password_md5[16] ="\0";
    char password_key[29]="\0";
    printf("����������:");
    HiddenInput(password);
    printf("���ٴ���������:");
    HiddenInput(password_agin);
    while(strcmp(password,password_agin))
    {
        printf("�������벻һ��������������:");
        HiddenInput(password);
        printf("���ٴ�����:");
        HiddenInput(password_agin);
    }


    while(p)
    {
        if(i==id&&strcmp(p->data.name,"admin"))
        {
            sprintf(password_key,"%s%s",password,p->data.Slat);
            password_len=strlen(password_key);
            md5(password_key,password_len,password_md5);
            memcpy(p->data.password,password_md5,16);
            printf("�޸ĳɹ�!\n");
            return ;
        }
        if(i==id&&!strcmp(p->data.name,"admin"))
        {
            printf("�޷��޸�admin�˺�!\n");
            return ;
        }
        p = p->next;
        i++;
    }

}



