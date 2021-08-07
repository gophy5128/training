#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
#include<iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // include open() function
#include <sys/types.h> // include mode_t class
#include <sys/stat.h> // flag of open function
#include <string.h>

using namespace std;
int customer(int fdr, int fdw, int customer){
    int k = 0;
    char* re = new char(100);
    //timeval timeout;
    //timeout.tv_sec = 3;
    //timeout.tv_usec = 0;
    while (strcmp(re, "allsoldout") != 0){
        srand(time(NULL) ^ (getpid() << 16+k));
        int buy = (rand() % 3);
        char* text = new char(100);
        sprintf(text, "%d", buy);
        write(fdw, text, sizeof(char));
        //sleep(0.1);
        //select(sizeof(readset), &readset, NULL, NULL, &timeout);
        //if(FD_ISSET(fdr, &readset) != 0){
        while (read(fdr, re, 100) <= 0);
        printf("%s\n", re);
        char* get = new char(100);
        if (strcmp(re, "soldout") == 0){
            if (buy == 0) get = "0 Apple";
            else if (buy == 1) get = "0 Banana";
            else get = "0 Orange";
        }
        else if (strcmp(re, "allsoldout") == 0) return 1;
        else sprintf(get, "%d %s", 1, re);
        printf("Customer %d buys %s.", customer, get);
        k++;
        usleep((rand()%10)*100000);
    }
    return 1;
}

int main(){
    fd_set readset;
    FD_ZERO(&readset);
    int fdr, fdw, ficustomer;
    ficustomer = open("fiplayer", O_RDONLY);
    //printf("%d\n", ficustomer);
    char* t = new char(1);
    int re = read(ficustomer, t, 1);
    char* r = new char(5);
    char* w = new char(6);
    int i = atoi(t);
    sprintf(r, "fifo%c", t[0]);
    sprintf(w, "fifo%cw", t[0]);
    fdw = open(r, O_WRONLY);
    printf("%s\n", r);
    fdr = open(w, O_RDONLY);
    //FD_SET(fdw, &readset);
    int temp = customer(fdr, fdw, i);
}
