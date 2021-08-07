#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
    int ans = 0;
    int c = atoi(argv[1]);
    for (int i = 1; i <= c; i++) ans+=i;
    printf("%d\n", ans);
}
