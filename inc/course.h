//
// Created by Jack on 2023/6/4.
//

#ifndef EDUADMINSYSTEM_COURSE_H
#define EDUADMINSYSTEM_COURSE_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <map>
#include <vector>
#include <sstream>

class Course {
public:
    Course(std::string id, std::string name, int people_num, std::string teacher_id, std::string teacher_name);
    void set_id(std::string id){m_id = id;}
    void set_name(std::string name){m_name = name;}
    void set_people_num(int people_num){m_people_num = people_num;}
    void set_selected_num(int selected_num){m_selected_num = selected_num;}
    void add_selected_num(){m_selected_num++;}
    void add_student(std::string student_id, std::string student_name){m_student[student_id] = student_name;}
    std::string get_id(){return m_id;}
    std::string get_name(){return m_name;}
    int get_people_num(){return m_people_num;}
    int get_selected_num(){return m_selected_num;}
    std::map<std::string, std::string>& get_student(){return m_student;}
    std::string get_teacher_id(){return m_teacher_id;}
    std::string get_teacher_name(){return m_teacher_name;}
    void del_student(std::string student_id);
    inline void clear_student(){m_student.clear();}
private:
    std::string m_id;
    std::string m_name;
    int m_people_num;
    int m_selected_num;
    std::string m_teacher_id;
    std::string m_teacher_name;
    std::map<std::string, std::string> m_student;
};

Course::Course(std::string id, std::string name, int people_num, std::string teacher_id, std::string teacher_name) :
        m_id(id), m_name(name), m_people_num(people_num), m_teacher_id(teacher_id), m_teacher_name(teacher_name)
{
    m_selected_num = 0;
}

void Course::del_student(std::string student_id)
{
    std::map<std::string, std::string>::iterator it = m_student.find(student_id);
    m_student.erase(it);
    if(m_selected_num != 0)
        m_selected_num--;
}

void readCourse(std::vector<Course>& course_list, std::string filename)
{
    std::ifstream file;
    char buf[255];
    std::string s, stu_id, stu_name;
    std::string id, name, teacher_id, teacher_name;
    int people_num, selected_num;
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
        ss >> id;
        ss >> name;
        ss >> people_num;
        ss >> selected_num;
        ss >> teacher_id;
        ss >> teacher_name;
        Course course(id, name, people_num, teacher_id, teacher_name);
        course.set_selected_num(selected_num);
        while(ss >> stu_id)
        {
            ss >> stu_name;
            course.add_student(stu_id, stu_name);
        }
        course_list.push_back(course);
    }
    file.close();
}

void writeCourse(std::vector<Course> course_list, std::string filename)
{
    std::ofstream file;
    file.open(filename, std::ios::out);
    std::map<std::string, std::string>::iterator it;
    if(!file.is_open())
    {
        std::cout << "文件打开失败" << std::endl;
        return;
    }
    for(int i = 0; i < course_list.size(); i++)
    {
        file << course_list[i].get_id() << ' ';
        file << course_list[i].get_name() << ' ';
        file << course_list[i].get_people_num() << ' ';
        file << course_list[i].get_selected_num() << ' ';
        file << course_list[i].get_teacher_id() << ' ';
        file << course_list[i].get_teacher_name() << ' ';
        it = course_list[i].get_student().begin();
        for(int j = 0; j < course_list[i].get_student().size(); j++)
        {
            file << it->first << ' ';
            file << it->second << ' ';
        }
        file << std::endl;
    }
    file.close();
}

#endif //EDUADMINSYSTEM_COURSE_H
