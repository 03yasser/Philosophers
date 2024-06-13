# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
//milisec : 1702944000000
//          4294967295
//          18446744073709551615
//      2147483647
int main()
{
    struct timeval tm;
    size_t       time;
    while (1)
    {
        gettimeofday(&tm, NULL);
        time = tm.tv_sec * 1000;
        printf("%zu\n", time);
    }
}