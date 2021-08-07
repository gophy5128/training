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
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;
int main(){
    vector<char*> end;
    vector<int> v(3, 5);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0) printf("Socket Create Error\n");
    struct sockaddr_in info;
    struct sockaddr_in client_info;
    socklen_t client_addr_len;
    info.sin_family = AF_INET;
    info.sin_addr.s_addr = INADDR_ANY; // Local IP Address
    info.sin_port = htons(8000); // Port 8080

    int bind_result = bind(sockfd, (struct sockaddr*)&info, sizeof(info));
    if(bind_result < 0) printf("Bind Error\n");

    listen(sockfd,3); // block until listen a client
    fd_set allset;
    FD_ZERO(&allset);
    FD_SET(sockfd, &allset);
    int client_fd;
    vector<int> clientset;
    int id=0;
    //int re = 55;
    while(v[0] + v[1] + v[2] != 0)
    {
        fd_set workset;
        memcpy(&workset, &allset, sizeof(allset));
        timeval timeout;
        timeout.tv_sec = 3;
        timeout.tv_usec = 0;
        select(10, &workset, NULL, NULL, &timeout);
        if(FD_ISSET(sockfd, &workset) == 0){
            client_fd = accept(sockfd, (struct sockaddr*)&client_info, &client_addr_len);
            printf("Accept client, client port: %d\n", client_info.sin_port);
            FD_SET(client_fd, &allset);
            clientset.push_back(client_fd);
            char* clientno = new char(100);
            sprintf(clientno, "%d", id);
            send(client_fd, clientno, strlen(clientno), 0);
            id++;
            //printf("%d\n", se);
        }
        for (int i = 0; i < clientset.size(); i++){
            if(FD_ISSET(clientset[i], &workset) != 0){
                char* buy = new char(100);
                char* sell = new char(100);
                recv(clientset[i], buy, sizeof(char), 0);
                //printf("%s\n", buy);
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
                send(clientset[i], sell, strlen(sell), 0);
                if (strcmp(sell, "soldout") != 0) {
                    char* result = new char(100);
                    sprintf(result, "Sell %s to cusomer %d", sell, i);
                    end.push_back(result);
                }
            }
        }
    }
    for (int i = 0; i < 3; i++) send(clientset[i], "allsoldout", 10, 0);
    for (int i = 0; i < end.size(); i++){
        printf("%s\n", end[i]);
    }
}
