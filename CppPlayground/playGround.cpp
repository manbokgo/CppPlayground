#include <cstdio>
int main() {
    const int N=100000, M=15000;
    printf("%d\n", N);
    for(int i=1; i<=N; i++) printf("%d%c", M, " \n"[i==N]);
}
