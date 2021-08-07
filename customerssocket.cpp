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
# include <arpa/inet.h>
# include <netinet/in.h>

using namespace std;
int customer(int socketfd, int clientno){
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
        send(socketfd, text, sizeof(char), 0);
        //sleep(0.1);
        //select(sizeof(readset), &readset, NULL, NULL, &timeout);
        //if(FD_ISSET(fdr, &readset) != 0){
        while (recv(socketfd, re, 100, 0) <= 0);
        //printf("%s\n", re);
        char* get = new char(100);
        if (strcmp(re, "soldout") == 0){
            if (buy == 0) get = "0 Apple";
            else if (buy == 1) get = "0 Banana";
            else get = "0 Orange";
        }
        else if (strcmp(re, "allsoldout") == 0) return 1;
        else sprintf(get, "%d %s", 1, re);
        printf("Customer %d buys %s.", clientno, get);
        k++;
        usleep((rand()%10+1)*100000);
    }
    return 1;
}

int main(){
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd < 0) printf("Socket Create Error\n");
    struct sockaddr_in info;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = inet_addr("127.0.0.1"); // Local IP Address
    info.sin_port = htons(8000); // Port 8080
    int connect_result = connect(socketfd, (struct sockaddr*)&info, sizeof(info));
    if(connect_result) printf("Connect Error\n");
    char* no = new char(100);
    recv(socketfd, no, 100, 0);
    //printf("%d\n", re);
    int clientno = no[0] - '0';
    //printf("%d\n", clientno);
    int temp = customer(socketfd, clientno);
}
