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
    UserList* User_head = CreatUserNode(User_begin);//�����û�ͷ��㣬������ֵΪNULL
    mail Mail_begin;
    MailList* Mail_head = CreatMailNode(Mail_begin);//�����ʼ�ͷ��㣬������ֵΪNULL
    bulletin Bulletin_begin;
    BulletinList* Bulletin_head = CreatBulletinNode(Bulletin_begin);//���ɹ���ͷ��㣬������ֵΪNULL
    initSystem(User_head,Mail_head,Bulletin_head);
    int choice=0;
    while(1)
    {
        mainMenu();
        printf("����������Ҫ���еĲ�����1~3����");
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
            free(User_head);// �ͷ�ͷ����ڴ�
            free(Mail_head);// �ͷ�ͷ����ڴ�
            free(Bulletin_head);// �ͷ�ͷ����ڴ�
            exit(0);
            break;
        default:
            printf("�������������������ѡ��\n");
            fflush(stdin);
            break;
        }
    }
    return 0;
}
