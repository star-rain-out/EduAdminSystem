//
// Created by Jack on 2023/6/4.
//

#ifndef EDUADMINSYSTEM_MENU_H
#define EDUADMINSYSTEM_MENU_H

#include <iostream>
#include <string.h>
#include <vector>
#include "user.h"
#include "course.h"

void mainMenu(std::vector<User>& user_list, std::vector<Course>& course_list);
void adminMenu(std::vector<User>& user_list, std::vector<Course>& course_list);
void teacherMenu(std::vector<User> user_list, std::vector<Course>& course_list);
void studentMenu(std::vector<User> user_list, std::vector<Course>& course_list);

void mainMenu(std::vector<User>& user_list, std::vector<Course>& course_list)
{
    int op;
    bool isExit = false;
    while(!isExit)
    {
        std::cout << "*欢迎您使用教务系统*" << std::endl
                  << "*1) 管理员" << std::endl
                  << "*2）教师用户" << std::endl
                  << "*3）学生用户" << std::endl
                  << "*4）退出系统" << std::endl
                  << "*请选择登录用户类型[1-4]: ";
        std::cin >> op;
        std::cin.ignore();
        switch (op)
        {
            case 1:
                adminMenu(user_list, course_list);
                break;
            case 2:
                teacherMenu(user_list, course_list);
                break;
            case 3:
                studentMenu(user_list, course_list);
                break;
            case 4:
                isExit = true;
                break;
            default:
                std::cout << "输入的指令有误，请重新输入" << std::endl;
                break;
        }
    }
}

void adminMenu(std::vector<User>& user_list, std::vector<Course>& course_list)
{
    std::string account, password;
    bool isExit = false;
    int op;
    std::cout << "请输入账号：";
    std::cin >> account;
    std::cout << "请输入密码：";
    std::cin >> password;
    if(account != "admin" || password != "123456")
    {
        std::cout << "账号或密码有误！" << std::endl;
        return;
    }
    Administrator admin("管理员", account, password, "管理员");
    while(!isExit)
    {
        std::cout << "*欢迎您admin，您的角色是管理员！具有如下功能权限：" << std::endl
                  << "*1）增加用户" << std::endl
                  << "*2）编辑用户" << std::endl
                  << "*3）删除用户" << std::endl
                  << "*4）用户列表" << std::endl
                  << "*5）返回" << std::endl
                  << "*请输入命令[1-5]：";
        std::cin >> op;
        std::cin.ignore();
        switch (op)
        {
            case 1:
                admin.add_user(user_list);
                break;
            case 2:
                admin.edit_user(user_list);
                break;
            case 3:
                admin.delete_user(user_list, course_list);
                break;
            case 4:
                admin.show_user(user_list);
                break;
            case 5:
                isExit = true;
                break;
            default:
                std::cout << "输入的指令有误，请重新输入" << std::endl;
                break;
        }
    }

}

void teacherMenu(std::vector<User> user_list, std::vector<Course>& course_list)
{
    std::string account, password;
    bool isExit = false;
    int op;
    int pos = -1;
    std::cout << "请输入账号：";
    std::cin >> account;
    std::cout << "请输入密码：";
    std::cin >> password;
    for(int i = 0; i < user_list.size(); i++)
    {
        if(user_list[i].get_user_type() == "教师")
        {
            if(user_list[i].get_account() == account)
            {
                if(user_list[i].get_password() == password)
                {
                    pos = i;
                    break;
                }
            }
        }
    }
    if(pos == -1)
    {
        std::cout << "账号或密码错误！" << std::endl;
        return;
    }
    Teacher teacher(user_list[pos].get_user_type(), user_list[pos].get_account(), user_list[pos].get_password(), user_list[pos].get_name());
    while (!isExit)
    {
        std::cout << "*欢迎您" << teacher.get_account() << "，您的角色是教师用户！具有如下功能权限：" << std::endl
                  << "*1）增加课程" << std::endl
                  << "*2）编辑课程" << std::endl
                  << "*3）课程列表" << std::endl
                  << "*4）返回" << std::endl
                  << "*请输入命令[1-4]：";
        std::cin >> op;
        std::cin.ignore();
        switch (op)
        {
            case 1:
                teacher.add_course(course_list);
                break;
            case 2:
                teacher.edit_course(course_list);
                break;
            case 3:
                teacher.show_course(course_list);
                break;
            case 4:
                isExit = true;
                break;
            default:
                std::cout << "输入的指令有误，请重新输入" << std::endl;
                break;
        }
    }

}

void studentMenu(std::vector<User> user_list, std::vector<Course>& course_list)
{
    std::string account, password;
    bool isExit = false;
    int op;
    int pos = -1;
    std::cout << "请输入账号：";
    std::cin >> account;
    std::cout << "请输入密码：";
    std::cin >> password;
    for(int i = 0; i < user_list.size(); i++)
    {
        if(user_list[i].get_user_type() == "学生")
        {
            if(user_list[i].get_account() == account)
            {
                if(user_list[i].get_password() == password)
                {
                    pos = i;
                    break;
                }
            }
        }
    }
    if(pos == -1)
    {
        std::cout << "账号或密码错误！" << std::endl;
        return;
    }
    Student student(user_list[pos].get_user_type(), user_list[pos].get_account(), user_list[pos].get_password(), user_list[pos].get_name());
    while (!isExit)
    {
        std::cout << "*欢迎您" << student.get_account() << "，您的角色是学生用户！具有如下功能权限：" << std::endl
                  << "*1）浏览课程" << std::endl
                  << "*2）选课" << std::endl
                  << "*3）已选课程" << std::endl
                  << "*4）返回" << std::endl
                  << "*请输入命令[1-4]：";
        std::cin >> op;
        std::cin.ignore();
        switch (op)
        {
            case 1:
                student.show_course(course_list);
                break;
            case 2:
                student.select_course(course_list);
                break;
            case 3:
                student.show_selected(course_list);
                break;
            case 4:
                isExit = true;
                break;
            default:
                std::cout << "输入的指令有误，请重新输入" << std::endl;
                break;
        }
    }
}

#endif //EDUADMINSYSTEM_MENU_H
