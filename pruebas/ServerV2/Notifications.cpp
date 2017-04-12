#include "Notifications.hpp"
#include <stdio.h>
#include <stdlib.h>

void error(const char* msg){
    printf("\033[1;31m ERROR: %s\033[0m\n", msg);
    exit(1);
}

void warning(const char* msg){
    printf("\033[1,31m WARNING: %s\033[0m\n", msg);
}

void notify(const char* msg){
    printf("\033[1,36m %s\033[0m\n", msg);
}
