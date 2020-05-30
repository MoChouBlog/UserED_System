#ifndef _HEADER_LIST
#define _HEADER_LIST
#include "../common/list.h"
#include "Mail.h"
#include "bulletin.h"
#endif

void RSA(user* node);
void ModifyPassword(UserList* head,char name[20]);
void doRegister(UserList* head);
void doLogin(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head);
void SuperPower(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head);
void DelMail(MailList* head);
void DelMailNode(MailList* head,int id);
void DelBulletin(BulletinList* head);
void DelBulletinNode(BulletinList* head,int id);
void DelUser(UserList* head);
void DelUserNode(UserList* head,int id);
void ModifyUserPassword(UserList* head);
void ModifyUserPasswordNode(UserList* head,int id);

