#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "common/file.h"
#include "common/Menu.h"
#include "common/common.h"
#include "business/Authority.h"
int main()
{
    user User_begin;
    UserList* User_head = CreatUserNode(User_begin);//生成用户头结点，数据域赋值为NULL
    mail Mail_begin;
    MailList* Mail_head = CreatMailNode(Mail_begin);//生成邮件头结点，数据域赋值为NULL
    bulletin Bulletin_begin;
    BulletinList* Bulletin_head = CreatBulletinNode(Bulletin_begin);//生成公告头结点，数据域赋值为NULL
    initSystem(User_head,Mail_head,Bulletin_head);
    int choice=0;
    while(1)
    {
        mainMenu();
        printf("请输入你所要进行的操作（1~3）：");
        IsNumber(&choice,1);
        switch(choice)
        {
        case 1:
            doRegister(User_head);
            break;
        case 2:
            doLogin(User_head,Mail_head,Bulletin_head);
            break;
        case 3:
            uninitSystem(User_head,Mail_head,Bulletin_head);
            free(User_head);// 释放头结点内存
            free(Mail_head);// 释放头结点内存
            free(Bulletin_head);// 释放头结点内存
            exit(0);
            break;
        default:
            printf("输入错误，请从新输入你的选择：\n");
            fflush(stdin);
            break;
        }
    }
    return 0;
}
