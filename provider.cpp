#include<cstdio>
#include<iostream>
#include <fcntl.h> // include open() function
#include <sys/types.h> // include mode_t class
#include <sys/stat.h> // flag of open function
#include<unistd.h>
#include<string.h>
using namespace std;

int main(){
    char* x = new char(100);
    scanf("%s", x);
    if (strcmp(x, "writeNum") == 0){
        //printf("x: %s\n", x);
        char* a = new char(100);
        char* b = new char(100);
        scanf("%s %s", a, b);
        int fd = open("/home/gophy5128/Desktop/OS/tmp.txt", O_CREAT|O_RDWR, 0770);
        if (fd != -1) {
            int re = write(fd, a, sizeof(a));
            printf("a: %s\n", a);
            if (re != -1){
                char blank = ' ';
                re = write(fd, " ", sizeof(char));
                if (re != -1){
                    //re = write(fd, " ", sizeof(char));
                    re = write(fd, b, sizeof(b));
                    re = write(fd, " ", sizeof(char));
                    printf("b: %s\n", b);
                }
                else printf("b error\n");
            }
            else printf("blank error\n");
        }
        else printf("a error\n");
        //close(fd);
        //fd = open("/home/gophy5128/Desktop/OS/tmp.txt", O_CREAT|O_RDWR, 770);
        //char* reada= new char(100);
        //int re = read(fd, reada, sizeof(a));
        //cout<<reada<<endl;

        //cout << "success"<<endl;
    }
    else if (strcmp(x, "readAns") == 0){
        //cout<<"readAns"<<endl;
        int fd = open("/home/gophy5128/Desktop/OS/tmp.txt", O_RDWR);
        int re = lseek(fd, 0, SEEK_SET);
        char* ans = new char(100);
        re = read(fd, ans, sizeof(ans));
        int space = 0;
        for (int i = 0; i < re; i++){
            if (ans[i] == ' ') space++;
            else if (space == 2){
                printf("%c", ans[i]);
            }
        }
    }
}
