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
int player(int fdr, int fdw, int player){
    int win = 0;
    for (int i = 0; i < 10; i++){
        srand(time(NULL) ^ (getpid() << 16+i));
        int play = (rand() %10);
        //cout<<"player write:"<<play<<endl;
        char* text = new char(100);
        sprintf(text, "%d", play);
        write(fdw, text, sizeof(char));
        sleep(0.1);
        char* wintemp = new char(2);
        while (read(fdr, wintemp, 2) <= 0);
        int roundwin = atoi(wintemp);
        if (roundwin == 1){
            printf("Player%d wins round %d\n", player, i+1);
            win++;
        }
    }
    char* text1 = new char(100);
    sprintf(text1, "%d", win);
    write(fdw, text1, sizeof(char));
    return 0;
}

int main(){
    //int a, b, c, d, e;
    //a = mkfifo("fifo0", 0777);
    //b = mkfifo("fifo1", 0777);
    //c = mkfifo("fifo2", 0777);
    //d = mkfifo("fifo3", 0777);
    //e = mkfifo("fifo4", 0777);
    //cout<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<e<<endl;
    //if (a < 0 || b < 0 || c < 0 || d < 0 ||e < 0) printf("fifo error\n");
    //else{
    int fdr, fdw, fiplayer;
    fiplayer = open("fiplayer", O_RDONLY);
    char* t = new char(1);
    int re = read(fiplayer, t, 1);
    char* r = new char(5);
    char* w = new char(6);
    int i = atoi(t);
    sprintf(r, "fifo%c", t[0]);
    sprintf(w, "fifo%cw", t[0]);
    fdr = open(r, O_RDONLY);
    fdw = open(w, O_WRONLY);
    int temp = player(fdr, fdw, i);
}
