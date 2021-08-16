#include <stdio.h>
#include <cstdio>
#include <pthread.h>
#include <unistd.h>
#include <vector>

using namespace std;
typedef struct inputdata
{
    int a;
    int b;
    long long res;
}inputdata;

void *func(void*arg){
    inputdata* input = (inputdata*) arg;
    input->res = ((input->b + input->a) * (input->b - input->a + 1)) /2;
}
int main(){
    int k;
    scanf("%d", &k);
    int p = 10000000/k;
    vector<pthread_t> v;
    vector<inputdata> vinput;
    long long answer = 0;
    for (int i = 0; i < k; i++){
        inputdata input;
        input.a = i*p;
        if (i == k-1) input.b = 10000000;
        else input.b = (i+1) * p - 1;
        pthread_t t;
        pthread_create(&t, NULL, func, (void*) &input);
        //v.push_back(t);
        //vinput.push_back(input);
        pthread_join(t, NULL);
        answer += input.res;
    }
    //for (int i = 0; i < k; i++){
        //pthread_join(v[i], NULL);
    //}
    //for (int i = 0; i < k; i++){
        //answer += vinput[i].res;
    //}
    printf("%lld\n", answer);

}
