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

using namespace std;
int player(int readpipe, int writepipe, int player){
    int win = 0;
    for (int i = 0; i < 10; i++){
        srand(time(NULL) ^ (getpid() << 16+i));
        int play = (rand() %10);
        //cout<<"player write:"<<play<<endl;
        char* text = new char[100];
        sprintf(text, "%d", play);
        write(writepipe, text, sizeof(char));
        sleep(0.1);
        char* wintemp = new char[2];
        while (read(readpipe, wintemp, 2) <= 0);
        int roundwin = atoi(wintemp);
        if (roundwin == 1){
            printf("Player%d wins round %d\n", player, i+1);
            win++;
        }
    }
    char* text1 = new char(100);
    sprintf(text1, "%d", win);
    write(writepipe, text1, sizeof(char));
    close(readpipe);
    close(writepipe);
    return 0;
}
int host(vector<int> readpipe, vector<int> writepipe){
    vector<int> win (5,0);
    for (int i = 0; i < 10; i++){
        vector<int> round;
        for (int j = 0; j < 5; j++){
            char* temp = new char(100);
            while(read(writepipe[j], temp, sizeof(char))<= 0);
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
            int wr = write(readpipe[j], &ch[0], sizeof(char));
        }
    }
    vector<int> final;
    unordered_map<int, queue<int>> m;
    for (int j = 0; j < 5; j++){
        char* temp = new char(100);
        int re = read(writepipe[j], temp, sizeof(char));
        int temp1 = atoi(temp);
        final.push_back(temp1);
        m[temp1].push(j);
    }
    sort(final.begin(), final.end());
    printf("Result:\n");
    for (int i = 4; i >= 0; i--){
        printf("Player%d, win %d times.\n", m[final[i]].front(), final[i]);
        close(readpipe[i]);
        close(writepipe[i]);
        m[final[i]].pop();
    }
    return 1;
}

int main(){
    vector<int> readp;
    vector<int> writep;
    vector<pid_t> pipeid;
    pid_t parent;
    for (int i = 0; i < 5; i++){
        int read[2];
        int write[2];
        int c = pipe(read);
        int d = pipe(write);
        pid_t pid=fork();
        //cout<<pid<<endl;
        if(c < 0 || d < 0 || pid < 0) printf ("fork error\n");
        else if (pid == 0){
            close(read[1]);
            close(write[0]);
            pipeid.push_back(getpid());
            //cout<<"child: "<<i<<endl;
            int temp = player(read[0], write[1], i);
            //return 0;
            exit(0);
        }
        else{
            readp.push_back(read[1]);
            writep.push_back(write[0]);
            close(write[1]);
            close(read[0]);
            parent = getpid();
        }
    }
    if (getpid()== parent) int s = host(readp, writep);
    exit(0);
}
