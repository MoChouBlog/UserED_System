#include <time.h>

//�û�
typedef struct user
{
    char name[20];
    char password[16];
    char Slat[9];
    long e;
    long n;
    time_t time;
} user;

//�û����
typedef struct user_node
{
    user data;
    struct node* next;
} UserList;

//�ʼ�
typedef struct mail
{
    char sendname[20];
    char receivename[20];
    char mailtext[100];
    long DesKey[8];
    time_t timep;
} mail;

//�ʼ����
typedef struct mail_node
{
    mail data;
    struct node* next;
} MailList;

//����
typedef struct bulletin
{
    char sendname[20];
    char bulletintext[100];
    long idkey[16];
    time_t timep;
} bulletin;

//������
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
