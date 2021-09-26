#include <iostream>
#include "../include/person.h"
// #include <person.h>
#pragma once
// class person
// {
// private:
//     /* data */
// public:
//     person(/* args */);
//     void say();
//     ~person();
// };



person::person(/* args */)
{
    std::cout<<"init person"<<std::endl;

}
void person::say()
{
std::cout<<"say"<<std::endl;
}

person::~person()
{
}
