#include "Authority.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//产生RSA所需的e,d,n
void RSA(user* node)
{
    long p,q,e,d;//公钥
    while(1)
    {
        //输入RSA的p
        printf("请输入p:");
        scanf("%ld",&p);
        getchar();
        while(!isPrime(p))
        {
            printf("不是素数请重新输入:");
            scanf("%ld",&p);
            getchar();
        }

        //输入RSA的p
        printf("请输入q:");
        scanf("%ld",&q);
        getchar();
        while(!isPrime(q))
        {
            printf("不是素数请重新输入:");
            scanf("%ld",&q);
            getchar();
        }
        if(p*q < 128)
            printf("p×q 不能小于128\n");
        else
            break;
    }

    //打印p q
    printf("p:%ld q:%ld\n",p,q);

    //输入RSA公钥的e
    printf("请输入e(0~%ld):",(p-1)*(q-1));
    scanf("%ld",&e);
    getchar();
    while(!extendedEuclid(e, (p-1)*(q-1), &d))
    {
        printf("e和%ld不互素,请重新输入:",(p-1)*(q-1));
        scanf("%ld",&e);
        getchar();
    }

    //将公钥私钥信息写入
    node->n=p*q;//公钥n
    node->e=e;//公钥e

    //打印公私钥信息
    printf("公钥{n=%ld ,e=%ld}\n",node->n,node->e);
    printf("私钥{d=%ld ,n=%ld}\n",d,node->n);
    printf("请牢记你的私钥:%ld\n",d);
}

//修改密码
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
    printf("请输入旧密码:");
    HiddenInput(password_old);
    sprintf(password_key,"%s%s",password_old,UserInfo.Slat);
    password_len=strlen(password_key);
    md5(password_key,password_len,password_md5);
    while(!CheckPassword(head,name,password_md5))
    {
        printf("旧密码验证错误!请重新输入:");
        HiddenInput(password_old);
        sprintf(password_key,"%s%s",password_old,UserInfo.Slat);
        password_len=strlen(password_key);
        md5(password_key,password_len,password_md5);
    }
    printf("请输入新密码:");
    HiddenInput(password);
    printf("请再次输入新密码:");
    HiddenInput(password_agin);
    while(strcmp(password,password_agin))
    {
        printf("两次密码不一样，请重新输入:");
        HiddenInput(password);
        printf("请再次输入:");
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
    printf("修改成功!\n");
}

//注册
void doRegister(UserList* head)
{
    user newnode;
    char password[20] ="\0";
    char password_key[29]="\0";
    int password_len = 0;
    char password_agin[20] ="\0";
    char password_md5[16] = "\0";
    char name[20];
    printf("请输入用户名：");
    scanf("%s",name);
    getchar();
    while(LookUser(head,name))
    {
        printf("用户名存在,请输入用户名：");
        scanf("%s",name);
        getchar();
    }
    strcpy(newnode.name,name);//将名字存入
    printf("请输入密码:");
    HiddenInput(password);
    printf("请再次输入密码:");
    HiddenInput(password_agin);
    while(strcmp(password,password_agin))
    {
        printf("两次密码不一样，请重新输入:");
        HiddenInput(password);
        printf("请再次输入:");
        HiddenInput(password_agin);
    }
    char key[8]="\0";
    MakeRandStr(key, 8);//随机产生密钥
    strcpy(newnode.Slat,key);//将Slat存入
    sprintf(password_key,"%s%s",password,key);
    password_len=strlen(password_key);
    md5(password_key,password_len,password_md5);
    memcpy(newnode.password,password_md5,16);//将密码存入
    RSA(&newnode);
    UserListInsertTail(head,newnode);
    SaveUserFile(head);
    OpenUserFile(head);
    return ;
}

//登陆
void doLogin(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head)
{
    char name[20];
    char password[20]="\0";
    char password_key[29]="\0";
    int password_len = 0;
    char password_md5[16] ="\0";
    user UserInfo;
    int Exit=0;
    printf("请输入用户名：");
    scanf("%s",name);
    getchar();
    if(!LookUser(User_head,name))
    {
        printf("用户名不存在!\n");
        return ;
    }

    if(!LookUserBan(User_head,name))
    {
        return ;
    }

    UserInfo=LookUserInfo(User_head,name);
    printf("请输入密码:");
    HiddenInput(password);
    sprintf(password_key,"%s%s",password,UserInfo.Slat);
    password_len=strlen(password_key);
    md5(password_key,password_len,password_md5);
    while(!CheckPassword(User_head,name,password_md5)&&Exit<3)
    {
        printf("密码错误!请重新输入密码:");
        HiddenInput(password);
        sprintf(password_key,"%s%s",password,UserInfo.Slat);
        password_len=strlen(password_key);
        md5(password_key,password_len,password_md5);
        Exit++;
    }


    if(Exit==3)
    {
        printf("重输密码超过三次！\n");
        UserBan(User_head,name);
        return ;
    }
    else
        printf("\n登陆成功!\n");
    int choice=0;
    while(1)
    {
        subMenu(name);
        if(!strcmp(name,"admin"))
        {
            printf("请输入你所要进行的操作（1~7）：");
        }
        else
            printf("请输入你所要进行的操作（1~6）：");
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
            printf("退出成功！\n");
            return ;
            break;
        case 7:
            if(!strcmp(name,"admin"))
            {
                printf("欢迎使用超级权限\n");
                SuperPower(User_head,Mail_head,Bulletin_head);
            }
            else
                printf("输入错误，请从新输入你的选择：\n");
            break;

        default:
            printf("输入错误，请从新输入你的选择：\n");
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
        printf("请输入你所要进行的操作（1~5）：");
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
            printf("退出成功！\n");
            return ;
        default:
            printf("输入错误，请从新输入你的选择：\n");
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
        printf("请输入需要删除的序号(0退出):");
        IsNumber(&id);
        if(id>i)
        {
            printf("此私信不存在!\n");
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
            printf("删除成功!\n");
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
        printf("请输入需要删除的序号(0退出):");
        IsNumber(&id);
        if(id>i)
        {
            printf("此公告不存在!\n");
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
            printf("删除成功!\n");
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
        printf("请输入需要删除的序号(0退出):");
        IsNumber(&id);
        getchar();
        if(id>i)
        {
            printf("此用户不存在!\n");
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
            printf("删除成功!\n");
            return ;
        }
        if(i==id&&!strcmp(p->data.name,"admin"))
        {
            printf("无法删除admin账号!\n");
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
        printf("请输入需要修改密码的序号(0退出):");
        IsNumber(&id,1);
        if(id>i)
        {
            printf("此用户不存在!\n");
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
    printf("请输入密码:");
    HiddenInput(password);
    printf("请再次输入密码:");
    HiddenInput(password_agin);
    while(strcmp(password,password_agin))
    {
        printf("两次密码不一样，请重新输入:");
        HiddenInput(password);
        printf("请再次输入:");
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
            printf("修改成功!\n");
            return ;
        }
        if(i==id&&!strcmp(p->data.name,"admin"))
        {
            printf("无法修改admin账号!\n");
            return ;
        }
        p = p->next;
        i++;
    }

}



