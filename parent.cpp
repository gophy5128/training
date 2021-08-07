#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main()
{
    for (int i = 0; i < 3; i++){
        pid_t PID =fork();
        if (PID == 0){
            char* input = new char(100);
            int c;
            scanf("%d", &c);
            sprintf(input, "%d", c);
            execl("./child", "./child", input);
        }
    }
    for (int i = 0; i < 3; i++){
        pid_t PID = wait(nullptr);
    }
    //printf("Both process exe here!?\n");
}
