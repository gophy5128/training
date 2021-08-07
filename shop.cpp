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
#include<memory.h>
#include<string.h>
#include<string>

using namespace std;
int host(fd_set readset, vector<int> readfd, vector<int> writefd){
    fd_set workset;
    vector<char*> end;
    vector<int> v(3, 5);
    // workset = readset

    char* temp = new char(100);
    while (v[0] + v[1] + v[2] != 0){
        //printf("select\n");
        memcpy(&workset, &readset, sizeof(readset));
        timeval timeout;
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;
        select(10, &workset, NULL, NULL, &timeout);
        if(FD_ISSET(readfd[0], &workset) != 0){
            char* buy = new char(100);
            char* sell = new char(100);
            read(readfd[0], buy, sizeof(char));
            printf("%s\n", buy);
            int buyfd = atoi(buy);
            if (buyfd == 0){
                if (v[buyfd] > 0) {
                    sell = "Apple";
                    v[buyfd]--;
                }
                else sell = "soldout";
            }
            else if (buyfd == 1){
                if (v[buyfd] > 0) {
                    sell = "Banana";
                    v[buyfd]--;
                }
                else sell = "soldout";
            }
            else if (buyfd == 2){
                if (v[buyfd] > 0) {
                    sell = "Orange";
                    v[buyfd]--;
                }
                else sell = "soldout";
            }
            write(writefd[0], sell, strlen(sell));
            if (strcmp(sell, "soldout") != 0) {
                char* result = new char(100);
                sprintf(result, "Sell %s to cusomer 0", sell);
                end.push_back(result);
            }
        }
        else if(FD_ISSET(readfd[1], &workset) != 0){
            char* buy = new char(100);
            char* sell = new char(100);
            read(readfd[1], buy, sizeof(char));
            int buyfd = atoi(buy);
            if (buyfd == 0){
                if (v[buyfd] > 0) {
                    sell = "Apple";
                    v[buyfd]--;
                }
                else sell = "soldout";
            }
            else if (buyfd == 1){
                if (v[buyfd] > 0) {
                    sell = "Banana";
                    v[buyfd]--;
                }
                else sell = "soldout";
            }
            else if (buyfd == 2){
                if (v[buyfd] > 0) {
                    sell = "Orange";
                    v[buyfd]--;
                }
                else sell = "soldout";
            }
            write(writefd[1], sell, strlen(sell));
            if (strcmp(sell, "soldout") != 0) {
                char* result = new char(100);
                sprintf(result, "Sell %s to cusomer 1", sell);
                end.push_back(result);
            }
        }
        else if(FD_ISSET(readfd[2], &workset) != 0){
            char* buy = new char(100);
            char* sell = new char(100);
            read(readfd[2], buy, sizeof(char));
            int buyfd = atoi(buy);
            if (buyfd == 0){
                if (v[buyfd] > 0) {
                    sell = "Apple";
                    v[buyfd]--;
                }
                else sell = "soldout";
            }
            else if (buyfd == 1){
                if (v[buyfd] > 0) {
                    sell = "Banana";
                    v[buyfd]--;
                }
                else sell = "soldout";
            }
            else if (buyfd == 2){
                if (v[buyfd] > 0) {
                    sell = "Orange";
                    v[buyfd]--;
                }
                else sell = "soldout";
            }
            write(writefd[2], sell, strlen(sell));
            if (strcmp(sell, "soldout") != 0) {
                char* result = new char(100);
                sprintf(result, "Sell %s to cusomer 2", sell);
                end.push_back(result);
            }
        }
    }
    for (int i = 0; i < 3; i++) write(writefd[i], "allsoldout", 10);
    for (int i = 0; i < end.size(); i++){
        printf("%s\n", end[i]);
    }
    return 1;
}
int main(){
    vector<int> readfd, writefd;
    fd_set readset;
    FD_ZERO(&readset);
    int a, fdr, fdw;
    a = open("fiplayer", O_WRONLY);
    //printf("%d\n", a);

    for (int i = 0; i < 3; i++){
        char* t = new char(1);
        sprintf(t, "%d", i);
        write(a, t, 1);
        char* r = new char(5);
        sprintf(r, "fifo%d", i);
        int fdr = open(r, O_RDONLY);
        FD_SET(fdr, &readset);
        char* w = new char(6);
        sprintf(w, "fifo%dw", i);
        int fdw = open(w, O_WRONLY);
        readfd.push_back(fdr);
        writefd.push_back(fdw);
    }
    int temp = host(readset, readfd, writefd);
}
