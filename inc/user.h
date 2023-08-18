//
// Created by Jack on 2023/6/1.
//
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
//#include <direct.h>
#include <unistd.h>
#include "course.h"
#ifndef EDUADMINSYSTEM_USER_H
#define EDUADMINSYSTEM_USER_H
class User{
public:
    User(std::string user_type, std::string account, std::string password, std::string name) :
            m_user_type(user_type), m_account(account), m_password(password), m_name(name){}
    void set_user_type(std::string user_type){m_user_type = user_type;}
    void set_account(std::string account){m_account = account;}
    void set_password(std::string password){m_password = password;}
    void set_name(std::string name){m_name = name;}
    std::string get_user_type(){return m_user_type;}
    std::string get_account(){return m_account;}
    std::string get_password(){return m_password;}
    std::string get_name(){return m_name;}
private:
    std::string m_user_type;
    std::string m_account;
    std::string m_password;
    std::string m_name;
};

class Administrator : public User{
public:
    Administrator(std::string user_type, std::string account, std::string password, std::string name) :
            User(user_type, account, password, name){}
    void add_user(std::vector<User>& user_list);
    void edit_user(std::vector<User>& user_list);
    void delete_user(std::vector<User>& user_list, std::vector<Course>& course_list);
    void show_user(std::vector<User> user_list);
private:

};

void Administrator::add_user(std::vector<User>& user_list) {
    std::string user_type, account, password, name;
    std::cout << "【增加用户】请输入类型：";
    std::cin >> user_type;
    if(user_type != "教师" && user_type != "学生")
    {
        std::cout << "请输入'教师'或'学生'！" << std::endl;
        return;
    }
    std::cout << "【增加用户】请输入账号：";
    std::cin >> account;
    for(int i = 0; i < user_list.size(); i++)
    {
        if(user_list[i].get_account() == account)
        {
            std::cout << "该账号已经存在！" << std::endl;
            return;
        }
    }
    std::cout << "【增加用户】请输入密码：";
    std::cin >> password;
    std::cout << "【增加用户】请输入姓名：";
    std::cin >> name;
    User user(user_type, account, password, name);
    user_list.push_back(user);
    std::cout << "【增加用户】账号已添加" << std::endl;
}

void Administrator::edit_user(std::vector<User>& user_list) {
    std::string account, password, name;
    int pos = -1;
    std::cout << "【编辑账号】请输入账号：";
    std::cin >> account;
    for(int i = 0; i < user_list.size(); i++)
    {
        if(user_list[i].get_account() == account)
        {
            pos = i;
            break;
        }
    }
    if(pos == -1)
    {
        std::cout << "该账号不存在！" << std::endl;
    }
    else
    {
        std::cout << "【增加用户】请输入密码：";
        std::cin >> password;
        std::cout << "【增加用户】请输入姓名：";
        std::cin >> name;
        user_list[pos].set_password(password);
        user_list[pos].set_name(name);
        std::cout << "【编辑用户】账号已修改" << std::endl;
    }
}

void Administrator::delete_user(std::vector<User>& user_list, std::vector<Course>& course_list) {
    std::string account;
    int pos = -1;
    std::cout << "【删除账号】请输入账号：";
    std::cin >> account;
    for(int i = 0; i < user_list.size(); i++)
    {
        if(user_list[i].get_account() == account)
        {
            char ch;
            std::cout << "【删除用户】确认删除账号（" << user_list[i].get_account() << "）？确认输入(Y), 取消输入(N)：";
            std::cin >> ch;
            std::cin.ignore();
            int size = course_list.size();
            if(ch == 'Y' || ch == 'y')
            {
                for(int j = 0; j < size; j++)
                {
                    std::map<std::string, std::string>::iterator it;
                    std::vector<Course>::iterator it1 = course_list.begin();
                    for(int k = 0; k < course_list.size(); k++)
                    {
                        if(it1->get_teacher_id() == account)
                        {
                            course_list.erase(it1);
                        }
                        if(it1 != course_list.end())
                        {
                            //it = it1->get_student().begin();
                            if(it1->get_student().find(account) != it1->get_student().end())
                            {
                                it1->del_student(account);
                            }
                        }
                        it1++;
                    }


                }
                user_list.erase(user_list.begin() + i);
                std::cout << "【删除用户】账号已删除" << std::endl;
                return;
            }
            else
            {
                return;
            }
        }
    }
    std::cout << "该账号不存在！" << std::endl;
}

void Administrator::show_user(std::vector<User> user_list) {
    int size = user_list.size();
    char ch;
    if(size == 0)
    {
        std::cout << "当前用户列表中没有用户" << std::endl;
        return;
    }
    std::cout << "【用户列表】账号总数是：" << size << std::endl;
    std::cout << "【用户列表】是否列出所有账号？确认输入(Y), 取消输入(N)：";
    std::cin >> ch;
    std::cin.ignore();
    if(ch == 'Y' || ch == 'y')
    {
        std::cout << std::setiosflags(std::ios::left) << std::setw(20) << "账号"
                  << std::setw(20) << "类型"
                  << std::setw(20) << "密码"
                  << std::setw(20) << "姓名" << std::endl;
        for(int i = 0; i < size; i++)
        {
            std::cout << std::setiosflags(std::ios::left) << std::setw(20) << user_list[i].get_account()
                      << std::setw(20) << user_list[i].get_user_type()
                      << std::setw(20) << user_list[i].get_password()
                      << std::setw(20) << user_list[i].get_name() << std::endl;
        }
    }
    else
        return;
}

class Teacher : public User {
public:
    Teacher(std::string user_type, std::string account, std::string password, std::string name) :
            User(user_type, account, password, name){}
    void add_course(std::vector<Course>& course_list);
    void edit_course(std::vector<Course>& course_list);
    void show_course(std::vector<Course> course_list);
private:

};

void Teacher::add_course(std::vector<Course>& course_list)
{
    std::string id, name;
    int people_num, pos = -1;
    std::cout << "【增加课程】请输入课程ID：";
    std::cin >> id;
    std::cout << "【增加课程】请输入课程名称：";
    std::cin >> name;
    std::cout << "【增加课程】请输入课程人数：";
    std::cin >> people_num;
    Course c(id, name, people_num, this->get_account(), this->get_name());
    for(int i = 0; i < course_list.size(); i++)
    {
        if(course_list[i].get_id() == this->get_account())
        {
            pos = i;
            break;
        }
    }
    if(pos == -1)
    {
        course_list.push_back(c);
    }
    else
    {
        course_list.insert(course_list.begin() + pos, c);
    }
    std::cout << "【增加课程】课程已添加。" << std::endl;
}

void Teacher::edit_course(std::vector<Course>& course_list)
{
    std::string id, name;
    int people_num, pos = -1;
    std::cout << "【编辑课程】请输入课程ID：";
    std::cin >> id;
    for(int i = 0; i < course_list.size(); i++)
    {
        if(course_list[i].get_id() == id)
        {
            pos = i;
            break;
        }
    }
    if(pos == -1)
    {
        std::cout << "输入的课程ID不存在！" << std::endl;
        return;
    }
    else
    {
        std::cout << "【编辑课程】请输入课程名称：";
        std::cin >> name;
        std::cout << "【编辑课程】请输入课程人数：";
        std::cin >> people_num;
        course_list[pos].set_name(name);
        if(course_list[pos].get_people_num() > people_num)
        {
            //如果要修改的课程人数小于原有的课程人数，则将所有选课学生清空
            course_list[pos].clear_student();
        }
        course_list[pos].set_people_num(people_num);
    }
}

void Teacher::show_course(std::vector<Course> course_list)
{
    int course_num = 0;
    std::vector<int> c;
    char ch;
    for(int i = 0; i < course_list.size(); i++)
    {
        if(course_list[i].get_teacher_id() == this->get_account())
        {
            c.push_back(i);
            course_num++;
        }
    }
    if(course_num == 0)
    {
        std::cout << "当前没有课程！" << std::endl;
        return;
    }
    std::cout << "【课程列表】课程总数是：" << course_num << std::endl;
    std::cout << "【课程列表】是否列出所有课程？确认输入(Y), 取消输入(N)：";
    std::cin >> ch;
    std::cin.ignore();
    if(ch == 'Y' || ch == 'y')
    {
        for(int i = 0; i < c.size(); i++)
        {
            std::cout << std::setiosflags(std::ios::left) << std::setw(20) << "课程ID"
                      << std::setw(20) << "课程名称"
                      << std::setw(20) << "课程人数"
                      << std::setw(20) << "已选人数" << std::endl;
            std::cout << std::setiosflags(std::ios::left) << std::setw(20) << course_list[c[i]].get_id()
                      << std::setw(20) << course_list[c[i]].get_name()
                      << std::setw(20) << course_list[c[i]].get_people_num()
                      << std::setw(20) << course_list[c[i]].get_selected_num() << std::endl;
            std::cout << "已选课学生列表" << std::endl;
            std::cout << std::setiosflags(std::ios::left) << std::setw(20) << "学生ID"
                      << std::setw(20) << "学生姓名" << std::endl;
            for(int j = 0; j < course_list[c[i]].get_student().size(); j++)
            {
                if(course_list[c[i]].get_student().size() == 0)
                {
                    std::cout << "无" << std::endl;
                    break;
                }
                std::map<std::string, std::string>::iterator it = course_list[c[i]].get_student().begin();
                std::cout << std::setiosflags(std::ios::left) << std::setw(20) << it->first << std::setw(20) << it->second;
                it++;
            }
            std::cout << std::endl << std::endl;
        }

    }
    else
    {
        return;
    }
    std::cout << "【课程列表】是否导出课程列表？确认输入(Y), 取消输入(N)：";
    std::cin >> ch;
    std::cin.ignore();
    if(ch == 'Y' || ch == 'y')
    {
        std::ofstream file;
        std::string filename = "../data/" + this->get_account() + "-course.txt";
        file.open(filename, std::ios::out);
        if(!file.is_open())
        {
            std::cout << "文件打开失败" << std::endl;
            return;
        }
        for(int i = 0; i < c.size(); i++)
        {
            file << std::setiosflags(std::ios::left) << std::setw(20) << "课程ID"
                 << std::setw(20) << "课程名称"
                 << std::setw(20) << "课程人数"
                 << std::setw(20) << "已选人数" << std::endl;
            file << std::setiosflags(std::ios::left) << std::setw(20) << course_list[c[i]].get_id()
                 << std::setw(20) << course_list[c[i]].get_name()
                 << std::setw(20) << course_list[c[i]].get_people_num()
                 << std::setw(20) << course_list[c[i]].get_selected_num() << std::endl;
            file << "已选课学生列表" << std::endl;
            file << std::setiosflags(std::ios::left) << std::setw(20) << "学生ID"
                 << std::setw(20) << "学生姓名" << std::endl;
            for(int i = 0; i < course_list[c[i]].get_student().size(); i++)
            {
                if(course_list[c[i]].get_student().size() == 0)
                {
                    file << "无" << std::endl;
                    break;
                }
                std::map<std::string, std::string>::iterator it = course_list[c[i]].get_student().begin();
                file << std::setiosflags(std::ios::left) << std::setw(20) << it->first << std::setw(20) << it->second;
                it++;
            }
            file << std::endl << std::endl;
        }
        char path[255];
        getcwd(path, 255);
        std::cout << "【课程列表】课程列表已导出！存放路径为："<< '/' << path << filename << std::endl;
        file.close();
    }
    else
    {
        return;
    }
}

class Student : public User {
public:
    Student(std::string user_type, std::string account, std::string password, std::string name) :
            User(user_type, account, password, name){}
    void show_course(std::vector<Course> course_list);
    void select_course(std::vector<Course>& course_list);
    void show_selected(std::vector<Course> course_list);
private:
};

void Student::show_course(std::vector<Course> course_list)
{
    int course_num = 0;
    char ch;
    for(int i = 0; i < course_list.size(); i++)
    {
        course_num++;
    }
    if(course_num == 0)
    {
        std::cout << "当前没有课程！" << std::endl;
        return;
    }
    std::cout << "【课程列表】课程总数是：" << course_num << std::endl;
    std::cout << "【课程列表】是否列出所有课程？确认输入(Y), 取消输入(N)：";
    std::cin >> ch;
    std::cin.ignore();
    if(ch == 'Y' || ch == 'y')
    {
        std::cout << std::setiosflags(std::ios::left) << std::setw(20) << "课程ID"
                  << std::setw(20) << "课程名称"
                  << std::setw(20) << "课程人数"
                  << std::setw(20) << "已选人数"
                  << std::setw(20) << "任课教师" << std::endl;
        for(int i = 0; i < course_list.size(); i++)
        {
            std::cout << std::setiosflags(std::ios::left) << std::setw(20) << course_list[i].get_id()
                      << std::setw(20) << course_list[i].get_name()
                      << std::setw(20) << course_list[i].get_people_num()
                      << std::setw(20) << course_list[i].get_selected_num()
                      << std::setw(20) << course_list[i].get_teacher_name() << std::endl;
            std::cout << std::endl << std::endl;
        }

    }
    else
    {
        return;
    }
}

void Student::select_course(std::vector<Course>& course_list)
{
    std::string id;
    int pos = -1;
    char ch;
    std::cout << "【选课】请输入课程ID：";
    std::cin >> id;
    for(int i = 0; i < course_list.size(); i++)
    {
        if(course_list[i].get_id() == id)
        {
            pos = i;
            break;
        }
    }
    if(pos == -1)
    {
        std::cout << "输入的课程ID不存在！" << std::endl;
        return;
    }
    else
    {
        std::cout << "【选课】确定选择此课程？确认输入(Y), 取消输入(N)：";
        std::cin >> ch;
        std::cin.ignore();
        if(ch == 'Y' || ch == 'y')
        {

            if(course_list[pos].get_student().find(this->get_account()) == course_list[pos].get_student().end()) {
                course_list[pos].add_student(this->get_account(), this->get_name());
                course_list[pos].add_selected_num();
                std::cout << "【选课】选课成功！" << std::endl;
            }
            else
            {
                std::cout << "你已经选择了该课程！" << std::endl;
            }
        }
        else
        {
            std::cout << "选课取消" << std::endl;
            return;
        }
    }
}

void Student::show_selected(std::vector<Course> course_list)
{
    int num = 0;
    char ch;
    std::vector<int> c;
    std::map<std::string, std::string>::iterator it;
    for(int i = 0; i < course_list.size(); i++)
    {
        it = course_list[i].get_student().begin();
        if(course_list[i].get_student().find(this->get_account()) != course_list[i].get_student().end())
        {
            c.push_back(i);
            num++;
        }
    }
    if(num == 0)
    {
        std::cout << "当前没有已选课程！" << std::endl;
        return;
    }
    else
    {
        std::cout << "【已选课程】已选课程总数是：" << num << std::endl;
        std::cout << "【已选课程】是否列出所有课程？确认输入(Y), 取消输入(N)：";
        std::cin >> ch;
        std::cin.ignore();
        if(ch == 'Y' || ch == 'y')
        {
            std::cout << std::setiosflags(std::ios::left) << std::setw(20) << "课程ID"
                      << std::setw(20) << "课程名称"
                      << std::setw(20) << "课程人数"
                      << std::setw(20) << "已选人数"
                      << std::setw(20) << "任课教师" << std::endl;
            for(int i = 0; i < c.size(); i++)
            {
                std::cout << std::setiosflags(std::ios::left) << std::setw(20) << course_list[c[i]].get_id()
                          << std::setw(20) << course_list[c[i]].get_name()
                          << std::setw(20) << course_list[c[i]].get_people_num()
                          << std::setw(20) << course_list[c[i]].get_selected_num()
                          << std::setw(20) << course_list[c[i]].get_teacher_name() << std::endl;
                std::cout << std::endl << std::endl;
            }
        }
        else
        {
            return;
        }
    }
}

void readUser(std::vector<User>& user_list, std::string filename)
{
    std::ifstream file;
    char buf[255];
    std::string s;
    std::string type, account, password, name;
    file.open(filename, std::ios::in);
    if(!file.is_open())
    {
        std::cout << "文件打开失败" << std::endl;
        return;
    }
    while(file.getline(buf, sizeof(buf)))
    {
        s = buf;
        std::istringstream ss(s);
        ss >> type;
        ss >> account;
        ss >> password;
        ss >> name;
        User user(type, account, password, name);
        user_list.push_back(user);
    }
    file.close();
}

void writeUser(std::vector<User> user_list, std::string filename)
{
    std::ofstream file;
    file.open(filename, std::ios::out);
    if(!file.is_open())
    {
        std::cout << "文件打开失败" << std::endl;
        return;
    }
    for(int i = 0; i < user_list.size(); i++)
    {
        file << user_list[i].get_user_type() << ' ';
        file << user_list[i].get_account() << ' ';
        file << user_list[i].get_password() << ' ';
        file << user_list[i].get_name() << ' ';
        file << std::endl;
    }
    file.close();
}

bool userLogin(std::vector<User> user_list, std::string user_type, std::string account, std::string password)
{
    for(int i = 0; i < user_list.size(); i++)
    {
        if(user_list[i].get_user_type() == user_type)
        {
            if(user_list[i].get_account() == account)
            {
                if(user_list[i].get_password() == password)
                    return true;
            }
        }
    }
    return false;
}

#endif //EDUADMINSYSTEM_USER_H