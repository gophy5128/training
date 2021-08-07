#include<unistd.h>
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

using namespace std;
int host(vector<int> readfd, vector<int> writefd){
    vector<int> win (5,0);
    for (int i = 0; i < 10; i++){
        vector<int> round;
        for (int j = 0; j < 5; j++){
            char* temp = new char(100);
            while(read(writefd[j], temp, sizeof(char))<= 0);
            //cout<<"parent read: "<<temp<<endl;
            //int re = read(writepipe[j], temp, sizeof(char));
            int temp1 = atoi(temp);
            round.push_back(temp1);
            printf("Player%d : %d\n", j, temp1);
        }
        int win = round[0];
        unordered_map<int, vector<int>> map;
        for (int j = 0; j < 5; j++){
            map[round[j]].push_back(j);
            win = max(win, round[j]);
        }
        vector<int> v = map[win];
        char c[5] = {'0', '0', '0', '0', '0'};
        for (int j = 0; j < 5; j++){
            for (int k = 0; k < v.size(); k++){
                c[v[k]] = '1';
            }
        }
        for (int j = 0; j < 5; j++){
            char* ch = new char(2);
            ch[0] = c[j];
            int wr = write(readfd[j], &ch[0], sizeof(char));
        }
    }
    vector<int> final;
    unordered_map<int, queue<int>> m;
    for (int j = 0; j < 5; j++){
        char* temp = new char(100);
        int re = read(writefd[j], temp, sizeof(char));
        int temp1 = atoi(temp);
        final.push_back(temp1);
        m[temp1].push(j);
    }
    sort(final.begin(), final.end());
    printf("Result:\n");
    for (int i = 4; i >= 0; i--){
        printf("Player%d, win %d times.\n", m[final[i]].front(), final[i]);
        m[final[i]].pop();
    }
    return 1;
}

int main(){
    int a;
    vector<int> vr, vw;
    a = open("fiplayer", O_WRONLY);
    for (int i = 0; i < 5; i++){
        char* t = new char(1);
        sprintf(t, "%d", i);
        write(a, t, 1);
        char* r = new char(5);
        sprintf(r, "fifo%d", i);
        int fdr = open(r, O_WRONLY);
        char* w = new char(6);
        sprintf(w, "fifo%dw", i);
        int fdw = open(w, O_RDONLY);
        vr.push_back(fdr);
        vw.push_back(fdw);
    }
    int s = host(vr, vw);
}
