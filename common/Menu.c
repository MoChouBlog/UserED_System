

//主菜单
void mainMenu()
{
    printf("*********************欢迎使用*********************\n");
    printf("*                 1  注册用户                    *\n");
    printf("*                 2    登陆                      *\n");
    printf("*                 3  退出系统                    *\n");
    printf("**************************************************\n");
}

//子菜单
void subMenu(char name[20])
{
    printf("*********************欢迎使用*********************\n");
    printf("*                 1  发送邮件                    *\n");
    printf("*                 2  接受邮件                    *\n");
    printf("*                 3  发送公告                    *\n");
    printf("*                 4  浏览公告                    *\n");
    printf("*                 5  修改密码                    *\n");
    printf("*                 6    退出                      *\n");
    if(!strcmp(name,"admin"))
    {
        printf("*                 7  超级菜单                    *\n");
    }
    printf("**************************************************\n");
}

//超级菜单
void superMenu()
{
    printf("*********************欢迎使用*********************\n");
    printf("*                 1  删除邮件                    *\n");
    printf("*                 2  删除公告                    *\n");
    printf("*                 3  删除用户                    *\n");
    printf("*                 4修改用户密码                  *\n");
    printf("*                 5    退出                      *\n");
    printf("**************************************************\n");
}
