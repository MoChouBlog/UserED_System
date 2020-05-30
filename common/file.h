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

/*������������ͷ��ȥ�����ļ���ȡ����Ϣд�뵽��Ӧ��������*/
void initSystem(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head);
/*������������ͷ��ȥ�����������е���Ϣд�뵽��Ӧ���ļ���*/
void uninitSystem(UserList* User_head,MailList* Mail_head,BulletinList* Bulletin_head);

