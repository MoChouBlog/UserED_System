#ifndef _HEADER_LIST
#define _HEADER_LIST
#include "../common/list.h"
#endif
#include "../common/common.h"

void doSendMail(UserList* User_head,MailList* head,char name[20]);
void doRecvMail(UserList* User_head,MailList* Mail_head,char name[20]);
