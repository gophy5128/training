#include<cstdio>
#include <fcntl.h> // include open() function
#include <sys/types.h> // include mode_t class
#include <sys/stat.h> // flag of open function
#include<unistd.h>
#include<string>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int main(){
    char* a = new char(100);
    char* b = new char(100);
    int fd = open("/home/gophy5128/Desktop/OS/tmp.txt", O_RDWR);
    if (fd!= -1){
        int re = lseek(fd, 0, SEEK_SET);
        int rd = read(fd, a, sizeof(a));
        printf("%d", rd);
        char* c = new char(100);
        int space = 0;
        int space1 = 0;
        for (int i = 0; i < rd; i++){
            if (a[i] == ' ') space++;
            else if (space == 0) {
                b[i] = a[i];
            }
                //space1 = i;
            else if (space == 1 ){
                c[space1] = a[i];
                space1++;
            }
        }
        int a1 = atoi(b);
        int a2 = atoi(c);
        printf("%s %s", b, c);
        int ans = a1 + a2;
        char* ans1 = new char(100);
        sprintf(ans1, "%d", ans);
        re = lseek(fd, 0, SEEK_END);
        re = write(rd, " ", sizeof(char));
        re = write(fd, ans1, sizeof(ans1));
    }
}
