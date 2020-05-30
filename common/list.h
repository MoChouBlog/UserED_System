#include <time.h>

//用户
typedef struct user
{
    char name[20];
    char password[16];
    char Slat[9];
    long e;
    long n;
    time_t time;
} user;

//用户结点
typedef struct user_node
{
    user data;
    struct node* next;
} UserList;

//邮件
typedef struct mail
{
    char sendname[20];
    char receivename[20];
    char mailtext[100];
    long DesKey[8];
    time_t timep;
} mail;

//邮件结点
typedef struct mail_node
{
    mail data;
    struct node* next;
} MailList;

//公告
typedef struct bulletin
{
    char sendname[20];
    char bulletintext[100];
    long idkey[16];
    time_t timep;
} bulletin;

//公告结点
typedef struct bulletin_node
{
    bulletin data;
    struct node* next;
} BulletinList;

UserList* CreatUserNode(user data);
int UserListInsertTail(UserList* L, user data);
MailList* CreatMailNode(mail data);
int MailListInsertTail(MailList* L, mail data);
BulletinList* CreatBulletinNode(bulletin data);
int BulletinListInsertTail(BulletinList* L, bulletin data);
int LookUser(UserList* head,char name[20]);
int LookUserBan(UserList* head,char name[20]);
int UserBan(UserList* head,char name[20]);
int UserListTraverse(UserList* L);
int MailListTraverse(MailList* L);
int BulletinListTraverse(BulletinList* L);
user UserPubKey(UserList* head,char name[20]);
user* P_User(UserList* head,char name[20]);
user LookUserInfo(UserList* head,char name[20]);
