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
int player(int readfd, int writefd, int player){
    int win = 0;
    for (int i = 0; i < 10; i++){
        //srand(time(NULL) ^ (getpid() << 16+i));
        int play = (rand() %10);
        //cout<<"player write:"<<play<<endl;
        char* text = new char[100];
        sprintf(text, "%d", play);
        write(writefd, text, sizeof(char));
        sleep(0.1);
        char* wintemp = new char[2];
        while (read(readfd, wintemp, 2) <= 0);
        int roundwin = atoi(wintemp);
        if (roundwin == 1){
            printf("Player%d wins round %d\n", player, i+1);
            win++;
        }
    }
    char* text1 = new char(100);
    sprintf(text1, "%d", win);
    write(writefd, text1, sizeof(char));
    return 0;
}
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
    int a, b, c, d, e;
    //a = mkfifo("fifo0", 0777);
    //b = mkfifo("fifo1", 0777);
    //c = mkfifo("fifo2", 0777);
    //d = mkfifo("fifo3", 0777);
    //e = mkfifo("fifo4", 0777);
    //cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
    //if (a < 0 || b < 0 || c < 0 || d < 0 ||e < 0) printf("fifo error\n");
    //else{
        int fdr0, fdr1, fdr2, fdr3, fdr4, fdw0, fdw1, fdw2, fdw3, fdw4;
        vector<int> vr, vw;
        fdr0 = open("fifo0", O_RDONLY);
        vr.push_back(fdr0);
        fdr1 = open("fifo1", O_RDONLY);
        vr.push_back(fdr1);
        fdr2 = open("fifo2", O_RDONLY);
        vr.push_back(fdr2);
        fdr3 = open("fifo3", O_RDONLY);
        vr.push_back(fdr3);
        fdr4 = open("fifo4", O_RDONLY);
        vr.push_back(fdr4);
        fdw0 = open("fifo0", O_WRONLY);
        vw.push_back(fdw0);
        fdw1 = open("fifo1", O_WRONLY);
        vw.push_back(fdw1);
        fdw2 = open("fifo2", O_WRONLY);
        vw.push_back(fdw2);
        fdw3 = open("fifo3", O_WRONLY);
        vw.push_back(fdw3);
        fdw4 = open("fifo4", O_WRONLY);
        vw.push_back(fdw4);
        for (int i = 0; i < 5; i++){
            //cout<<"child: "<<i<<endl;
            int temp = player(vr[i], vw[i], i);

            //return 0;
            exit(0);
        }
        int s = host(vr, vw);
        exit(0);
    //}

}
