#include<unistd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <vector>
#include <unordered_map>
#include <queue>
#include <algorithm>
using namespace std;
int main (){
    vector<int> round(5, 0);
    for (int i = 0; i < 10; i++){
        int win = 0;
        int winner = 0;
        for (int j = 0; j < 5; j++){
            int fd[2];
            char line[100];
            int c = pipe(fd);
            pid_t pid=fork();
            if (pid < 0) printf("%s", "fork error");
            else if (pid == 0){
                close(fd[0]);
                int player = (rand() %10);
                char* text = new char[100];
                sprintf(text, "%d", player);
                write(fd[1], text, sizeof(text));
                printf("Player%d : %d\n", j, player);
            }
            else{
                pid_t pid1 = waitpid(pid, NULL, NULL);
                //sleep(1);
                close(fd[1]);
                char* b = new char[100];
                int re = read(fd[0], b, sizeof(b));
                int p = atoi(b);
                if (p > win) {
                    //printf("old winner: %d\n", winner);
                    //printf("p: %d\n", p);
                    winner = j;
                    win = p;
                    if (j == 4){
                        printf("Player%d wins round %d\n", winner, i+1);
                        round[winner]++;
                    }
                    if (i == 9){
                        unordered_map<int, queue<int>> map;
                        for (int k = 0; k < 5; k++){
                            map[round[k]].push(k);
                        }
                        sort(round.begin(), round.end());
                        printf("Result:\n");
                        for (int k = 4; k >= 0; k--){
                            //printf("%d/n", i);
                            printf("Player%d, win %d times.\n", map[round[k]].front(), round[k]);
                            map[round[k]].pop();
                        }
                        printf("Gameover\n");
                }
                    //printf("new winner: %d %d\n", j, winner);
                }
                //exit(0);
            }
        }
    }

}

