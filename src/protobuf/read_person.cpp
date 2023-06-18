/*
 * @Author: glider
 * @Date: 2022-10-13 19:34:48
 * @LastEditTime: 2022-10-13 19:40:13
 * @FilePath: /SubstrateDevelopment/protobuf/read_person.cpp
 * @Version:  v0.01
 * @Description: 
 * ************************************************************************
 * Copyright (c) 2022 by  glider.guo@ankobot.com, All Rights Reserved. 
 * ************************************************************************
 */
#include <iostream>  
#include "person.pb.h"  
#include <fstream>  
#include <string>  
  
using namespace std;  
  
int main(){  
    Person *person = new Person;  
    char buffer[BUFSIZ];  
    fstream input("myfile",ios::in|ios::binary);  
    input.read(buffer,sizeof(Person));  
    person->ParseFromString(buffer);  //用这个方法，通常不用ParseFromString  
    cout << person->name() << person->phonenum(1) << endl;  
    return 0;  
}  