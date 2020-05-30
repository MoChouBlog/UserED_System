#ifndef _HEADER_LIST
#define _HEADER_LIST
#include "list.h"
#endif
int OpenUserFile(UserList* head);
void SaveUserFile(UserList* head);
int OpenMailFile(MailList* head);
void SaveMailFile(MailList* head);
int OpenBulletinFile(BulletinList* head);
void SaveBulletinFile(BulletinList* head);

/*传递三个链表头进去，将文件读取的信息写入到对应的链表中*/
void initSystem(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head);
/*传递三个链表头进去，将文链表中的信息写入到对应的文件中*/
void uninitSystem(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head);

