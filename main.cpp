#include <iostream>
#include <stdlib.h>
#include "inc/course.h"
#include "inc/user.h"
#include "inc/menu.h"

int main(){
    std::vector<Course> course_list;
    std::vector<User> user_list;
    readUser(user_list,"../data/user.txt");
    readCourse(course_list,"../data/course.txt");
    mainMenu(user_list, course_list);
    writeUser(user_list, "../data/user.txt");
    writeCourse(course_list, "../data/course.txt");
    return 0;
}