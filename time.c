#include <sys/syscall.h>
#include <stdio.h>
#include <time.h> // JUST FOR EPOCH TO DATE CONVERSION

int main()
{
    long time;
    time = syscall(201);
    
    printf("%s", ctime(&time));
    
    return 0;
}

