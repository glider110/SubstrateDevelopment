/*
 * @Author: 郭小凡 glider.guo@ankobot.com
 * @Date: 2022-07-14 16:08:07
 * @LastEditors: 郭小凡 glider.guo@ankobot.com
 * @LastEditTime: 2022-07-18 18:27:39
 * @FilePath: /SubstrateDevelopment/coredump/core.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int myfunc(int i) {
    int aa = 4;
    *(int*)(NULL) = i; /* line 7 */
    return i - 1;
}


void myfunc1(void) {
    int a = 1;
    float b = 3.2;
}

int main(int argc, char **argv) {
    /* Setup some memory. */
    char data_ptr[] = "string in data segment";
    char *mmap_ptr;
    char *text_ptr = "string in text segment";
    (void)argv;
    mmap_ptr = (char *)malloc(sizeof(data_ptr) + 1);
    strcpy(mmap_ptr, data_ptr);
    mmap_ptr[10] = 'm';
    mmap_ptr[11] = 'm';
    mmap_ptr[12] = 'a';
    mmap_ptr[13] = 'p';
    printf("text addr: %p\n", text_ptr);
    printf("data addr: %p\n", data_ptr);
    printf("mmap addr: %p\n", mmap_ptr);
    myfunc1();
    /* Call a function to prepare a stack trace. */
    return myfunc(argc);
}
