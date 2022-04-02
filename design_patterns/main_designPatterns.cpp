#include <iostream>
#include <stdlib.h>
#include "Singleton.h"

int main(int argc, char const *argv[])
{
    Singleton::getinstance();
    return 0;
}
